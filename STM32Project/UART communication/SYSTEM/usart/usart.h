#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define MAX_BUFFER_SIZE 0xff
extern u8 RecieveSendBuffer[MAX_BUFFER_SIZE];
extern GPIO_InitTypeDef GPIO_InitStructure;
extern USART_InitTypeDef USART_InitStructure;
extern NVIC_InitTypeDef NVIC_InitStructure;


/*	0-7: recieve or send size; 8: reciving; 9: sending;
*	10:recieve done; 11: send done; 12: dealing
*	13:receive error; 143: send error;
*/
extern u16 RecieveSendFlag;


//must put in the begining of main()
void uart_communication_init(void);
void communicationProtoco(void);

#endif
