#ifndef __INC_TIMER_H
#define __INC_TIMER_H

#include <stm32f10x_tim.h>

void Init_Tim3(u16 autoReloadValue, u16 prescaler);
void Init_TIM3_PWM(u16 autoReloadValue, u16 prescaler);
void Init_TIM5_Cap(u16 autoReloadValue, u16 prescaler);

void Init_TIM2_CH4_Cap(u16 autoReloadValue, u16 prescaler);
void Init_TIM5_CH3_PWM(u16 autoReloadValue, u16 prescaler);

#endif
