#ifndef __UART_H
#define __UART_H

#include <stm32f10x.h>
#include <stm32f10x_usart.h>
#include <stdio.h>
#include <gobalDefination.h>

void printToUSARTx(USART_TypeDef *USARTx);
void uart1Init(u32 bound);
void uart2Init(u32 bound);
void uart3Init(u32 bound);

#endif
