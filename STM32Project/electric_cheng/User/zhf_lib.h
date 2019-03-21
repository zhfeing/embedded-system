#ifndef __INC_ZHF_LIB_H
#define __INC_ZHF_LIB_H

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_usart.h>
#include <gobalDefination.h>

BOOL Init_GPIO(GPIO_TypeDef* GPIOx, u16 GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, 
		GPIOSpeed_TypeDef GPIO_Speed, GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef GPIO_PuPd);
void Init_NVIC(u8 NVIC_IRQChannel, u8 NVIC_IRQChannelPreemptionPriority, u8 NVIC_IRQChannelSubPriority);
void Init_TIM_General_Base(u16 autoReloadValue, u16 prescaler, u16 TIM_CounterMode, TIM_TypeDef *TIMx);
void Init_TIM_OC(u16 TIM_OCMode, u16 TIM_OCPolarity, TIM_TypeDef *TIMx, u16 TIM_Channel);
void Init_partial_USART(u32 bound, USART_TypeDef *USARTx, u16 USART_Parity);

#endif
