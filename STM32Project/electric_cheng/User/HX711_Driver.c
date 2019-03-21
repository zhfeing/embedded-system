#include <HX711_Driver.h>
#include <delay.h>
#include <stdio.h>

s32 HX711_GetData;
BOOL SetAmp_128 = FALSE;
BOOL DataReady = FALSE;

void HX711_Init()
{
	Init_EXTIx(GPIOD, GPIO_Pin_0, EXTI_Trigger_Falling);
	Init_EXTIx_NVIC(EXTI_PortSourceGPIOD, EXTI_PinSource0, EXTI0_IRQn, 1, 1);
	Init_GPIO(GPIOD, GPIO_Pin_1, GPIO_Mode_OUT, GPIO_Speed_50MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	GPIO_ResetBits(GPIOD, GPIO_Pin_1);
}
// this function can only be called after external interruption D0 is triggered
s32 get_HX711data()
{
	u8 i = 0;
	s32 data = 0;
	delay_us(1);
	for(i = 0; i < 24; i++)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_1);
		delay_us(5);
		GPIO_ResetBits(GPIOD, GPIO_Pin_1);
		u8 b = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0);
		data <<= 1;
		if(b)
		{
			data++;
		}
	}
	// clk #25
	GPIO_SetBits(GPIOD, GPIO_Pin_1);
	delay_us(5);
	GPIO_ResetBits(GPIOD, GPIO_Pin_1);
	delay_us(5);
	// # clk #27
	if(!SetAmp_128)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_1);
		delay_us(5);
		GPIO_ResetBits(GPIOD, GPIO_Pin_1);
		delay_us(5);
		GPIO_SetBits(GPIOD, GPIO_Pin_1);
		delay_us(5);
		GPIO_ResetBits(GPIOD, GPIO_Pin_1);
	}
	// printf("data is %08x\r\n", (u32)data);
	if(data & 0x00800000)	 //negetive
	{
		data = ~data + 1;
		data &= 0x00FFFFFF;
		data = -data;
	}
	// printf("result is %d\r\n", data);
	return data;
}



const VolAgainstWeight Vol_Weight_Data[SampleNumber] = 
{
{0, 241}, 
{10, 327},
{20, 414},
{30, 499},
{40, 585},
{50, 673},
{60, 760},
{70, 847},
{80, 933},
{90, 1019},
{100, 1106},
{110, 1191},
{120, 1278},
{130, 1364},
{140, 1450},
{150, 1536},
{160, 1623},
{170, 1709},
{180, 1797},
{190, 1884},
{200, 1920},
{210, 2057},
//{220, 5},
//{230, 5},
//{240, 5},
//{250, 5},
//{260, 5},
//{270, 5},
//{280, 5},
//{290, 5},
//{300, 5},
//{310, 5},
//{320, 5},
//{330, 5},
//{340, 5},
//{350, 5},
//{360, 5},
//{370, 5},
//{380, 5},
//{390, 5},
//{40, 5},
//{40, 5},
//{40, 5},
//{40, 5},
};



double getWeightFromVol(s32 voltage)
{
	u8 p, q;
	u32 weight;
	p = 0;
	q = SampleNumber - 1;
	if (voltage <= Vol_Weight_Data[0].vol)
	{
		weight = Vol_Weight_Data[0].weight;
	}
	else if (voltage >= Vol_Weight_Data[SampleNumber - 1].vol)
	{
		weight = Vol_Weight_Data[SampleNumber - 1].weight;
		printf("Out of Range]\r\n");
	}
	else
	{
		u8 r;
		while (p < q - 1)
		{
			r = (p + q) / 2;
			if (voltage < Vol_Weight_Data[r].vol)
			{
				q = r;
			}
			else if (voltage > Vol_Weight_Data[r].vol)
			{
				p = r;
			}
			else	// condition happens scarcely
			{
				p = r;
				q = r;
			}
		}
		// printf("p is %d, q is %d\n", p, q);
		if (p == q)
		{
			weight = Vol_Weight_Data[p].weight;
		}
		else	// linear insertion
		{
			double xp, xq, yp, yq;
			xp = Vol_Weight_Data[p].vol;
			xq = Vol_Weight_Data[q].vol;
			yp = Vol_Weight_Data[p].weight;
			yq = Vol_Weight_Data[q].weight;
			weight = yp + (voltage - xp)*(yp - yq) / (xp - xq) + 0.5;
		}
		printf("voltage is %d, vol is %d\n", voltage, Vol_Weight_Data[p].vol);
	}
	return weight;
}
