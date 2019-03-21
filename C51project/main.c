#include<reg51.h>
#include<intrins.h>
#include <main.h>


//--定义要使用的IO口--//
#define COMMONPORTS		P0

//--列选通控制--//
unsigned char code TAB[8]  = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

//--点阵字码--//
unsigned char code LightCode[4][18] = 
{	{0x00,0x00,0x00,0x80,0x40,0x20,0x1F,0x00}, 
	{0x00,0x00,0x40,0xA0,0x50,0x20,0x1F,0x00}, 
	{0x00,0x20,0x50,0xA8,0x50,0x20,0x1F,0x00},
	{0x00,0x00,0x00,0x80,0x40,0x20,0x1F,0x00},
};

void main()
{
	unsigned char number;
	unsigned AD_Value;
	while(1)
	{
		AD_Value = Read_AD_Data(0xA4);		//   AIN2 光敏电阻
		if(AD_Value > 95)
			LED_matrix_show(0);
		else if(AD_Value > 55)
			LED_matrix_show(1);
		else
			LED_matrix_show(2);
	}
}
void LED_matrix_show(unsigned char number)
{
	unsigned char tab;
	number = number % 4;
	for(tab=0;tab<8;tab++)
	{
		Hc595SendByte(0x00);			     //消隐
		COMMONPORTS	= TAB[tab];				 //输出字码
		Hc595SendByte(LightCode[number][tab]);
		//delay(1);
	}
}
unsigned Read_AD_Data(unsigned char cmd)
{
	uchar i;
	uint AD_Value;
	CLK = 0;
	CS  = 0;
	SPI_Write(cmd);
	for(i=6; i>0; i--); 	//延时等待转换结果
	CLK = 1;	  //发送一个时钟周期，清除BUSY
	_nop_();
	_nop_();
	CLK = 0;
	_nop_();
	_nop_();
	AD_Value=SPI_Read();
	CS = 1;
	return AD_Value;	
}
void delay(unsigned int time)
{
  unsigned int i,j;
  for(i=0;i<time;i++)
    for(j=0;j<121;j++);
}


void Hc595SendByte(unsigned char dat)
{
	unsigned char a;
	SRCLK=0;
	RCLK=0;
	for(a=0;a<8;a++)
	{
		SER=dat>>7;
		dat<<=1;

		SRCLK=1;
		_nop_();
		_nop_();
		SRCLK=0;	
	}

	RCLK=1;
	_nop_();
	_nop_();
	RCLK=0;
}