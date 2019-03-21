#ifndef __INC_GOBALDEFINATION
#define __INC_GOBALDEFINATION

#include <stm32f10x.h>

typedef enum BOOL
{FALSE = 0, TRUE}
BOOL;

extern USART_TypeDef *PrintToUSARTx;	//used in printf function

extern u16 Usart1Recieve;

// extern const double VoltageTable[10];

#endif
