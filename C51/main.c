#include <reg52.h>
sbit LED0 = P1^0;
sbit LED2 = P1^2;
int main(void)
{
	LED0 = 0;
	while(1)
	{
		int i = 1000;
		LED2 = ~LED2;
		for(i = 1000; i > 0; i--)
			;
	}
}