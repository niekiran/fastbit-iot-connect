/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "esp32_at.h"
#include "application_config.h"
#include "sensor_util.h"
#include "W25Q128.h"
#include "sd_card.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define TEST_ESP32_C6
#define TEST_HDC1080
#define TEST_NOR_FLASH
#define TEST_SDCARD
//#define TEST_LCD_DISPLAY
//#define TEST_TOUCH
#define TEST_CAN_MOD
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RED_TXT(msg)    "\033[1;31m" msg "\033[0m"
#define GREEN_TXT(msg)  "\033[1;32m" msg "\033[0m"
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;

I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim7;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart3_rx;

/* USER CODE BEGIN PV */
static bool esp32_test_passed = false;
static bool hdc1080_test_passed = false;
static bool nor_flash_test_passed = false;
static bool sdcard_test_passed = false;
static bool lcd_display_test_passed = false;
static bool touch_test_passed = false;
static bool can_mod_test_passed = false;

uint8_t req_counter = 0;
uint8_t led_no = 0;
CAN_RxHeaderTypeDef RxHeader;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_SPI1_Init(void);
static void MX_CAN1_Init(void);
static void MX_TIM7_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void CAN_filter_config(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len) {
  HAL_UART_Transmit(&huart2, (uint8_t *)ptr, len, HAL_MAX_DELAY);
  return len;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_SPI1_Init();
  MX_FATFS_Init();
  MX_CAN1_Init();
  MX_TIM7_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

#ifdef TEST_ESP32_C6
  /* Step 1: Initialize the ESP32 Wi-Fi module */
  LogInfo(("Initializing Wi-Fi module..."));
  if (esp32_init() != ESP32_OK) {
    LogError(("Failed to initialize Wi-Fi module."));
    esp32_test_passed = false;
  } else {
    LogInfo(("Wi-Fi module initialized successfully.\n"));

    /* Step 2: Connect to Wi-Fi network */
    LogInfo(("Joining Access Point: '%s' ...", WIFI_SSID));
    while (esp32_join_ap((uint8_t *)WIFI_SSID, (uint8_t *)WIFI_PASSWORD) != ESP32_OK) {
      LogInfo(("Retrying to join Access Point: %s", WIFI_SSID));
    }
    LogInfo(("Successfully joined Access Point: %s", WIFI_SSID));

    /* Step 3: Configure SNTP for time synchronization */
    if (esp32_config_sntp(UTC_OFFSET) != ESP32_OK) {
      LogError(("Failed to configure SNTP."));
      esp32_test_passed = false;
    } else {
      LogInfo(("SNTP configured !"));

      /* Retrieve the current time from SNTP */
      sntp_time_t sntp_time;
      if (esp32_get_sntp_time(&sntp_time) != ESP32_OK) {
        LogError(("Failed to retrieve current time from SNTP."));
        esp32_test_passed = false;
      } else {
        LogInfo(("SNTP time retrieved: %s, %02d %s %04d %02d:%02d:%02d",
                 sntp_time.day, sntp_time.date, sntp_time.month, sntp_time.year,
                 sntp_time.hour, sntp_time.min, sntp_time.sec));
        esp32_test_passed = true;
      }
    }
  }
  LogInfo(("\r\n"));
  HAL_Delay(1000);
#endif

#ifdef TEST_HDC1080
  uint8_t humidity = 0;
  float temperature = 0.0;

  get_temperature_reading(&temperature);
  get_humidity_reading(&humidity);
  if (temperature == 0.0 && humidity == 0) {
    LogError(("Failed to read HDC1080 sensor."));
    hdc1080_test_passed = false;
  } else {
    LogDebug(("Sensor readings: Temperature: %.2fC, Humidity: %d %", temperature, humidity));
    hdc1080_test_passed = true;
  }
  LogInfo(("\r\n"));
  HAL_Delay(1000);
#endif

#ifdef TEST_NOR_FLASH
  w25qxx_config_t w25qxx_config = {
      .hspi = &hspi1,
      .flash_size = 4 * 1024 * 1024
  };

  // Initialize W25QXX
  if (w25qxx_init(&w25qxx_config) != W25QXX_OK) {
    LogError(("Failed to initialize W25QXX NOR flash."));
    nor_flash_test_passed = false;
  } else {
    // Read ID
    uint8_t manufacturer_id;
    uint16_t device_id;
    if (w25qxx_read_id(&manufacturer_id, &device_id) != W25QXX_OK || manufacturer_id != 0xEF) {
      LogError(("Failed to read W25QXX ID."));
      nor_flash_test_passed = false;
    } else {
      // Write data to page 0
      uint8_t write_data[256] = {0x12, 0x34};
      uint8_t read_data[256] = {0};
      if (w25qxx_erase_sector(0) != W25QXX_OK || w25qxx_write_page(0, write_data, sizeof(write_data)) != W25QXX_OK) {
        LogError(("Failed to write to W25QXX."));
        nor_flash_test_passed = false;
      } else if (w25qxx_read_data(0, read_data, sizeof(read_data)) != W25QXX_OK ||
                 memcmp(write_data, read_data, sizeof(write_data)) != 0) {
        LogError(("Failed to verify W25QXX data."));
        nor_flash_test_passed = false;
      } else {
        LogInfo(("W25QXX NOR flash test passed."));
        nor_flash_test_passed = true;
      }
    }
  }
  LogInfo(("\r\n"));
  HAL_Delay(1000);
#endif

#ifdef TEST_SDCARD
  FATFS       FatFs;
  FIL         fil;
  FRESULT     fres;
  char        buf[100];
  do
  {
    //Mount the SD Card
    fres = f_mount(&FatFs, "", 1);    //1=mount now
    if (fres != FR_OK)
    {
      LogError(("No SD Card found : (%i)\r\n", fres));
      break;
    }
    LogInfo(("SD Card Mounted Successfully!!!\r\n"));
    //Read the SD Card Total size and Free Size
    FATFS *pfs;
    DWORD fre_clust;
    uint32_t totalSpace, freeSpace;
    f_getfree("", &fre_clust, &pfs);
    totalSpace = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
    freeSpace = (uint32_t)(fre_clust * pfs->csize * 0.5);
    LogInfo(("TotalSpace : %lu bytes, FreeSpace = %lu bytes\n", totalSpace, freeSpace));
    //Open the file
    fres = f_open(&fil, "TEST.TXT", FA_WRITE | FA_READ | FA_CREATE_ALWAYS);
    if(fres != FR_OK)
    {
      LogError(("File creation/open Error : (%i)\r\n", fres));
      sdcard_test_passed = false;
      break;
    }
    LogInfo(("Writing data!!!\r\n"));
    //write the data
    f_puts("Welcome to fastbit embedded", &fil);
    //close your file
    f_close(&fil);
    //Open the file
    fres = f_open(&fil, "TEST.TXT", FA_READ);
    if(fres != FR_OK)
    {
      LogError(("File opening Error : (%i)\r\n", fres));
      sdcard_test_passed = false;
      break;
    }
    //read the data
    f_gets(buf, sizeof(buf), &fil);
    LogInfo(("Read Data : %s\n", buf));
    //close your file
    f_close(&fil);
    LogInfo(("Closing File!!!\r\n"));

    sdcard_test_passed = true;
    } while( false );
    //We're done, so de-mount the drive
    f_mount(NULL, "", 0);
    LogInfo(("SD Card Unmounted Successfully!!!\r\n"));

    LogInfo(("\r\n"));
    HAL_Delay(1000);
#endif

#ifdef TEST_LCD_DISPLAY

#endif

#ifdef TEST_TOUCH

  LogInfo(("\r\n"));
#endif

#ifdef TEST_CAN_MOD
  CAN_filter_config();

  if(HAL_CAN_ActivateNotification(&hcan1,CAN_IT_TX_MAILBOX_EMPTY|CAN_IT_RX_FIFO0_MSG_PENDING|CAN_IT_BUSOFF)!= HAL_OK)
  {
    Error_Handler();
  }

  if( HAL_CAN_Start(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }


  LogInfo(("\r\n"));
#endif
  /* Print test results */
  LogInfo(("=== Test Results ===\n"));
#ifdef TEST_ESP32_C6
  LogInfo(("ESP32 C6: %s\n", esp32_test_passed ? GREEN_TXT("Success") : RED_TXT("Failure")));
#endif
#ifdef TEST_HDC1080
  LogInfo(("HDC1080 Sensor: %s\n", hdc1080_test_passed ? GREEN_TXT("Success") : RED_TXT("Failure")));
#endif
#ifdef TEST_NOR_FLASH
  LogInfo(("NOR Flash: %s\n", nor_flash_test_passed ? GREEN_TXT("Success") : RED_TXT("Failure")));
#endif
#ifdef TEST_SDCARD
  LogInfo(("SD Card: %s\n", sdcard_test_passed ? GREEN_TXT("Success") : RED_TXT("Failure")));
#endif
#ifdef TEST_LCD_DISPLAY
  LogInfo(("LCD Display: %s\n", lcd_display_test_passed ? GREEN_TXT("Success") : RED_TXT("Failure")));
#endif
#ifdef TEST_TOUCH
  LogInfo(("Touch Controller: %s\n", touch_test_passed ? GREEN_TXT("Success") : RED_TXT("Failure")));
#endif
#ifdef TEST_CAN_MOD
  LogInfo(("CAN Module: %s\n", can_mod_test_passed ? GREEN_TXT("Success") : RED_TXT("Failure")));
#endif
  LogInfo(("===================\n"));
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 5;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_8TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = ENABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = ENABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 4999;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 10000-1;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GREEN_LED_Pin|ORANGE_LED_Pin|RED_LED_Pin|BLUE_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PE7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PE8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : GREEN_LED_Pin ORANGE_LED_Pin RED_LED_Pin BLUE_LED_Pin */
  GPIO_InitStruct.Pin = GREEN_LED_Pin|ORANGE_LED_Pin|RED_LED_Pin|BLUE_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void CAN_filter_config(void)
{
  CAN_FilterTypeDef can1_filter_init;
  can1_filter_init.FilterActivation = ENABLE;
  can1_filter_init.FilterBank = 0;
  can1_filter_init.FilterFIFOAssignment = CAN_RX_FIFO0;
  can1_filter_init.FilterIdHigh = 0x65D << 5; // Standard ID 0x65D
  can1_filter_init.FilterIdLow = 0;
  can1_filter_init.FilterMaskIdHigh = 0x7FF << 5; // Match 0x65D exactly
  can1_filter_init.FilterMaskIdLow = 0;
  can1_filter_init.FilterMode = CAN_FILTERMODE_IDMASK;
  can1_filter_init.FilterScale = CAN_FILTERSCALE_16BIT;
  if (HAL_CAN_ConfigFilter(&hcan1, &can1_filter_init) != HAL_OK)
  {
    printf("Node 2: HAL_CAN_ConfigFilter failed.\n");
    Error_Handler();
  }
}

void LED_Manage_Output(uint8_t led_no)
{
  HAL_GPIO_WritePin(GPIOD, GREEN_LED_Pin | ORANGE_LED_Pin | RED_LED_Pin | BLUE_LED_Pin, GPIO_PIN_RESET);
  switch (led_no)
  {
    case 0:
      HAL_GPIO_WritePin(GPIOD, BLUE_LED_Pin, GPIO_PIN_SET);
      break;
    case 1:
      HAL_GPIO_WritePin(GPIOD, GREEN_LED_Pin, GPIO_PIN_SET);
      break;
    case 2:
      HAL_GPIO_WritePin(GPIOD, ORANGE_LED_Pin, GPIO_PIN_SET);
      break;
    case 3:
      HAL_GPIO_WritePin(GPIOD, RED_LED_Pin, GPIO_PIN_SET);
      break;
    default:
      HAL_GPIO_WritePin(GPIOD, RED_LED_Pin, GPIO_PIN_SET); // Error indication
      break;
  }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  uint8_t rcvd_msg[8];
  if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, rcvd_msg) == HAL_OK)
  {
    if (RxHeader.StdId == 0x65D && RxHeader.RTR == CAN_RTR_DATA && RxHeader.DLC == 1)
    {
      printf("Node 2: Received data frame ID: 0x65D, LED No: %d\n", rcvd_msg[0]);
      LED_Manage_Output(rcvd_msg[0]);
    }
    else
    {
      printf("Node 2: Unexpected frame ID: 0x%X, RTR: %d, DLC: %d\n",
             RxHeader.StdId, RxHeader.RTR, RxHeader.DLC);
    }
  }
  else
  {
    printf("Node 2: HAL_CAN_GetRxMessage failed.\n");
  }
}

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  if (htim->Instance == TIM7)
  {

  }
  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
   while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
