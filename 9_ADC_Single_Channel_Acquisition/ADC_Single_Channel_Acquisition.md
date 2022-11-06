# ADC HAL 轮询

- Optionally, perform an automatic ADC calibration to improve the conversion accuracy
        using function `HAL_ADCEx_Calibration_Start()`

- ADC conversion by polling:
      - Activate the ADC peripheral and start conversions using function `HAL_ADC_Start()`
      
      - Wait for ADC conversion completion using function `HAL_ADC_PollForConversion()` (or for injected group: `HAL_ADCEx_InjectedPollForConversion()` )
      
      - Retrieve conversion results using function `HAL_ADC_GetValue()` (or for injected group: `HAL_ADCEx_InjectedGetValue()` )
      
      - Stop conversion and disable the ADC peripheral using function `HAL_ADC_Stop()`