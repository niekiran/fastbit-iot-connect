/*
 * W25Q128.c
 *
 *  Created on: Jun 29, 2025
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#include "W25Q128.h"
#include <string.h>

// W25QXX commands
#define CMD_WRITE_ENABLE        0x06
#define CMD_WRITE_DISABLE       0x04
#define CMD_READ_STATUS_REG1    0x05
#define CMD_READ_DATA           0x03
#define CMD_PAGE_PROGRAM        0x02
#define CMD_SECTOR_ERASE        0x20
#define CMD_CHIP_ERASE          0xC7
#define CMD_JEDEC_ID            0x9F
#define DUMMY_BYTE              0xFF

// W25QXX configuration
static w25qxx_config_t *w25qxx_config = NULL;
static volatile bool w25qxx_initialized = false;

// Private function prototypes
static w25qxx_status_t w25qxx_wait_busy(void);
static void w25qxx_select(void);
static void w25qxx_deselect(void);
static w25qxx_status_t w25qxx_send_command(uint8_t cmd, uint32_t address, uint8_t *data, uint32_t length, bool is_write);

// Initialize W25QXX flash
w25qxx_status_t w25qxx_init(w25qxx_config_t *config) {
    if (!config || !config->hspi || config->flash_size == 0) {
        return W25QXX_INVALID_PARAM;
    }

    w25qxx_config = config;
    w25qxx_initialized = false;

    // Initialize chip select pin
    FLASH_SELECT;

    // Send dummy clocks to stabilize SPI
    uint8_t dummy = DUMMY_BYTE;
    w25qxx_deselect();
    for (uint8_t i = 0; i < 10; i++) {
        if (HAL_SPI_Transmit(w25qxx_config->hspi, &dummy, 1, W25QXX_TIMEOUT_MS) != HAL_OK) {
            return W25QXX_ERROR;
        }
    }

    // Read JEDEC ID to verify communication
    uint8_t manufacturer_id;
    uint16_t device_id;
    if (w25qxx_read_id(&manufacturer_id, &device_id) != W25QXX_OK) {
        return W25QXX_ERROR;
    }

    // Verify manufacturer (Winbond = 0xEF)
    if (manufacturer_id != 0xEF) {
        return W25QXX_ERROR;
    }

    w25qxx_initialized = true;
    return W25QXX_OK;
}

// Read JEDEC ID
w25qxx_status_t w25qxx_read_id(uint8_t *manufacturer_id, uint16_t *device_id) {
    if (!manufacturer_id || !device_id) {
        return W25QXX_INVALID_PARAM;
    }

    uint8_t cmd = CMD_JEDEC_ID;
    uint8_t response[3];
    w25qxx_select();
    if (HAL_SPI_Transmit(w25qxx_config->hspi, &cmd, 1, W25QXX_TIMEOUT_MS) != HAL_OK ||
        HAL_SPI_Receive(w25qxx_config->hspi, response, 3, W25QXX_TIMEOUT_MS) != HAL_OK) {
        w25qxx_deselect();
        return W25QXX_ERROR;
    }
    w25qxx_deselect();

    *manufacturer_id = response[0];
    *device_id = (response[1] << 8) | response[2];
    return W25QXX_OK;
}

// Read data from specified address
w25qxx_status_t w25qxx_read_data(uint32_t address, uint8_t *buffer, uint32_t length) {
    if (!w25qxx_initialized || !buffer || address >= w25qxx_config->flash_size) {
        return W25QXX_INVALID_PARAM;
    }

    return w25qxx_send_command(CMD_READ_DATA, address, buffer, length, false);
}

// Write data to a page
w25qxx_status_t w25qxx_write_page(uint32_t address, const uint8_t *buffer, uint32_t length) {
    if (!w25qxx_initialized || !buffer || address >= w25qxx_config->flash_size) {
        return W25QXX_INVALID_PARAM;
    }

    if (length > W25QXX_PAGE_SIZE || (address % W25QXX_PAGE_SIZE) + length > W25QXX_PAGE_SIZE) {
        return W25QXX_INVALID_PARAM; // Must not cross page boundary
    }

    // Enable write
    uint8_t cmd = CMD_WRITE_ENABLE;
    w25qxx_select();
    if (HAL_SPI_Transmit(w25qxx_config->hspi, &cmd, 1, W25QXX_TIMEOUT_MS) != HAL_OK) {
        w25qxx_deselect();
        return W25QXX_ERROR;
    }
    w25qxx_deselect();

    // Write page
    w25qxx_status_t status = w25qxx_send_command(CMD_PAGE_PROGRAM, address, (uint8_t *)buffer, length, true);
    if (status != W25QXX_OK) {
        return status;
    }

    // Wait for write to complete
    if (w25qxx_wait_busy() != W25QXX_OK) {
        return W25QXX_TIMEOUT;
    }

    // Disable write
    cmd = CMD_WRITE_DISABLE;
    w25qxx_select();
    if (HAL_SPI_Transmit(w25qxx_config->hspi, &cmd, 1, W25QXX_TIMEOUT_MS) != HAL_OK) {
        w25qxx_deselect();
        return W25QXX_ERROR;
    }
    w25qxx_deselect();

    return W25QXX_OK;
}

// Erase a sector
w25qxx_status_t w25qxx_erase_sector(uint32_t sector_addr) {
    if (!w25qxx_initialized || sector_addr >= w25qxx_config->flash_size) {
        return W25QXX_INVALID_PARAM;
    }

    // Enable write
    uint8_t cmd = CMD_WRITE_ENABLE;
    w25qxx_select();
    if (HAL_SPI_Transmit(w25qxx_config->hspi, &cmd, 1, W25QXX_TIMEOUT_MS) != HAL_OK) {
        w25qxx_deselect();
        return W25QXX_ERROR;
    }
    w25qxx_deselect();

    // Send sector erase command
    uint8_t command[4] = {CMD_SECTOR_ERASE, (uint8_t)(sector_addr >> 16), (uint8_t)(sector_addr >> 8), (uint8_t)sector_addr};
    w25qxx_select();
    if (HAL_SPI_Transmit(w25qxx_config->hspi, command, 4, W25QXX_TIMEOUT_MS) != HAL_OK) {
        w25qxx_deselect();
        return W25QXX_ERROR;
    }
    w25qxx_deselect();

    // Wait for erase to complete
    if (w25qxx_wait_busy() != W25QXX_OK) {
        return W25QXX_TIMEOUT;
    }

    return W25QXX_OK;
}

// Erase entire chip
w25qxx_status_t w25qxx_erase_chip(void) {
    if (!w25qxx_initialized) {
        return W25QXX_NOT_READY;
    }

    // Enable write
    uint8_t cmd = CMD_WRITE_ENABLE;
    w25qxx_select();
    if (HAL_SPI_Transmit(w25qxx_config->hspi, &cmd, 1, W25QXX_TIMEOUT_MS) != HAL_OK) {
        w25qxx_deselect();
        return W25QXX_ERROR;
    }
    w25qxx_deselect();

    // Send chip erase command
    cmd = CMD_CHIP_ERASE;
    w25qxx_select();
    if (HAL_SPI_Transmit(w25qxx_config->hspi, &cmd, 1, W25QXX_TIMEOUT_MS) != HAL_OK) {
        w25qxx_deselect();
        return W25QXX_ERROR;
    }
    w25qxx_deselect();

    // Wait for erase to complete
    if (w25qxx_wait_busy() != W25QXX_OK) {
        return W25QXX_TIMEOUT;
    }

    return W25QXX_OK;
}

// Get flash status
w25qxx_status_t w25qxx_get_status(void) {
    return w25qxx_initialized ? W25QXX_OK : W25QXX_NOT_READY;
}

// Deinitialize flash
void w25qxx_deinit(void) {
    w25qxx_initialized = false;
    w25qxx_config = NULL;
}

// Wait for flash to be ready
static w25qxx_status_t w25qxx_wait_busy(void) {
    uint8_t cmd = CMD_READ_STATUS_REG1;
    uint8_t status;
    uint32_t start_time = HAL_GetTick();

    do {
        w25qxx_select();
        if (HAL_SPI_Transmit(w25qxx_config->hspi, &cmd, 1, W25QXX_TIMEOUT_MS) != HAL_OK ||
            HAL_SPI_Receive(w25qxx_config->hspi, &status, 1, W25QXX_TIMEOUT_MS) != HAL_OK) {
            w25qxx_deselect();
            return W25QXX_ERROR;
        }
        w25qxx_deselect();
        if (HAL_GetTick() - start_time > W25QXX_TIMEOUT_MS) {
            return W25QXX_TIMEOUT;
        }
    } while (status & 0x01); // Busy bit

    return W25QXX_OK;
}

// Select flash chip
static void w25qxx_select(void) {
    FLASH_DESELECT; // Active-low CS
    HAL_Delay(1); // Small delay for stability
}

// Deselect flash chip
static void w25qxx_deselect(void) {
    FLASH_SELECT; // Set CS high
    uint8_t dummy = DUMMY_BYTE;
    if (HAL_SPI_Transmit(w25qxx_config->hspi, &dummy, 1, W25QXX_TIMEOUT_MS) != HAL_OK) {
        // Ignore error for dummy byte
    }
}

// Send command with address and data (polling-based)
static w25qxx_status_t w25qxx_send_command(uint8_t cmd, uint32_t address, uint8_t *data, uint32_t length, bool is_write) {
    uint8_t command[4] = {cmd, (uint8_t)(address >> 16), (uint8_t)(address >> 8), (uint8_t)address};
    w25qxx_select();

    // Send command and address
    if (HAL_SPI_Transmit(w25qxx_config->hspi, command, 4, W25QXX_TIMEOUT_MS) != HAL_OK) {
        w25qxx_deselect();
        return W25QXX_ERROR;
    }

    // Perform data transfer
    if (is_write) {
        if (HAL_SPI_Transmit(w25qxx_config->hspi, data, length, W25QXX_TIMEOUT_MS) != HAL_OK) {
            w25qxx_deselect();
            return W25QXX_ERROR;
        }
    } else {
        if (HAL_SPI_Receive(w25qxx_config->hspi, data, length, W25QXX_TIMEOUT_MS) != HAL_OK) {
            w25qxx_deselect();
            return W25QXX_ERROR;
        }
    }

    w25qxx_deselect();
    return W25QXX_OK;
}
