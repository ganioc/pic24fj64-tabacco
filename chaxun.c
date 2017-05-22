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
#include "chaxun.h"

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
extern uchar lskc;
extern uchar zsjs_bz;

extern unsigned char zishe_sector[39];
extern unsigned char xiabu_sector[39];
extern unsigned char zhongbu_sector[39];
extern unsigned char shangbu_sector[39];

extern uchar chaxunbz;		//当前电流查询标志
extern uchar chucunkc;							//储存到的烤次
extern uchar chaxunkc;							//查询到的烤次
extern uint16 chauxnwzcs[10][3];//前一个下标代表烤次 其中两个参数前一个为首地址次一个为尾地址,最后长度
extern uchar zhuanhuanfanhui[2];				//16位转化8位返回的两个8位值
extern uint16 chaxuncs;							//查询次数（段数）
extern uchar chaxun_bz;							//查询标志 是否在查询中
extern uint16 dyzhi;									//电压值
extern uint16 fa_232[10];
extern uchar ljkc;
//uchar mkc_ljcs[9]={0,0,0,0,0,0,0,0,0};				//每烤次的查询存数数量
void zhuanhuan_16to8 (uint16 zhi)
{
	zhuanhuanfanhui[1]=zhi%256;
	zhuanhuanfanhui[0]=zhi/256;
}

uint16 zhuanhuan_8to16 (uchar zhi1,uchar zhi2)
{
	uint16 zhuanhuanzhi=0;
	zhuanhuanzhi=zhi1*256+zhi2;
	return zhuanhuanzhi;
}
void chaxun_chunchu(void)
{
//	uint16 lsbl;
	uchar lschcsz[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uchar lsdzcs[8]={0,0,0,0,0,0,0,0};
	uchar lsdzcs1[6]={0,0,0,0,0,0,},i;
//	uint16 zongchunchucs=0;
//	uchar lswz[4]={0,0,0,0},i;
//	if(gongzuo[4]%10==0&&time_sec==0)
//	{
//	LED_SET_ON;
		zhuanhuan_16to8 (WD[0]);
		lschcsz[0]=zhuanhuanfanhui[0];
		lschcsz[1]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (WD[1]);
		lschcsz[2]=zhuanhuanfanhui[0];
		lschcsz[3]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (wd_yd);
		lschcsz[4]=zhuanhuanfanhui[0];
		lschcsz[5]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (sd_yd);
		lschcsz[6]=zhuanhuanfanhui[0];
		lschcsz[7]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (dyzhi);
		lschcsz[8]=zhuanhuanfanhui[0];
		lschcsz[9]=zhuanhuanfanhui[1];
		/*阶段时间分开值
		lschcsz[10]=gongzuo[5];
		lschcsz[11]=gongzuo[6];
		lschcsz[13]=yushetime[gongzuo[1]];
		*/
		lschcsz[12]=gongzuo[3];			//总时间小时

	//	lschcsz[13]=gongzuo[1];

		if(zsjs_bz==0)lschcsz[10]=((yushetime[gongzuo[1]]*10)-(gongzuo[5]*60+gongzuo[6])/6);		//阶段时间总值
		else lschcsz[10]=(gongzuo[5]*60+gongzuo[6])/6;
		lschcsz[14]=(gongzuo[7]|(time_tab[5]<<4));	//考次加月份
		lschcsz[11]=time_tab[2];					//时
		lschcsz[13]=time_tab[4];					//日
		lschcsz[15]=time_tab[6];					//年


	//		HDSequentialReadI2C(0xa0,0x01,(0x80+(chucunkc*6)),lsdzcs1,6);
	//		DelayMS(10);
	//	for(i=0;i<6;i++)
	//	{
	//		chauxnwzcs[chucunkc][i]=lsdzcs1[i];
	//	}
		if(gongzuo[7]==chucunkc)
		{

			zhuanhuan_16to8((chauxnwzcs[chucunkc][1]));
		}
		else
		{
		//	chauxnwzcs[gongzuo[7]][0]=chauxnwzcs[chucunkc][1];
			chauxnwzcs[gongzuo[7]][1]=chauxnwzcs[gongzuo[7]][0];
			chauxnwzcs[gongzuo[7]][2]=0;								//去除上一轮次的当前烤次数据
			chucunkc=gongzuo[7];
			if(ljkc!=8)ljkc=chucunkc;
		//	if()
			zhuanhuan_16to8 (chauxnwzcs[chucunkc][1]);
		}
		if(chauxnwzcs[chucunkc][1]<(chauxnwzcs[chucunkc][0]+0x0c80))
		{
			HDduanWriteI2C(0xa0,zhuanhuanfanhui[0],zhuanhuanfanhui[1],lschcsz,16);
			chauxnwzcs[chucunkc][1]=chauxnwzcs[chucunkc][1]+16;
			chauxnwzcs[chucunkc][2]++;
		}
	//	chauxnwzcs[gongzuo[7],1]++;
		DelayMS(10);
	//	for(i=0;i<3;i++)
	//	{
	//		lswz[i]=chauxnwzcs[i];
	//	}
	//	lswz[3]=chucunkc;
		zhuanhuan_16to8 (chauxnwzcs[chucunkc][0]);
		lsdzcs[0]=zhuanhuanfanhui[0];
		lsdzcs[1]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (chauxnwzcs[chucunkc][1]);
		lsdzcs[2]=zhuanhuanfanhui[0];
		lsdzcs[3]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (chauxnwzcs[chucunkc][2]);
		lsdzcs[4]=zhuanhuanfanhui[0];
		lsdzcs[5]=zhuanhuanfanhui[1];
	//	for(i=0;i<=chucunkc;i++)
	//	{
	//		zongchunchucs=dqcs+chauxnwzcs[i][2];
	//	}
		HDduanWriteI2C(0xa0,0x01,(0x80+(chucunkc*6)),lsdzcs,6);
		DelayMS(10);
//		for(i=0;i<3;i++)
//		{
//			fa_232[i]=chauxnwzcs[chucunkc][i];
//		}
		HDByteWriteI2C(0xa0,0x01,0xbf,chucunkc);
	//	HDByteWriteI2C(0xa0,0x01,0xd1,chucunkc);
		DelayMS(5);
//		if
//	}
//LED_SET_OFF;
}
/*
void chaxun_chunchu(void)
{
//	uint16 lsbl;
	uchar lschcsz[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uchar lsdzcs[8]={0,0,0,0,0,0,0,0};
	uchar lsdzcs1[6]={0,0,0,0,0,0,},i;
//	uint16 zongchunchucs=0;
//	uchar lswz[4]={0,0,0,0},i;
//	if(gongzuo[4]%10==0&&time_sec==0)
//	{

		zhuanhuan_16to8 (WD[0]);
		lschcsz[0]=zhuanhuanfanhui[0];
		lschcsz[1]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (WD[1]);
		lschcsz[2]=zhuanhuanfanhui[0];
		lschcsz[3]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (wd_yd);
		lschcsz[4]=zhuanhuanfanhui[0];
		lschcsz[5]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (sd_yd);
		lschcsz[6]=zhuanhuanfanhui[0];
		lschcsz[7]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (dyzhi);
		lschcsz[8]=zhuanhuanfanhui[0];
		lschcsz[9]=zhuanhuanfanhui[1];
		lschcsz[10]=gongzuo[5];
		lschcsz[11]=gongzuo[6];
		lschcsz[12]=gongzuo[3];
	//	lschcsz[13]=gongzuo[1];
		lschcsz[13]=yushetime[gongzuo[1]];
		lschcsz[14]=gongzuo[7];
	//		HDSequentialReadI2C(0xa0,0x01,(0x80+(chucunkc*6)),lsdzcs1,6);
	//		DelayMS(10);
	//	for(i=0;i<6;i++)
	//	{
	//		chauxnwzcs[chucunkc][i]=lsdzcs1[i];
	//	}
		if(gongzuo[7]==chucunkc)
		{

			zhuanhuan_16to8((chauxnwzcs[chucunkc][1]));
		}
		else
		{
			chauxnwzcs[gongzuo[7]][0]=chauxnwzcs[chucunkc][1];
			chauxnwzcs[gongzuo[7]][1]=chauxnwzcs[chucunkc][1];
			chucunkc=gongzuo[7];
			zhuanhuan_16to8 (chauxnwzcs[chucunkc][0]);
		}
		HDduanWriteI2C(0xa0,zhuanhuanfanhui[0],zhuanhuanfanhui[1],lschcsz,16);
		chauxnwzcs[chucunkc][1]=chauxnwzcs[chucunkc][1]+16;
		chauxnwzcs[chucunkc][2]++;
	//	chauxnwzcs[gongzuo[7],1]++;
		DelayMS(10);
	//	for(i=0;i<3;i++)
	//	{
	//		lswz[i]=chauxnwzcs[i];
	//	}
	//	lswz[3]=chucunkc;
		zhuanhuan_16to8 (chauxnwzcs[chucunkc][0]);
		lsdzcs[0]=zhuanhuanfanhui[0];
		lsdzcs[1]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (chauxnwzcs[chucunkc][1]);
		lsdzcs[2]=zhuanhuanfanhui[0];
		lsdzcs[3]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (chauxnwzcs[chucunkc][2]);
		lsdzcs[4]=zhuanhuanfanhui[0];
		lsdzcs[5]=zhuanhuanfanhui[1];
	//	for(i=0;i<=chucunkc;i++)
	//	{
	//		zongchunchucs=dqcs+chauxnwzcs[i][2];
	//	}
		HDduanWriteI2C(0xa0,0x01,(0x80+(chucunkc*6)),lsdzcs,6);
		DelayMS(10);
		for(i=0;i<3;i++)
		{
			fa_232[i]=chauxnwzcs[chucunkc][i];
		}
		HDByteWriteI2C(0xa0,0x01,0xbf,chucunkc);
	//	HDByteWriteI2C(0xa0,0x01,0xd1,chucunkc);
		DelayMS(5);
//		if
//	}
}
*/
/*
void chaxun_chunchu(void)
{
//	uint16 lsbl;
	uchar lschcsz[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uchar lsdzcs[8]={0,0,0,0,0,0,0,0};
//	uint16 zongchunchucs=0;
//	uchar lswz[4]={0,0,0,0},i;
//	if(gongzuo[4]%10==0&&time_sec==0)
//	{

		zhuanhuan_16to8 (WD[0]);
		lschcsz[0]=zhuanhuanfanhui[0];
		lschcsz[1]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (WD[1]);
		lschcsz[2]=zhuanhuanfanhui[0];
		lschcsz[3]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (wd_yd);
		lschcsz[4]=zhuanhuanfanhui[0];
		lschcsz[5]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (sd_yd);
		lschcsz[6]=zhuanhuanfanhui[0];
		lschcsz[7]=zhuanhuanfanhui[1];

		if(gongzuo[7]==chucunkc)
		zhuanhuan_16to8((chauxnwzcs[chucunkc][1]));
		else
		{
			chauxnwzcs[gongzuo[7]][0]=chauxnwzcs[chucunkc][1];
			chauxnwzcs[gongzuo[7]][1]=chauxnwzcs[chucunkc][1];
			chucunkc=gongzuo[7];
			zhuanhuan_16to8 (chauxnwzcs[chucunkc][1]);
		}
		HDduanWriteI2C(0xa0,zhuanhuanfanhui[0],zhuanhuanfanhui[1],lschcsz,8);
		chauxnwzcs[chucunkc][1]=chauxnwzcs[chucunkc][1]+8;
		chauxnwzcs[chucunkc][2]++;
	//	chauxnwzcs[gongzuo[7],1]++;
		DelayMS(10);
	//	for(i=0;i<3;i++)
	//	{
	//		lswz[i]=chauxnwzcs[i];
	//	}
	//	lswz[3]=chucunkc;
		zhuanhuan_16to8 (chauxnwzcs[chucunkc][0]);
		lsdzcs[0]=zhuanhuanfanhui[0];
		lsdzcs[1]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (chauxnwzcs[chucunkc][1]);
		lsdzcs[2]=zhuanhuanfanhui[0];
		lsdzcs[3]=zhuanhuanfanhui[1];
		zhuanhuan_16to8 (chauxnwzcs[chucunkc][2]);
		lsdzcs[4]=zhuanhuanfanhui[0];
		lsdzcs[5]=zhuanhuanfanhui[1];
	//	for(i=0;i<=chucunkc;i++)
	//	{
	//		zongchunchucs=dqcs+chauxnwzcs[i][2];
	//	}
		HDduanWriteI2C(0xa0,0x01,(0x80+(chucunkc*6)),lsdzcs,6);
		DelayMS(10);
		HDByteWriteI2C(0xa0,0x01,0xbf,chucunkc);
	//	HDByteWriteI2C(0xa0,0x01,0xd1,chucunkc);
		DelayMS(5);
//		if
//	}
}
*/

void chaxun_xianshi(void)
{
	uchar lschaxundq[16],j=0,kc=0;
	uint16 xianshi[5],bencicishu=0,bccshu=0,zongkaocishu=0;
	int i=0;
//	chucunkc=HDByteReadI2C(0xa0,0x01,0xbf);
//	DelayMS(5);chaxuncs
//fa_232[0]=chaxuncs;
//fa_232[2]=kc;

zongkaocishu=0;
bencicishu=chaxuncs;
/*
for(j=0;j<i;j++)
{
zongkaocishu=zongkaocishu+chauxnwzcs[i][2];
}
bencicishu=chaxuncs+1;
for(i=lskc001;i>=0;i--)
{
	if(chauxnwzcs[i][2]>0)	bccshu=chauxnwzcs[i][2]-1;
//fa_232[i]=chauxnwzcs[i][2];
	if(bencicishu-chauxnwzcs[i][2]>0)
	{
		bencicishu=bencicishu-chauxnwzcs[i][2];
		kc++;
	}
	else break;
}
*/
//fa_232[5]=chaxuncs;
//fa_232[5]=ljkc;
for(i=ljkc;i>=0;i--)
{
zongkaocishu=0;
	for(j=0;j<i;j++)
	{
		zongkaocishu=zongkaocishu+chauxnwzcs[j][2];
	}
	if(bencicishu>zongkaocishu)
	{
		kc=i;
		bccshu=bencicishu-zongkaocishu;
		break;
	}
}
kc=lskc;
bccshu=chaxuncs;
/*
bencicishu=chaxuncs+1;
for(i=0;i<=lskc001;i++)
{
	bccshu=bencicishu-1;
	kc=i;
	if(bencicishu-chauxnwzcs[i][2]>0)
	{
		bencicishu=bencicishu-chauxnwzcs[i][2];
						//	i++;
	}
	else break;
}
*/

/*
bencicishu=chaxuncs+1;
while(bencicishu-chauxnwzcs[i][2]>0)
{
	bencicishu=bencicishu-chauxnwzcs[i][2];
	i++;
}
bccshu=bencicishu-1;
*/
/*
do	{
		bccshu=chaxuncs+1-bencicishu;
		bencicishu=bencicishu+chauxnwzcs[i][2];
		i++;
	}
//fa_232[2]=bencicishu;
	while(chaxuncs+1-bencicishu>0);
*/
//kc=i;
//fa_232[4]=kc;
//fa_232[3]=chaxuncs;
/*
	while(lskc-i>=0)
	{
		bccshu=chaxuncs-bencicishu;
		bencicishu=bencicishu+chauxnwzcs[i][2];

		i++;
	}
*/
/*
if(chaxuncs!=0)
{
	bencicishu=chaxuncs;
	while(bencicishu-chauxnwzcs[i][2]>=0)
	{
		bencicishu=bencicishu-chauxnwzcs[i][2];
		i++;
	}
}
else i=1;
bccshu=chauxnwzcs[i-1][2];
*/


//		lschcsz[14]=(gongzuo[7]|(time_tab[5]<<4));	//考次加月份
//		lschcsz[11]=time_tab[2];					//时
//		lschcsz[13]=time_tab[4];					//日
//		lschcsz[15]=time_tab[6];					//年

	zhuanhuan_16to8 ((chauxnwzcs[kc][0]+bccshu*16));
	HDSequentialReadI2C(0xa0,zhuanhuanfanhui[0],zhuanhuanfanhui[1],lschaxundq,16);
	DelayMS(10);
	xianshi[0]=zhuanhuan_8to16 (lschaxundq[0],lschaxundq[1]);
	xianshi[1]=zhuanhuan_8to16 (lschaxundq[2],lschaxundq[3]);
	xianshi[2]=zhuanhuan_8to16 (lschaxundq[4],lschaxundq[5]);
	xianshi[3]=zhuanhuan_8to16 (lschaxundq[6],lschaxundq[7]);
	xianshi[4]=zhuanhuan_8to16 (lschaxundq[8],lschaxundq[9]);
	write_lcd_shuzi_sanwei(1,1,xianshi[0]);
	write_lcd_shuzi_sanwei(2,1,xianshi[1]);
//	write_lcd_shuzi_sanwei(3,1,((lschaxundq[13]*10)-(lschaxundq[10]*60+lschaxundq[11])/6));
	write_lcd_shuzi_sanwei(3,1,lschaxundq[10]);

	write_lcd_shuzi_sanwei(4,1,lschaxundq[12]);
	write_lcd_shuzi_sanwei(5,1,xianshi[2]);
	write_lcd_shuzi_sanwei(6,1,xianshi[3]);
	write_lcd_shuzi_sanwei(7,1,xianshi[4]);
	write_lcd_shuzi_yiwei(1,kc+1);//chaxunkc//lschaxundq[14]
	write_lcd_shuzi_erwei(43,1,lschaxundq[11]);
	write_lcd_shuzi_erwei(42,1,lschaxundq[13]);
	write_lcd_shuzi_erwei(41,1,(lschaxundq[14]>>4));
	write_lcd_shuzi_erwei(40,1,lschaxundq[15]);

	//	fa_232[3]=i;
//fa_232[6]=xianshi[2];
//fa_232[7]=xianshi[3];
	//	for(i=0;i<3;i++)
	//	{
	//		fa_232[i]=chauxnwzcs[kc][i];
	//	}
}
/*
void chaxun_xianshi(uchar dqkc,uint16 cishu)
{
	uchar lschaxundq[16];
	uint16 xianshi[5];
//	chucunkc=HDByteReadI2C(0xa0,0x01,0xbf);
//	DelayMS(5);
	zhuanhuan_16to8 ((chauxnwzcs[0][0]+chaxuncs*8));
	HDSequentialReadI2C(0xa0,zhuanhuanfanhui[0],zhuanhuanfanhui[1],lschaxundq,8);
	DelayMS(10);
	xianshi[0]=zhuanhuan_8to16 (lschaxundq[0],lschaxundq[1]);
	xianshi[1]=zhuanhuan_8to16 (lschaxundq[2],lschaxundq[3]);
	xianshi[2]=zhuanhuan_8to16 (lschaxundq[4],lschaxundq[5]);
	xianshi[3]=zhuanhuan_8to16 (lschaxundq[6],lschaxundq[7]);
//	xianshi[4]=zhuanhuan_8to16 (lschaxundq[8],lschaxundq[9]);
	write_lcd_shuzi_sanwei(1,1,xianshi[0]);
	write_lcd_shuzi_sanwei(2,1,xianshi[1]);
//	write_lcd_shuzi_sanwei(3,1,((lschaxundq[13]*10)-(lschaxundq[10]*60+lschaxundq[11])/6));

//	write_lcd_shuzi_sanwei(3,1,cishu);
//	write_lcd_shuzi_sanwei(4,1,cishu/6);
	write_lcd_shuzi_sanwei(5,1,xianshi[2]);
	write_lcd_shuzi_sanwei(6,1,xianshi[3]);
//	write_lcd_shuzi_sanwei(7,1,xianshi[4]);
	write_lcd_shuzi_yiwei(1,dqkc);
}
*/
void chuxun_xuanze(void)
{
//	uint16 dqcs=0;
	uchar ls_cxsx=0;
	uchar i,j=0;;//,lskc=0,lskc001=0
	if(chaxun_bz==0&&key_mid==128&&key_down_count>30)
	{
		chaxunbz=0;
		chaxun_bz=1;
	//	lskc=gongzuo[7];
		lskc=chucunkc;
		if(chauxnwzcs[lskc][2]>0)	chaxuncs=chauxnwzcs[lskc][2]-1;
		else chaxuncs=chauxnwzcs[lskc][2];
		chaxun_xianshi();
		DelayMS(200);
	}
	if(chaxun_bz==1)
	{
		if(key_mid==4&&lskc<ljkc)//chaxunkc
		{
			lskc++;
			if(chauxnwzcs[lskc][2]>0)	chaxuncs=chauxnwzcs[lskc][2]-1;
			else chaxuncs=chauxnwzcs[lskc][2];
			chaxun_xianshi();
			DelayMS(200);
		}
		if(key_mid==2&&lskc>0)
		{
			lskc--;
			if(chauxnwzcs[lskc][2]>0)	chaxuncs=chauxnwzcs[lskc][2]-1;
			else chaxuncs=chauxnwzcs[lskc][2];
			chaxun_xianshi();
			DelayMS(200);
		}
ClrWdt();
		if(key_mid==1)
		{
			if(chauxnwzcs[lskc][2]>0)	ls_cxsx=chauxnwzcs[lskc][2]-1;
			else ls_cxsx=chauxnwzcs[lskc][2];
			if(chaxuncs<ls_cxsx)
				chaxuncs++;
			else if(lskc<ljkc)
			{
				lskc++;
				chaxuncs=0;
			}
			chaxun_xianshi();
			DelayMS(200);
		}
		if(key_mid==16)
		{
			if(chaxuncs>0)
				chaxuncs--;
			else if(lskc>0)
			{
				lskc--;
				if(chauxnwzcs[lskc][2]>0)	chaxuncs=chauxnwzcs[lskc][2]-1;
				else chaxuncs=chauxnwzcs[lskc][2];
			}
			chaxun_xianshi();
			DelayMS(200);
		}
	}
	if(chaxun_bz==1&&(key_up_count>200||key_mid==64))
	{
		chaxun_bz=0;
	write_lcd_shuzi_sanwei(1,1,WD[0]);
	write_lcd_shuzi_sanwei(2,1,WD[1]);
	write_lcd_shuzi_sanwei(3,1,((yushetime[gongzuo[1]]*10)-(gongzuo[5]*60+gongzuo[6])/6));
	write_lcd_shuzi_sanwei(4,1,gongzuo[3]);
	write_lcd_shuzi_sanwei(5,1,wd_yd);
	write_lcd_shuzi_sanwei(6,1,sd_yd);
	write_lcd_shuzi_sanwei(7,1,dyzhi);
	write_lcd_shuzi_yiwei(1,gongzuo[7]+1);
	}
}
/*
void chuxun_xuanze(void)
{
	uint16 dqcs=0;
	uchar i,j=0;;//,lskc=0,lskc001=0
	if(chaxun_bz==0&&key_mid==128&&key_down_count>30)
	{
		chaxunbz=0;
		chaxun_bz=1;
		lskc=gongzuo[7];
		dqcs=0;
	//	j=0;
		for(i=0;i<=lskc;i++)//chaxunkc
		{
		//	if(chauxnwzcs[i][2]>0)j++;
			dqcs=dqcs+chauxnwzcs[i][2];
		//	dqcs=dqcs-j;
		}
			if(dqcs>0){--dqcs;}
		chaxuncs=dqcs;
		chaxun_xianshi();
//		chucunkc=HDByteReadI2C(0xa0,0x01,0xbf);
//		DelayMS(5);
//		HDSequentialReadI2C(0xa0,0x80,zhuanhuanfanhui[1],lschaxundq,16);
//		DelayMS(10);
		DelayMS(200);
	}
	if(chaxun_bz==1)
	{
		if(key_mid==4&&lskc<ljkc)//chaxunkc
		{
			lskc++;
			dqcs=0;
			for(i=0;i<lskc;i++)
			{
				dqcs=dqcs+chauxnwzcs[i][2];
			}
			chaxuncs=dqcs;
			chaxun_xianshi();
			DelayMS(200);
		}
		if(key_mid==2&&lskc>0)
		{
		//	chaxunkc--;
			lskc--;
			dqcs=0;
			for(i=0;i<lskc;i++)
			{
	
				dqcs=dqcs+chauxnwzcs[i][2];
			}
			chaxuncs=dqcs;
			chaxun_xianshi();
			DelayMS(200);
		}
ClrWdt();
		dqcs=0;
	//	if(ljkc!=9)lskc001=lskc;
	//	else lskc001=9;
	//	j=0;
		for(i=0;i<=ljkc;i++)
		{
		//	if(chauxnwzcs[i][2]>0)j++;
			dqcs=dqcs+chauxnwzcs[i][2];
		//	dqcs=dqcs-j;
		}
			if(dqcs>0){--dqcs;}
		if(key_mid==1&&chaxuncs<dqcs)
		{
		//	if(key_down_count<1)
				chaxuncs++;
		//	else if(key_down_count>30&&chaxuncs<(dqcs-9))
		//		chaxuncs=chaxuncs+10;
		//	else if(key_down_count>30&&chaxuncs>(dqcs-9))
		//		chaxuncs=dqcs;
//kaocai_panduan(chaxuncs);
			chaxun_xianshi();
//write_lcd_shuzi_sanwei(4,1,dqcs);
			DelayMS(200);
		}
		if(key_mid==16&&chaxuncs>1)
		{
		//	if(key_down_count<1)
				chaxuncs--;
		//	else if(key_down_count>30&&chaxuncs>9)
		//		chaxuncs=chaxuncs-10;
		//	else if(key_down_count>30&&chaxuncs<9)
		//		chaxuncs=0;
//kaocai_panduan(chaxuncs);
			chaxun_xianshi();
//write_lcd_shuzi_sanwei(4,1,dqcs);
//write_lcd_shuzi_sanwei(4,1,chaxuncs);
//write_lcd_shuzi_erwei(25,1,dqcs);
//write_lcd_shuzi_erwei(26,1,chaxuncs);
			DelayMS(200);
		}
	}
	if(chaxun_bz==1&&(key_up_count>200||key_mid==64))
	{
		chaxun_bz=0;
	write_lcd_shuzi_sanwei(1,1,WD[0]);
	write_lcd_shuzi_sanwei(2,1,WD[1]);
	write_lcd_shuzi_sanwei(3,1,((yushetime[gongzuo[1]]*10)-(gongzuo[5]*60+gongzuo[6])/6));
	write_lcd_shuzi_sanwei(4,1,gongzuo[3]);
	write_lcd_shuzi_sanwei(5,1,wd_yd);
	write_lcd_shuzi_sanwei(6,1,sd_yd);
	write_lcd_shuzi_sanwei(7,1,dyzhi);
	write_lcd_shuzi_yiwei(1,gongzuo[7]+1);
	}
}
*/
/*
void chuxun_xuanze(void)
{
	uint16 dqcs=0,lscs=0,dycs=0,sycs=0;
	uchar i;
	if(chaxun_bz==0&&key_mid==128&&key_down_count>30)
	{
		chaxunbz=0;
		chaxun_bz=1;
		lskc=gongzuo[7];
		dqcs=0;
		for(i=0;i<=chaxunkc;i++)
		{
			dqcs=dqcs+chauxnwzcs[i][2];
		}
		chaxuncs=dqcs;
		chaxun_xianshi(lskc,chauxnwzcs[lskc][2]);
//		chucunkc=HDByteReadI2C(0xa0,0x01,0xbf);
//		DelayMS(5);
//		HDSequentialReadI2C(0xa0,0x80,zhuanhuanfanhui[1],lschaxundq,16);
//		DelayMS(10);
		DelayMS(400);
	}
		for(i=0;i<=chaxunkc;i++)
		{
			dqcs=dqcs+chauxnwzcs[i][2];
		}
	if(chaxun_bz==1)
	{
		if(key_mid==4&&lskc<chaxunkc)
		{
			lskc++;
		//	dqcs=0;
lscs=0;
			for(i=0;i<lskc;i++)
			{
			//	dqcs=dqcs+chauxnwzcs[i][2];
				chaxuncs=lscs+chauxnwzcs[i][2];
			}
		//	chaxuncs=dqcs;
			chaxun_xianshi(lskc,chauxnwzcs[lskc][2]);
			DelayMS(400);
		}
		if(key_mid==2&&lskc>0)
		{
		//	chaxunkc--;
			lskc--;
		//	dqcs=0;
lscs=0;
			for(i=0;i<lskc;i++)
			{
			//	dqcs=dqcs+chauxnwzcs[i][2];
				chaxuncs=lscs+chauxnwzcs[i][2];
			}
		//	chaxuncs=dqcs;
			chaxun_xianshi(lskc,chauxnwzcs[lskc][2]);
			DelayMS(400);
		}
		ClrWdt();

	//	dqcs=0;
	//	for(i=0;i<=chucunkc;i++)
	//	{
	//		dqcs=dqcs+chauxnwzcs[i][2];
	//	}

		if(key_mid==1&&chaxuncs<dqcs)
		{
		//	if(key_down_count<1)
				chaxuncs++;
		//	else if(key_down_count>30&&chaxuncs<(dqcs-9))
		//		chaxuncs=chaxuncs+10;
		//	else if(key_down_count>30&&chaxuncs>(dqcs-9))
		//		chaxuncs=dqcs;
			i=0;
			dycs=0;

	//		sycs=chaxuncs;
	//		while(sycs-chauxnwzcs[i][2]>0)
	//		{
	//			sycs=sycs-chauxnwzcs[i][2];
	//			dycs=dycs+chauxnwzcs[i][2];
	//			i++;
	//		}
	//		lskc=i;

			for(i=0;i<=lskc;i++)
			{
				dycs=dycs+chauxnwzcs[i][2];
			}
			chaxun_xianshi(lskc,chaxuncs-dycs);//,sycs,chaxuncs
			DelayMS(200);
		}
		if(key_mid==16&&chaxuncs>1)
		{
		//	if(key_down_count<1)
				chaxuncs--;
		//	else if(key_down_count>30&&chaxuncs>9)
		//		chaxuncs=chaxuncs-10;
		//	else if(key_down_count>30&&chaxuncs<9)
		//		chaxuncs=0;
			i=0;
			dycs=0;

	//		sycs=chaxuncs;
	//		while(sycs-chauxnwzcs[i][2]>0)
	//		{
	//			sycs=sycs-chauxnwzcs[i][2];
	//			dycs=dycs+chauxnwzcs[i][2];
	//			i++;
	//		}

			for(i=0;i<=lskc;i++)
			{
				dycs=dycs+chauxnwzcs[i][2];
			}
		//	lskc=i;
			chaxun_xianshi(lskc,chaxuncs-dycs);//,sycs,chaxuncs
			DelayMS(200);
		}
	}
	if(chaxun_bz==1&&(key_up_count>200||key_mid==64))
	{
		chaxun_bz=0;
	write_lcd_shuzi_sanwei(1,1,WD[0]);
	write_lcd_shuzi_sanwei(2,1,WD[1]);
	write_lcd_shuzi_sanwei(3,1,((yushetime[gongzuo[1]]*10)-(gongzuo[5]*60+gongzuo[6])/6));
	write_lcd_shuzi_sanwei(4,1,gongzuo[3]);
	write_lcd_shuzi_sanwei(5,1,wd_yd);
	write_lcd_shuzi_sanwei(6,1,sd_yd);
	write_lcd_shuzi_sanwei(7,1,dyzhi);
	write_lcd_shuzi_yiwei(1,chucunkc);
	}
}
*/

void huihuchaxunzhi(void)
{
	uchar i=0,lschaxun[10][6];
//	if(key_mid==132&&key_down_count>30)
//	{
		for(i=0;i<10;i++)
		{
			chauxnwzcs[i][0]=512+(3200*i);
			chauxnwzcs[i][1]=512+(3200*i);
			chauxnwzcs[i][2]=0;
		}
		for(i=0;i<10;i++)
		{
			zhuanhuan_16to8 (chauxnwzcs[i][0]);
			lschaxun[i][0]=zhuanhuanfanhui[0];
			lschaxun[i][1]=zhuanhuanfanhui[1];
			zhuanhuan_16to8 (chauxnwzcs[i][1]);
			lschaxun[i][2]=zhuanhuanfanhui[0];
			lschaxun[i][3]=zhuanhuanfanhui[1];
			zhuanhuan_16to8 (chauxnwzcs[i][2]);
			lschaxun[i][4]=zhuanhuanfanhui[0];
			lschaxun[i][5]=zhuanhuanfanhui[1];
		}
ljkc=0;
		HDduanWriteI2C(0xa0,0x01,0x80,lschaxun,60);
		DelayMS(20);
		chucunkc=0;
		HDByteWriteI2C(0xa0,0x01,0xbf,chucunkc);
		DelayMS(10);
//	}
}

void anjianhuifuchaxun(void)
{
	if(key_mid==132&&key_down_count>30)
	{
		huihuchaxunzhi();
	}
}

void kaocai_panduan(uint16 cunchu_cs)
{
	uchar i;
	for(i=0;i<9;i++)
	{
		if(0x0200+cunchu_cs>chauxnwzcs[i][0]&&0x0200+cunchu_cs<=chauxnwzcs[i][1]&&chauxnwzcs[i][2]!=0)
		{
			lskc=i;
		}
	}
}
