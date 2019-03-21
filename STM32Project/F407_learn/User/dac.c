#include <dac.h>
#include <delay.h>
#include <stdio.h>

void Init_DAC1()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);//使能DAC时钟  
	Init_GPIO(GPIOA, GPIO_Pin_4, GPIO_Mode_AN, GPIO_Speed_2MHz, GPIO_OType_PP, GPIO_PuPd_DOWN);

	DAC_InitTypeDef DAC_InitType;
	DAC_InitType.DAC_Trigger = DAC_Trigger_None;       //不使用触发功能 TEN1=0  
	DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None;//不使用波形发生
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Enable;       //DAC1输出缓存关闭BOFF1=1
	DAC_Init(DAC_Channel_1,&DAC_InitType);       //初始化DAC通道1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC通道1
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12位右对齐数据格式设置DAC值
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
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12位右对齐数据格式设置DAC值
}
