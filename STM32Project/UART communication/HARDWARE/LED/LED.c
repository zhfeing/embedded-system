#include <LED.h>
void LED_Init(void)
{
	//initial the IO clock 初始化io时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	GPIO_SetBits(GPIOE, GPIO_Pin_5);
}

void LED1_on(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}
void LED1_off(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
}
void LED0_on(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_5);	
}
void LED0_off(void)
{
	GPIO_SetBits(GPIOE, GPIO_Pin_5);	
}
