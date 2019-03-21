#include <usart.h>
#include <delay.h>
#include <gobalDefination.h>
#include <dac.h>

void USART2_IRQHandler()
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		u16 recieveData = USART_ReceiveData(USART2);
		printf("usart2 recieved %x\r\n", recieveData);
		if(recieveData == 1)
		{
			DAC_out += 0.1;
			if(DAC_out > DAC_Vref)
				DAC_out = DAC_Vref;
			DAC1_set_vol(DAC_out);
		}
		else if(recieveData == 0)
		{
			DAC_out -= 0.1;
			if(DAC_out < 0)
				DAC_out = 0;
			DAC1_set_vol(DAC_out);
		}
		else
		{
			printf("wrong dac value\r\n");
		}
	}
}

/*
void EXTI2_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)
	{
		if(RESET == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2))
		{
			ledOn(Led0);
			delay_ms(100);
			ledOff(Led0);
		}
		else if(RESET == GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2))
		{
			ledOn(Led1);
			delay_ms(100);
			ledOff(Led1);
		}
		else
		{
			printf("wrong\r\n");
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		ledSwitch(Led0);
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}*/
