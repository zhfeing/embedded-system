#include <adc.h>
#include <delay.h>
#include <stdio.h>

void Init_ADC1()
{  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ʱ��  
	Init_GPIO(GPIOA, GPIO_Pin_1, GPIO_Mode_AN, GPIO_Speed_2MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);


	ADC_CommonInitTypeDef ADC_CommonInitStructure;  
	ADC_InitTypeDef      ADC_InitStructure;
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ  
	ADC_CommonInitStructure.ADC_TwoSamplingDelay =ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��  
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//DMAʧ��  
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz  
	ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��  

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ  
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ          
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��  
	ADC_InitStructure.ADC_ExternalTrigConvEdge =ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������  
	ADC_InitStructure.ADC_DataAlign= ADC_DataAlign_Right;//�Ҷ���     
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1  
	ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ��  

	ADC_Cmd(ADC1, ENABLE);//����ADת����
}

u16 adcGetValue(u8 ADC_Channel, ADC_TypeDef *ADCx)
{
	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��   
	ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime_480Cycles );	
	ADC_SoftwareStartConv(ADCx); //ʹ��ָ����ADC1�����ת����������
	while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADCx);//�������һ��ADC1�������ת�����  
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

