#include <delay.h>

static void delay_init(void)
{
  static uint8_t first = 0;
  
  if(first == 0)
  {
    first = 1;
    
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Disability SysTick counter */
  }
}

void delay_us(uint64_t nus)
{
  uint32_t temp = 0;
  uint64_t nms = 0;
  
  delay_init();
  
  if(nus == 0)
  {
    return;
  }
  
  nms = nus / 1000;
  nus = nus % 1000;
  
  if(nms > 0)
  {
    delay_ms(nms);
  }

  if(nus > 0)
  {
    SysTick->LOAD = SystemCoreClock / 8000000 * nus;  /* Time load (SysTick-> LOAD is 24bit) */
    SysTick->VAL = 0x000000;                          /* Empty counter */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;         /* Start the countdown */

    do
    {
      temp = SysTick->CTRL;
    }
    while(temp&0x01 && !(temp&(1<<16)));        /* Wait time is reached */

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Close Counter */
    SysTick->VAL = 0x000000;                    /* Empty counter */
  }
}

void delay_ms(uint64_t nms)
{
  uint32_t temp = 0;
  
  delay_init();
  
  if(nms == 0)
  {
    return;
  }
  
  while(nms > 500)
  {
    SysTick->LOAD = SystemCoreClock / 8000 * 500; /* Time load (SysTick-> LOAD is 24bit) */
    SysTick->VAL = 0x000000;                      /* Empty counter */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     /* Start the countdown */

    do
    {
      temp = SysTick->CTRL;
    }
    while(temp&0x01 && !(temp&(1<<16)));        /* Wait time is reached */

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Close Counter */
    SysTick->VAL = 0x000000;                    /* Empty counter */
    
    nms -= 500;
  }
  
  SysTick->LOAD = SystemCoreClock / 8000 * nms; /* Time load (SysTick-> LOAD is 24bit) */
  SysTick->VAL = 0x000000;                      /* Empty counter */
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     /* Start the countdown */

  do
  {
    temp = SysTick->CTRL;
  }
  while(temp&0x01 && !(temp&(1<<16)));        /* Wait time is reached */

  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  /* Close Counter */
  SysTick->VAL = 0x000000;                    /* Empty counter */
}

void delay_s(uint64_t ns)
{
  while(ns > 0)
  {
    delay_ms(1000);
    ns--;
  }
}
