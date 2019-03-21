#ifndef __INC_ADC_H
#define __INC_ADC_H

#include <stm32f4xx_adc.h>
#include <gobalDefination.h>
#include <zhf_lib.h>

const extern double ADC_Vref;

void Init_ADC1(void);
u16 adcGetAverage(u8 ADC_Channel, u8 times, ADC_TypeDef *ADCx);

#endif
