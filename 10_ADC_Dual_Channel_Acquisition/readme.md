# Cube MX ADC 双通道

`Data Alignment`                        右对齐
`Scan Conversion Mode`                  扫描转换模式
`Continuous Conversion Mode`            连续转换模式
`Discontinuous Conversion Mode`         不连续转换模式
`Enable Regular Conversions`            使能常规转换
`Number Of Conversion`                  2   开两个转换通道
`External Trigger Conversion Source`    外部出发转换源
`Enable Injected Conversions`           注入通道使能

---

`Sampling Time`     取样时间

每个通道都可以单独配置为不同的采样时间，单个通道的转换时间计算公式为：

`Tconv = Sampling time + 12.5 cycles`

当ADC时钟为14MHz并且软件配置采样时间为1.5cycles（即1.5个ADC时钟）：

Tconv = 1.5 + 12.5 = 14cycles = 1us

（14 cycles即是14个ADC时钟，14 / 14MHz = 1us，即1us）

---