#ifndef __INC_RS485__H
#define __INC_RS485__H

#include <gobalDefination.h>
#include <uart.h>
#include <zhf_lib.h>



void enable_send(void);
void disable_send(void);
void rs485Init(u32 bound);
BOOL rs485_send32BitData(u32 Data);

#endif
