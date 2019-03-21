#ifndef __INC_HX_711_H
#define __INC_HX_711_H

#include <gobalDefination.h>
#include <zhf_lib.h>
#include <exti.h>

extern s32 HX711_GetData;
extern BOOL SetAmp_128;
extern BOOL DataReady;

void HX711_Init(void);
// this function can only be called after external interruption D0 is triggered
s32 get_HX711data(void);
double getWeightFromVol(s32 Voltage);

typedef struct VolAgainstWeight
{
	u32 weight;
	s32 vol;
}VolAgainstWeight;


#define SampleNumber 22

#endif
