#include <exti.h>
#include <zhf_lib.h>

BOOL Init_EXTIx(GPIO_TypeDef* GPIOx, u16 GPIO_Pin, EXTITrigger_TypeDef EXTI_Trigge)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//Ê¹ÄÜSYSCFGÊ±ÖÓ
	//IO enable	
	if(EXTI_Trigger_Falling == EXTI_Trigge)
		Init_GPIO(GPIOx, GPIO_Pin, GPIO_Mode_IN, GPIO_Speed_2MHz, GPIO_OType_OD, GPIO_PuPd_UP);
	else if(EXTI_Trigger_Rising == EXTI_Trigge)
		Init_GPIO(GPIOx, GPIO_Pin, GPIO_Mode_IN, GPIO_Speed_2MHz, GPIO_OType_OD, GPIO_PuPd_DOWN);
	else if(EXTI_Trigger_Rising_Falling == EXTI_Trigge)		
		Init_GPIO(GPIOx, GPIO_Pin, GPIO_Mode_IN, GPIO_Speed_2MHz, GPIO_OType_OD, GPIO_PuPd_NOPULL);
	else
		return FALSE;
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = (u32)GPIO_Pin;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigge;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	return TRUE;
}

void Init_EXTIx_NVIC(u8 EXTI_PortSourceGPIOx, u8 EXTI_PinSourcex, u8 NVIC_IRQChannel, 
	u8 NVIC_IRQChannelPreemptionPriority, u8 NVIC_IRQChannelSubPriority)
{
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOx, EXTI_PinSourcex);
	Init_NVIC(NVIC_IRQChannel, NVIC_IRQChannelPreemptionPriority, NVIC_IRQChannelSubPriority);	
}
