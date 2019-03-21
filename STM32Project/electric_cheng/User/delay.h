#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f4xx.h"

#ifdef __cplusplus
 extern "C" {
#endif  /* __cplusplus */

void delay_us(uint64_t nus);
void delay_ms(uint64_t nms);
void delay_s(uint64_t ns);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif	/* __DELAY_H */
