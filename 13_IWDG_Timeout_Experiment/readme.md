# STM32 CubeMX IWDG

## 实验实现
1. 配置IWDG预分频器
2. 配置IWDG重装载寄存器

## IWDG 独立看门狗时钟来源
- 独立看门狗(IWDG)由专用的低速时钟(LSI)驱动，即使主时钟发生故障它也仍然有效

## IWDG功能描述
1. 在键寄存器(IWDG_KR)中写入0xCCCC，开始启用独立看门狗，此时计数器开始从其复位值 0xFFF 递减计数，当计数器计数到末尾0x000时，会产生一个复位信号(IWDG_RESET)，无论何时，只要在键寄存器 IWDG_KR 中写入 0xAAAA，IWDG_RLR 中的值就会被重新加载到计数器，从而避免产生看门狗复位
2. IWDG_PR和IWDG_RLR寄存器具有写保护功能。要修改这两个寄存器的值，必须先向 IWDG_KR 寄存器中写入 0x5555，以不同的值写入这个寄存器将会打乱操作顺序，寄存器将重新被保护，重装载操作(即写入0xAAAA)也会启动写保护功能，状态寄存器指示预分频值和递减计数器是否正在被更新

## IWDG超时时间
![IWDG超时时间](./IWDG%E8%B6%85%E6%97%B6%E6%97%B6%E9%97%B4.png)

## 超时时间计算公式：
Tout = 4 * 2^PR * (重载值) / LSI
重载值取值范围：0~4095

## CubeMX设置
`IWDG counter clock prescaler`      设置为64
`IWDG down-counter reload value`    设置为625
`4 * 2^4 * 625 / 40KHZ = 1s`
