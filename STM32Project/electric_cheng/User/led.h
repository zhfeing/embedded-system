#ifndef __INC_LED
#define __INC_LED

#include <zhf_lib.h>

enum LED_Number
{
	Led3, Led4, Led5, Led6
};
void ledInit(enum LED_Number ledNumber);
void ledOn(enum LED_Number ledNumber);
void ledOff(enum LED_Number ledNumber);
void ledSwitch(enum LED_Number ledNumber);

#endif
