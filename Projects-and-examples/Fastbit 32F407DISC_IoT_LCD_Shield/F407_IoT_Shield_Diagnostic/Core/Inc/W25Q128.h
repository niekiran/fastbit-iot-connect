/*
 * W25Q128.h
 *
 *  Created on: Jun 29, 2025
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_W25Q128_H_
#define INC_W25Q128_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>

// Pin definitions from user
#define W25QXX_CS_PORT      GPIOB
#define W25QXX_CS_PIN       GPIO_PIN_1

#define W25QXX_SCK_PORT     GPIOA
#define W25QXX_SCK_PIN      GPIO_PIN_5

#define W25QXX_MISO_PORT    GPIOA
#define W25QXX_MISO_PIN     GPIO_PIN_6

#define W25QXX_MOSI_PORT    GPIOA
#define W25QXX_MOSI_PIN     GPIO_PIN_7

#define FLASH_SELECT        HAL_GPIO_WritePin(W25QXX_CS_PORT, W25QXX_CS_PIN, GPIO_PIN_SET)
#define FLASH_DESELECT      HAL_GPIO_WritePin(W25QXX_CS_PORT, W25QXX_CS_PIN, GPIO_PIN_RESET)

#define W25QXX_PAGE_SIZE          256   // Page size in bytes
#define W25QXX_SECTOR_SIZE        4096  // Sector size in bytes
#define W25QXX_BLOCK_SIZE         65536 // Block size in bytes
#define W25QXX_TIMEOUT_MS         1000  // Timeout for operations
#define W25QXX_DMA_BUFFER_SIZE    256   // DMA buffer size (matches page size)

// W25QXX configuration structure
typedef struct {
    SPI_HandleTypeDef *hspi;    // SPI handle
    uint32_t flash_size;        // Flash size in bytes (e.g., 4MB for W25Q32)
} w25qxx_config_t;

// W25QXX status
typedef enum {
    W25QXX_OK = 0,
    W25QXX_ERROR,
    W25QXX_TIMEOUT,
    W25QXX_NOT_READY,
    W25QXX_INVALID_PARAM
} w25qxx_status_t;

// Function prototypes
w25qxx_status_t w25qxx_init(w25qxx_config_t *config);
w25qxx_status_t w25qxx_read_id(uint8_t *manufacturer_id, uint16_t *device_id);
w25qxx_status_t w25qxx_read_data(uint32_t address, uint8_t *buffer, uint32_t length);
w25qxx_status_t w25qxx_write_page(uint32_t address, const uint8_t *buffer, uint32_t length);
w25qxx_status_t w25qxx_erase_sector(uint32_t sector_addr);
w25qxx_status_t w25qxx_erase_chip(void);
w25qxx_status_t w25qxx_get_status(void);
void w25qxx_deinit(void);


#endif /* INC_W25Q128_H_ */
