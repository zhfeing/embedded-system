#include <VGUS_Driver.h>

u32 RD;
u32 pweight;
u32 addprice;
u16 dj;
u32 price;
u8 tdata;

void initvgusdriver()
{
	 usart2Init(115200);
	 print_to(USART3);
}
void vgusdriver(u32 weight)
{
	SendVgusData(0x0002,weight,4);
	delay_ms(1);
	RecVgusData(0x0000,1);
	dj = RD;
	printf("the dj %d\r\n",dj);
	delay_ms(1);
	//去皮
	RecVgusData(0x0001,1);
	delay_ms(1);
	if (RD == 1)
	{
		RecVgusData(0x0002,2);
		delay_ms(1);
		pweight = RD;
		SendVgusData(0x0001,0,2);
		delay_ms(1);
	}
	
	price = dj*(weight - pweight);
	price = price / 100;
	printf("the price is %d\r\n", price);
	SendVgusData(0x0004,price,4);
	delay_ms(1);
	//价格计算
	
	//累计价格
	RecVgusData(0x0008,1);
	delay_ms(1);
	if (RD == 1)
	{
		addprice = addprice + price;
		SendVgusData(0x0006,addprice,4);
		pweight = 0;
		delay_ms(1);
		SendVgusData(0x0008,0,2);
		delay_ms(1);
	}
	//清零信号
	RecVgusData(0x0009,1);
	delay_ms(1);
	if (RD == 1)
	{
		addprice = 0;
		SendVgusData(0x0006,0,4);
		delay_ms(1);
		pweight = 0;
		SendVgusData(0x0009,0,2);
		delay_ms(1);
	}
		
}
void SendVgusData(uint16_t loc,uint32_t data,u8 num)
{
	USART_SendData(USART2,0xA5);
	delay_us(100);

	USART_SendData(USART2,0x5A);
	delay_us(100);

	USART_SendData(USART2,3+num);
	delay_us(100);

	USART_SendData(USART2,0x82);
	delay_us(100);

	unsigned char hloc = (u8) (loc >> 8);
	unsigned char lloc = (u8) (loc - (hloc << 8));
	USART_SendData(USART2,hloc);
	delay_us(100);

	USART_SendData(USART2,lloc);
	delay_us(100);
		
	for (int i = 1; i<= num;i++)
	{	
		tdata = data >> 24;
		data = data << 8;
		USART_SendData(USART2,tdata);
		delay_us(100);
	}
}

void RecVgusData(uint16_t loc,u8 num)
{
	USART_SendData(USART2,0xA5);
	delay_us(100);

	USART_SendData(USART2,0x5A);
	delay_us(100);

	USART_SendData(USART2,0x04);
	delay_us(100);

	USART_SendData(USART2,0x83);  //设置为发送模式
	delay_us(100);

	unsigned char hloc = (u8) (loc >> 8);
	unsigned char lloc = (u8) (loc - (hloc << 8));
	USART_SendData(USART2,hloc);
	delay_us(100);

	USART_SendData(USART2,lloc);
	delay_us(100);

	USART_SendData(USART2,num);  //Pay Attention!这是数据字长度
	delay_us(100);
	
	//*data=USART2->DR;
	//unsigned char hdat = (u8) (data >> 8);
	//unsigned char ldat = (u8) (data - (hdat << 8));
	//USART_SendData(Print_to_USARTx,hdat);
	//delay_us(100);
	
	//USART_SendData(Print_to_USARTx,ldat);
	//delay_us(100);
}

