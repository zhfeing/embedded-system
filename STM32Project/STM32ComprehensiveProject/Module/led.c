#include <led.h>

void ledInit()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE, ENABLE);
	//led0 initial
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	//led2 initial
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}

void ledOn(enum LED_Number ledNumber)
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
		printf("error: bad led number\r\n");
	}
}
void ledOff(enum LED_Number ledNumber)
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
		printf("error: bad led number\r\n");
	}
}
