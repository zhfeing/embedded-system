#ifndef __INC_DAC_H
#define __INC_DAC_H

#include <stm32f4xx_dac.h>
#include <stm32f4xx_rcc.h>
#include <gobalDefination.h>
#include <zhf_lib.h>

const extern double DAC_Vref;
void Init_DAC1(void);                 //DACͨ��1��ʼ��                
void DAC1_set_vol(double vol);    //����ͨ��1�����ѹ

#endif
