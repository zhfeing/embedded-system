#include "function.h"
void delay_s(unsigned second)
{
	const unsigned halfSecond = 41889;
	int i, j;
	for(i = 0; i < second; i++)
	{
		for(j = 0; j < halfSecond; j++)
			;
		for(j = 0; j < halfSecond; j++)
			;
	}
}
void delay_ms(unsigned ms)
{
    const uint mSecond = 84;
	uint i, j;
	for(i = 0; i < ms; i++)
	{
		for(j = 0; j < mSecond; j++)
			;
	}
}
uchar getNumCode(uchar n)
{
    switch(n)
    {
        case 0: return 0x3f;
        case 1: return 0x06;
        case 2: return 0x5b;
        case 3: return 0x4f;
        case 4: return 0x66;
        case 5: return 0x6d;
        case 6: return 0x7d;
        case 7: return 0x07;
        case 8: return 0x7f;
        case 9: return 0x6f;
        case 'A': return 0x77;
        case 'B': return 0x7c;
        case 'C': return 0x39;
        case 'D': return 0x5e;
        case 'E': return 0x79;
        case 'F': return 0x71;
        default: return 0x00;
    }
}
uchar getBitCode(uchar b)
{
    switch(b)
    {
        case 0: return 0xfe;
        case 1: return 0xfd;
        case 2: return 0xfb;
        case 3: return 0xf7;
        case 4: return 0xef;
        case 5: return 0xdf;
        default: return 0xff;
    }
}
void showInDigitron(uchar num[], uchar bits)
{
    int i;
    if(bits > 6)
        bits = 6;
    bits--;
    for(i = bits; i > -1; i--)
    {
        DLBits = 1;
        P0 = getBitCode(i);
        DLBits = 0;
        delay_ms(1);
        DLNums = 1;
        P0 = getNumCode(num[i]);
        DLNums = 0;
        
        delay_ms(10);
        
    }
}