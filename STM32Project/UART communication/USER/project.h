#ifndef __INC_PROJECT
#define __INC_PROJECT

#include <stm32f10x.h>
#include <exti.h>
#include <usart.h>
#include <key.h>
#include <string.h>

extern u32 Number;

void project_init(void);
void project_begin(void);
void dealWithKeys(enum Key k);
void dealWithUart(void);

#endif
