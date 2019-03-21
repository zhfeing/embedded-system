#include <rs485.h>
#include <delay.h>

void rs485Init(u32 bound)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	//initial PD7, RE 0 is recieve, 1 is transmite
	Init_GPIO(GPIOD, GPIO_Pin_7, GPIO_Mode_Out_PP, GPIO_Speed_2MHz);
	GPIO_ResetBits(GPIOD, GPIO_Pin_7);	//to prevent dangerous default is recieve
	
	USART_DeInit(USART2);	//reset usart1
	//GPIO init
	//TX
	Init_GPIO(GPIOA, GPIO_Pin_2, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);	
	//RX
	Init_GPIO(GPIOA, GPIO_Pin_3, GPIO_Mode_IN_FLOATING, GPIO_Speed_50MHz);
	//USART init
	Init_partial_USART(bound, USART2, USART_Parity_Odd);
	//NVIC init
	Init_NVIC(USART2_IRQn, 1, 2);
	
	//enable interruption
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	//enable usart
	USART_Cmd(USART2, ENABLE);
}

void enable_send()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_7);
}

void disable_send()
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_7);
}

BOOL rs485_send32BitData(u32 Data)
{
	enable_send();
	for(int i = 1; i <= 4; i++)
	{
		USART_SendData(USART2, Usart1Recieve);
	}
	disable_send();
	//delay_us(4);
	return TRUE;
}
u32 rs485_read32BitData()
{
	
}
