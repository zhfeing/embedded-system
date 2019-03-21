#include <adc.h>
#include <delay.h>

const double ADC_Vref = 3.3;

void Init_ADC()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	Init_GPIO(GPIOA, GPIO_Pin_1, GPIO_Mode_AIN, GPIO_Speed_2MHz);
	
	ADC_DeInit(ADC1);
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1))
		;//wait
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1))
		;//wait
}

u16 adcGetValue(u8 ADC_Channel)
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, 
		ADC_SampleTime_239Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
		;//wait for convertion end
	return ADC_GetConversionValue(ADC1);
}

u16 adcGetAverage(u8 ADC_Channel, u8 times)
{
	u32 temp_val = 0;
	if(times > 0)
	{
		for(u8 t = 0; t < times; t++)
		{
			temp_val += adcGetValue(ADC_Channel);
			delay_ms(5);
		}
		return temp_val/times;
	}
	else
	{
		return adcGetValue(ADC_Channel);
	}
}

