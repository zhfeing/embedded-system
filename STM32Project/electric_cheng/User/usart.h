#ifndef __INC_USART_H
#define __INC_USART_H

#include <stdio.h>
#include <stm32f4xx_usart.h>
#include <gobalDefination.h>
#include <zhf_lib.h>

int fputc(int ch, FILE *f);
void print_to(USART_TypeDef* USARTx);
void printToUSARTx(USART_TypeDef *USARTx);
void usart2Init(u32 bound);
void usart3Init(u32 bound);

#endif
