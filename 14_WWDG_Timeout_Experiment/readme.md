# STM32 CubeMX WWIG 窗口看门狗

## CubeMX配置
`WWDG counter clock prescaler`          预分频器值
`WWDG window value`                     上窗口值
`WWDG free-running downcounter value`   计数器初始值


## 超时时间计算
![WWDG超时时间计算](./WWDG%E8%B6%85%E6%97%B6%E6%97%B6%E9%97%B4%E8%AE%A1%E7%AE%97.png)

PCLK1为36M，预分频器值设置为1，对应WDGTB值0，上窗口值设置为127，下窗口值固定为64，计数器初始值设置为127

`TWWDG = 1/PCLK1 * 4096 * 2^WDGTB * (计数器初始值 - 最大/最小窗口值+1) = 7.28ms`

最小超时时间：`TWWDG = 1/36MHZ * 4096 * 2^0 * (127-127+1) = 113us`
最大超时时间：`TWWDG = 1/36MHZ * 4096 * 2^0 * (127-64+1) = 7.28ms`