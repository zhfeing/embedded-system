#include "myHead.h"
sbit led1 = P1^0;
void main()
{
    while(1)
    {
        unsigned a = 5;
        led1 = 0;
        while(a--);
        a = 5;
        led1 = 1;
        while(a--);
    }
}