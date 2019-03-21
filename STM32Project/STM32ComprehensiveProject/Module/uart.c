#include <uart.h>
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
	while((USART1->SR & 0X40) == 0)
		;//循环发送,直到发送完毕   
    USART1->DR = (u8)ch;      
	return ch;
}



void USART1_IRQHandler(void)
{
	
}
