#include <adc.h>
#include <delay.h>
#include <stdio.h>

void Init_ADC1()
{  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟  
	Init_GPIO(GPIOA, GPIO_Pin_1, GPIO_Mode_AN, GPIO_Speed_2MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);


	ADC_CommonInitTypeDef ADC_CommonInitStructure;  
	ADC_InitTypeDef      ADC_InitStructure;
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式  
	ADC_CommonInitStructure.ADC_TwoSamplingDelay =ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟  
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//DMA失能  
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz  
	ADC_CommonInit(&ADC_CommonInitStructure);//初始化  

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式  
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式          
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换  
	ADC_InitStructure.ADC_ExternalTrigConvEdge =ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发  
	ADC_InitStructure.ADC_DataAlign= ADC_DataAlign_Right;//右对齐     
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1  
	ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化  

	ADC_Cmd(ADC1, ENABLE);//开启AD转换器
}

u16 adcGetValue(u8 ADC_Channel, ADC_TypeDef *ADCx)
{
	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度   
	ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime_480Cycles );	
	ADC_SoftwareStartConv(ADCx); //使能指定的ADC1的软件转换启动功能
	while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADCx);//返回最近一次ADC1规则组的转换结果  
}

u16 adcGetAverage(u8 ADC_Channel, u8 times, ADC_TypeDef *ADCx)
{
	u32 temp_val = 0;  
	u8 t;  
	for(t = 0; t < times; t++)  
	{
		temp_val += adcGetValue(ADC_Channel, ADCx);  
		delay_ms(5);
	}  
	return temp_val/times;  
}

