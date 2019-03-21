#include <uart.h>
#include <led.h>
#include <delay.h>
#include <gobalDefination.h>
#include <dac.h>
double dac_vol;
void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Usart1Recieve = USART_ReceiveData(USART1);
		printToUSARTx(USART1);
		// printf("set data %x\r\n", Usart1Recieve);
		if(Usart1Recieve == 0)
		{
			dac_vol -= 0.01;
			if(dac_vol < 0)
				dac_vol = 0;
			DAC_set_vol(dac_vol);
		}
		else if(Usart1Recieve == 1)
		{
			dac_vol += 0.01;
			if(dac_vol > DAC_Vref)
				dac_vol = 3.3;
			DAC_set_vol(dac_vol);
		}
		else
		{
			printf("wrong code\r\n");
		}
		printf("dac vol %.4f\r\n", dac_vol);
	}
}

void USART2_IRQHandler()
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		u16 recieveData = USART_ReceiveData(USART2);
		
		printf("usart2 recieved %d%%\r\n", recieveData);
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
