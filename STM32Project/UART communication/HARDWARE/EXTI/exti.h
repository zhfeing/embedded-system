#ifndef __INC_EXTI
#define __INC_EXTI

#include <stm32f10x.h>
#include <key.h>
#include <delay.h>
#include <LED.h>

extern EXTI_InitTypeDef EXIT_InitStructure;
extern NVIC_InitTypeDef NVIC_InitStructure;
void EXTIX_Init(void);
#endif
