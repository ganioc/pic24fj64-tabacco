#include "Pin_Definitions.h"

void DelayMS(uint16 delay);
void Delay10US(uint16 delay);

void DelayMS(uint16 delay)  //ԭΪ85
{
    uint16 i;
    for(;delay>0;delay--)
        for(i=0;i<400;i++);
}

void Delay10US(uint16 delay)  //ԭΪ85
{
//	uchar i;
    for(;delay>0;delay--)
	{
//		for(i=0;i<1;i++)
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
	}
}
