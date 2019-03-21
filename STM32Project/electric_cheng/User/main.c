#include "stm32f4xx.h"
#include <stm32f4xx_gpio.h>
#include <stdio.h>
#include <delay.h>
#include <usart.h>
#include <gobalDefination.h>
#include <zhf_lib.h>
#include <led.h>
#include <exti.h>
#include <HX711_Driver.h>
#include <timer.h>
#include <VGUS_Driver.h>

// extern s32 HX711_GetData;
// extern BOOL SetAmp_128;
// extern BOOL DataReady;
double weight;


int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	Init_NVIC(USART3_IRQn, 0, 0);
	usart3Init(115200);
	Init_NVIC(USART2_IRQn, 0, 0);
	initvgusdriver();
	print_to(USART3);
	ledInit(Led3);
	HX711_Init();
	Init_Tim3(5000-1, 8400-1);	// 500 ms
	
	
	const s32 Threshold_Amp128 = 0x0FFFFFFF;
	s32 formalData;		// data after set proprate amp
	while(1)
	{
		// pre-read data
		SetAmp_128 = FALSE;
		DataReady = FALSE;	//wait for update
		while(!DataReady)
			;//wait
		DataReady = FALSE;	//wait for update
		while(!DataReady)
			;//wait
		if(HX711_GetData < Threshold_Amp128)
		{
			SetAmp_128 = TRUE;
			// printf("auto set amp 128\r\n");
		}
		else
		{
			SetAmp_128 = FALSE;
			printf("auto set amp 64\r\n");
		}
		// wait for two cycles for data become stable
		DataReady = FALSE;	//wait for update
		while(!DataReady)
			;//wait
		DataReady = FALSE;	//wait for update
		while(!DataReady)
			;//wait
		formalData = HX711_GetData;
		printf("formal data is %ld\r\n", formalData/50);
		weight = getWeightFromVol(formalData/50);
		printf("weight is %.2f\r\n\r\n\r\n", weight);
		// vgusdriver(weight*100 + 0.5);
		ledSwitch(Led3);
	}
}

