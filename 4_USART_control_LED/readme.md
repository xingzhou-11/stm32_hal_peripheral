# STM32_USART中断接收

1. 串口中断接收函数`HAL_UART_Receive_IT`中的`pData`不能放入指针变量，放入指针变量，无法触发中断，可以放入`& + 变量`，`数组名`

```c
uint8_t* Rx_USART_Data;
uint8_t rx_USART_data;
uint8_t RX_USART_DATA[10] = {0};

HAL_UART_Receive_IT(&huart1, Rx_USART_Data, 1); //REEOR
HAL_UART_Receive_IT(&huart1, &rx_USART_data, 1);
HAL_UART_Receive_IT(&huart1, RX_USART_DATA, 9);
```


# 初始化结构体中的数组

1. 结构体中的数组不能直接赋值，有以下两种方法
   
```c
typedef struct __LED_STATE
{
    char open[5];
    char close[6];
}LED_STATE;


LED_STATE LED0 = {"open", "close"};

LED_STATE LED1;

void LED1_State_Init(void)
{
    strcpy(LED1.open, "open");
    strcpy(LED1.close, "close");
}
```


# STM32_USART不定长数据接收

1. 初始化时使能RX中断，时刻准备着接收数据。
2. 第一个数据接收，触发RX中断，执行HAL_UART_RxCpltCallback()，函数里，接收的数据指向数组下一个存储空间，接收的长度+1，使能RX中断，准备下一数据接收。
3. 下一个数据接收，触发RX中断，执行HAL_UART_RxCpltCallback()，函数里，接收的数据指向数组下一个存储空间，接收的长度+1，使能RX中断，准备下一数据接收。
    …… ……
4. 整条命令接收完成，触发空闲中断，执行行HAL_UART_IdleCpltCallback()，函数里，处理接收到的数据，指针指向uart4Rx[]的第一个数据。

[USART接收不定长数据](https://blog.csdn.net/qq_39434851/article/details/116723649)
[USART接收不定长数据](https://blog.csdn.net/ForeverIT/article/details/82055917)