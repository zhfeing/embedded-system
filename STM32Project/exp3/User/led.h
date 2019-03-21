#ifndef __INC_LED
#define __INC_LED

#include <zhf_lib.h>

enum LED_Number
{
	Led0, Led1
};
void ledInit(void);
void ledOn(enum LED_Number ledNumber);
void ledOff(enum LED_Number ledNumber);
void ledSwitch(enum LED_Number ledNumber);

#endif
