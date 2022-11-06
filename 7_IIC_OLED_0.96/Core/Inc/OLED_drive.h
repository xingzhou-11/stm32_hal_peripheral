#ifndef __OLED_DRIVE_H
#define __OLED_DRIVE_H

#include "main.h"

void OLED_Init(void);

void OLED_Clear(void);

void OLED_Display_On(void);

void OLED_Display_Off(void);

void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size);

void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size);

void OLED_ShowCHinese(uint8_t x, uint8_t y, uint8_t no);

#endif /* __OLED_DRIVE_H */
