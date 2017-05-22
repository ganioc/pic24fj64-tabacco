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

void gongnengchanshu_set_all(void);
void pianwenbaojing_set(void);
void fengjibaohu_set(void);
void dianyabaohu_set(void);
void guzhanghuifu_set(void);
void paishimenkongzhi_set(void);

void dianyan_zhuanhuan_maintoi2c(void);
void dianyan_zhuanhuan_i2ctomain(void);

void I_U_SET(void);
