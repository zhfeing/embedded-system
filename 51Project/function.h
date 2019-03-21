#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include <reg52.h>
#include <intrins.h>

sbit beep = P2^3;
sbit DLBits = P2^7;//ฮปัก
sbit DLNums = P2^6;//ถฮัก

typedef unsigned char uchar;
typedef unsigned int uint;

//delay
void delay_s(unsigned second);
void delay_ms(unsigned ms);

uchar getNumCode(uchar n);
uchar getBitCode(uchar b);
void showInDigitron(uchar num[], uchar bits);

#endif