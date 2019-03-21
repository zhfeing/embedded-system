#include <usart.h>
#include <delay.h>
#include <project.h>
u16 RecieveSendFlag;
u8 RecieveSendBuffer[MAX_BUFFER_SIZE];
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
int _sys_exit(int x) 
{ 
	x = x;
	return 0;
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0)
		;//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}

/*
//使用microLib的方法
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/

void uart_communication_init(void)
{
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//setup the nvic-interrupt priority
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//enable GPIOA clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//enable USART1 clock
	//enable GPIOA_Pin_9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//AF output TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//setup GPIOA_Pin10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//floating input RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//setup USTRA1
	USART_InitStructure.USART_BaudRate = 115200;		//setup the baud rate
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		//recieve and send
	USART_InitStructure.USART_Parity = USART_Parity_No;		//no parity
	USART_InitStructure.USART_StopBits = USART_StopBits_1;		//1 stop bit
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//9 word length
	USART_Init(USART1, &USART_InitStructure);
	
	USART_Cmd(USART1, ENABLE);		//enable USART1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);		//enable USART1 interrupt
	//setup interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_Init(&NVIC_InitStructure);
	
	RecieveSendFlag = 0;
}

void USART1_IRQHandler(void)
{
	dealWithUart();
	//communicationProtoco();
}

void communicationProtoco(void)
{
	u8 recieveData = USART_ReceiveData(USART1);
	static u8 last_receive_not_done;
	static u8 last_data;
	if((RecieveSendFlag & 0x7<<12) != 0)//dealing or error
	{
		printf("dealing or error\n");
	}
	else
	{
		RecieveSendFlag |= 0x1<<8;//receiving
		//printf("receiving\n");
		if(last_receive_not_done)	//continue receiving
		{
			//printf("Goto 01\n");
			if(recieveData != '/')	//not the end
			{
				//printf("Goto 02\n");
				if((RecieveSendFlag & 0x00FF) < MAX_BUFFER_SIZE)
				{
					//printf("Goto 03\n");
					RecieveSendBuffer[RecieveSendFlag & 0x00FF] = recieveData;
					RecieveSendFlag++;
				}
				else
				{
					//printf("Goto 04\n");
					RecieveSendFlag |= 0x1<<13;	//receive error
				}
			}
			else
			{
				//printf("Goto 05\n");
				RecieveSendBuffer[RecieveSendFlag & 0x00FF] = 0;
				RecieveSendFlag |= 0x1<<10;	//receive done
				last_receive_not_done = 0;
				last_data = 0;
			}
		}
		else	//receiving head
		{
			if(last_data == '|' && recieveData == ':')	//begin to receive
			{
				//printf("Goto 06\n");
				last_receive_not_done = 1;
			}
			else
			{
				//printf("Goto 07\n");
				last_data = recieveData;
			}
		}
		RecieveSendFlag &= ~(0x1<<8);//not receiving
	}
}
