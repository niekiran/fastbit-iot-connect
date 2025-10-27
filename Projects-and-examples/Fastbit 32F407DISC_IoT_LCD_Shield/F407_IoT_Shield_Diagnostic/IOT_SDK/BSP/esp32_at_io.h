/*
 * esp32_at_io.h
 *
 * Created on: Dec 27, 2024
 * Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_ESP_AT_IO_H_
#define INC_ESP_AT_IO_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#ifdef STM32F446xx
  extern   UART_HandleTypeDef   huart4;
  #define  ESP32_UART_HANDLE    &huart4
#elif defined(STM32F407xx)
  extern   UART_HandleTypeDef   huart3;
  #define  ESP32_UART_HANDLE    &huart3
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define DEFAULT_TIME_OUT        7000  /* in ms */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
int8_t  esp32_io_init(void);
void    esp32_io_deinit(void);
void    io_buff_reset(void);
int8_t  uart_dma_restart(void);

int8_t  esp32_io_send(uint8_t *p_data, uint32_t length);
int32_t esp32_io_recv(uint8_t *buffer, uint32_t length);
int32_t esp32_io_recv_nb(uint8_t *buffer, uint32_t length);

#endif /* INC_ESP_AT_IO_H_ */
