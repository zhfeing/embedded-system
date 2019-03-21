#include <project.h>
#include <delay.h>

GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
EXTI_InitTypeDef EXIT_InitStructure;

int main()
{
	project_init();
	project_begin();	
	return 0;
}
