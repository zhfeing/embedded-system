#include <key.h>
#include <delay.h>
static enum Key getKey(void);
void key_init(void)
{
	GPIO_InitTypeDef PE, PA;
	PE.GPIO_Mode = GPIO_Mode_IPU;//key 0, 1, 2
	PE.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	
	PA.GPIO_Mode = GPIO_Mode_IPD;//key_up
	PA.GPIO_Pin = GPIO_Pin_0;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOA, ENABLE);//initial io clock
	
	GPIO_Init(GPIOA, &PA);
	GPIO_Init(GPIOE, &PE);
	
	delay_init();
}

enum Key scanKey(enum ScanMode mode)
{
	enum Key kk;
	static u8 isPressed = 0;
	kk = getKey();
	delay_ms(15);
	if(mode == Continue)
		isPressed = 0;
	if(kk == getKey() && !isPressed)
	{
		if(kk != NoKey)
			isPressed = 1;
		return kk;
	}
	else if(kk == getKey() && isPressed)
	{
		if(kk == NoKey)
			isPressed = 0;
		return NoKey;
	}
	else
	{
		return NoKey;
	}
}

static enum Key getKey(void)
{
	if(0 == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4))
		return Key0;
	else if(0 == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3))
		return Key1;
	else if(0 == GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2))
		return Key2;	
	else if(1 == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
		return Key_up;
	else
		return NoKey;
}
