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
#include "guzhangbaojing.h"
//#include "chaxun.h"

void zhuanhuan_16to8 (uint16 zhi);
uint16 zhuanhuan_8to16 (uchar zhi1,uchar zhi2);
void chaxun_chunchu(void);
void chaxun_xianshi(void);
//void chaxun_xianshi(uchar dqkc,uint16 cishu);
void chuxun_xuanze(void);
void huihuchaxunzhi(void);
void anjianhuifuchaxun(void);
void kaocai_panduan(uint16 cunchu_cs);
