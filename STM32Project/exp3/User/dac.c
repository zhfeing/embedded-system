#include <dac.h>
#include <delay.h>

const double DAC_Vref = 3.3;

void Init_DAC()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	Init_GPIO(GPIOA, GPIO_Pin_4, GPIO_Mode_AIN, GPIO_Speed_2MHz);
	DAC_InitTypeDef DAC_Init_Structure;
	DAC_Init_Structure.DAC_Trigger = DAC_Trigger_None;
	DAC_Init_Structure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_Init_Structure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init_Structure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_Init(DAC_Channel_1, &DAC_Init_Structure);
	
	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);
}

void DAC_set_vol(double voltage)
{
	u16 tmp;
	if(voltage < 0)
		voltage = 0;
	tmp = voltage/DAC_Vref*0xfff + 0.5;
	if(tmp > 0xfff)
		tmp = 0xfff;
	DAC_SetChannel1Data(DAC_Align_12b_R, tmp);
}

