#include "Pin_Definitions.h"

void chose_cs(uchar lcdcs);
void write_lcd_cmd(uchar cmd);
void write_lcd_address(uchar add);
void write_lcd_data(uchar data);
uchar read_lcd_data(void);
void write_lcd_cmddata(uchar cmddata);
void write_all_lcd(uchar dat);
void lcd_cs_pandan(uchar lcd_ic);
void init_lcd(uchar lcd_ic);
void write_lcd_bety(uchar lcd_cs,uchar lcd_address,uchar lcd_bety,uchar sign);
uchar read_lcd_bety(uchar lcd_cs,uchar lcd_address);

void write_lcd_kuang(uchar kuang_num,uchar sign);
void write_lcd_zi(uchar zi_num,uchar sign);
void write_lcd_point(uchar point_num,uchar sign);
void write_lcd_shuzi_yiwei(uchar sign,uchar zhi);
void write_lcd_shuzi_erwei(uchar shuzi_num,uchar sign,uchar zhi);
void write_lcd_shuzi_sanwei(uchar shuzi_num,uchar sign,uint16 zhi);

void ss_panduan_tiaozheng(uchar lei,uchar haoshu,uint16 zhi,uchar sign);
void shanshuo(void);

void shidukongzhi(uint16 zhi,uchar weizhi,uchar sign);
void lcd_xiepingmu(uchar bz);
void clear_shuzikuang(void);
