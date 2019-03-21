#include <timer.h>
#include <zhf_lib.h>

void Init_Tim3(u16 autoReloadValue, u16 prescaler)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	Init_TIM_General_Base(autoReloadValue, prescaler, TIM_CounterMode_Up, TIM3);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	Init_NVIC(TIM3_IRQn, 0, 3);	
	TIM_Cmd(TIM3, ENABLE);
}
/*
void Init_TIM3_PWM(u16 autoReloadValue, u16 prescaler)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	Init_GPIO(GPIOB, GPIO_Pin_5, GPIO_Mode_AF_PP, GPIO_Speed_2MHz);
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);	
	Init_TIM_General_Base(autoReloadValue, prescaler, TIM_CounterMode_Up, TIM3);	
	Init_TIM_OC(TIM_OCMode_PWM2, TIM_OCPolarity_Low, TIM3);	
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_Cmd(TIM3, ENABLE);
}*/


void Init_TIM5_CH3_PWM(u16 autoReloadValue, u16 prescaler)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	Init_GPIO(GPIOA, GPIO_Pin_2, GPIO_Mode_AF_PP, GPIO_Speed_2MHz);
	Init_TIM_General_Base(autoReloadValue, prescaler, TIM_CounterMode_Up, TIM5);	
	Init_TIM_OC(TIM_OCMode_PWM2, TIM_OCPolarity_Low, TIM5, TIM_Channel_3);	
	TIM_Cmd(TIM5, ENABLE);
}

void Init_TIM2_CH4_Cap(u16 autoReloadValue, u16 prescaler)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	Init_GPIO(GPIOA, GPIO_Pin_3, GPIO_Mode_IPD, GPIO_Speed_2MHz);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	Init_TIM_General_Base(autoReloadValue, prescaler, TIM_CounterMode_Up, TIM2);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0f;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	
	Init_NVIC(TIM2_IRQn, 2, 0);
	TIM_ITConfig(TIM2, TIM_IT_Update | TIM_IT_CC4, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}
