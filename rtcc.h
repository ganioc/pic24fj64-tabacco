#include "p24FJ64GA006.h"
#include "Pin_Definitions.h"

void time_read(void);
void time_write(uchar time[7]);
uchar BCD2HEX(uchar val);
uchar HEX2BCD(uchar val);
void lcd_time_write(void);
uchar read_time_onebety(uchar weizhi);
void time_write_bety(uchar weizhi,uchar time);
void set_time(void);
