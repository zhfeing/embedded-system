#include <project.h>

u32 Number = 0x0;

void project_init(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//setup the nvic-interrupt priority
	EXTIX_Init();
	uart_communication_init();
	key_init();
	delay_init();
}
void project_begin(void)
{
	while(1)		
	{
		if((RecieveSendFlag & 0x3<<13) != 0)	//error
		{
			printf("error01\n");
			RecieveSendFlag = 0;
		}
		else if((RecieveSendFlag & 0x1<<10) != 0)	//recieve done
		{
			u32 temp = Number;
			if(sscanf((char*)RecieveSendBuffer, "%ld", (long*)&Number) != 1)
			{
				printf("scan ERROR\n");
				Number = temp;
			}
			printf("num is %ld \n", (long)Number);
			RecieveSendFlag = 0;
		}
		delay_ms(10);
	}
}

void dealWithKeys(enum Key k)
{
	delay_ms(15);
	if(k == scanKey(Continue))
	{
		switch(k)
		{
		case Key0:
			Number++;
			printf("number is %ld \n", (long)Number);
			break;
		case Key2:			
			Number--;
			printf("number is %ld \n", (long)Number);
			break;
		default:
			printf("error02\n");
			break;
		}
	}
}
void dealWithUart(void)
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

