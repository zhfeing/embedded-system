#include <reg52.h>
sbit led = P1^0;
sbit beep = P2^3;

int count = 1;
int i = 5000;
int main()
{
    EA = 1;//打开总中断
    ET0 = 1;//打开定时器中断
    beep = 1;//start mode
    TMOD = 0x01;
    TH0 = (65538 - i)/256;
    TL0 = (65538 - i)%256;
    TR0 = 1;//启动定时器
    while(1)
    {
        if(count >= 2 && count <= 4)
        {
            beep = 0;//open the led
            
        }
        else if(count >= 5)            
        {
            beep = 1;
            count = 0;
            i -= 5;
        }
    }
}
void interruptFinction() interrupt 1
{
    TH0 = (65538 - i)/256;
    TL0 = (65538 - i)%256;
    count++;
    if(i < 13)
        i = 5000;
}