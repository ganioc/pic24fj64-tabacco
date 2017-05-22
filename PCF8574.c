#include "p24FJ64GA006.h"
#include "lcd.h"
#include "delay.h"
#include "Pin_Definitions.h"
#include "i2c.h"

extern uchar PCF8574;
extern uchar ad_ps_bz,ad_count,ad_kgd,psm_wz;//,ps_dl
extern uint16 ps_dl;
extern uchar ad_bz;
extern uchar ad_bz,ad_wzbz,ad_cytimes,ad_lc;
extern uchar time_1s,ad_1s;
extern uchar ad_tdbz;
extern uchar ad_tzbz;
extern uchar paishimencanshu[6];		//排湿门各项参数内容
extern uchar set_psmcs;	
extern uchar fjqh_sign;
extern uint16 key_mid;

void PCF8574_chose(uchar kou,uchar zhi)
{
	uchar ls=0x01;
	ls=ls<<kou;
	if(zhi)	PCF8574=PCF8574|ls;
	else PCF8574=PCF8574&(~ls);
	LDByteWriteI2C(0X40,PCF8574);
}
//开排湿门
void Discharge_wet_ON_left(void)
{
//	if(fenjiks==1)
//	{
//		Wet_exhaust_ONE=1;
//		Wet_exhaust_TWO=0;
//	}
//	else
//	{
		Wet_exhaust_ONE=0;
		Wet_exhaust_TWO=1;
//	}
//	Blast=1;
}

//关排湿门
void Discharge_wet_ON_right(void)
{
//	if(fenjiks==1)
//	{
//		Wet_exhaust_ONE=0;
//		Wet_exhaust_TWO=1;
//	}
//	else
//	{
		Wet_exhaust_ONE=1;
		Wet_exhaust_TWO=0;
//	}
//	Blast=1;
}

//排湿门停止
void Discharge_wet_OFF(void)
{
	Wet_exhaust_ONE=0;
	Wet_exhaust_TWO=0;
//	Blast=1;
}
void paishimen_kaiguan(uchar zt,uchar du )
{
	if(ad_tzbz==0)
	{
		ad_count=0;
	}
	switch (zt)
	{
		case 0:
		//	PCF8574_chose(2,0);
//JDQ_PAISHI_MIN_OFF;
	Discharge_wet_OFF();
			ad_ps_bz=0;
			ad_tdbz=0;
			ad_1s=0;
			ad_cytimes=0;
			ad_bz=0;
			IEC0bits.AD1IE=0;
			AD1CON1bits.ASAM=0;
//			PCF8574_chose();
		break;
		case 1:
			ad_bz=0;
			ad_ps_bz=1;
	//	ad_cytimes=0;
		//	if(psm_wz<paishimencanshu[3])//
		//	{
			//	PCF8574_chose(1,1);
//JDQ_PAISHI_BIG_ON;
			//	PCF8574_chose(2,1);
//JDQ_PAISHI_MIN_ON;
		Discharge_wet_ON_left();
				if(paishimencanshu[3]-psm_wz>=du)
				psm_wz=psm_wz+du;
				else 
				{
					psm_wz=paishimencanshu[3];
					du=paishimencanshu[3]-psm_wz;
				}
		//	}
		//	else ad_ps_bz=0;
			ad_kgd=du;
		break;
		case 2:
			if(ad_tzbz==0)
			{
				ad_bz=0;
				ad_ps_bz=1;
	//	ad_cytimes=0;
			//	if(psm_wz>0)
			//	{
					if(psm_wz>du)
					psm_wz=psm_wz-du;
					else {psm_wz=0;}//du=8;
				//	PCF8574_chose(1,0);
//JDQ_PAISHI_BIG_OFF;
				//	PCF8574_chose(2,1);
//JDQ_PAISHI_MIN_ON;

		Discharge_wet_ON_right();
					ad_tzbz=1;
			//	}
			//	else ad_ps_bz=0;
		//		if(psm_wz>0)
				ad_kgd=du;
		//		else ad_kgd=du*6;
			}
		break;
	}

}

void ad_ps_ds_stop(void)
{
	if(ad_count==ad_kgd*paishimencanshu[5]&&ad_ps_bz==1)
	{
		paishimen_kaiguan(0,0);
ad_ps_bz=0;
		//	PCF8574_chose(5,1);
//	write_lcd_shuzi_sanwei(6,1,ps_dl);
		ad_tzbz=0;
	}
}

void ad_ps_cl_stop(void)
{
	if((ps_dl>(paishimencanshu[2]+600))&&ad_ps_bz==1&&ad_count>6)//
	{
//	write_lcd_shuzi_sanwei(1,1,ps_dl);
		paishimen_kaiguan(0,0);
ad_ps_bz=0;
		ad_tzbz=0;
	}
}

void fengjikongzhi_qiehuan(void)
{
	if(key_mid==7)
	{
		if(fjqh_sign)
		{
			fjqh_sign=0;			//0为程序控制
			write_lcd_zi(5,0);		//关闭“自动”显示	
		}
		else 
		{
			fjqh_sign=1;			//1为变频器控制
			write_lcd_zi(5,1);		//开启“自动”显示
		}
		HDByteWriteI2C(0xa0,0x01,0x13,fjqh_sign);
		DelayMS(200);
	}
}
