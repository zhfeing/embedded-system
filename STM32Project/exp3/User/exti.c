#include <exti.h>
#include <zhf_lib.h>

BOOL Init_EXTIx(GPIO_TypeDef* GPIOx, u16 GPIO_Pin, EXTITrigger_TypeDef EXTI_Trigge)
{
	//IO enable	
	if(EXTI_Trigger_Falling == EXTI_Trigge)
		Init_GPIO(GPIOx, GPIO_Pin, GPIO_Mode_IPU, GPIO_Speed_2MHz);
	else if(EXTI_Trigger_Rising == EXTI_Trigge)
		Init_GPIO(GPIOx, GPIO_Pin, GPIO_Mode_IPD, GPIO_Speed_2MHz);
	else if(EXTI_Trigger_Rising_Falling == EXTI_Trigge)		
		Init_GPIO(GPIOx, GPIO_Pin, GPIO_Mode_IN_FLOATING, GPIO_Speed_2MHz);
	else
		return FALSE;
	
	
	//enable AFIO clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = (u32)GPIO_Pin;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigge;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	return TRUE;
}

void Init_EXTIx_NVIC(u8 GPIO_PortSource, u8 GPIO_PinSource, u8 NVIC_IRQChannel, 
	u8 NVIC_IRQChannelPreemptionPriority, u8 NVIC_IRQChannelSubPriority)
{
	GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource);
	Init_NVIC(NVIC_IRQChannel, NVIC_IRQChannelPreemptionPriority, NVIC_IRQChannelSubPriority);	
}
