#ifndef __INC_MAIN_H__
#define __INC_MAIN_H__
# include <XPT2046.h>

sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;

#define COMMONPORTS		P0

void delay(unsigned int time);
void LED_matrix_show(unsigned char number);
void Hc595SendByte(unsigned char dat);
unsigned Read_AD_Data(unsigned char cmd);

#endif
