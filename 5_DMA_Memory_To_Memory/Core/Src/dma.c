/**
  ******************************************************************************
  * @file    dma.c
  * @brief   This file provides code for the configuration
  *          of all the requested memory to memory DMA transfers.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "dma.h"

/* USER CODE BEGIN 0 */
#include "gpio.h"
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure DMA                                                              */
/*----------------------------------------------------------------------------*/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
DMA_HandleTypeDef hdma_memtomem_dma1_channel1;

/**
  * Enable DMA controller clock
  * Configure DMA for memory to memory transfers
  *   hdma_memtomem_dma1_channel1
  */
void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* Configure DMA request hdma_memtomem_dma1_channel1 on DMA1_Channel1 */
  hdma_memtomem_dma1_channel1.Instance = DMA1_Channel1;
  hdma_memtomem_dma1_channel1.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma1_channel1.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma1_channel1.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma1_channel1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_memtomem_dma1_channel1.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_memtomem_dma1_channel1.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma1_channel1.Init.Priority = DMA_PRIORITY_LOW;
  if (HAL_DMA_Init(&hdma_memtomem_dma1_channel1) != HAL_OK)
  {
    Error_Handler();
  }

}

/* USER CODE BEGIN 2 */

HAL_StatusTypeDef DMA_status;

/* 定义 aSRC_Const_Buffer 数组作为 DMA 传输数据源 
const 关键字将 aSRC_Const_Buffer 数组变量定义为常量类型 */

const uint32_t aSRC_Const_Buffer[BUFFER_SIZE]= {
	0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
	0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
	0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
	0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
	0x41424344,0x44564748,0x494A4B4C,0x4D4E4F50,
	0x51525345,0x55565758,0x595A5B5C,0x5D5E5F60,
	0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
	0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80
};

/* 定义 DMA 传输目标存储器 */
uint32_t aDST_Buffer[BUFFER_SIZE];

void DMA_Data_Transfer(void)
{
	DMA_status = HAL_DMA_Start(&hdma_memtomem_dma1_channel1, (uint32_t)aSRC_Const_Buffer, (uint32_t)aDST_Buffer, BUFFER_SIZE);
	
	/*DMA 出错就让程序运行下面循环： RGB 彩色灯闪烁*/
	if (DMA_status != HAL_OK) 
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		HAL_Delay(500);
	}
}

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
