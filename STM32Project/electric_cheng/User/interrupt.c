#include <usart.h>
#include <delay.h>
#include <gobalDefination.h>
#include <dac.h>
#include <HX711_Driver.h>

static int cnt = 0;
static u8 length = 0;

void USART2_IRQHandler()
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		u16 rec = USART_ReceiveData(USART2);
		if (cnt == 6)
		{
			 length = rec;
			 RD = 0;
			 cnt = cnt + 1;
		}
		else if (cnt <= length * 2 + 6 && cnt > 6)
		{
			 //rd1 = rec;
			 RD = RD * 256 + rec;
			 if (cnt == length * 2 + 6) cnt = 0;
			 else cnt = cnt + 1;
		}
		else
		{
				cnt = cnt + 1;
		}
		USART_SendData(USART1,rec);
		//printf("current rec %x",rec);
	}
}


void USART3_IRQHandler()
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		u16 recieveData = USART_ReceiveData(USART3);
		printf("usart3 recieved %x\r\n", recieveData);
		if(recieveData == 0)
		{
			SetAmp_128 = FALSE;
		}
		else
		{
			SetAmp_128 = TRUE;
		}
	}
}

void EXTI0_IRQHandler()
{
	static u8 counter;
	const u8 AverageTimes = 5;
	static s32 averageData = 0;
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
	{
		averageData += get_HX711data()/AverageTimes;
		if(++counter >= AverageTimes)
		{
			HX711_GetData = averageData;
			averageData = 0;
			counter = 0;
			DataReady = TRUE;
			// printf("average is %ld\r\n", HX711_GetData);
		}		
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void TIM3_IRQHandler(void)  
{
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	vgusdriver(weight*100 + 0.5);
}
