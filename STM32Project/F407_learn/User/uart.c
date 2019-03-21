#include <uart.h>
#include <zhf_lib.h>

USART_TypeDef *PrintToUSARTx = USART1;

void uart1Init(u32 bound)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	USART_DeInit(USART1);	//reset usart1
	//GPIO init
	//TX
	Init_GPIO(GPIOA, GPIO_Pin_9, GPIO_Mode_AF_PP, GPIO_Speed_2MHz);	
	//RX
	Init_GPIO(GPIOA, GPIO_Pin_10, GPIO_Mode_IN_FLOATING, GPIO_Speed_2MHz);
	//USART init
	Init_partial_USART(bound, USART1, USART_Parity_No);
	//NVIC init
	Init_NVIC(USART1_IRQn, 1, 1);
	//enable interruption
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//enable usart
	USART_Cmd(USART1, ENABLE);
}

void uart2Init(u32 bound)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	USART_DeInit(USART2);	//reset usart1
	//GPIO init
	//TX
	Init_GPIO(GPIOA, GPIO_Pin_2, GPIO_Mode_AF_PP, GPIO_Speed_2MHz);	
	//RX
	Init_GPIO(GPIOA, GPIO_Pin_3, GPIO_Mode_IN_FLOATING, GPIO_Speed_2MHz);
	//USART init
	Init_partial_USART(bound, USART2, USART_Parity_Odd);
	//NVIC init
	Init_NVIC(USART2_IRQn, 1, 2);
	
	//enable interruption
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	//enable usart
	USART_Cmd(USART2, ENABLE);
}
void uart3Init(u32 bound)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	USART_DeInit(USART3);	//reset usart1
	//GPIO init
	//TX
	Init_GPIO(GPIOB, GPIO_Pin_10, GPIO_Mode_AF_PP, GPIO_Speed_2MHz);	
	//RX
	Init_GPIO(GPIOB, GPIO_Pin_11, GPIO_Mode_IN_FLOATING, GPIO_Speed_2MHz);
	//USART init
	Init_partial_USART(bound, USART3, USART_Parity_Odd);
	//NVIC init
	Init_NVIC(USART3_IRQn, 1, 2);	
	//enable interruption
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	//enable usart
	USART_Cmd(USART3, ENABLE);	
}

void printToUSARTx(USART_TypeDef *USARTx)
{
	assert_param(USARTx == USART1 || USARTx == USART2 || USARTx == USART3);
	PrintToUSARTx = USARTx;
}
