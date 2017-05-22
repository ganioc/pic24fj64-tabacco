#include "Pin_Definitions.h"
#include "delay.h"
#include "key.h"

void __delay32(unsigned long cycles);

extern uchar key256;
extern uchar sound_duanl;

uint16 key(void);

//extern uchar key_down_count,key_up_count;

uint16 key(void)
{
  uint16 key_1=0,key_2=0,ret=0;
  if (KEY_ADD==0) key_1=key_1+1;
  if (KEY_LEFT==0) key_1=key_1+2;
  if (KEY_RIGHT==0) key_1=key_1+4;
  if (KEY_SET==0) key_1=key_1+8;
  if (KEY_DEL==0) key_1=key_1+16;
  if (KEY_RUN==0) key_1=key_1+32;
  if (KEY_OK==0) key_1=key_1+64;
  if (KEY_QUERY==0) key_1=key_1+128;

  if(key_1!=0)
   {
     DelayMS(60);
  if (KEY_ADD==0) key_2=key_2+1;
  if (KEY_LEFT==0) key_2=key_2+2;
  if (KEY_RIGHT==0) key_2=key_2+4;
  if (KEY_SET==0) key_2=key_2+8;
  if (KEY_DEL==0) key_2=key_2+16;
  if (KEY_RUN==0) key_2=key_2+32;
  if (KEY_OK==0) key_2=key_2+64;
  if (KEY_QUERY==0) key_2=key_2+128;
     if(key_1==key_2) ret=key_1;
   }
	if(JIANPANSUO==0&&ret==8)
	{
		ret=0;
		sound_duanl=53;
	}
	if(ret==0) key_down_count=0; else key_up_count=0;
 return ret;
}

/*
uint16 key(void)
{
	uint16 key_1=0,key_2=0,ret=0;
KEY_ROW1_DIR=0;
KEY_ROW2_DIR=1;
KEY_ROW3_DIR=1;
KEY_COLUMN1_DIR=1;
KEY_COLUMN2_DIR=1;
KEY_COLUMN3_DIR=1;
	KEY_ROW1=0;
	key256=0;
__delay32(10);
	if(KEY_COLUMN1==0) key_1=key_1+128;
	if(KEY_COLUMN2==0) key_1=key_1+1;
	if(KEY_COLUMN3==0) key_1=key_1+8;
KEY_ROW1_DIR=1;
KEY_ROW2_DIR=0;
	KEY_ROW2=0;
__delay32(10);
	if(KEY_COLUMN1==0) key_1=key_1+64;
	if(KEY_COLUMN2==0) key_1=key_1+4;
	if(KEY_COLUMN3==0) key_1=key_1+32;
KEY_ROW2_DIR=1;
KEY_ROW3_DIR=0;
	KEY_ROW3=0;
__delay32(10);
	if(KEY_COLUMN1==0) key_1=key_1+16;
	if(KEY_COLUMN2==0) key_1=key_1+2;
	if(KEY_COLUMN3==0) key256=1;
//	KEY_ROW3=1;
KEY_ROW3_DIR=1;
KEY_ROW1_DIR=0;
	if(key_1!=0)
	{
		DelayMS(40);
KEY_ROW2_DIR=1;
KEY_ROW3_DIR=1;
		KEY_ROW1=0;
__delay32(10);
		if(KEY_COLUMN1==0) key_2=key_2+128;
		if(KEY_COLUMN2==0) key_2=key_2+1;
		if(KEY_COLUMN3==0) key_2=key_2+8;
KEY_ROW1_DIR=1;
KEY_ROW2_DIR=0;
		KEY_ROW2=0;
__delay32(10);
		if(KEY_COLUMN1==0) key_2=key_2+64;
		if(KEY_COLUMN2==0) key_2=key_2+4;
		if(KEY_COLUMN3==0) key_2=key_2+32;
KEY_ROW2_DIR=1;
KEY_ROW3_DIR=0;
		KEY_ROW3=0;
__delay32(10);
		if(KEY_COLUMN1==0) key_2=key_2+16;
		if(KEY_COLUMN2==0) key_2=key_2+2;
//		KEY_ROW3=1;
KEY_ROW3_DIR=1;
KEY_ROW1_DIR=0;
		if(key_1==key_2) ret=key_1;
	}
	if(key256==1&&ret==8)
	{
		ret=0;
		sound_duanl=53;
	}
	if(ret==0) key_down_count=0; else key_up_count=0;
KEY_ROW1_DIR=0;
KEY_ROW2_DIR=0;
KEY_ROW3_DIR=0;
	KEY_ROW1=1;
	KEY_ROW2=1;
	KEY_ROW3=1;
KEY_COLUMN1_DIR=0;
KEY_COLUMN2_DIR=0;
KEY_COLUMN3_DIR=0;
 KEY_COLUMN1_O=1;
 KEY_COLUMN1_O=1;
 KEY_COLUMN1_O=1;
	return ret;
}
*/
