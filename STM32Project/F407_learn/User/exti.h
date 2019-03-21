#ifndef __EXTI_H
#define __EXTI_H

#include <stm32f10x.h>
#include <stm32f10x_exti.h>
#include <gobalDefination.h>


BOOL Init_EXTIx(GPIO_TypeDef* GPIOx, u16 GPIO_Pin, EXTITrigger_TypeDef EXTI_Trigge);
void Init_EXTIx_NVIC(u8 GPIO_PortSource, u8 GPIO_PinSource, u8 NVIC_IRQChannel, 
	u8 NVIC_IRQChannelPreemptionPriority, u8 NVIC_IRQChannelSubPriority);

#endif
