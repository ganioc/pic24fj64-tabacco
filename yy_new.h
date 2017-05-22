#ifndef _YY_NEW_H_
#define _YY_NEW_H_

#define uint16 unsigned int
#define uchar unsigned char
#define uint8 unsigned char
#define uint32 unsigned long

#define PERIOD_COLLECT_DATA  20
// 25 * 0.2 = 5 s

void toggle(unsigned char bMark);
void yy_check();
void outStr(char * str, uint8 len);
void outChar1(uint8 u8_c);

#endif
