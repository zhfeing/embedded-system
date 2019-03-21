#ifndef __INC_ADC_H
#define __INC_ADC_H

#include <stm32f10x_adc.h>
#include <gobalDefination.h>
#include <zhf_lib.h>

extern const double ADC_Vref;

void Init_ADC(void);
u16 adcGetAverage(u8 ADC_Channel, u8 times);

#endif
