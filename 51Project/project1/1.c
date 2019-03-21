#include "function.h"
uchar flag;
uchar a;
void main()
{
	TMOD = 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 1;
	REN = 1;
	SM0 = 0;
	SM1 = 1;
	EA = 1;
	ES = 1;
	while(1)
	{
		if(flag == 1)
		{
			ES = 0;
			flag = 0;
			SBUF = a;
			while(!TI)
				;
			TI = 0;
			ES = 1;
		}
	}
}
void ser() interrupt 4
{
	RI = 0;
	P1 = SBUF;
	a = SBUF;
	flag = 1;
}