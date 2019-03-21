#include "stm32f4xx.h"
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>
#include <misc.h>
#include <stdio.h>
#include <delay.h>
#include <usart.h>
#include <gobalDefination.h>
#include <zhf_lib.h>
#include <led.h>
#include <stm32f4xx_rcc.h>
#include <adc.h>
#include <dac.h>

const double DAC_Vref = 2.854;
const double ADC_Vref = 2.9;
double DAC_out = 0.0;

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	Init_NVIC(USART2_IRQn, 0, 0);
	usart2Init(115200);
	print_to(USART2);
	ledInit(Led3);
	Init_ADC1();
	Init_DAC1();
	DAC1_set_vol(DAC_out);
	while(1)
	{
		ledSwitch(Led3);
		delay_s(1);
		u16 adc_average = adcGetAverage(ADC_Channel_1, 3, ADC1);
		double adc_vol = adc_average/(double)0xfff*ADC_Vref;
		printf("sample voltage is %.3f\r\n", adc_vol);
	}
}


