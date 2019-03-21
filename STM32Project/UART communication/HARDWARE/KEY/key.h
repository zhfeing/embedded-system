#ifndef __INC_KEY
#define __INC_KEY
#include <stm32f10x.h>
extern GPIO_InitTypeDef GPIO_InitStructure;
enum Key {NoKey = 0, Key0, Key1, Key2, Key_up};
enum ScanMode {Once, Continue};

void key_init(void);
enum Key scanKey(enum ScanMode mode);

#endif
