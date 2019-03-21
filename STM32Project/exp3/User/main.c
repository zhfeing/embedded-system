#include <project.h>
#include <zhf_lib.h>
#include <adc.h>
#include <math.h>
#include <timer.h>
#include <rs485.h>
#include <dac.h>
#include <key.h>

u16 Usart1Recieve = 0x0000;
const double VoltageTable[10] = {3.25, 3.08, 2.90, 2.71, 2.52, 
									2.31, 2.10, 0.71, 0.675, 0.66};
int Vol_index = 0;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	uart1Init(115200);
	Usart1Recieve = 0x00;
	printToUSARTx(USART1);
	Init_ADC();
	Init_DAC();
	keyInit();
	Init_GPIO(GPIOA, GPIO_Pin_2, GPIO_Mode_Out_PP, GPIO_Speed_2MHz);
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
	u16 ADC_value;
	double sample_vol = 0;
	DAC_set_vol(3.14);
	while(1)
	{
		ADC_value = adcGetAverage(ADC_Channel_1, 20);
		sample_vol = ADC_value/4096.0*ADC_Vref;
		// printf("sample voltage is %.3f\r\n", sample_vol);
		if(sample_vol >= 1.55)
		{
			printf("current is larger than 1.5A and shutdown now\r\n");
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		}
		enum Key k;
		k = scanKey(Once);
		if(k == Key_up)
		{
			Vol_index++;
			if (Vol_index > 9)
				Vol_index = 9;
			double vol = VoltageTable[Vol_index];
			printf("set voltage %.2f\r\n", 3.3 + Vol_index*0.2);
			DAC_set_vol(vol);
		}
		else if(k == Key1)
		{
			Vol_index--;
			if (Vol_index < 0)
				Vol_index = 0;
			double vol = VoltageTable[Vol_index];
			printf("set voltage %.2f\r\n", 3.3 + Vol_index*0.2);
			DAC_set_vol(vol);
		}
		else if(k != NoKey)
		{
			printf("invalid key!\r\n");
		}
		delay_ms(1);
	}
}

