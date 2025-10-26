# STM32F407 IoT Shield Test Application

### Overview
This firmware is designed to **validate and test all onboard peripherals** of the `32F407DIS_IoT_LCD_SHIELD` — a daughterboard for the **STM32F407VG Discovery Board**.  
It performs hardware-level diagnostics for communication, storage, and sensor modules integrated into the shield.

---

### Features Tested

| Module | Interface | Description |
|---------|------------|-------------|
| **ESP32-C6** | UART3 | Wi-Fi module tested via AT commands |
| **HDC1080** | I2C1 | Temperature and Humidity sensor |
| **W25Q128** | SPI1 | External NOR Flash memory test |
| **MicroSD Card** | SPI1 + FatFs | File system mount and read/write test |
| **CAN Module** | CAN1 | CAN communication loopback test |
| *(Optional)* **LCD Display** | SPI | Future integration |
| *(Optional)* **Touch Panel** | I2C | Future integration |

---

### Configuration

You can enable or disable specific tests using macros defined at the top of `main.c`:

```c
/* === Select which modules to test === */
#define TEST_ESP32_C6     // WiFi via AT commands
#define TEST_HDC1080      // Humidity & temperature sensor
#define TEST_NOR_FLASH    // External SPI Flash (W25Q128)
#define TEST_SDCARD       // MicroSD via SPI
#define TEST_CAN_MOD      // CAN transceiver loopback
//#define TEST_LCD_DISPLAY // Future use
//#define TEST_TOUCH       // Future use

``` 
---

### Viewing Output

The **32F407DISC_IoT_LCD_SHIELD** includes an onboard **USB-to-UART converter**  
You can view all diagnostic log messages **directly** by connecting the shield’s **USB port** to your computer — no extra hardware required.

**Steps:**

1. Connect the **IoT Shield’s USB port** to your PC.  
2. Open a serial terminal such as **Tera Term**, **PuTTY**, or **RealTerm**.  
3. In *Device Manager*, note the **COM port** assigned to the shield (e.g., `COM6`).  
4. Configure the terminal settings:  
   - **Baud Rate:** 115200  
   - **Data Bits:** 8  
   - **Parity:** None  
   - **Stop Bits:** 1  
   - **Flow Control:** None  
5. Click **Connect** — real-time diagnostic logs from the STM32 will appear immediately.

### Modules & Drivers Included

This project includes all necessary drivers to use the modules present on the **32F407DIS_IoT_LCD_SHIELD**:

- **ESP32-C6 Wi-Fi module** – connect and communicate via AT commands  
- **HDC1080 Temperature & Humidity sensor**  
- **W25Q128 NOR Flash**  
- **SD Card interface** – FATFS support  
- **CAN module** – CAN bus communication  

> 📘 For detailed hardware connections, pinout, and module info, refer to the  
> [Fastbit 32F407DISC IoT LCD Shield User Manual (PDF)](https://github.com/niekiran/fastbit-iot-connect/blob/main/Documents/UserManual/Fastbit%2032F407DISC_IoT_LCD_Shield_UserManual.pdf)


