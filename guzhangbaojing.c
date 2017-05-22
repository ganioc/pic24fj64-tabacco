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
//extern uint16 time_zong;				//总时间
extern uchar time_sec;
//extern uchar gzzt;						//工作状态
//extern uchar hkdw;						//烘烤段位
extern uint16 hw_shijian;
//extern uint16 time_dqd;					//当前段的时间计数
extern uint16 WD[4];
extern uchar gongzuo[9];
extern uchar set_bz;
extern uchar sound_duanl;					//声音段数
extern uchar key256;
extern uchar dwxcbc;
extern uint16 ad_dlz[3];
extern uchar xianshi_bz[5];				//显示的标志 用来控制第一次显示和不重复显示

extern unsigned char zishe_sector[39];
extern unsigned char xiabu_sector[39];
extern unsigned char zhongbu_sector[39];
extern unsigned char shangbu_sector[39];
extern uchar ok_bz;
extern uchar ok_bz_cs;
extern uchar ad_ps_bz,ad_count,ad_kgd,psm_wz;//,ps_dl

extern uchar pianwencanshu[5];
extern uchar set_pwcs;


extern uchar fengjibaohucanshu[4];
extern uchar set_fjbhcs;

extern uint16 dianyabaohucanshu[4];		//电压保护各项参数内容
extern uchar set_dybhcs;								//电压参数选择
extern uchar ls_dy[6];

extern uchar guzhanghuifucanshu[2];		//故障恢复各项参数内容
extern uchar set_gzhfcs;								//故障恢复参数选择

extern uchar paishimencanshu[4];		//排湿门各项参数内容
extern uchar set_psmcs;	

extern uchar set_gncs_all;
extern uchar gncs_set_bz;
extern uchar san_dan_sign;				//三、单相风机标志1：三相，0单项
extern uint16 baojingbz[3];				//报警标志
extern uchar fjsd;						//风机速度
extern uint16 pianwenjishi;				//偏温报警计时延时
extern uchar pianwanbaojingbz;			//偏温报警标志
extern uint16 fengjigzjishi,fengjihuifucs;				//风机故障恢复计时,风机恢复次数
extern uchar fengjikgbz;								//风机开关标志
extern uint16 dyzhi;									//电压值
extern uint16 dianyachaoxianjishi;					//电压超限计时
extern uchar fengjigzjs,fengjigzbhsj;			//风机过载计时，风机过载保护时间
extern uchar baojingjishizong;						//报警间隔时间

extern uchar shenyinpaixu[5];			//多段声音调用排序声音
extern uchar leijishenyinduanshu;				//累计还有多少段声音要读
extern uchar sound_qdbz;
extern uchar chaxun_bz;							//查询标志 是否在查询中
extern uint16 fengjiqxcs;							//风机缺项次数
extern uchar ds18b20_1bz;
extern uchar sound_i;
uchar ls_js001=0;
extern uchar sound_all[5][4];	
//各项报警声音预存数组分别【风机 温度 湿度 电压】【对应 段数 间隔时间 报警次数 响不响】
extern uchar soundtime,sound_qsbz,leiji;		//声音计时，声音报警起始标志，每次累计报警次数
extern uchar soundbusytime;
extern uchar fjqh_sign;
extern uchar fengjiqishi_bz;				//风机起始开关标志
extern uchar bg_bj_count,bg_bj_bz;					//背光报警计时背，光报警标志

void fengjikaikongzhi(void)
{
	if((fengjigzjishi>=fengjibaohucanshu[3])&&fengjikgbz==0&&fengjiqishi_bz==0)
	{
	//	PCF8574_chose(0,1);				//循环风机
JDQ_FENGJI_ON;
	//	baojingbz[2]=1;
		fengjikgbz=1;
fengjiqxcs=0;
	write_lcd_zi(4,1);
		if(fjqh_sign)
		{

			write_lcd_zi(5,1);		//关闭“自动”显示	
		}
		else 
		{
			write_lcd_zi(5,0);		//开启“自动”显示
		}
	}
	if((fengjigzjishi>=guzhanghuifucanshu[0]*60)&&(fengjikgbz==2||fengjikgbz==4))
	{
	//	PCF8574_chose(0,1);				//循环风机
JDQ_FENGJI_ON;
	//	baojingbz[2]=1;
		fengjikgbz=1;
		fengjiqxcs=0;
		if(fjqh_sign)
		{

			write_lcd_zi(5,1);		//关闭“自动”显示	
		}
		else 
		{
			write_lcd_zi(5,0);		//开启“自动”显示
		}
	}

}



void fengjiguankongzhi(void)
{
	uchar ls_dl[3]={0,0,0},i,j,ls=0;
	if(baojingbz[1]==2)
	{
	//	PCF8574_chose(0,0);				//循环风机关
JDQ_FENGJI_OFF;
		fengjigzjishi=0;				//风机的故障计时
		fengjihuifucs++;
		fengjikgbz=2;
		if(fengjihuifucs>guzhanghuifucanshu[1])	fengjikgbz=3;
		baojingbz[1]=22;
		write_lcd_zi(4,0);
		write_lcd_zi(6,0);
		write_lcd_zi(7,0);
		write_lcd_zi(19,0);
		write_lcd_kuang(47,0);
		write_lcd_zi(20,1);
		write_lcd_kuang(48,1);
JDQ_FENGJI_OFF;
	//0		shenyinpaixu[leijishenyinduanshu]=56;
	//0					leijishenyinduanshu++;
/*
		if(sound_all[0][4]==0)
		{
			sound_all[0][0]=56;
			sound_all[0][1]=10;
			sound_all[0][2]++;
			sound_all[0][3]=1;
		}
		else
		{
			sound_all[0][2]++;
		}
*/
shengyingexiang_jiaru(0,56,10);
	}
else
{
//0	 shengyin_huifu_panduan(56);
shengyingexiang_huifu(0,56);
/*
			sound_all[0][0]=0;
			sound_all[0][1]=0;
			sound_all[0][2]=0;
			sound_all[0][3]=0;
*/
}
	if(baojingbz[1]==1)
	{
		baojingbz[1]=11;
		if(ad_dlz[0]/10>fengjibaohucanshu[fjsd])
			ls_dl[0]=ad_dlz[0]/10-fengjibaohucanshu[fjsd];
//if(san_dan_sign==1){
		if(ad_dlz[1]/10>fengjibaohucanshu[fjsd])
			ls_dl[1]=ad_dlz[1]/10-fengjibaohucanshu[fjsd];
		if(ad_dlz[2]/10>fengjibaohucanshu[fjsd])
			ls_dl[2]=ad_dlz[2]/10-fengjibaohucanshu[fjsd];
			for(j=0;j<2;j++)
			{
				for(i=j+1;i<3;i++)
				{
					if(ls_dl[j]<ls_dl[i])
					{
						ls=ls_dl[i];
						ls_dl[i]=ls_dl[j];
						ls_dl[j]=ls;
					}
				}
			}
	//	}
		if(ls_dl[0]*100/fengjibaohucanshu[fjsd]>60)	fengjigzbhsj=8;
		else fengjigzbhsj=((65-ls_dl[0])*20/fengjibaohucanshu[fjsd]);
		fengjigzjs=0;

	}
	if(baojingbz[1]==11&&fengjigzjs>=fengjigzbhsj)
	{
	//	PCF8574_chose(0,0);				//循环风机
JDQ_FENGJI_OFF;
		fengjigzjishi=0;
		fengjihuifucs++;
		fengjikgbz=4;
		if(fengjihuifucs>guzhanghuifucanshu[1])	fengjikgbz=5;
		write_lcd_zi(4,0);
		write_lcd_zi(6,0);
		write_lcd_zi(7,0);
		write_lcd_zi(20,0);
		write_lcd_kuang(48,0);
		write_lcd_zi(19,1);
		write_lcd_kuang(47,1);
	//0		shenyinpaixu[leijishenyinduanshu]=57;
	//0					leijishenyinduanshu++;
shengyingexiang_jiaru(0,57,10);
		baojingbz[1]=21;
	}
else if(baojingbz[1]!=21)shengyingexiang_huifu(0,57);//shengyin_huifu_panduan(57);

}


void fengjiguankongzhi_two(void)
{
	uchar ls_dl[3]={0,0,0},i,j,ls=0;
	if(baojingbz[1]==2)
	{
	//	PCF8574_chose(0,0);				//循环风机关
JDQ_FENGJI_OFF;
		fengjigzjishi=0;				//风机的故障计时
		fengjihuifucs++;
		fengjikgbz=2;
		if(fengjihuifucs>guzhanghuifucanshu[1])	fengjikgbz=3;
		baojingbz[1]=22;
		write_lcd_zi(4,0);
		write_lcd_zi(6,0);
		write_lcd_zi(7,0);
		write_lcd_zi(19,0);
		write_lcd_kuang(47,0);
		write_lcd_zi(20,1);
		write_lcd_kuang(48,1);
	//0		shenyinpaixu[leijishenyinduanshu]=56;
	//0					leijishenyinduanshu++;
/*
		if(sound_all[0][4]==0)
		{
			sound_all[0][0]=56;
			sound_all[0][1]=10;
			sound_all[0][2]++;
			sound_all[0][3]=1;
		}
		else
		{
			sound_all[0][2]++;
		}
*/
shengyingexiang_jiaru(0,56,10);
	}
else
{
//0	 shengyin_huifu_panduan(56);
shengyingexiang_huifu(0,56);
/*
			sound_all[0][0]=0;
			sound_all[0][1]=0;
			sound_all[0][2]=0;
			sound_all[0][3]=0;
*/
}
	if(baojingbz[1]==1)
	{
		baojingbz[1]=11;
		if(ad_dlz[0]/10>fengjibaohucanshu[fjsd])
			ls_dl[0]=ad_dlz[0]/10-fengjibaohucanshu[fjsd];
/*
if(san_dan_sign==1){
		if(ad_dlz[1]/10>fengjibaohucanshu[fjsd])
			ls_dl[1]=ad_dlz[1]/10-fengjibaohucanshu[fjsd];
		if(ad_dlz[2]/10>fengjibaohucanshu[fjsd])
			ls_dl[2]=ad_dlz[2]/10-fengjibaohucanshu[fjsd];
			for(j=0;j<2;j++)
			{
				for(i=j+1;i<3;i++)
				{
					if(ls_dl[j]<ls_dl[i])
					{
						ls=ls_dl[i];
						ls_dl[i]=ls_dl[j];
						ls_dl[j]=ls;
					}
				}
			}
		}
*/
		if(ls_dl[0]*100/fengjibaohucanshu[fjsd]>60)	fengjigzbhsj=8;
		else fengjigzbhsj=((65-ls_dl[0])*20/fengjibaohucanshu[fjsd]);
		fengjigzjs=0;

	}
	if(baojingbz[1]==11&&fengjigzjs>=fengjigzbhsj)
	{
	//	PCF8574_chose(0,0);				//循环风机
JDQ_FENGJI_OFF;
		fengjigzjishi=0;
		fengjihuifucs++;
		fengjikgbz=4;
		if(fengjihuifucs>guzhanghuifucanshu[1])	fengjikgbz=5;
		write_lcd_zi(4,0);
		write_lcd_zi(6,0);
		write_lcd_zi(7,0);
		write_lcd_zi(20,0);
		write_lcd_kuang(48,0);
		write_lcd_zi(19,1);
		write_lcd_kuang(47,1);
	//0		shenyinpaixu[leijishenyinduanshu]=57;
	//0					leijishenyinduanshu++;
shengyingexiang_jiaru(0,57,10);
		baojingbz[1]=21;
	}
else if(baojingbz[1]!=21)shengyingexiang_huifu(0,57);//shengyin_huifu_panduan(57);

}

void fengjibaojing(void)
{
	uchar ls_dl=0,ls_bz=0;
	if(fengjikgbz==1)
	{
		if(baojingbz[1]!=11)
		{
			baojingbz[1]=0;
		}
		else ls_bz=1;
		//ls_dl=(ad_dlz[0]/10+ad_dlz[2]/10)/2;
		//if(ls_dl>25)fjsd=0;
		//if(ls_dl<=25)fjsd=1;
		if(ad_dlz[0]/10>fengjibaohucanshu[fjsd]||ad_dlz[1]/10>fengjibaohucanshu[fjsd]||ad_dlz[2]/10>fengjibaohucanshu[fjsd])
		{
			if(baojingbz[1]!=11)
			{
				baojingbz[1]=1;
			}
			else ls_bz=ls_bz+2;
		}
		if((ad_dlz[0]<100&&ad_dlz[1]>150&&ad_dlz[2]>150)||(ad_dlz[0]>150&&ad_dlz[1]<100&&ad_dlz[2]>150)||(ad_dlz[0]>150&&ad_dlz[1]>150&&ad_dlz[2]<100))
		{
			fengjiqxcs++;
		}
		else fengjiqxcs=0;
		if(fengjiqxcs>2000)	baojingbz[1]=2;
		if(ad_dlz[0]<20&&ad_dlz[1]<20&&ad_dlz[2]<20)
		{
			baojingbz[1]=3;
			fjsd=3;
//0		shengyin_chongfu_panduan(58);
shengyingexiang_jiaru(0,58,10);
//shengyingexiang_jiaru(2,64,10);
//shengyingexiang_jiaru(1,62,10);
/*
			while(leijishenyinduanshu-j!=0)
			{
				if(shenyinpaixu[leijishenyinduanshu-j]==58) ls_bz2=1;
				j++;
			//	leijishenyinduanshu-j;
			}
			if(ls_bz2!=1||leijishenyinduanshu==0)
			{
				shenyinpaixu[leijishenyinduanshu]=58;
				leijishenyinduanshu++;
			}
*/
		}
		if(baojingbz[1]!=3)	shengyingexiang_huifu(0,58);		//shengyin_huifu_panduan(58);
//		if(baojingbz[0]!=2)fengjiqxcs=0;
		if(ls_bz==1&&baojingbz[1]!=1&&baojingbz[1]!=2&&baojingbz[1]!=3)
		{
			baojingbz[1]=0;
			fengjihuifucs=0;

		}
	//	write_lcd_zi(4,0);
		if(fjsd==0&&xianshi_bz[0]!=1){write_lcd_zi(6,1);write_lcd_zi(7,0);	write_lcd_zi(4,1);xianshi_bz[0]=1;}
		if(fjsd==1&&xianshi_bz[0]!=2){write_lcd_zi(7,1);write_lcd_zi(6,0);	write_lcd_zi(4,1);xianshi_bz[0]=2;}
		if(fjsd==3&&xianshi_bz[0]!=3)
		{
			write_lcd_zi(7,0);
			write_lcd_zi(6,0);
			write_lcd_zi(4,1);
			write_lcd_zi(20,0);
			write_lcd_kuang(48,0);
			write_lcd_zi(19,0);
			write_lcd_kuang(47,0);
			xianshi_bz[0]=3;
		}
//		write_lcd_zi(20,0);
//		write_lcd_kuang(48,0);
//	write_lcd_shuzi_sanwei(4,1,baojingbz[1]);
//	DelayMS(1000);
		if(baojingbz[1]==0)
		{
			fengjihuifucs=0;
			write_lcd_zi(20,0);
			write_lcd_kuang(48,0);
			write_lcd_zi(19,0);
			write_lcd_kuang(47,0);
		}
	}
}

void fengjibaojing_two(void)
{
	uchar ls_dl=0,ls_bz=0;
	if(fengjikgbz==1)
	{
		if(baojingbz[1]!=11)
		{
			baojingbz[1]=0;
		}
		else ls_bz=1;
		//ls_dl=(ad_dlz[0]/10+ad_dlz[2]/10)/2;
		//if(ls_dl>25)fjsd=0;
		//if(ls_dl<=25)fjsd=1;
	//	if(ad_dlz[0]/10>fengjibaohucanshu[fjsd]||ad_dlz[1]/10>fengjibaohucanshu[fjsd]||ad_dlz[2]/10>fengjibaohucanshu[fjsd])
		if(ad_dlz[0]/10>fengjibaohucanshu[fjsd])
		{
			if(baojingbz[1]!=11)
			{
				baojingbz[1]=1;
			}
			else ls_bz=ls_bz+2;
		}
/*
		if((ad_dlz[0]<10&&ad_dlz[1]>15&&ad_dlz[2]>15)||(ad_dlz[0]>15&&ad_dlz[1]<10&&ad_dlz[2]>15)||(ad_dlz[0]>15&&ad_dlz[1]>15&&ad_dlz[2]<10))
		{
			fengjiqxcs++;
		}
		else fengjiqxcs=0;
		if(fengjiqxcs>2000)	baojingbz[1]=2;
*/
//		if(ad_dlz[0]<20&&ad_dlz[1]<20&&ad_dlz[2]<20)
		if(ad_dlz[0]<20)
		{
			baojingbz[1]=3;
			fjsd=3;
//0		shengyin_chongfu_panduan(58);
shengyingexiang_jiaru(0,58,10);
//shengyingexiang_jiaru(2,64,10);
//shengyingexiang_jiaru(1,62,10);
/*
			while(leijishenyinduanshu-j!=0)
			{
				if(shenyinpaixu[leijishenyinduanshu-j]==58) ls_bz2=1;
				j++;
			//	leijishenyinduanshu-j;
			}
			if(ls_bz2!=1||leijishenyinduanshu==0)
			{
				shenyinpaixu[leijishenyinduanshu]=58;
				leijishenyinduanshu++;
			}
*/
		}
		if(baojingbz[1]!=3)	shengyingexiang_huifu(0,58);		//shengyin_huifu_panduan(58);
//		if(baojingbz[0]!=2)fengjiqxcs=0;
		if(ls_bz==1&&baojingbz[1]!=1&&baojingbz[1]!=2&&baojingbz[1]!=3)
		{
			baojingbz[1]=0;
			fengjihuifucs=0;

		}
	//	write_lcd_zi(4,0);
		if(fjsd==0&&xianshi_bz[0]!=1){write_lcd_zi(6,1);write_lcd_zi(7,0);	write_lcd_zi(4,1);xianshi_bz[0]=1;}
		if(fjsd==1&&xianshi_bz[0]!=2){write_lcd_zi(7,1);write_lcd_zi(6,0);	write_lcd_zi(4,1);xianshi_bz[0]=2;}
		if(fjsd==3&&xianshi_bz[0]!=3)
		{
			write_lcd_zi(7,0);
			write_lcd_zi(6,0);
			write_lcd_zi(4,1);
			write_lcd_zi(20,0);
			write_lcd_kuang(48,0);
			write_lcd_zi(19,0);
			write_lcd_kuang(47,0);
			xianshi_bz[0]=3;
		}
//		write_lcd_zi(20,0);
//		write_lcd_kuang(48,0);
//	write_lcd_shuzi_sanwei(4,1,baojingbz[1]);
//	DelayMS(1000);
		if(baojingbz[1]==0)
		{
			fengjihuifucs=0;
			write_lcd_zi(20,0);
			write_lcd_kuang(48,0);
			write_lcd_zi(19,0);
			write_lcd_kuang(47,0);
		}
	}
}
/*
void pianwenbaojing(void)
{
	if(pianwenjishi>pianwencanshu[2]*60||pianwanbaojingbz==1)
	{
		pianwanbaojingbz=1;
		if(baojingbz[0]==16)
		{
	//		shenyinpaixu[leijishenyinduanshu]=61;
	//		leijishenyinduanshu++;
//0		shengyin_chongfu_panduan(61);
shengyingexiang_jiaru(1,61,50);
		}
		else shengyingexiang_huifu(1,61);	//0shengyin_huifu_panduan(61);
 if(baojingbz[0]>=8&&baojingbz[0]<16)
		{
		//	write_lcd_zi(18,1);
		//	write_lcd_kuang(46,1);
	//		shenyinpaixu[leijishenyinduanshu]=64;
	//					leijishenyinduanshu++;
//0		shengyin_chongfu_panduan(64);
shengyingexiang_jiaru(2,64,50);
			if(baojingbz[0]-8==1)
			{
	//		shenyinpaixu[leijishenyinduanshu]=63;
	//						leijishenyinduanshu++;
//0		shengyin_chongfu_panduan(63);
shengyingexiang_jiaru(1,63,50);
			}
			else 
			{
//0		shengyin_huifu_panduan(63);
shengyingexiang_huifu(1,63);
			if(baojingbz[0]-8==2)
				{

	//		shenyinpaixu[leijishenyinduanshu]=62;
	//						leijishenyinduanshu++;
//0		shengyin_chongfu_panduan(62);
shengyingexiang_jiaru(1,62,50);
				}
			else shengyingexiang_huifu(1,62);			//0	shengyin_huifu_panduan(62);
			}

		}
		else shengyingexiang_huifu(2,64);//0			shengyin_huifu_panduan(64);
if(baojingbz[0]>=4&&baojingbz[0]<8)
		{
		//	write_lcd_zi(18,1);
		//	write_lcd_kuang(46,1);
	//		shenyinpaixu[leijishenyinduanshu]=65;
		//				leijishenyinduanshu++;
//0		shengyin_chongfu_panduan(65);
shengyingexiang_jiaru(2,65,50);
			if(baojingbz[0]-4==1)
			{
	//		shenyinpaixu[leijishenyinduanshu]=63;
	//						leijishenyinduanshu++;
//0		shengyin_chongfu_panduan(63);
shengyingexiang_jiaru(1,63,50);
			}
			else
			{
				if(baojingbz[0]-4==2)
				{
//0		shengyin_huifu_panduan(63);
shengyingexiang_huifu(1,63);
	//		shenyinpaixu[leijishenyinduanshu]=62;
	//						leijishenyinduanshu++;

	//0			shengyin_chongfu_panduan(62);
shengyingexiang_jiaru(1,62,50);
				}
				else shengyingexiang_huifu(1,62);			//0 shengyin_huifu_panduan(62);
			}
		}
		else shengyingexiang_huifu(2,65);			//0 shengyin_huifu_panduan(65);
if(baojingbz[0]==1)
		{
		//	write_lcd_zi(18,1);
		//	write_lcd_kuang(46,1);
	//		shenyinpaixu[leijishenyinduanshu]=63;
	//					leijishenyinduanshu++;
//0		shengyin_chongfu_panduan(63);
shengyingexiang_jiaru(1,63,50);
		}
		else shengyingexiang_huifu(1,63);			//0 shengyin_huifu_panduan(63);
if(baojingbz[0]==2)
		{
		//	write_lcd_zi(18,1);
		//	write_lcd_kuang(46,1);
	//		shenyinpaixu[leijishenyinduanshu]=62;
	//					leijishenyinduanshu++;
//0		shengyin_chongfu_panduan(62);
shengyingexiang_jiaru(1,62,50);
		}
else shengyingexiang_huifu(1,62);			//0 shengyin_huifu_panduan(62);
		if(xianshi_bz[1]!=1)
		{
			xianshi_bz[1]=1;
			write_lcd_zi(18,1);
			write_lcd_kuang(46,1);
		}
	}
}
*/
void pianwenbaojing(void)
{
	if(pianwenjishi>pianwencanshu[2]*60||pianwanbaojingbz==1)
	{
		pianwanbaojingbz=1;
		if(baojingbz[0]==16)
		{
			shengyingexiang_jiaru(1,61,50);
		}
		else
		{ 
			shengyingexiang_huifu(1,61);
			if(baojingbz[0]>=8&&baojingbz[0]<16)
			{
				shengyingexiang_jiaru(2,65,50);
				if(baojingbz[0]-8==1)
				{
					shengyingexiang_jiaru(1,62,50);
				}
				else 
				{
					shengyingexiang_huifu(1,62);
					if(baojingbz[0]-8==2)
					{
						shengyingexiang_jiaru(1,63,50);
					}
					else shengyingexiang_huifu(1,63);
				}	
			}
			else
			{
				shengyingexiang_huifu(2,65);
				if(baojingbz[0]>=4&&baojingbz[0]<8)
				{
					shengyingexiang_jiaru(2,64,50);
					if(baojingbz[0]-4==1)
					{
						shengyingexiang_jiaru(1,62,50);
					}
					else
					{
						shengyingexiang_huifu(1,62);
						if(baojingbz[0]-4==2)
						{
							shengyingexiang_jiaru(1,63,50);
						}
						else shengyingexiang_huifu(1,63);
					}
				}
				else
				{
					shengyingexiang_huifu(2,64);
					if(baojingbz[0]==1)
					{
						shengyingexiang_jiaru(1,62,50);
					}
					else
					{
						shengyingexiang_huifu(1,62);
						if(baojingbz[0]==2)
						{
							shengyingexiang_jiaru(1,63,50);
						}
						else shengyingexiang_huifu(1,63);
					}
				}
			}
		}
		if(xianshi_bz[1]!=1)
		{
			xianshi_bz[1]=1;
			write_lcd_zi(18,1);
			write_lcd_kuang(46,1);
		}
	}
}
void pianwenpanduan(void)
{
	uchar ls_bz=0,i,j;
	if((pianwencanshu[0]!=56||pianwencanshu[1]!=56)&&ds18b20_1bz==2)
	{
		if(baojingbz[0]!=0)	ls_bz=1;
			baojingbz[0]=0;
		if(WD[0]!=65534)
		{
			if(WD[0]>wd_yd)
			{
				if(WD[0]-wd_yd>=pianwencanshu[0])baojingbz[0]=baojingbz[0]+1;
				else shengyingexiang_huifu(1,63);
			}
			else
			{
				if(wd_yd-WD[0]>=pianwencanshu[0])baojingbz[0]=baojingbz[0]+2;
				else shengyingexiang_huifu(1,62);
			}
		}
		if(WD[1]!=65534)
		{
			if(WD[1]>sd_yd)
			{
				if(WD[1]-sd_yd>=pianwencanshu[1])baojingbz[0]=baojingbz[0]+4;
				else shengyingexiang_huifu(2,65);
			}
			else
			{
				if(sd_yd-WD[1]>=pianwencanshu[1])baojingbz[0]=baojingbz[0]+8;
				else shengyingexiang_huifu(2,64);
			}
		}
			if(WD[0]==65534||WD[1]==65534||WD[2]==65534||WD[3]==65534)baojingbz[0]=16;
		if(ls_bz==0&&baojingbz[0]!=0)
			pianwenjishi=0;
		if(baojingbz[0]==0&&xianshi_bz[1]!=0)	
		{
			for(i=1;i<3;i++)
			{
				for(j=0;j<4;j++)
				{
					sound_all[i][j]=0;
				}
			}
			xianshi_bz[1]=0;
			pianwanbaojingbz=0;
	//		if(	xianshi_bz[0]!=0)
			write_lcd_zi(18,0);
			write_lcd_kuang(46,0);
		}
	}
}

void dianyabaojing(void)
{
	if(baojingbz[2]!=0)
	{
		if(baojingbz[2]==2&&dianyachaoxianjishi>dianyabaohucanshu[2]*60)
		{
//	PCF8574_chose(0,0);				//循环风机关
JDQ_FENGJI_OFF;
			shenyinpaixu[leijishenyinduanshu]=60;
						leijishenyinduanshu++;
			shengyingexiang_jiaru(3,60,10);
//PCF8574_chose(2,0);
//JDQ_PAISHI_MIN_OFF;
	Discharge_wet_OFF();
//	PCF8574_chose(4,0);
JDQ_ZHURAN_OFF;
		}
		if(baojingbz[2]==3&&dianyachaoxianjishi>dianyabaohucanshu[2]*60)
		{
			shenyinpaixu[leijishenyinduanshu]=59;
						leijishenyinduanshu++;
			shengyingexiang_jiaru(3,59,10);
//	PCF8574_chose(0,0);				//循环风机关
JDQ_FENGJI_OFF;
//PCF8574_chose(2,0);
//JDQ_PAISHI_MIN_OFF;
	Discharge_wet_OFF();
//	PCF8574_chose(4,0);
JDQ_ZHURAN_OFF;
		}
		if(baojingbz[2]==4&&dianyachaoxianjishi>8)
		{
			shenyinpaixu[leijishenyinduanshu]=60;
						leijishenyinduanshu++;
			shengyingexiang_jiaru(3,60,10);
//	PCF8574_chose(0,0);				//循环风机关
JDQ_FENGJI_OFF;
//PCF8574_chose(2,0);
//JDQ_PAISHI_MIN_OFF;
	Discharge_wet_OFF();
//	PCF8574_chose(4,0);
JDQ_ZHURAN_OFF;
		}
	}
}

void dianyapanduan(void)
{
		if(baojingbz[2]==0)
		{
			dianyachaoxianjishi=0;
		}
		baojingbz[2]=0;
		if(dyzhi>dianyabaohucanshu[0])baojingbz[2]=2;
		else shengyingexiang_huifu(3,60);
		if(dyzhi<dianyabaohucanshu[1])baojingbz[2]=3;
		else shengyingexiang_huifu(3,59);
		if(dyzhi>dianyabaohucanshu[3])baojingbz[2]=4;
		else shengyingexiang_huifu(1,60);
}

void baojing(void)
{
	uchar i=0;
	if(baojingbz[2]==0&&baojingbz[1]==0&&baojingbz[0]==0)
	{
		baojingjishizong=0;
	}
	if(baojingjishizong==50)
	{
		dianyabaojing();
		pianwenbaojing();				//温度报警	
		baojingjishizong=0;	
		sound_qdbz=1;
	}
	else if(baojingjishizong%10==0)
	{
		while(leijishenyinduanshu-i!=0)
		{
			if(shenyinpaixu[leijishenyinduanshu-i]==58&&ls_js001==0)
			{
				sound_duanl=58;
ls_js001=1;
			//	sound_i=leijishenyinduanshu;
			}
			i++;
		}
	}
if(baojingjishizong%10==8)ls_js001=0;
}

void huifu(void)
{
	uchar i=0,j=0;
	if(key_mid==64&&set_bz==0&&gncs_set_bz==0&&chaxun_bz==0)
	{
		baojingbz[2]=0;
		baojingbz[1]=0;
		baojingbz[0]=0;
		bg_bj_bz=0;
		dianyachaoxianjishi=0;
		pianwenjishi=0;
		pianwanbaojingbz=0;
		fengjikgbz=0;
		fengjigzjishi=0;
			write_lcd_zi(18,0);
			write_lcd_kuang(46,0);
			write_lcd_zi(20,0);
			write_lcd_kuang(48,0);
			write_lcd_zi(19,0);
			write_lcd_kuang(47,0);
xianshi_bz[0]=0;
xianshi_bz[1]=0;
		for(i=0;i<5;i++)
		{
			for(j=0;j<4;j++)
			{
				sound_all[i][j]=0;
			}
		}
	}
}

void shengyin_chongfu_panduan(uchar sound_duan)		//old
{
	uchar j=0,ls_bz2=0;
			while(leijishenyinduanshu-j!=0)
			{
				if(shenyinpaixu[leijishenyinduanshu-j]==sound_duan) ls_bz2=1;
				j++;
			//	leijishenyinduanshu-j;
			}
			if(ls_bz2!=1||leijishenyinduanshu==0)
			{
				shenyinpaixu[leijishenyinduanshu]=sound_duan;
				leijishenyinduanshu++;
			}
}

void shengyin_huifu_panduan(uchar sound_duan)		//old
{
	uchar j=0,ls_bz2=0,ls_bl=0;
	while(leijishenyinduanshu-j!=0)
	{
		if(shenyinpaixu[leijishenyinduanshu-j]==sound_duan)
		{
			ls_bz2=1;
			ls_bl=leijishenyinduanshu-j;
		}
		j++;
	//	leijishenyinduanshu-j;
	}
			if(ls_bz2==1)
			{
				for(j=ls_bl;j<leijishenyinduanshu;j++)
				{
					shenyinpaixu[j]=shenyinpaixu[j+1];
				}
				shenyinpaixu[leijishenyinduanshu]=0;
				leijishenyinduanshu--;
			}
}

void shengyingexiang_jiaru(uchar leibie,uchar duan,uchar shijian)//new
{
		if(sound_all[leibie][3]==0)
		{
			sound_all[leibie][0]=duan;
			sound_all[leibie][1]=shijian;
			sound_all[leibie][2]++;
			sound_all[leibie][3]=1;
		}
		else 
		{
			sound_all[leibie][2]++;
		}
		if(sound_all[leibie][2]==60)sound_all[leibie][1]=50;
}

void shengyingexiang_huifu(uchar leibie,uchar duan)		//new
{
		if(sound_all[leibie][0]==duan&&sound_all[leibie][3]!=0)
		{
			sound_all[leibie][0]=0;
			sound_all[leibie][1]=0;
			sound_all[leibie][2]=0;
			sound_all[leibie][3]=0;
		}
}

void shengyinbaojing(void)
{
	uchar i=0;
//	uchar 
	if(sound_qsbz==0)
	{
		for(i=0;i<5;i++)
		{
			if(sound_all[i][1]!=0)
			{
				if(soundtime%sound_all[i][1]==0&&sound_all[i][3]==1) 
				{
					sound_all[i][3]=2;
		
				}
			}
		}
		sound_qsbz=1;
	}
/*
	if(SOUND_BUSY&&sound_all[leiji][3]==2&&sound_qsbz==1) 
	{
		sound_duanl=sound_all[leiji][0];
		leiji++;
	}
	else if(SOUND_BUSY&&sound_qsbz==1)leiji++;
*/
	if(SOUND_BUSY==0)soundbusytime=0;

	if(leiji==5)
	{
		for(i=0;i<5;i++)
		{
			if(sound_all[i][3]==2)
			sound_all[i][3]=1;
		}
//sound_duanl=0;
		sound_qsbz=0;
		leiji=0;
	}
	if(SOUND_BUSY&&sound_qsbz==1&&soundbusytime>2) 
	{
		if(sound_all[leiji][3]==2)		sound_duanl=sound_all[leiji][0];
		leiji++;
	}
	if(soundtime==50)soundtime=0;
}

void beiguang_baojing(void)
{
//	static uchar bg_bj_bz=0;
	if(baojingbz[0]!=0||baojingbz[1]!=0||baojingbz[2]!=0)//
	{
		if(bg_bj_bz==0)
		{
			bg_bj_bz=1;
			bg_bj_count=0;
		//	LCD_BG2_EN; 
		//	LCD_BG_DIS;
		}
		if(bg_bj_bz==1&&bg_bj_count>180)
		{
			bg_bj_bz=2;
			LCD_BG2_EN; 
			LCD_BG_DIS;
		}
	}
	else
	{
		bg_bj_bz=0;
		LCD_BG_EN; 
		LCD_BG2_DIS;
	}	
}
