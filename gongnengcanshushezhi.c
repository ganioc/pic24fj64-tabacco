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

extern void ad_zongduanDIANYAcaiyan(void);
extern void ad_zongduanAxiangcaiyan(void);
extern void ad_zongduanCxiangcaiyan(void);
extern void ad_zongduanBxiangcaiyan(void);

extern uchar yushewendu[10];
extern uint16 yusheshidu[10];

extern uchar yusheshidu1[10];
extern uchar yushetime[19];
extern uint16 sd_count,wd_count,wd_yd,sd_yd,hw_time,wenduxielv,shiduxielv;
extern uchar bz;
extern uchar quxianweizhi,time_weizhi;
extern	uchar key_mid;
extern	uchar set_key;
extern uchar time_tab[8];
extern uint16 ss_tab[5][3];
//extern uint16 time_zong;				//总时间
extern uchar time_sec;
extern uchar time_1s;
extern	uchar ad_tdbz;
//extern uchar gzzt;						//工作状态
//extern uchar hkdw;						//烘烤段位
extern uint16 hw_shijian;
//extern uint16 time_dqd;					//当前段的时间计数
extern uint16 WD[4];
extern uchar gongzuo[9];
extern uchar set_bz;
extern uchar sound_duanl;
extern uchar key256;
extern uchar dwxcbc;

extern uchar time_100ms;
extern uchar ss_js,ss_count;

extern unsigned char zishe_sector[39];
extern unsigned char xiabu_sector[39];
extern unsigned char zhongbu_sector[39];
extern unsigned char shangbu_sector[39];

extern uint16 ad_dlz[3];
extern uint16 dyzhi;									//电压值


extern uchar ok_bz;
extern uchar ok_bz_cs;

extern uchar pianwencanshu[5];
extern uchar set_pwcs;


extern uchar fengjibaohucanshu[4];
extern uchar set_fjbhcs;

extern uint16 dianyabaohucanshu[4];		//电压保护各项参数内容
extern uchar set_dybhcs;								//电压参数选择
extern uchar ls_dy[6];

extern uchar guzhanghuifucanshu[2];		//故障恢复各项参数内容
extern uchar set_gzhfcs;								//故障恢复参数选择

//extern uchar paishimencanshu[4];		//排湿门各项参数内容
extern uchar paishimencanshu[6];		//排湿门各项参数内容
extern uchar set_psmcs;	

extern uchar set_gncs_all;
extern uchar gncs_set_bz;

extern uchar set_ui_zhi[4];			//电压电流参数设置
extern uchar key_zhi;


/**************************偏温报警的参数设置***********************************/
void pianwenbaojing_set(void)			
{
	if(key_mid==4&&set_pwcs<4)
	{
		write_lcd_shuzi_sanwei(1,1,pianwencanshu[set_pwcs]);
		set_pwcs++;
		DelayMS(200);
		write_lcd_shuzi_sanwei(1,2,pianwencanshu[set_pwcs]);
		if(set_pwcs==0||set_pwcs==1) write_lcd_point(10,2);
		else write_lcd_point(10,0);
	}
	if(key_mid==2&&set_pwcs>0)
	{
		write_lcd_shuzi_sanwei(1,1,pianwencanshu[set_pwcs]);
		set_pwcs--;
		DelayMS(200);
		write_lcd_shuzi_sanwei(1,2,pianwencanshu[set_pwcs]);
		if(set_pwcs==0||set_pwcs==1) write_lcd_point(10,2);
		else write_lcd_point(10,0);
	}
	if(key_mid==1)
	{
		write_lcd_shuzi_sanwei(1,1,pianwencanshu[set_pwcs]);
		DelayMS(200);
		ok_bz_cs=0;
		switch(set_pwcs)
		{
			case 0:
			if(pianwencanshu[0]<56)
			pianwencanshu[0]++;
		//	write_lcd_point(10,2);
			break;
			case 1:
			if(pianwencanshu[1]<56)
			pianwencanshu[1]++;
		//	write_lcd_point(10,2);
			break;
			case 2:
			if(pianwencanshu[2]<60)
			pianwencanshu[2]++;
		//	write_lcd_point(10,0);
			break;
			case 3:
			if(pianwencanshu[3]<60)
			pianwencanshu[3]++;
		//	write_lcd_point(10,0);
			break;
			case 4:
			if(pianwencanshu[4]<38)
			pianwencanshu[4]++;
		//	write_lcd_point(10,0);
			break;	
		}
		if(pianwencanshu[set_pwcs]==56&&(set_pwcs==0||set_pwcs==1))
		{
			write_lcd_shuzi_sanwei(1,2,65533);
			write_lcd_point(10,0);
		}
		else
		write_lcd_shuzi_sanwei(1,2,pianwencanshu[set_pwcs]);
	}
	if(key_mid==16)
	{
		if(pianwencanshu[set_pwcs]==56&&(set_pwcs==0||set_pwcs==1))
		write_lcd_shuzi_sanwei(1,1,65533);
		else
		write_lcd_shuzi_sanwei(1,1,pianwencanshu[set_pwcs]);
		DelayMS(200);
		ok_bz_cs=0;
		switch(set_pwcs)
		{
			case 0:
			if(pianwencanshu[0]>5)
			pianwencanshu[0]--;
		//	write_lcd_point(10,2);
			break;
			case 1:
			if(pianwencanshu[1]>5)
			pianwencanshu[1]--;
		//	write_lcd_point(10,2);
			break;
			case 2:
			if(pianwencanshu[2]>0)
			pianwencanshu[2]--;
		//	write_lcd_point(10,0);
			break;
			case 3:
			if(pianwencanshu[3]>0)
			pianwencanshu[3]--;
		//	write_lcd_point(10,0);
			break;
			case 4:
			if(pianwencanshu[4]>28)
			pianwencanshu[4]--;
		//	write_lcd_point(10,0);
			break;	
		}
		write_lcd_shuzi_sanwei(1,2,pianwencanshu[set_pwcs]);
	}
	write_lcd_shuzi_sanwei(6,1,set_pwcs);
	write_lcd_point(14,0);
}
/**************************风机保护电流的参数设置***********************************/
void fengjibaohu_set(void)
{
	if(key_mid==4&&set_fjbhcs<3)
	{
		write_lcd_shuzi_sanwei(1,1,fengjibaohucanshu[set_fjbhcs]);
		set_fjbhcs++;
		DelayMS(200);
		write_lcd_shuzi_sanwei(1,2,fengjibaohucanshu[set_fjbhcs]);
		write_lcd_point(10,2);
	}
	if(key_mid==2&&set_fjbhcs>0)
	{
		write_lcd_shuzi_sanwei(1,1,fengjibaohucanshu[set_fjbhcs]);
		set_fjbhcs--;
		DelayMS(200);
		write_lcd_shuzi_sanwei(1,2,fengjibaohucanshu[set_fjbhcs]);
		write_lcd_point(10,2);
	}
	if(key_mid==1)
	{
		write_lcd_shuzi_sanwei(1,1,fengjibaohucanshu[set_fjbhcs]);
		DelayMS(200);
		ok_bz_cs=0;
		switch(set_fjbhcs)
		{
			case 0:
			if(fengjibaohucanshu[0]<100)
			fengjibaohucanshu[0]++;
		//	write_lcd_point(10,2);
			break;
			case 1:
			if(fengjibaohucanshu[1]<100)
			fengjibaohucanshu[1]++;
		//	write_lcd_point(10,2);
			break;
			case 2:
			if(fengjibaohucanshu[2]<150)
			fengjibaohucanshu[2]++;
		//	write_lcd_point(10,0);
			break;
			case 3:
			if(fengjibaohucanshu[3]<30)
			fengjibaohucanshu[3]++;
		//	write_lcd_point(10,0);
			break;	
		}

		write_lcd_shuzi_sanwei(1,2,fengjibaohucanshu[set_fjbhcs]);
	}
	if(key_mid==16)
	{

		write_lcd_shuzi_sanwei(1,1,fengjibaohucanshu[set_fjbhcs]);
		DelayMS(200);
		ok_bz_cs=0;
		switch(set_fjbhcs)
		{
			case 0:
			if(fengjibaohucanshu[0]>10)
			fengjibaohucanshu[0]--;
		//	write_lcd_point(10,2);
			break;
			case 1:
			if(fengjibaohucanshu[1]>10)
			fengjibaohucanshu[1]--;
		//	write_lcd_point(10,2);
			break;
			case 2:
			if(fengjibaohucanshu[2]>10)
			fengjibaohucanshu[2]--;
		//	write_lcd_point(10,0);
			break;
			case 3:
			if(fengjibaohucanshu[3]>10)
			fengjibaohucanshu[3]--;
		//	write_lcd_point(10,0);
			break;	
		}
		write_lcd_shuzi_sanwei(1,2,fengjibaohucanshu[set_fjbhcs]);
	}
	write_lcd_shuzi_sanwei(6,1,set_fjbhcs);
	write_lcd_point(14,0);
}

/**************************电压保护的参数设置***********************************/
void dianyabaohu_set(void)
{
	if(key_mid==4&&set_dybhcs<3)
	{
		write_lcd_shuzi_sanwei(1,1,dianyabaohucanshu[set_dybhcs]);
		set_dybhcs++;
		DelayMS(200);
		write_lcd_shuzi_sanwei(1,2,dianyabaohucanshu[set_dybhcs]);
//		write_lcd_point(10,2);
	}
	if(key_mid==2&&set_dybhcs>0)
	{
		write_lcd_shuzi_sanwei(1,1,dianyabaohucanshu[set_dybhcs]);
		set_dybhcs--;
		DelayMS(200);
		write_lcd_shuzi_sanwei(1,2,dianyabaohucanshu[set_dybhcs]);
//		write_lcd_point(10,2);
	}
	if(key_mid==1)
	{
		write_lcd_shuzi_sanwei(1,1,dianyabaohucanshu[set_dybhcs]);
		DelayMS(200);
		ok_bz_cs=0;
		switch(set_dybhcs)
		{
			case 0:
			if(dianyabaohucanshu[0]<290)
			dianyabaohucanshu[0]++;
		//	write_lcd_point(10,2);
			break;
			case 1:
			if(dianyabaohucanshu[1]<200)
			dianyabaohucanshu[1]++;
		//	write_lcd_point(10,2);
			break;
			case 2:
			if(dianyabaohucanshu[2]<30)
			dianyabaohucanshu[2]++;
		//	write_lcd_point(10,0);
			break;
			case 3:
			if(dianyabaohucanshu[3]<300)
			dianyabaohucanshu[3]++;
		//	write_lcd_point(10,0);
			break;	
		}

		write_lcd_shuzi_sanwei(1,2,dianyabaohucanshu[set_dybhcs]);
	}
	if(key_mid==16)
	{

		write_lcd_shuzi_sanwei(1,1,dianyabaohucanshu[set_dybhcs]);
		DelayMS(200);
		ok_bz_cs=0;
		switch(set_dybhcs)
		{
			case 0:
			if(dianyabaohucanshu[0]>240)
			dianyabaohucanshu[0]--;
		//	write_lcd_point(10,2);
			break;
			case 1:
			if(dianyabaohucanshu[1]>120)
			dianyabaohucanshu[1]--;
		//	write_lcd_point(10,2);
			break;
			case 2:
			if(dianyabaohucanshu[2]>1)
			dianyabaohucanshu[2]--;
		//	write_lcd_point(10,0);
			break;
			case 3:
			if(dianyabaohucanshu[3]>290)
			dianyabaohucanshu[3]--;
		//	write_lcd_point(10,0);
			break;	
		}
		write_lcd_shuzi_sanwei(1,2,dianyabaohucanshu[set_dybhcs]);
	}
	write_lcd_shuzi_sanwei(6,1,set_dybhcs);
	write_lcd_point(14,0);
}

/**************************故障恢复参数设置***********************************/
void guzhanghuifu_set(void)
{
	if(key_mid==4&&set_gzhfcs<1)
	{
		write_lcd_shuzi_sanwei(1,1,guzhanghuifucanshu[set_gzhfcs]);
		set_gzhfcs++;
		DelayMS(200);
		write_lcd_shuzi_sanwei(1,2,guzhanghuifucanshu[set_gzhfcs]);
//		write_lcd_point(10,2);
	}
	if(key_mid==2&&set_gzhfcs>0)
	{
		write_lcd_shuzi_sanwei(1,1,guzhanghuifucanshu[set_gzhfcs]);
		set_gzhfcs--;
		DelayMS(200);
		write_lcd_shuzi_sanwei(1,2,guzhanghuifucanshu[set_gzhfcs]);
//		write_lcd_point(10,2);
	}
	if(key_mid==1)
	{
		write_lcd_shuzi_sanwei(1,1,guzhanghuifucanshu[set_gzhfcs]);
		DelayMS(200);
		ok_bz_cs=0;
		switch(set_gzhfcs)
		{
			case 0:
			if(guzhanghuifucanshu[0]<30)
			guzhanghuifucanshu[0]++;
		//	write_lcd_point(10,2);
			break;
			case 1:
			if(guzhanghuifucanshu[1]<9)
			guzhanghuifucanshu[1]++;
		//	write_lcd_point(10,2);
			break;
		}

//		write_lcd_shuzi_sanwei(1,2,guzhanghuifucanshu[set_gzhfcs]);
//	}
		if(guzhanghuifucanshu[set_gzhfcs]==9&&set_gzhfcs==1)
		{
			write_lcd_shuzi_sanwei(1,2,1011);
			write_lcd_point(10,0);
		}
		else
		write_lcd_shuzi_sanwei(1,2,guzhanghuifucanshu[set_gzhfcs]);
	}



	if(key_mid==16)
	{
		if(guzhanghuifucanshu[set_gzhfcs]==9&&set_gzhfcs==1)
		write_lcd_shuzi_sanwei(1,1,1011);
		else
		write_lcd_shuzi_sanwei(1,1,guzhanghuifucanshu[set_gzhfcs]);
	//	write_lcd_shuzi_sanwei(1,1,guzhanghuifucanshu[set_gzhfcs]);

		DelayMS(200);
		ok_bz_cs=0;
		switch(set_gzhfcs)
		{
			case 0:
			if(guzhanghuifucanshu[0]>3)
			guzhanghuifucanshu[0]--;
		//	write_lcd_point(10,2);
			break;
			case 1:
			if(guzhanghuifucanshu[1]>0)
			guzhanghuifucanshu[1]--;
		//	write_lcd_point(10,2);
			break;
		}
		write_lcd_shuzi_sanwei(1,2,guzhanghuifucanshu[set_gzhfcs]);
	}
	write_lcd_shuzi_sanwei(6,1,set_gzhfcs);
	write_lcd_point(14,0);
}


/**************************排湿门参数设置***********************************/
void paishimenkongzhi_set(void)
{
	if(key_mid==4&&set_psmcs<5)
	{
		write_lcd_shuzi_sanwei(1,1,paishimencanshu[set_psmcs]);
		set_psmcs++;
		DelayMS(200);
		write_lcd_shuzi_sanwei(1,2,paishimencanshu[set_psmcs]);
//		write_lcd_point(10,2);
	}
	if(key_mid==2&&set_psmcs>0)
	{
		write_lcd_shuzi_sanwei(1,1,paishimencanshu[set_psmcs]);
		set_psmcs--;
		DelayMS(200);
		write_lcd_shuzi_sanwei(1,2,paishimencanshu[set_psmcs]);
//		write_lcd_point(10,2);
	}
	if(key_mid==1)
	{
		write_lcd_shuzi_sanwei(1,1,paishimencanshu[set_psmcs]);
		DelayMS(200);
		ok_bz_cs=0;
		switch(set_psmcs)
		{
			case 0:
			if(paishimencanshu[0]<15)
			paishimencanshu[0]++;
		//	write_lcd_point(10,2);
			break;
			case 1:
			if(paishimencanshu[1]<15)
			paishimencanshu[1]++;
		//	write_lcd_point(10,2);
			break;
			case 2:
			if(paishimencanshu[2]<250)
			paishimencanshu[2]++;
		//	write_lcd_point(10,0);
			break;
			case 3:
			if(paishimencanshu[3]<15)
			paishimencanshu[3]++;
		//	write_lcd_point(10,0);
			break;
			case 4:
			if(paishimencanshu[4]<4)
			paishimencanshu[4]++;
		//	write_lcd_point(10,0);
			break;
			case 5:
			if(paishimencanshu[5]<20)
			paishimencanshu[5]++;
		//	write_lcd_point(10,0);
			break;	
		}

		write_lcd_shuzi_sanwei(1,2,paishimencanshu[set_psmcs]);
	}
	if(key_mid==16)
	{

		write_lcd_shuzi_sanwei(1,1,paishimencanshu[set_psmcs]);
		DelayMS(200);
		ok_bz_cs=0;
		switch(set_psmcs)
		{
			case 0:
			if(paishimencanshu[0]>1)
			paishimencanshu[0]--;
		//	write_lcd_point(10,2);
			break;
			case 1:
			if(paishimencanshu[1]>1)
			paishimencanshu[1]--;
		//	write_lcd_point(10,2);
			break;
			case 2:
			if(paishimencanshu[2]>100)
			paishimencanshu[2]--;
		//	write_lcd_point(10,0);
			break;
			case 3:
			if(paishimencanshu[3]>1)
			paishimencanshu[3]--;
		//	write_lcd_point(10,0);
			break;
			case 4:
			if(paishimencanshu[4]>1)
			paishimencanshu[4]--;
		//	write_lcd_point(10,0);
			break;
			case 5:
			if(paishimencanshu[5]>7)
			paishimencanshu[5]--;
		//	write_lcd_point(10,0);
			break;	
		}
		write_lcd_shuzi_sanwei(1,2,paishimencanshu[set_psmcs]);
	}
	write_lcd_shuzi_sanwei(6,1,set_psmcs);
	write_lcd_point(14,0);
}

/**************************系统功能参数总设置***********************************/
void gongnengchanshu_set_all(void)
{

	if(key_mid==8)
	{
	DelayMS(200);
		if(set_gncs_all<4)
		{
	//		write_lcd_shuzi_sanwei(1,1,pianwencanshu[0]);
			switch(set_gncs_all)
			{
				case 0:
				write_lcd_shuzi_sanwei(1,1,pianwencanshu[set_pwcs]);
				break;
				case 1:
				write_lcd_shuzi_sanwei(1,1,fengjibaohucanshu[set_fjbhcs]);
				break;
				case 2:
				write_lcd_shuzi_sanwei(1,1,dianyabaohucanshu[set_dybhcs]);
				break;
				case 3:
				write_lcd_shuzi_sanwei(1,1,guzhanghuifucanshu[set_gzhfcs]);
				break;
			}
			set_gncs_all++;
		}
		else
		{
			write_lcd_shuzi_sanwei(1,1,guzhanghuifucanshu[set_gzhfcs]);
			set_gncs_all=0;
		}
		write_lcd_shuzi_sanwei(5,1,set_gncs_all+1500);
		switch(set_gncs_all)
		{
			case 0:
			write_lcd_shuzi_sanwei(5,1,set_gncs_all+1500);
			write_lcd_point(13,0);
			write_lcd_shuzi_sanwei(1,2,pianwencanshu[0]);
			write_lcd_point(10,2);
			write_lcd_shuzi_sanwei(6,1,set_pwcs);
			write_lcd_point(14,0);
	//		write_lcd_shuzi_sanwei(1,2,65532);
	//		write_lcd_point(11,0);
			break;
			case 1:
			write_lcd_shuzi_sanwei(5,1,set_gncs_all+1500);
			write_lcd_point(13,0);
			write_lcd_shuzi_sanwei(1,2,fengjibaohucanshu[0]);
			write_lcd_point(10,0);
			write_lcd_shuzi_sanwei(6,1,set_fjbhcs);
			write_lcd_point(14,0);
	//		write_lcd_shuzi_sanwei(1,2,65532);
	//		write_lcd_point(11,0);
			break;
			case 2:
			write_lcd_shuzi_sanwei(5,1,set_gncs_all+1500);
			write_lcd_point(13,0);
			write_lcd_shuzi_sanwei(1,2,dianyabaohucanshu[0]);
			write_lcd_point(10,0);
			write_lcd_shuzi_sanwei(6,1,set_dybhcs);
			write_lcd_point(14,0);
	//		write_lcd_shuzi_sanwei(1,2,65532);
	//		write_lcd_point(11,0);
			break;
			case 3:
			write_lcd_shuzi_sanwei(5,1,set_gncs_all+1500);
			write_lcd_point(13,0);
			write_lcd_shuzi_sanwei(1,2,guzhanghuifucanshu[0]);
			write_lcd_point(10,0);
			write_lcd_shuzi_sanwei(6,1,set_gzhfcs);
			write_lcd_point(14,0);
	//		write_lcd_shuzi_sanwei(1,2,65532);
	//		write_lcd_point(11,0);
			break;
			case 4:
			write_lcd_shuzi_sanwei(5,1,set_gncs_all+1500);
			write_lcd_point(13,0);
			write_lcd_shuzi_sanwei(1,2,paishimencanshu[0]);
			write_lcd_point(10,0);
			write_lcd_shuzi_sanwei(6,1,set_psmcs);
			write_lcd_point(14,0);
	//		write_lcd_shuzi_sanwei(1,2,65532);
	//		write_lcd_point(11,0);
			break;
		}

	}
	if(key_mid==64)
	{
	DelayMS(200);

		if(ok_bz_cs==1)
		{
			write_lcd_shuzi_sanwei(5,1,wd_yd);
			write_lcd_shuzi_sanwei(1,1,WD[0]);
			write_lcd_shuzi_sanwei(6,1,sd_yd);
			write_lcd_shuzi_sanwei(2,1,WD[1]);
			write_lcd_point(11,1);
			write_lcd_point(10,1);
			write_lcd_point(13,1);
			write_lcd_point(14,1);
			gncs_set_bz=0;
		//	PCF8574_chose(5,1);
LED_SET_OFF;
		}
		if(ok_bz_cs==0)
		{
			HDduanWriteI2C(0xa0,0x01,0x40,pianwencanshu,5);
			DelayMS(10);
			HDduanWriteI2C(0xa0,0x01,0x45,fengjibaohucanshu,4);
			DelayMS(10);
			dianyan_zhuanhuan_maintoi2c();
			HDduanWriteI2C(0xa0,0x01,0x49,ls_dy,6);
			DelayMS(10);
			HDduanWriteI2C(0xa0,0x01,0x4f,guzhanghuifucanshu,2);
			DelayMS(10);
			HDduanWriteI2C(0xa0,0x01,0x51,paishimencanshu,6);
			DelayMS(10);
			ok_bz_cs=1;
		}
	}	
	if(key_up_count>200)
	{
	//	PCF8574_chose(5,1);
LED_SET_OFF;
		HDSequentialReadI2C(0xa0,0x01,0x40,pianwencanshu,5);
		DelayMS(10);
		HDSequentialReadI2C(0xa0,0x01,0x45,fengjibaohucanshu,4);
		DelayMS(10);
		HDSequentialReadI2C(0xa0,0x01,0x49,ls_dy,6);
		dianyan_zhuanhuan_i2ctomain();
		DelayMS(10);
		HDSequentialReadI2C(0xa0,0x01,0x4f,guzhanghuifucanshu,2);
		DelayMS(10);
		HDSequentialReadI2C(0xa0,0x01,0x51,paishimencanshu,6);
		DelayMS(10);
		write_lcd_shuzi_sanwei(5,1,wd_yd);
		write_lcd_shuzi_sanwei(1,1,WD[0]);
		write_lcd_shuzi_sanwei(6,1,sd_yd);
		write_lcd_point(10,1);
		write_lcd_point(13,1);
		write_lcd_point(14,1);
		gncs_set_bz=0;
	}
	switch (set_gncs_all)
	{
		case 0:
		pianwenbaojing_set();
		break;
		case 1:
		fengjibaohu_set();
		break;
		case 2:
		dianyabaohu_set();
		break;
		case 3:
		guzhanghuifu_set();
		break;
		case 4:
		paishimenkongzhi_set();
		break;
	}

}

/**************************电压功能参数16位转8位***********************************/
void dianyan_zhuanhuan_maintoi2c(void)
{
//	uchar ls_dy[6];
	ls_dy[0]=dianyabaohucanshu[0]/256;
	ls_dy[1]=dianyabaohucanshu[0]%256;
	ls_dy[2]=dianyabaohucanshu[1];
	ls_dy[3]=dianyabaohucanshu[2];
	ls_dy[4]=dianyabaohucanshu[3]/256;
	ls_dy[5]=dianyabaohucanshu[3]%256;
}

/**************************电压功能参数8位转16位***********************************/
void dianyan_zhuanhuan_i2ctomain(void)
{
//	uchar ls_dy[6];

	dianyabaohucanshu[0]=ls_dy[0]*256+ls_dy[1];
	dianyabaohucanshu[1]=ls_dy[2];
	dianyabaohucanshu[2]=ls_dy[3];
	dianyabaohucanshu[3]=ls_dy[4]*256+ls_dy[5];

}

void I_U_SET(void)
{
uchar set_wz=0,ss_count1=0;
uchar	baocun_bz=0;
//		HDSequentialReadI2C(0xa0,0x01,0x55,set_ui_zhi,4);
//		DelayMS(10);
	//	write_lcd_kuang(45,2);
	write_lcd_shuzi_sanwei(3,2,(ad_dlz[0]));
		write_lcd_point(12,2);
						write_lcd_shuzi_sanwei(5,1,(ad_dlz[1]));
		write_lcd_point(13,1);
						write_lcd_shuzi_sanwei(6,1,(ad_dlz[2]));
		write_lcd_point(14,1);
	write_lcd_shuzi_sanwei(7,1,dyzhi);
	key_up_count=0;
	DelayMS(200);
/*
while(1)
{
			shanshuo();
		//	ss_count++;
ClrWdt();
}
*/
	while(key_up_count<200)
	{

        key_zhi=key(); 
		if(key_zhi==2&&set_wz>0)
		{
			set_wz--;
			switch(set_wz)
			{
				case 2:
				write_lcd_shuzi_sanwei(7,1,dyzhi);
			//	write_lcd_point(14,1);
				write_lcd_shuzi_sanwei(6,2,(ad_dlz[2]));
				write_lcd_point(14,2);
				break;
				case 1:
				write_lcd_shuzi_sanwei(6,1,(ad_dlz[2]));
				write_lcd_point(14,1);
				write_lcd_shuzi_sanwei(5,2,(ad_dlz[1]));
				write_lcd_point(13,2);
				break;
				case 0:
				write_lcd_shuzi_sanwei(5,1,(ad_dlz[1]));
				write_lcd_point(13,1);
				write_lcd_shuzi_sanwei(3,2,(ad_dlz[0]));
				write_lcd_point(12,2);
				break;
			}
	DelayMS(200);
		}
		if(key_zhi==4&&set_wz<3)
		{
			set_wz++;
			switch(set_wz)
			{
				case 3:
				write_lcd_shuzi_sanwei(6,1,(ad_dlz[2]));
				write_lcd_point(14,1);
				write_lcd_shuzi_sanwei(7,2,dyzhi);
				break;
				case 2:
				write_lcd_shuzi_sanwei(5,1,(ad_dlz[1]));
				write_lcd_point(13,1);
				write_lcd_shuzi_sanwei(6,2,(ad_dlz[2]));
				write_lcd_point(14,2);
				break;
				case 1:
				write_lcd_shuzi_sanwei(3,1,(ad_dlz[0]));
				write_lcd_point(12,1);
				write_lcd_shuzi_sanwei(5,2,(ad_dlz[1]));
				write_lcd_point(13,2);
				break;
			}
	DelayMS(200);
		}

		if(key_zhi==1&&set_ui_zhi[set_wz]<255)
		{
	DelayMS(200);
			set_ui_zhi[set_wz]++;
//ss_tab[0][2]=set_ui_zhi[set_wz];
		}
		if(key_zhi==16&&set_ui_zhi[set_wz]>1)
		{
	DelayMS(200);
			set_ui_zhi[set_wz]--;
//ss_tab[0][2]=set_ui_zhi[set_wz];
		}

		if(time_1s==1)
		{
			ad_zongduanDIANYAcaiyan();							//ad采样
			ad_zongduanAxiangcaiyan();
			ad_zongduanCxiangcaiyan();
			ad_zongduanBxiangcaiyan();
			if(ad_tdbz==4)
			{
/*
				write_lcd_shuzi_sanwei(3,1,(ad_dlz[0]));
				write_lcd_point(12,1);
				write_lcd_shuzi_sanwei(5,1,(ad_dlz[1]));
				write_lcd_point(13,1);
				write_lcd_shuzi_sanwei(6,1,(ad_dlz[2]));
				write_lcd_point(14,1);
				write_lcd_shuzi_sanwei(7,1,dyzhi);
*/
				switch(set_wz)
				{
					case 3:
				write_lcd_shuzi_sanwei(3,1,(ad_dlz[0]));
				write_lcd_point(12,1);
				write_lcd_shuzi_sanwei(5,1,(ad_dlz[1]));
				write_lcd_point(13,1);
				write_lcd_shuzi_sanwei(6,1,(ad_dlz[2]));
				write_lcd_point(14,1);
					write_lcd_shuzi_sanwei(7,2,dyzhi);
					break;
					case 2:
				write_lcd_shuzi_sanwei(3,1,(ad_dlz[0]));
				write_lcd_point(12,1);
				write_lcd_shuzi_sanwei(5,1,(ad_dlz[1]));
				write_lcd_point(13,1);
				write_lcd_shuzi_sanwei(7,1,dyzhi);
					write_lcd_shuzi_sanwei(6,2,(ad_dlz[2]));
					write_lcd_point(14,2);
					break;
					case 1:
				write_lcd_shuzi_sanwei(3,1,(ad_dlz[0]));
				write_lcd_point(12,1);
				write_lcd_shuzi_sanwei(6,1,(ad_dlz[2]));
				write_lcd_point(14,1);
				write_lcd_shuzi_sanwei(7,1,dyzhi);
					write_lcd_shuzi_sanwei(5,2,(ad_dlz[1]));
					write_lcd_point(13,2);
					break;
					case 0:
				write_lcd_shuzi_sanwei(5,1,(ad_dlz[1]));
				write_lcd_point(13,1);
				write_lcd_shuzi_sanwei(6,1,(ad_dlz[2]));
				write_lcd_point(14,1);
				write_lcd_shuzi_sanwei(7,1,dyzhi);
					write_lcd_shuzi_sanwei(3,2,(ad_dlz[0]));
					write_lcd_point(12,2);
					break;
				}
				time_1s=0;
				ad_tdbz=0;
			}
		}

		if(key_zhi==64)
		{
			baocun_bz=1;
			break;
		}

	//	if(ss_js>0&&key_zhi==0&&time_100ms==1) 
if(time_100ms==1) //ss_js>0&&
		{
	//		shanshuo();
			if(ss_count1==5)
			{
				switch(set_wz)
				{
					case 3:

					write_lcd_shuzi_sanwei(7,3,dyzhi);
					break;
					case 2:

					write_lcd_shuzi_sanwei(6,3,(ad_dlz[2]));
					write_lcd_point(14,3);
					break;
					case 1:

					write_lcd_shuzi_sanwei(5,3,(ad_dlz[1]));
					write_lcd_point(13,3);
					break;
					case 0:

					write_lcd_shuzi_sanwei(3,3,(ad_dlz[0]));
					write_lcd_point(12,3);
					break;
				}
			}
			if(ss_count1==10)
			{
				switch(set_wz)
				{
					case 3:

					write_lcd_shuzi_sanwei(7,4,dyzhi);
					break;
					case 2:

					write_lcd_shuzi_sanwei(6,4,(ad_dlz[2]));
					write_lcd_point(14,4);
					break;
					case 1:

					write_lcd_shuzi_sanwei(5,4,(ad_dlz[1]));
					write_lcd_point(13,4);
					break;
					case 0:

					write_lcd_shuzi_sanwei(3,4,(ad_dlz[0]));
					write_lcd_point(12,4);
					break;
				}
				ss_count1=0;
			}
	//		ss_js++;
			ss_count1++;
			time_100ms=0;
		}
ClrWdt();
	}
	if(	baocun_bz==1)
	{
		HDduanWriteI2C(0xa0,0x01,0x57,set_ui_zhi,4);
		DelayMS(10);
	}
	else
	{
		HDSequentialReadI2C(0xa0,0x01,0x57,set_ui_zhi,4);
		DelayMS(10);
	}
	write_lcd_shuzi_sanwei(3,1,((yushetime[gongzuo[1]]*10)-(gongzuo[5]*60+gongzuo[6])/6));
	write_lcd_point(12,1);
			//		write_lcd_shuzi_sanwei(4,1,(gongzuo[3]));
	write_lcd_shuzi_sanwei(5,1,wd_yd);
	write_lcd_point(13,1);
	write_lcd_shuzi_sanwei(6,1,sd_yd);
	write_lcd_point(14,1);

}
