#include <delay.h>
#include <usart.h>
#include <gobalDefination.h>
#include <zhf_lib.h>


void SendVgusData(uint16_t loc,uint32_t data,u8 num);
void RecVgusData(uint16_t loc,u8 num);
void vgusdriver(u32 weight);
void initvgusdriver(void);
