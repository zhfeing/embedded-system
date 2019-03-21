#ifndef _INC_LED
#define _INC_LED

#include <stm32f10x.h>
extern GPIO_InitTypeDef GPIO_InitStructure;
void LED_Init(void);
void LED0_on(void);
void LED0_off(void);
void LED1_on(void);
void LED1_off(void);

#endif
