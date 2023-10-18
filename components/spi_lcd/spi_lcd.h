#ifndef _LCD_SPI_H
#define _LCD_SPI_H

#include "stdint.h"

// Get the original and adjust the direction
#define LCD_MY      0x80
#define LCD_MX      0x40
#define LCD_MV      0x20
#define LCD_ML      0x10

#define LCD_RGBMODE      0x00 ///< Red-Green-Blue pixel order
#define LCD_BGRMODE      0x08 ///< Blue-Green-Red pixel order


// BGR Color
#define WHITE       0xFFFF
#define BLACK      	0x0000
#define BLUE       	0x001F
#define BRED        0XF81F
#define GRED 		0XFFE0
#define GBLUE		0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 		0XBC40
#define BRRED 		0XFC07
#define GRAY  		0X8430
#define DARKBLUE    0X01CF
#define LIGHTBLUE   0X7D7C
#define GRAYBLUE    0X5458
#define LIGHTGREEN  0X841F
#define LIGHTGRAY   0XEF5B
#define LGRAY 		0XC618
#define LGRAYBLUE   0XA651
#define LBBLUE      0X2B12

void LCD_Init(void);

void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void LCD_ShowImage(const uint8_t * img, uint16_t width, uint16_t height);
void LCD_ColorFill(uint16_t sx,uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color);
void LCD_Flush(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t * color_map);
void LCD_SetBlck(uint8_t brightness);
#endif
