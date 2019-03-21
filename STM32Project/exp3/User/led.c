#include <led.h>

void ledInit()
{
	Init_GPIO(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP, GPIO_Speed_2MHz);	
	Init_GPIO(GPIOE, GPIO_Pin_5, GPIO_Mode_Out_PP, GPIO_Speed_2MHz);
}

void ledOff(enum LED_Number ledNumber)
{
	switch(ledNumber)
	{
	case Led0:
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		break;
	case Led1:
		GPIO_SetBits(GPIOE, GPIO_Pin_5);
		break;
	default:
		;//printf("error: bad led number\r\n");
	}
}
void ledOn(enum LED_Number ledNumber)
{
	switch(ledNumber)
	{
	case Led0:
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		break;
	case Led1:
		GPIO_ResetBits(GPIOE, GPIO_Pin_5);
		break;
	default:
		;//printf("error: bad led number\r\n");
	}
}

void ledSwitch(enum LED_Number ledNumber)
{
	switch(ledNumber)
	{
	case Led0:
		if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_5) == 0)	//off
			GPIO_SetBits(GPIOB, GPIO_Pin_5);
		else
			GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		break;
	case Led1:
		if(GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_5) == 0)	//off
			GPIO_SetBits(GPIOE, GPIO_Pin_5);
		else
			GPIO_ResetBits(GPIOE, GPIO_Pin_5);
		break;
	default:
		;//printf("error: bad led number\r\n");
	}
}
