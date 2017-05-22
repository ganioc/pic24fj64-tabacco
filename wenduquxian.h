#include "p24FJ64GA006.h"
#include "lcd.h"
#include "Pin_Definitions.h"



extern uchar yushewendu[10];
extern uint16 yusheshidu[10];
extern uchar yushetime[19];
extern uint16 sd_count,wd_count,wd_ud,sd_yd;


uint16 shiduyingyongzhuanhuan_2to1(uchar zhi);
uchar shiduyingyongzhuanhuan_1to2(uint16 zhi);
void xielvjisuan (uchar duan);
void yudingwendu(uchar duan,uint16 xlwd);
void yudingshidu(uchar duan,uint16 xlsd);
void duanwei(uchar wsd_duan);
void time_temp_choose(void);
void temp_time_tiaozheng(void);
void duanweixuanze(void);
void stop_run(void);
void fengjipaishi_kongzhi(void);
void fengjipaishi_kongzhi(void);
void fengjizhuran_kongzhi(void);

void set_all(void);
void huifuchuchangzhi(void);
void jinduanchushitiaozheng(void);
void danqianduan_tiaozhenpd(void);
void close_system(void);
