#ifndef __BUTTON_DRIVE_H__
#define __BUTTON_DRIVE_H__

#include "main.h"

typedef enum
{
  BUTTON_RESET,
  BUTTON_SET
} Button_State;


Button_State Button_Detection(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif /*__BUTTON_DRIVE_H__ */
