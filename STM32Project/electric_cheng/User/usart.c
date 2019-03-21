#include <usart.h>
#include <zhf_lib.h>

static USART_TypeDef *Print_to_USARTx = USART2;

void print_to(USART_TypeDef* USARTx)
{
	assert_param(USARTx == USART1 || USARTx == USART2 || USARTx == USART3);
	Print_to_USARTx = USARTx;
}

int fputc(int ch, FILE *f)
{
	USART_SendData(Print_to_USARTx, (unsigned char) ch);
	while (!(Print_to_USARTx->SR & USART_FLAG_TXE))
		;
	return (ch);

}


void usart2Init(u32 bound)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	
	USART_DeInit(USART2);
	Init_GPIO(GPIOA, GPIO_Pin_2 | GPIO_Pin_3, GPIO_Mode_AF, 
		GPIO_Speed_2MHz, GPIO_OType_PP, GPIO_PuPd_UP);
	
	Init_partial_USART(bound, USART2, USART_Parity_No);
	USART_Cmd(USART2, ENABLE);  //使能串口2
	//NVIC init
	Init_NVIC(USART2_IRQn, 1, 1);
	//enable interruption
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}
void usart3Init(u32 bound)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	// PB10Tx      PB11Rx
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
	
	USART_DeInit(USART3);
	Init_GPIO(GPIOB, GPIO_Pin_10 | GPIO_Pin_11, GPIO_Mode_AF, 
		GPIO_Speed_2MHz, GPIO_OType_PP, GPIO_PuPd_UP);
	
	Init_partial_USART(bound, USART3, USART_Parity_No);
	USART_Cmd(USART3, ENABLE);  //使能串口2
	//NVIC init
	Init_NVIC(USART3_IRQn, 1, 1);
	//enable interruption
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}

