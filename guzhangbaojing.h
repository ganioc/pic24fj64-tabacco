#include "p24FJ64GA006.h"

#include "Pin_Definitions.h"
//#include "lcd_guding.h"
#include "lcd.h"
#include "delay.h"
#include "key.h"
#include "sound.h"
#include "init.h"
#include "rtcc.h"
#include "DS18B20.h"
#include "i2c.h"
#include "i2c_24lc512.h"
#include "wenduquxian.h"
#include "PCF8574.h"
#include "gongnengcanshushezhi.h"

void fengjikaikongzhi(void);
void fengjiguankongzhi(void);
void fengjiguankongzhi_two(void);
void fengjibaojing(void);
void fengjibaojing_two(void);
void pianwenbaojing(void);
void pianwenpanduan(void);
void dianyabaojing(void);
void dianyapanduan(void);
void baojing(void);
void huifu(void);
void shengyin_chongfu_panduan(uchar sound_duan);
void shengyin_huifu_panduan(uchar sound_duan);
void shengyingexiang_jiaru(uchar leibie,uchar duan,uchar shijian);
void shengyingexiang_huifu(uchar leibie,uchar duan);
void shengyinbaojing(void);
void beiguang_baojing(void);
