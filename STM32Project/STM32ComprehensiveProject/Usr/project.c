#include <project.h>
#include <led.h>

GPIO_InitTypeDef GPIO_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;

//the initial of gobal environment
//this function must be called before all the functions starts
 void projectInit()
 {
	 delay_init();
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 
	 //initial led
	 ledInit();
 }
 