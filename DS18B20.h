#include "p24FJ64GA006.h"
#include "Pin_Definitions.h"

void DQ_LOW(void);
void DQ_HIGH(void);
void DQ_HIGH_HANDS(void);
//void Start_18B20(void);
//void get_temp(void);
void get_star_temp(void);
void Write_byte_18B20(uchar val);
uchar reset_18B20(void);

extern uchar ret_18B20;                //18B20复位标志
extern uchar SWD_Z,SWD_X,SSD_Z,SSD_X,XWD_Z,XWD_X,XSD_Z,XSD_X;   //温度、湿度的整数和小数
extern void DS18B20_err_baocun(void);
extern void DS18B20_err_disp(void);
