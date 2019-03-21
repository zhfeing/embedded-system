#include <dac.h>
#include <delay.h>
#include <stdio.h>

void Init_DAC1()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);//ʹ��DACʱ��  
	Init_GPIO(GPIOA, GPIO_Pin_4, GPIO_Mode_AN, GPIO_Speed_2MHz, GPIO_OType_PP, GPIO_PuPd_DOWN);

	DAC_InitTypeDef DAC_InitType;
	DAC_InitType.DAC_Trigger = DAC_Trigger_None;       //��ʹ�ô������� TEN1=0  
	DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Enable;       //DAC1�������ر�BOFF1=1
	DAC_Init(DAC_Channel_1,&DAC_InitType);       //��ʼ��DACͨ��1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DACͨ��1
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12λ�Ҷ������ݸ�ʽ����DACֵ
}	
void DAC1_set_vol(double vol)
{
	u16 temp;
	temp = vol*0x1000/DAC_Vref + 0.5;
	if(temp > 0x0fff)
	{
		printf("vol is too large!\r\n");
		temp = 0x0fff;
	}
	printf("DAC Value is %30x\r\n", temp);
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
}
