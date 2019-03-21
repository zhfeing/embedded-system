#include <project.h>
#include <led.h>

int main(void)
{
	projectInit();
	while(1)
	{
		ledOn(Led0);
		delay_ms(100);
		ledOn(Led1);
		delay_ms(100);
		ledOff(Led0);
		delay_ms(100);
		ledOff(Led1);
		delay_ms(100);
	}
}
