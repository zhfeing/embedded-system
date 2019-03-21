#ifndef __INC_DAC_H
#define __INC_DAC_H

#include <stm32f10x_adc.h>
#include <gobalDefination.h>
#include <zhf_lib.h>

extern const double DAC_Vref;

void Init_DAC(void);
void DAC_set_vol(double voltage);

#endif
