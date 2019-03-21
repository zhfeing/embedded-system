#ifndef __INC_DAC_H
#define __INC_DAC_H

#include <stm32f4xx_dac.h>
#include <stm32f4xx_rcc.h>
#include <gobalDefination.h>
#include <zhf_lib.h>

const extern double DAC_Vref;
void Init_DAC1(void);                 //DAC通道1初始化                
void DAC1_set_vol(double vol);    //设置通道1输出电压

#endif
