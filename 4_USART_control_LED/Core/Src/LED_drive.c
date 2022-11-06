#include "LED_drive.h"
#include "usart.h"
#include "string.h"
#include "stdint.h"


Rx_USART_Data rx_usart_data;

void Rx_USART_Data_Init(void)
{
	rx_usart_data.data = 0;
}

void USART_Drive_LED(uint8_t *pData)
{
	uint8_t open = '1';
	uint8_t close = '2';
	
	if(*pData == open)
		HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
	
	if(*pData == close)
		HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
}
