#include <uart.h>

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
	while((PrintToUSARTx->SR & 0X40) == 0)
		;//循环发送,直到发送完毕   
    PrintToUSARTx->DR = (u8)ch;      
	return ch;
}
