#ifndef __INC_UART
#define __INC_UART

#include <project.h>

#define MAX_BUFFER_SIZE 0xff
extern u8 RecieveSendBuffer[MAX_BUFFER_SIZE];
extern GPIO_InitTypeDef GPIO_InitStructure;
extern USART_InitTypeDef USART_InitStructure;
extern NVIC_InitTypeDef NVIC_InitStructure;


#endif
