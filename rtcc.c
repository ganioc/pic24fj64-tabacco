#include "p24FJ64GA006.h"
#include "Pin_Definitions.h"
#include "lcd.h"
#include "key.h"
#include "delay.h"

extern uchar time_tab[8];

extern uint16 ss_tab[5][3];
extern uchar ss_js,ss_count;
extern	uchar key_mid;
extern uchar quxianweizhi,yushequxian,time_weizhi;
extern uchar ok_bz;
//extern uchar time_seting;

uchar BCD2HEX(uchar val);
uchar HEX2BCD(uchar val);
void time_read(void);
void time_write(uchar time[7]);
void lcd_time_write(void);
uchar read_time_onebety(uchar weizhi);
void time_write_bety(uchar weizhi,uchar time);
void set_time(void);

void time_read(void)
{
	uchar i;
	uint16  ls;
	for(i=0;i<4;i++)
	{
		_RTCPTR=i;
		ls=RTCVAL;
		time_tab[i*2]=ls;
		time_tab[i*2]=BCD2HEX(time_tab[i*2]);
		time_tab[i*2+1]=ls>>8;
		time_tab[i*2+1]=BCD2HEX(time_tab[i*2+1]);
	}
}

void time_write(uchar time[8])
{
	uint16 time_tab1[4];
	uchar i;
	_RTCWREN=1;
	for(i=0;i<4;i++)
	{
		_RTCPTR=i;
		time_tab1[i]=HEX2BCD(time[i*2+1])<<8;
		time_tab1[i]=time_tab1[i]|HEX2BCD(time[i*2]);
		RTCVAL=time_tab1[i];
	}
	_RTCWREN=0;
}

uchar BCD2HEX(uchar val)    //BCD转换为Byte
{
    uchar temp;
    temp=val&0x0f;
    val>>=4;
    val&=0x0f;
    val*=10;
    temp+=val;
   
    return temp;
}

uchar HEX2BCD(uchar val)    //Byte码转换为BCD码
{
    uchar i,j,temp;
    i=val / 10;
    j=val % 10 ;
    temp=j+(i<<4);
    return temp;
}

void lcd_time_write(void)
{
	write_lcd_shuzi_erwei(44,1,time_tab[1]);
	write_lcd_shuzi_erwei(43,1,time_tab[2]);
	write_lcd_shuzi_erwei(42,1,time_tab[4]);
	write_lcd_shuzi_erwei(41,1,time_tab[5]);
	write_lcd_shuzi_erwei(40,1,time_tab[6]);
}

uchar read_time_onebety(uchar weizhi)
{
	uint16  ls;
	_RTCPTR=weizhi/2;
	ls=RTCVAL;
	if(weizhi%2) ls=BCD2HEX(ls>>8);
	else ls=BCD2HEX(ls);
	return ls;
}

void time_write_bety(uchar weizhi,uchar time)
{
	uint16 ls;
	_RTCPTR=weizhi/2;
	ls=RTCVAL;
	asm volatile("disi	#5");
	asm volatile("mov	#0x55, w7");
	asm volatile("mov	w7, _NVMKEY");
	asm volatile("mov	#0xAA, w8");
	asm volatile("mov	w8, _NVMKEY");
    asm volatile("bset	_RCFGCAL, #13");
	_RTCPTR=weizhi/2;
//	_RTCWREN=1;
	if(weizhi%2)
	{
	_RTCWREN=1;
 		ls=ls&0x00ff;
		RTCVAL=(HEX2BCD(time))<<8|ls;
	}
	else 
	{
	_RTCWREN=1;
		ls=ls&0xff00;
		RTCVAL=HEX2BCD(time)|ls;
	}
	_RTCWREN=0;
}

void set_time(void)
{
//	uchar time_val,wei=44,timeset_able=1;
	uchar time_val;
//	uchar i=4,zb[5]={6,5,4,2,1};
	uchar zb[5]={6,5,4,2,1};
//	keyval=key();
//	time_read();

/*
	for(i=0;i<ss_js;i++)
	{
		if(ss_tab[i][0]==2&&ss_tab[i][1]>39&&ss_tab[i][1]<45)
		{
			wei=ss_tab[i][1];
			timeset_able=1;
			time_seting=1;
			time_read();
			zb=i;
	//		goto dxp;
//	write_lcd_shuzi_erwei(44,4,time_tab[1]);
//	write_lcd_shuzi_erwei(43,4,time_tab[2]);
//	write_lcd_shuzi_erwei(42,4,time_tab[4]);
//	write_lcd_shuzi_erwei(41,4,time_tab[5]);
//	write_lcd_shuzi_erwei(40,4,time_tab[6]);
		}
		else
		{
			timeset_able=0;
			time_seting=0;
		}
	}
*/
//	dxp:
/*
	write_lcd_shuzi_erwei(44,4,time_tab[1]);
	write_lcd_shuzi_erwei(43,4,time_tab[2]);
	write_lcd_shuzi_erwei(42,4,time_tab[4]);
	write_lcd_shuzi_erwei(41,4,time_tab[5]);
	write_lcd_shuzi_erwei(40,4,time_tab[6]);
	write_lcd_shuzi_erwei(44,2,time_tab[1]);
*/
//	while(timeset_able)
//	{
//	keyval=key();
//	write_lcd_shuzi_erwei(4,1,keyval);
		if(key_mid==2&&time_weizhi>40)
		{
			write_lcd_shuzi_erwei(time_weizhi,1,time_tab[zb[time_weizhi-40]]);
			time_weizhi--;
	//		i--;
			write_lcd_shuzi_erwei(time_weizhi,2,time_tab[zb[time_weizhi-40]]);
	DelayMS(200);
		}
		if(key_mid==4&&time_weizhi<44)
		{
			write_lcd_shuzi_erwei(time_weizhi,1,time_tab[zb[time_weizhi-40]]);
			time_weizhi++;
	//		i++;
			write_lcd_shuzi_erwei(time_weizhi,2,time_tab[zb[time_weizhi-40]]);
	DelayMS(200);
		}
		switch(time_weizhi)
		{
			case 44:		//分钟
		//	time_val=read_time_onebety(1);
			time_val=time_tab[1];
			if(key_mid==16&&time_val>0)
			{
ok_bz=0;
				time_tab[1]--;
				write_lcd_shuzi_erwei(44,1,time_val);
				time_val--;
				time_write_bety(1,time_val);
	//			ss_tab[zb[i]][2]=time_val;

				write_lcd_shuzi_erwei(44,2,time_val);
	DelayMS(200);
			}
			if(key_mid==1&&time_val<59)
			{
ok_bz=0;
				time_tab[1]++;
				write_lcd_shuzi_erwei(44,1,time_val);
				time_val++;
				time_write_bety(1,time_val);
		//		ss_tab[zb[i]][2]=time_val;

				write_lcd_shuzi_erwei(44,2,time_val);
	DelayMS(200);
			}

	//		ss_tab[0][2]=time_val;
//			write_lcd_shuzi_erwei(43,1,time_tab[2]);
//			write_lcd_shuzi_erwei(42,1,time_tab[4]);
//			write_lcd_shuzi_erwei(41,1,time_tab[5]);
//			write_lcd_shuzi_erwei(40,1,time_tab[6]);
			break;
			case 43:		//小时
		//	time_val=read_time_onebety(2);
			time_val=time_tab[2];
			if(key_mid==16&&time_val>0)
			{
ok_bz=0;
				time_tab[2]--;
				write_lcd_shuzi_erwei(43,1,time_val);
				time_val--;
				time_write_bety(2,time_val);
		//		ss_tab[zb[i]][2]=time_val;

				write_lcd_shuzi_erwei(43,2,time_val);
	DelayMS(200);
			}
			if(key_mid==1&&time_val<23)
			{
ok_bz=0;
				time_tab[2]++;
				write_lcd_shuzi_erwei(43,1,time_val);
				time_val++;
				time_write_bety(2,time_val);
		//		ss_tab[zb[i]][2]=time_val;

				write_lcd_shuzi_erwei(43,2,time_val);
	DelayMS(200);
			}
	//		ss_tab[0][2]=time_val;
	//		write_lcd_shuzi_erwei(44,1,time_tab[1]);
	//		write_lcd_shuzi_erwei(42,1,time_tab[4]);
	//		write_lcd_shuzi_erwei(41,1,time_tab[5]);
	//		write_lcd_shuzi_erwei(40,1,time_tab[6]);
			break;
			case 42:		//日
	//		time_val=read_time_onebety(4);
			time_val=time_tab[4];
			if(key_mid==16&&time_val>1)
			{
ok_bz=0;
				time_tab[4]--;
				write_lcd_shuzi_erwei(42,1,time_val);
				time_val--;
				time_write_bety(4,time_val);
		//		ss_tab[zb[i]][2]=time_val;

				write_lcd_shuzi_erwei(42,2,time_val);
	DelayMS(200);
			}
			if(key_mid==1&&time_val<31)
			{
ok_bz=0;
				time_tab[4]++;
				write_lcd_shuzi_erwei(42,1,time_val);
				time_val++;
				time_write_bety(4,time_val);
		//		ss_tab[zb[i]][2]=time_val;

				write_lcd_shuzi_erwei(42,2,time_val);
	DelayMS(200);
			}
	//		ss_tab[0][2]=time_val;
	//		write_lcd_shuzi_erwei(44,1,time_tab[1]);
	//		write_lcd_shuzi_erwei(43,1,time_tab[2]);
	//		write_lcd_shuzi_erwei(41,1,time_tab[5]);
	//		write_lcd_shuzi_erwei(40,1,time_tab[6]);
			break;
			case 41:
	//		time_val=read_time_onebety(5);
			time_val=time_tab[5];
			if(key_mid==16&&time_val>1)
			{
ok_bz=0;
				time_tab[5]--;
				write_lcd_shuzi_erwei(41,1,time_val);
				time_val--;
				time_write_bety(5,time_val);
		//		ss_tab[zb[i]][2]=time_val;

				write_lcd_shuzi_erwei(41,2,time_val);
	DelayMS(200);
			}
			if(key_mid==1&&time_val<12)
			{
ok_bz=0;
				time_tab[5]++;
				write_lcd_shuzi_erwei(41,1,time_val);
				time_val++;
				time_write_bety(5,time_val);
		//		ss_tab[zb[i]][2]=time_val;

				write_lcd_shuzi_erwei(41,2,time_val);
	DelayMS(200);
			}
	//		ss_tab[0][2]=time_val;
	//		write_lcd_shuzi_erwei(44,1,time_tab[1]);
	//		write_lcd_shuzi_erwei(43,1,time_tab[2]);
	//		write_lcd_shuzi_erwei(42,1,time_tab[4]);
	//		write_lcd_shuzi_erwei(40,1,time_tab[6]);
			break;
			case 40:
	//		time_val=read_time_onebety(6);
			time_val=time_tab[6];
			if(key_mid==16&&time_val>1)
			{
ok_bz=0;
				time_tab[6]--;
				write_lcd_shuzi_erwei(40,1,time_val);
				time_val--;
				time_write_bety(6,time_val);
		//		ss_tab[zb[i]][2]=time_val;

				write_lcd_shuzi_erwei(40,2,time_val);
	DelayMS(200);
			}
			if(key_mid==1&&time_val<99)
			{
ok_bz=0;
				time_tab[6]++;
				write_lcd_shuzi_erwei(40,1,time_val);
				time_val++;
				time_write_bety(6,time_val);
		//		ss_tab[zb[i]][2]=time_val;

				write_lcd_shuzi_erwei(40,2,time_val);
	DelayMS(200);
			}
	//		ss_tab[0][2]=time_val;
	//		write_lcd_shuzi_erwei(44,1,time_tab[1]);
	//		write_lcd_shuzi_erwei(43,1,time_tab[2]);
	//		write_lcd_shuzi_erwei(42,1,time_tab[4]);
	//		write_lcd_shuzi_erwei(41,1,time_tab[5]);
			break;
		}
	/*
		if(key_up_count>100||key_mid==128)
		{
			timeset_able=0;
		}
		DelayMS(60);
*/
//	}
	//		time_seting=0;
	//		lcd_time_write();
//	return timeset_start;
}
