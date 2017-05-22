#include "Pin_Definitions.h"
#include "lcd_guding.h"
#include "delay.h"
#include "i2c_24lc512.h"
#include "wenduquxian.h"

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

void __delay32(unsigned long cycles);

extern uchar lcd_RAM[4][32];
extern uint16 ss_tab[5][3];
extern uchar ss_js,ss_count;
extern	uchar key_mid;
extern uchar yushewendu[10];
extern uint16 yusheshidu[10];

extern uchar yusheshidu1[10];
extern uchar yushetime[19];
extern uint16 sd_count,wd_count,wd_yd,sd_yd,hw_time,wenduxielv,shiduxielv;
extern uchar bz;
extern uchar quxianweizhi,time_weizhi;
//extern	uchar key_mid;
extern	uchar set_key;
extern uchar time_tab[8];
//extern uint16 time_zong;				//总时间
extern uchar time_sec;
//extern uchar gzzt;						//工作状态
//extern uchar hkdw;						//烘烤段位
extern uint16 hw_shijian;
//extern uint16 time_dqd;					//当前段的时间计数
extern uint16 WD[4];
extern uchar gongzuo[6];
extern uchar set_bz;
extern uchar sound_duanl;
extern uchar key_zhi;

extern unsigned char zishe_sector[39];
extern unsigned char xiabu_sector[39];
extern unsigned char zhongbu_sector[39];
extern unsigned char shangbu_sector[39];
extern uchar ok_bz;

//以下为字写
void chose_cs(uchar lcdcs)
{
	switch (lcdcs)
	{
		case 1:
			LCD_CS1=0;
			LCD_CS2=0;
		break;
		case 2:
			LCD_CS1=0;
			LCD_CS2=1;
		break;
		case 3:
			LCD_CS1=1;
			LCD_CS2=0;
		break;
		case 4:
			LCD_CS1=1;
			LCD_CS2=1;
		break;
	}
//__delay32(12);
}

void write_lcd_cmd(uchar cmd)
{
	uchar i,ls;
//	    LCD_RD=1;
	ls=cmd<<5;
	for(i=0;i<3;i++)
	{

	//	LCD_DATA=0;
		if(ls&0x80)
			LCD_DATA=1;
		else 	LCD_DATA=0;
		LCD_WR=0;
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
//__delay32(12);
	    LCD_WR=1;
		ls=ls<<1;
	}

}

void write_lcd_address(uchar add)
{
	uchar i,ls;
	ls=add<<2;
//	    LCD_RD=1;
	for(i=0;i<6;i++)
	{
	//	LCD_DATA=0;
		if(ls&0x80)
			LCD_DATA=1;
		else 	LCD_DATA=0;
		LCD_WR=0;
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
//__delay32(12);
	    LCD_WR=1;
		ls=ls<<1;
	}
}

void write_lcd_data(uchar data)
{
	uchar i,ls;
	ls=data;
//	ls=data<<4;
//	    LCD_RD=1;
	for(i=0;i<8;i++)
	{
	//	LCD_DATA=0;
		if(ls&0x80)
			LCD_DATA=1;
		else LCD_DATA=0;
		LCD_WR=0;
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
//__delay32(12);
	    LCD_WR=1;
		ls=ls<<1;
	}
}
/*
uchar read_lcd_data(void)
{
	uchar i,ls=0X00;
	    LCD_WR=1;
	LCD_DATA_OD=0;
	LCD_DATA_DIR=1;

	for(i=0;i<8;i++)
	{
		ls=ls<<1;
//		LCD_RD=0;
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
//	    LCD_RD=1;
//		if(LCD_DATA_IN)
		ls=ls|0x01;
	}
	LCD_DATA_DIR=0;
	LCD_DATA_OD=1;
	return ls;
}
*/
void write_lcd_cmddata(uchar cmddata)
{
	uchar i,ls;
	ls=cmddata;
//	    LCD_RD=1;
	for(i=0;i<8;i++)
	{
	//	LCD_DATA=0;
		if(ls&0x80)
			LCD_DATA=1;
		else LCD_DATA=0;
		LCD_WR=0;
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	    LCD_WR=1;
		ls=ls<<1;
	}
	LCD_DATA=1;
	LCD_WR=0;
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
    LCD_WR=1;
}

void init_lcd(uchar lcd_ic)
{
    
	LCD_WR=1;
	chose_cs(lcd_ic);
DelayMS(1);
	write_lcd_cmd(0b00000100);
DelayMS(1);
	write_lcd_cmddata(0x01);
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	write_lcd_cmddata(0x03);
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	write_lcd_cmddata(0x29);
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	lcd_cs_pandan(lcd_ic);
DelayMS(1);
}

void write_all_lcd(uchar dat)
{
	uchar i,j,k;
	for(i=1;i<5;i++)
	{
//		DelayMS(6000);
		chose_cs(i);
		write_lcd_cmd(0b00000101);
		write_lcd_address(0x00);
		for(j=0;j<32;j++)
		{
			for(k=0;k<8;k++)
			{
				LCD_DATA=dat;
				LCD_WR=0;
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
			    LCD_WR=1;
			}
		}
	}
}

void lcd_cs_pandan(uchar lcd_ic)
{
	if (lcd_ic==4)
		lcd_ic=1;
	else if (lcd_ic==1)
		lcd_ic=4;
	else if (lcd_ic==2)
		lcd_ic=3;
	else if (lcd_ic==3)
		lcd_ic=2;
	chose_cs(lcd_ic);
__delay32(12);
}
/*
uchar read_lcd_bety(uchar lcd_cs,uchar lcd_address)
{
	uchar read;
	chose_cs(lcd_cs);
	write_lcd_cmd(0b00000110);
	write_lcd_address(lcd_address);
	read=read_lcd_data();
	lcd_cs_pandan(lcd_cs);
	return read;
}
*/
void write_lcd_bety(uchar lcd_cs,uchar lcd_address,uchar lcd_bety,uchar sign)
{
	chose_cs(lcd_cs);
	write_lcd_cmd(0b00000101);
//	DelayMS(4);
__delay32(12);
	write_lcd_address(lcd_address);
//	DelayMS(4);
__delay32(12);
	write_lcd_data(lcd_bety);
//	DelayMS(4);
__delay32(12);
	lcd_cs_pandan(lcd_cs);
//	DelayMS(4);
__delay32(12);
}

void write_lcd_kuang(uchar kuang_num,uchar sign)
{
	uchar lcd_read,num,k_bit=0;
	num=kuang_num-1;
//	lcd_read=read_lcd_bety(lcd_kuang[num][0],lcd_kuang[num][1]);
lcd_read=lcd_RAM[lcd_kuang[num][0]-1][lcd_kuang[num][1]/2];
	ss_panduan_tiaozheng(4,kuang_num,0,sign);
//	if(sign==1||sign==4||sign==2)
	if(sign==1||sign==4)
		k_bit=lcd_read|lcd_kuang[num][2];
	else  if(sign==0||sign==3)
	{
		k_bit=(~lcd_kuang[num][2])&lcd_read;
	}
if(sign==2)
{
return;
/*
	if(ss_count>=0&&ss_count<=5)
	k_bit=lcd_read|lcd_kuang[num][2];
	else
	k_bit=(~lcd_kuang[num][2])&lcd_read;
*/
}
	write_lcd_bety(lcd_kuang[num][0],lcd_kuang[num][1],k_bit,sign);
lcd_RAM[lcd_kuang[num][0]-1][lcd_kuang[num][1]/2]=k_bit;
}

void write_lcd_zi(uchar zi_num,uchar sign)
{
	uchar lcd_read,num,z_bit=0;
	num=zi_num-1;
//	lcd_read=read_lcd_bety(lcd_zi[num][0],lcd_zi[num][1]);
lcd_read=lcd_RAM[lcd_zi[num][0]-1][lcd_zi[num][1]/2];
	ss_panduan_tiaozheng(5,zi_num,0,sign);
//	if(sign==1||sign==4||sign==2)
	if(sign==1||sign==4)
		z_bit=lcd_read|lcd_zi[num][2];
	else  if(sign==0||sign==3)
	{
		z_bit=(~lcd_zi[num][2])&lcd_read;
	}
if(sign==2)
{
return;
/*
	if(ss_count>=0&&ss_count<=5)
	z_bit=lcd_read|lcd_zi[num][2];
	else
	z_bit=(~lcd_zi[num][2])&lcd_read;
*/
}
	write_lcd_bety(lcd_zi[num][0],lcd_zi[num][1],z_bit,sign);
lcd_RAM[lcd_zi[num][0]-1][lcd_zi[num][1]/2]=z_bit;
}

void write_lcd_point(uchar point_num,uchar sign)
{
	uchar lcd_read,num,p_bit=0;
	num=point_num-1;
//	lcd_read=read_lcd_bety(lcd_point[num][0],lcd_point[num][1]);
lcd_read=lcd_RAM[lcd_point[num][0]-1][lcd_point[num][1]/2];
	ss_panduan_tiaozheng(6,point_num,0,sign);
//	if(sign==1||sign==4||sign==2)
	if(sign==1||sign==4)
	p_bit=lcd_read|lcd_point[num][2];
	else if(sign==0||sign==3)
	{
		p_bit=(~lcd_point[num][2])&lcd_read;
	}
if(sign==2)
{
return;
/*
	if(ss_count>=0&&ss_count<=5)
	p_bit=lcd_read|lcd_point[num][2];
	else
	p_bit=(~lcd_point[num][2])&lcd_read;
*/
}
	write_lcd_bety(lcd_point[num][0],lcd_point[num][1],p_bit,sign);
lcd_RAM[lcd_point[num][0]-1][lcd_point[num][1]/2]=p_bit;
}

void write_lcd_shuzi_erwei(uchar shuzi_num,uchar sign,uchar zhi)
{
	uchar lcd_read,num,s_bit,gw,sw,shuzhig=0,shuzhis=0;
	gw=zhi%10;
	sw=zhi/10;
	num=shuzi_num-1;
	ss_panduan_tiaozheng(2,shuzi_num,zhi,sign);
	switch (lcd_shuzi_erwei[num][2])
	{
		case 1:
			shuzhig=shuzi_1lei[gw];
			shuzhis=shuzi_1lei[sw];
		break;
		case 2:
			shuzhig=shuzi_2lei[gw];
			shuzhis=shuzi_2lei[sw];
		break;
	}
//	lcd_read=read_lcd_bety(lcd_shuzi_erwei[num][0],lcd_shuzi_erwei[num][1]);
	lcd_read=lcd_RAM[lcd_shuzi_erwei[num][0]-1][(lcd_shuzi_erwei[num][1])/2];
	if(lcd_shuzi_erwei[num][3]==1)
	{

		shuzhis=shuzhis>>1;
		s_bit=lcd_read&0x80;
//		if(sign==1||sign==4||sign==2)
	if(sign==1||sign==4)
			shuzhis=shuzhis|s_bit;
		else  if(sign==0||sign==3)
			shuzhis=s_bit;
if(sign==2)
{
return;
/*
	if(ss_count>=0&&ss_count<=5)
	shuzhis=shuzhis|s_bit;
	else
	shuzhis=s_bit;
*/
}
	}
	else
	{

		s_bit=lcd_read&0x01;
//		if(sign==1||sign==4||sign==2)
	if(sign==1||sign==4)
			shuzhis=shuzhis|s_bit;
		else  if(sign==0||sign==3)
			shuzhis=s_bit;
if(sign==2)
{
return;
/*
	if(ss_count>=0&&ss_count<=5)
	shuzhis=shuzhis|s_bit;
	else
	shuzhis=s_bit;
*/
}
	}
	lcd_RAM[lcd_shuzi_erwei[num][0]-1][(lcd_shuzi_erwei[num][1])/2]=shuzhis;
	write_lcd_bety(lcd_shuzi_erwei[num][0],lcd_shuzi_erwei[num][1],shuzhis,sign);

//	lcd_read=read_lcd_bety(lcd_shuzi_erwei[num][0],(lcd_shuzi_erwei[num][1]+2));
	lcd_read=lcd_RAM[lcd_shuzi_erwei[num][0]-1][(lcd_shuzi_erwei[num][1])/2+1];
	if(lcd_shuzi_erwei[num][3]==1)
	{

		shuzhig=shuzhig>>1;
		s_bit=lcd_read&0x80;
//		if(sign==1||sign==4||sign==2)
	if(sign==1||sign==4)
			shuzhig=shuzhig|s_bit;
		else  if(sign==0||sign==3)
			shuzhig=s_bit;
if(sign==2)
{
return;
/*
	if(ss_count>=0&&ss_count<=5)
	shuzhig=shuzhig|s_bit;
	else
	shuzhig=s_bit;
*/
}
	}
	else
	{

		s_bit=lcd_read&0x01;
//		if(sign==1||sign==4||sign==2)
	if(sign==1||sign==4)
			shuzhig=shuzhig|s_bit;
		else if(sign==0||sign==3)
			shuzhig=s_bit;
if(sign==2)
{
return;
/*
	if(ss_count>=0&&ss_count<=5)
	shuzhig=shuzhig|s_bit;
	else
	shuzhig=s_bit;
*/
}
	}
	lcd_RAM[lcd_shuzi_erwei[num][0]-1][(lcd_shuzi_erwei[num][1])/2+1]=shuzhig;
	write_lcd_bety(lcd_shuzi_erwei[num][0],(lcd_shuzi_erwei[num][1]+2),shuzhig,sign);
}

void write_lcd_shuzi_sanwei(uchar shuzi_num,uchar sign,uint16 zhi)
{
	uchar lcd_read[6],num,s_bit[6],gw=19,sw=19,bw=19;
	uchar shuzhig1,shuzhis1,shuzhib1,shuzhig2,shuzhis2,shuzhib2;
	if(zhi!=65534&&zhi!=65533&&zhi!=65532)
	{
		gw=zhi%10;
		sw=(zhi/10)%10;
		bw=zhi/100;
	}
	else if(zhi==65534)
	{
		gw=18;
		sw=18;
		bw=14;
	}
	else if(zhi==65533)
	{
		gw=15;
		sw=15;
		bw=0;
	}
	else if(zhi==65532)
	{
		gw=19;
		sw=19;
		bw=19;
	}

	num=shuzi_num-1;
	ss_panduan_tiaozheng(3,shuzi_num,zhi,sign);
	switch (lcd_shuzi_sanwei[num][2])
	{
		case 1:
			shuzhig1=shuzi_1lei[gw];
			shuzhis1=shuzi_1lei[sw];
			shuzhib1=shuzi_1lei[bw];
	//		lcd_read[0]=read_lcd_bety(lcd_shuzi_sanwei[num][0],lcd_shuzi_sanwei[num][1]);
	//		lcd_read[1]=read_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+2));
	//		lcd_read[2]=read_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+4));
	lcd_read[0]=lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2];
	lcd_read[1]=lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+1];
	lcd_read[2]=lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+2];
			if(lcd_shuzi_sanwei[num][3]==1)
			{

				shuzhib1=shuzhib1>>1;
				shuzhis1=shuzhis1>>1;
				shuzhig1=shuzhig1>>1;
				s_bit[0]=lcd_read[0]&0x80;
				s_bit[1]=lcd_read[1]&0x80;
				s_bit[2]=lcd_read[2]&0x80;
		//		if(sign==1||sign==4||sign==2)
	if(sign==1||sign==4)
				{
					shuzhib1=shuzhib1|s_bit[0];
					shuzhis1=shuzhis1|s_bit[1];
					shuzhig1=shuzhig1|s_bit[2];
				}
				else if(sign==0||sign==3)
				{ 
					shuzhib1=s_bit[0];
					shuzhis1=s_bit[1];
					shuzhig1=s_bit[2];
				}
if(sign==2)
{
return;
/*
	if(ss_count>=0&&ss_count<=5)
				{
					shuzhib1=shuzhib1|s_bit[0];
					shuzhis1=shuzhis1|s_bit[1];
					shuzhig1=shuzhig1|s_bit[2];
				}
	else
				{ 
					shuzhib1=s_bit[0];
					shuzhis1=s_bit[1];
					shuzhig1=s_bit[2];
				}
*/
}
				write_lcd_bety(lcd_shuzi_sanwei[num][0],lcd_shuzi_sanwei[num][1],shuzhib1,sign);
				write_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+2),shuzhis1,sign);
				write_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+4),shuzhig1,sign);
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2]=shuzhib1;
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+1]=shuzhis1;
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+2]=shuzhig1;
			}
			else
			{

				s_bit[0]=lcd_read[0]&0x01;
				s_bit[1]=lcd_read[1]&0x01;
				s_bit[2]=lcd_read[2]&0x01;
	//			if(sign==1||sign==4||sign==2)
	if(sign==1||sign==4)
				{
					shuzhib1=shuzhib1|s_bit[2];
					shuzhis1=shuzhis1|s_bit[1];
					shuzhig1=shuzhig1|s_bit[0];
				}
				else if(sign==0||sign==3)
				{ 
					shuzhib1=s_bit[0];
					shuzhis1=s_bit[1];
					shuzhig1=s_bit[2];
				}
if(sign==2)
{
return;
/*
	if(ss_count>=0&&ss_count<=5)
				{
					shuzhib1=shuzhib1|s_bit[2];
					shuzhis1=shuzhis1|s_bit[1];
					shuzhig1=shuzhig1|s_bit[0];
				}
	else
				{ 
					shuzhib1=s_bit[0];
					shuzhis1=s_bit[1];
					shuzhig1=s_bit[2];
				}
*/
}
				write_lcd_bety(lcd_shuzi_sanwei[num][0],lcd_shuzi_sanwei[num][1],shuzhig1,sign);
				write_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+2),shuzhis1,sign);
				write_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+4),shuzhib1,sign);
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2]=shuzhig1;
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+1]=shuzhis1;
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+2]=shuzhib1;
			}
		break;
		case 3:
			shuzhig1=shuzi_3lei[gw][0];
			shuzhis1=shuzi_3lei[sw][0];
			shuzhib1=shuzi_3lei[bw][0];
			shuzhig2=shuzi_3lei[gw][1];
			shuzhis2=shuzi_3lei[sw][1];
			shuzhib2=shuzi_3lei[bw][1];
	//		lcd_read[0]=read_lcd_bety(lcd_shuzi_sanwei[num][0],lcd_shuzi_sanwei[num][1]);
	//		lcd_read[1]=read_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+2));
	//		lcd_read[2]=read_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+4));
	//		lcd_read[3]=read_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+6));
	//		lcd_read[4]=read_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+8));
	//		lcd_read[5]=read_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+10));
	lcd_read[0]=lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2];
	lcd_read[1]=lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+1];
	lcd_read[2]=lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+2];
	lcd_read[3]=lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+3];
	lcd_read[4]=lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+4];
	lcd_read[5]=lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+5];
			if(lcd_shuzi_sanwei[num][3]==1)
			{
				shuzhib1=shuzhib1>>4;
				shuzhis1=shuzhis1>>4;
				shuzhig1=shuzhig1>>4;
				shuzhib2=shuzhib2>>4;
				shuzhis2=shuzhis2>>4;
				shuzhig2=shuzhig2>>4;
				s_bit[0]=lcd_read[0]&0xf1;
				s_bit[1]=lcd_read[1]&0xf0;
				s_bit[2]=lcd_read[2]&0xf1;
				s_bit[3]=lcd_read[3]&0xf0;
				s_bit[4]=lcd_read[4]&0xf1;
				s_bit[5]=lcd_read[5]&0xf0;
	//			if(sign==1||sign==4||sign==2)
	if(sign==1||sign==4)
				{
					shuzhib1=shuzhib1|s_bit[4];
					shuzhis1=shuzhis1|s_bit[2];
					shuzhig1=shuzhig1|s_bit[0];
					shuzhib2=shuzhib2|s_bit[5];
					shuzhis2=shuzhis2|s_bit[3];
					shuzhig2=shuzhig2|s_bit[1];
				}
				else if(sign==0||sign==3)
				{ 
					shuzhib1=s_bit[4];
					shuzhis1=s_bit[2];
					shuzhig1=s_bit[0];
					shuzhib2=s_bit[5];
					shuzhis2=s_bit[3];
					shuzhig2=s_bit[1];
				}
if(sign==2)
{
return;
/*
	if(ss_count>=0&&ss_count<=5)
				{
					shuzhib1=shuzhib1|s_bit[4];
					shuzhis1=shuzhis1|s_bit[2];
					shuzhig1=shuzhig1|s_bit[0];
					shuzhib2=shuzhib2|s_bit[5];
					shuzhis2=shuzhis2|s_bit[3];
					shuzhig2=shuzhig2|s_bit[1];
				}
	else
				{ 
					shuzhib1=s_bit[4];
					shuzhis1=s_bit[2];
					shuzhig1=s_bit[0];
					shuzhib2=s_bit[5];
					shuzhis2=s_bit[3];
					shuzhig2=s_bit[1];
				}
*/
}
				write_lcd_bety(lcd_shuzi_sanwei[num][0],lcd_shuzi_sanwei[num][1],shuzhig1,sign);
				write_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+2),shuzhig2,sign);
				write_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+4),shuzhis1,sign);
				write_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+6),shuzhis2,sign);
				write_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+8),shuzhib1,sign);
				write_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+10),shuzhib2,sign);
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2]=shuzhig1;
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+1]=shuzhig2;
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+2]=shuzhis1;
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+3]=shuzhis2;
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+4]=shuzhib1;
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+5]=shuzhib2;
			}
			else
			{
				s_bit[0]=lcd_read[0]&0x1f;
				s_bit[1]=lcd_read[1]&0x0f;
				s_bit[2]=lcd_read[2]&0x1f;
				s_bit[3]=lcd_read[3]&0x0f;
				s_bit[4]=lcd_read[4]&0x1f;
				s_bit[5]=lcd_read[5]&0x0f;
	//			if(sign==1||sign==4||sign==2)
	if(sign==1||sign==4)
				{
					shuzhib1=shuzhib1|s_bit[4];
					shuzhis1=shuzhis1|s_bit[2];
					shuzhig1=shuzhig1|s_bit[0];
					shuzhib2=shuzhib2|s_bit[5];
					shuzhis2=shuzhis2|s_bit[3];
					shuzhig2=shuzhig2|s_bit[1];
				}
				else if(sign==0||sign==3)
				{ 
					shuzhib1=s_bit[4];
					shuzhis1=s_bit[2];
					shuzhig1=s_bit[0];
					shuzhib2=s_bit[5];
					shuzhis2=s_bit[3];
					shuzhig2=s_bit[1];
				}
if(sign==2)
{
return;
/*
	if(ss_count>=0&&ss_count<=5)
				{
					shuzhib1=shuzhib1|s_bit[4];
					shuzhis1=shuzhis1|s_bit[2];
					shuzhig1=shuzhig1|s_bit[0];
					shuzhib2=shuzhib2|s_bit[5];
					shuzhis2=shuzhis2|s_bit[3];
					shuzhig2=shuzhig2|s_bit[1];
				}
	else
				{ 
					shuzhib1=s_bit[4];
					shuzhis1=s_bit[2];
					shuzhig1=s_bit[0];
					shuzhib2=s_bit[5];
					shuzhis2=s_bit[3];
					shuzhig2=s_bit[1];
				}
*/
}
				write_lcd_bety(lcd_shuzi_sanwei[num][0],lcd_shuzi_sanwei[num][1],shuzhig1,sign);
				write_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+2),shuzhig2,sign);
				write_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+4),shuzhis1,sign);
				write_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+6),shuzhis2,sign);
				write_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+8),shuzhib1,sign);
				write_lcd_bety(lcd_shuzi_sanwei[num][0],(lcd_shuzi_sanwei[num][1]+10),shuzhib2,sign);
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2]=shuzhig1;
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+1]=shuzhig2;
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+2]=shuzhis1;
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+3]=shuzhis2;
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+4]=shuzhib1;
	lcd_RAM[lcd_shuzi_sanwei[num][0]-1][(lcd_shuzi_sanwei[num][1])/2+5]=shuzhib2;
			}
		break;
	}
}

void write_lcd_shuzi_yiwei(uchar sign,uchar zhi)
{
	uchar shu_zhi,lcd_read,s_bit;
//	lcd_read=read_lcd_bety(lcd_shuzi_yiwei[0],lcd_shuzi_yiwei[1]);
	lcd_read=lcd_RAM[lcd_shuzi_yiwei[0]-1][(lcd_shuzi_yiwei[1])/2];
	s_bit=lcd_read&0x01;
	shu_zhi=shuzi_2lei[zhi];
	ss_panduan_tiaozheng(1,0,zhi,sign);
//	if(sign==1||sign==4||sign==2)
	if(sign==1||sign==4)
	{
		shu_zhi=shu_zhi|s_bit;
	}
	else if(sign==0||sign==3)
		shu_zhi=s_bit;
if(sign==2)
{
return;
/*
	if(ss_count>=0&&ss_count<=5)
	shu_zhi=shu_zhi|s_bit;
	else
	shu_zhi=s_bit;
*/
}
	write_lcd_bety(lcd_shuzi_yiwei[0],lcd_shuzi_yiwei[1],shu_zhi,sign);
	lcd_RAM[lcd_shuzi_yiwei[0]-1][(lcd_shuzi_yiwei[1])/2]=shu_zhi;
}
//分别代表是哪类图形，所属类别中的号码，值，标志
void ss_panduan_tiaozheng(uchar lei,uchar haoshu,uint16 zhi,uchar sign)
{
	uchar i,j,ls_bz=0;
	if (sign==1||sign==0)
	{
		for(i=0;i<5;i++)
		{
			if(ss_tab[i][0]==lei&&ss_tab[i][1]==haoshu)
			{
				for(j=i;j<ss_js;j++)
				{
					ss_tab[j][0]=ss_tab[j+1][0];
					ss_tab[j][1]=ss_tab[j+1][1];
					ss_tab[j][2]=ss_tab[j+1][2];
				}
				ss_js--;
				ss_tab[ss_js][0]=0x00;
				ss_tab[ss_js][1]=0x00;
				ss_tab[ss_js][2]=0x00;
		//		return;
			}	
		}
	}
	if(sign==2)
	{
		for(i=0;i<5;i++)
		{
			if(ss_tab[i][0]==lei&&ss_tab[i][1]==haoshu)
			{
				ss_tab[i][2]=zhi;
				ls_bz=1;
			}
		}
		if(ss_js<5&&ls_bz==0)
		{
		ss_tab[ss_js][0]=lei;
		ss_tab[ss_js][1]=haoshu;
		ss_tab[ss_js][2]=zhi;
		ss_js++;
		}
	}
}

void shanshuo(void)
{
	uchar i,sign;
//	if(ss_js>0)
//	{
		if(ss_count==5)
//		if(ss_count>=0&&ss_count<=5)
		{
		 sign=4;
		for(i=0;i<ss_js;i++)
		{
			switch (ss_tab[i][0])
			{
				case 1:
				write_lcd_shuzi_yiwei(sign,ss_tab[i][2]);
				break;
				case 2:
				write_lcd_shuzi_erwei(ss_tab[i][1],sign,ss_tab[i][2]);
				break;
				case 3:
				write_lcd_shuzi_sanwei(ss_tab[i][1],sign,ss_tab[i][2]);
				break;
				case 4:
				write_lcd_kuang(ss_tab[i][1],sign);
				break;
				case 5:
				write_lcd_zi(ss_tab[i][1],sign);
				break;
				case 6:
				write_lcd_point(ss_tab[i][1],sign);
				break;
			}
		}
		}
		else if(ss_count==10)
//		else if(ss_count>5&&ss_count<=10)
		{
			sign=3;
			if(	key_mid!=0||key_zhi!=0 )
			sign=4;
		for(i=0;i<ss_js;i++)
		{
			switch (ss_tab[i][0])
			{
				case 1:
				write_lcd_shuzi_yiwei(sign,ss_tab[i][2]);
				break;
				case 2:
				write_lcd_shuzi_erwei(ss_tab[i][1],sign,ss_tab[i][2]);
				break;
				case 3:
				write_lcd_shuzi_sanwei(ss_tab[i][1],sign,ss_tab[i][2]);
				break;
				case 4:
				write_lcd_kuang(ss_tab[i][1],sign);
				break;
				case 5:
				write_lcd_zi(ss_tab[i][1],sign);
				break;
				case 6:
				write_lcd_point(ss_tab[i][1],sign);
				break;
			}
		}
		}
		else if(ss_count>10)ss_count=0;

//	}
}

void shidukongzhi(uint16 zhi,uchar weizhi,uchar sign)
{
	write_lcd_shuzi_erwei(weizhi,sign,zhi/10);
	if(zhi%10==5)	write_lcd_point(weizhi/4+1,sign);
	else write_lcd_point(weizhi/4+1,0);
}

void lcd_xiepingmu(uchar bz)
{
	uchar i;
	uchar weizhi[19]={3,4,7,8,11,12,15,16,19,20,23,24,27,28,31,32,35,36,39};
	if(bz==1)
	{
		//	gongzuo[0]=HDByteReadI2C(0xa0,0x01,0x08);//读取所选烘烤方式的当前方式
		//	DelayMS(5);
	//		lsi2c=(yushequxian-10)*64;
		HDSequentialReadI2C(0xa0,0x00,(0x00+(gongzuo[0]-10)*64),yushewendu,10);
		DelayMS(10);
		HDSequentialReadI2C(0xa0,0x00,(0x0a+(gongzuo[0]-10)*64),yusheshidu1,10);
		DelayMS(10);
		HDSequentialReadI2C(0xa0,0x00,(0x14+(gongzuo[0]-10)*64),yushetime,19);
		DelayMS(10);
			gongzuo[8]=HDByteReadI2C(0xa0,0x01,0x10);
		DelayMS(5);
		for(i=0;i<10;i++)
		{
			yusheshidu[i]=shiduyingyongzhuanhuan_2to1(yusheshidu1[i]);
		}
	}
	if(bz==0&&ok_bz==0)
	{
		HDByteWriteI2C(0xa0,0x01,0x08,gongzuo[0]);
		DelayMS(5);
	//		lsi2c=(yushequxian-10)*64;
		for(i=0;i<10;i++)
		{
			yusheshidu1[i]=shiduyingyongzhuanhuan_1to2(yusheshidu[i]);
		}
		HDduanWriteI2C(0xa0,0x00,(0x00+(gongzuo[0]-10)*64),yushewendu,10);
		DelayMS(10);
		HDduanWriteI2C(0xa0,0x00,(0x0a+(gongzuo[0]-10)*64),yusheshidu1,10);
		DelayMS(10);
		HDduanWriteI2C(0xa0,0x00,(0x14+(gongzuo[0]-10)*64),yushetime,19);
		DelayMS(10);
		HDByteWriteI2C(0xa0,0x01,0x10,gongzuo[8]);
		DelayMS(5);
	}

if(bz==1||ok_bz==1)
{
	clear_shuzikuang();
	if(set_key!=2)
	{

		write_lcd_zi(gongzuo[0],1);
		write_lcd_kuang(gongzuo[0]+30,1);
	}
		write_lcd_kuang(weizhi[gongzuo[1]],1);
	if(gongzuo[0]!=10)
	{
		for(i=0;i<10;i++)
		{
			write_lcd_shuzi_erwei((i*4+1),1,yushewendu[i]);
			write_lcd_shuzi_erwei((i*4+2),1,yusheshidu[i]/10);
			if(yusheshidu[i]%10==5)	write_lcd_point(i+1,1);
			else write_lcd_point(i+1,0);
			write_lcd_shuzi_erwei((i*4+3),1,yushetime[i*2]);
			if(i*4+4!=40)
			write_lcd_shuzi_erwei((i*4+4),1,yushetime[i*2+1]);
		}
	}
	else 
	{
	//	write_lcd_shuzi_sanwei(4,1,gongzuo[8]);
		for(i=0;i<(gongzuo[8]/2+1);i++)
		{
			write_lcd_shuzi_erwei((i*4+1),1,yushewendu[i]);
			write_lcd_shuzi_erwei((i*4+2),1,yusheshidu[i]/10);
			if(yusheshidu[i]%10==5)	write_lcd_point(i+1,1);
			else write_lcd_point(i+1,0);
			write_lcd_shuzi_erwei((i*4+3),1,yushetime[i*2]);
			if(i*4+4!=44&&i>0)

			write_lcd_shuzi_erwei(((i-1)*4+4),1,yushetime[(i-1)*2+1]);
		}
/*
			for(i=gongzuo[8]/2+1;i<10;i++)
		{
			write_lcd_shuzi_erwei((i*4+1),0,yushewendu[i]);
			write_lcd_shuzi_erwei((i*4+2),0,yusheshidu[i]/10);
		//	if(yusheshidu[i]%10==5)	write_lcd_point(i+1,1);
			 write_lcd_point(i+1,0);
			write_lcd_shuzi_erwei((i*4+3),0,yushetime[i*2]);
			if(i*4+4!=40&&i>0)
			write_lcd_shuzi_erwei(((i-1)*4+4),0,yushetime[(i-1)*2+1]);
		}
*/
	}
ok_bz=0;
}
}

void clear_shuzikuang(void)
{
	uchar i;
	if(set_key!=2)
	{
		for(i=0;i<4;i++)
		{
			write_lcd_zi(10+i,0);
			write_lcd_kuang(i+40,0);
		}
	}
	for(i=0;i<10;i++)
	{
		write_lcd_shuzi_erwei((i*4+1),0,yushewendu[i]);
		write_lcd_shuzi_erwei((i*4+2),0,yusheshidu[i]/10);
	//	if(yusheshidu[i]%10==5)	write_lcd_point(i+1,1);
	//	else write_lcd_point(i+1,0);
		write_lcd_point(i+1,0);
		write_lcd_shuzi_erwei((i*4+3),0,yushetime[i*2]);
		write_lcd_kuang((i*4+3),0);
		if(i*4+4!=40)
		{
			write_lcd_shuzi_erwei((i*4+4),0,yushetime[i*2+1]);
			write_lcd_kuang((i*4+4),0);
		}
	}
}
