#include <led.h>

void ledInit(enum LED_Number ledNumber)
{
	switch(ledNumber)
	{
	case Led3://PD13
		Init_GPIO(GPIOD, GPIO_Pin_13, GPIO_Mode_OUT, GPIO_Speed_2MHz, 
			GPIO_OType_PP, GPIO_PuPd_NOPULL);
		break;
	default:
		;//printf("error: bad led number\r\n");
	}
}

void ledOff(enum LED_Number ledNumber)
{
	switch(ledNumber)
	{
	case Led3:
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		break;
	default:
		;//printf("error: bad led number\r\n");
	}
}
void ledOn(enum LED_Number ledNumber)
{
	switch(ledNumber)
	{
	case Led3:
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		break;
	default:
		;//printf("error: bad led number\r\n");
	}
}

void ledSwitch(enum LED_Number ledNumber)
{
	switch(ledNumber)
	{
	case Led3:
		if(GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_13) == 0)	//off
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
		else
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		break;
	default:
		;//printf("error: bad led number\r\n");
	}
}
