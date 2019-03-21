#ifndef INC_FUNCTION
#define INC_FUNCTION
#include <reg52.h>

sbit led1 = P1^0;
sbit beep = P2^3;
sbit DLBits = P2^7;//bit select
sbit DLNums = P2^6;//light number select
sbit DA_cs = P3^2;
sbit DA_wr = P3^6;

typedef unsigned char uchar;
typedef unsigned int uint;

//delay
void delay_s(unsigned second);
void delay_ms(unsigned ms);

uchar getNumCode(uchar n);
uchar getBitCode(uchar b);
void showInDigitron(uchar num[], uchar bits);
#endif