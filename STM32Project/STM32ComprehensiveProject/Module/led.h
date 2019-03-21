#ifndef __INC_LED
#define __INC_LED

#include <project.h>
#include <uart.h>

extern GPIO_InitTypeDef GPIO_InitStruct;

enum LED_Number
{
	Led0, Led1
};
void ledInit(void);
void ledOn(enum LED_Number ledNumber);
void ledOff(enum LED_Number ledNumber);

#endif
