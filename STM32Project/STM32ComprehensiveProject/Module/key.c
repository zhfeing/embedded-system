#include <key.h>

GPIO_InitTypeDef GPIO_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;
void key_init(void);
/*Key0~2 are connected to GND
*Key_up is connected to VCC_3.3
*/
enum Key
{
	Key0, Key1, Key2, Key_up
};
void key_init()
{
	//init GPIO
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode
}