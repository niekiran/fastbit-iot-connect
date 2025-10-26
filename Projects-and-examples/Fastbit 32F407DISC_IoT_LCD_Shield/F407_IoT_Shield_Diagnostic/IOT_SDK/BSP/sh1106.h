/*
 * sh1106.h
 *
 * Created on: Oct 2, 2024
 * Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef SH1106_H_
#define SH1106_H_

#include "stm32f4xx_hal.h"
#include <string.h>
#include "fonts.h"
// Uncomment one of the following or define in project settings
//#define SH1106_USE_I2C
#define SH1106_USE_SPI

#define SH1106_WIDTH  128
#define SH1106_HEIGHT 64
#define SH1106_BUFFER_SIZE (SH1106_WIDTH * SH1106_HEIGHT / 8)

typedef enum {
    SH1106_OK = 0,
    SH1106_ERR = 1,
    SH1106_I2C_ERR = 2,
    SH1106_SPI_ERR = 3
} sh1106_t;

typedef enum {
    SH1106_COLOR_BLACK = 0,
    SH1106_COLOR_WHITE = 1
} sh1106_color_t;

typedef struct {
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Inverted;
    uint8_t Initialized;
    uint8_t Buffer[SH1106_BUFFER_SIZE];
} SH1106_t;

sh1106_t sh1106_init(void* sh_handle);
sh1106_t sh1106_clear(void);
sh1106_t sh1106_update_screen(void* sh_handle);
sh1106_t sh1106_draw_pixel(uint8_t x, uint8_t y, sh1106_color_t color);
sh1106_t sh1106_gotoXY(uint8_t x, uint8_t y);
sh1106_t sh1106_draw_line(void* sh_handle, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, sh1106_color_t color);
sh1106_t sh1106_draw_rect(void* sh_handle, uint8_t x, uint8_t y, uint8_t w, uint8_t h, sh1106_color_t color);
sh1106_t sh1106_draw_circle(void* sh_handle, uint8_t x0, uint8_t y0, uint8_t r, sh1106_color_t color);
char sh1106_putc(char ch, FontDef_t* Font, sh1106_color_t color);
char sh1106_puts(char* str, FontDef_t* Font, sh1106_color_t color);

#endif /* SH1106_H_ */
