# STM32 TIM 高级定时器

## 定时器基本初始化结构体
```c
typedef struct {
uint32_t Prescaler;         // 预分频器
uint32_t CounterMode;       // 计数模式
uint32_t Period;            // 定时器周期
uint32_t ClockDivision;     // 时钟分频
uint32_t RepetitionCounter; // 重复计算器，只存在于高级定时器
} TIM_TimeBaseInitTypeDef;
```

## 定时器比较输出初始化结构体
```c
typedef struct {
uint32_t OCMode;        // 比较输出模式，总共有八种，常用的为 PWM1/PWM2
uint32_t Pulse;         // 脉冲宽度
uint32_t OCPolarity;    // 输出极性，可选 OCx 为高电平有效或低电平有效
uint32_t OCNPolarity;   // 互补输出极性，可选 OCxN 为高电平有效或低电平有效
uint32_t OCFastMode;    // 比较输出模式快速使能
uint32_t OCIdleState;   // 空闲状态下比较输出状态（可选输出 1 或输出 0，经过死区时间后定时器通道输出高电平或低电平）
uint32_t OCNIdleState;  // 空闲状态下比较互补输出状态（可选输出 1 或输出 0，经过死区时间后定时器通道输出高电平或低电平，设定的值必须与OCIdleState相反）
} TIM_OCInitTypeDef;
```

## 定时器输入捕获初始化结构体
```c
typedef struct {
uint32_t ICPolarity;    // 输入捕获触发选择，可选上升沿触发、下降沿触发或边沿跳变触发
uint32_t ICSelection;   // 输入捕获选择，捕获通道 ICx 的信号可来自三个输入通道，分别为TIM_ICSELECTION_DIRECTTI、 TIM_ICSELECTION_INDIRECTTI 或 TIM_ICSELECTION_TRC
uint32_t ICPrescaler;   // 输入捕获预分频器，可设置 1、 2、 4、 8 分频，如果需要捕获输入信号的每个有效边沿，则设置 1 分频即可
uint32_t ICFilter;      // 输入捕获滤波器，可选设置 0x0 至 0x0F，一般我们不使用滤波器，即设置为 0
} TIM_IC_InitTypeDef;
```

## 断路和死区结构体
```c
typedef struct {
uint32_t OffStateRunMode;   // 运行模式下的关闭状态选择
uint32_t OffStateIDLEMode;  // 空闲模式下的关闭状态选择
uint32_t LockLevel;         // 锁定配置
uint32_t DeadTime;          // 死区时间，定义死区持续时间，可选设置范围为 0x0 至 0xFF
uint32_t BreakState;        // 断路输入使能控制
uint32_t BreakPolarity;     // 断路输入极性
uint32_t BreakFilter;       // 断路输入滤波器，定义 BRK 输入的采样频率和适用于 BRK 的数字滤波器带宽
uint32_t Break2State;       // 断路 2 输入使能控制
uint32_t Break2Polarity;    // 断路 2 输入极性，可选高电平有效或低电平有效
uint32_t Break2Filter;      // 断路 2 输入滤波器，定义 BRK2 输入的采样频率和适用于 BRK2 的数字滤波器带宽
uint32_t AutomaticOutput;   // 自动输出使能
} TIM_BreakDeadTimeConfigTypeDef;
```


## 实验实现

1. 配置TIM1高级定时器
2. 生成工程代码
3. 实现PWM方波输出


## cubemx配置

1. Clock Source
   - `Internal Clock`   内同步时钟
   - `ETR2`             外部触发输入(ETR)(仅适用TIM2,3,4），外接界的其他信号源

2. Channel1
   - `PwM Generation No Output`    PWM不输出
   - `PwM Generation CH1`          CH1 PWM 输出
   - `PwM Generation CH1N`         CH1 PwM 输出的互补输出
   - `PwM Generation CH1 CH1N`     同时打开CH1 PWM 输出和互补输出

3. Counter Settings
  - `Prescaler(PSC - 16 bits value)`
    - 预分频器(PSC - 16位值)
    - 可设置范围为 0 至 65535，实现 1 至 65536 分频
    - 1MHZ(1us)

   - `Counter Mode`
     - 计数器模式
     - 基本定时器只能是向上计数，即 TIMx_CNT 只能从 0 开始递增，并且无需初始化

   - `Counter Period (AutoReload Register - 16 bits value)`
     - 计数器周期(自动重新加载寄存器- 16位值)
     - 设定定时器重新向上计数的值，可设置范围为 0 至 65535

   - `auto-reload preload`
     - 自动重载预加载

4. PWM Generation Channel 1
   - `Mode`                     选择PWM模式1
   - `Pulse`                    占空比值
   - `Output compare preload`   输出比较预加载
   - `Fast Mode`                PWM脉冲快速模式
   - `CH Polarity`              PWM极性

   1. 占空比计算
      - 需要的脉冲宽度（ms）
      - 时钟周期（ms）
      - 计数器周期 `Counter Period`
      - 占空比 = 需要的脉冲宽度 / 时钟周期 * 计数器周期