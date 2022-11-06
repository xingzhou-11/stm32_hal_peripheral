#ifndef __LED_DRIVE_H__
#define __LED_DRIVE_H__

#include "main.h"

/**
  * @brief  State of the LED 
  */
typedef struct __Rx_USART_Data
{
	uint8_t data;
}Rx_USART_Data;


extern Rx_USART_Data rx_usart_data;

void RX_USART_DATA_Init(void);

void USART_Drive_LED(uint8_t *pData);

#endif /* __LED_DRIVE_H__ */
