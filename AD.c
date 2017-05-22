#include "p24FJ64GA006.h"
#include "Pin_Definitions.h"
#include "lcd.h"
#include "math.h"
#include "delay.h"
#include "guzhangbaojing.h"

void __delay32(unsigned long cycles);
uchar jifen_ad_caiyang(uchar jcz);

extern uint16 ad_axdl,ad_bxdl,ad_cxdl,ad_dy;
extern uint16 ad_amax,ad_amin;//,ad_bmax[5]
extern long ad_bmax[8],ad_bmin[8];
extern uchar ad_bz,ad_wzbz,ad_cytimes,ad_lc;
extern uchar time_1s,ad_1s;//

extern uchar ad_tdbz;
extern uchar ad_ps_bz,ad_count;//,ps_dl
extern uint16 ps_dl;
extern uint16 ad_dlz[3];
extern uint16 dyzhi;									//电压值

extern uchar ls_zddl[3];
extern uchar ls_zddl1[3];
extern uchar ls_dlbz;

extern uchar set_ui_zhi[4];			//电压电流参数设置
extern uchar dz_wc_bz;								//堵转检测完成一次标志
extern uchar san_dan_xz;					//三、单相风机修正值
extern uint16 ad_dianchi;				//电池电压ad值
extern uchar bj_bz,bj_cs;				//报警标志 次数
extern uint16 ad_dichi_dy;
extern uchar sound_all[5][4];	
//各项报警声音预存数组分别【风机 温度 湿度 电压】【对应 段数 间隔时间 报警次数 响不响】
extern uchar gongdian_bz;				//供电标志
extern uchar fengjiqishi_bz;				//风机起始开关标志
//*****************************
uint16 ad_dycy(void)
{
	uint16 ad_max=0;
	TMR2=0;
	_T2IF=0;
	while(!_T2IF)
	{
		AD1CON1bits.SAMP = 1; // start sampling then...
	//	after 31Tad go to conversion
		__delay32(13);
		AD1CON1bits.SAMP = 0; // start sampling then...
		while (!AD1CON1bits.DONE); // conversion done?
//		ADCValue = ADC1BUF0; // yes then get ADC value
		if(ADC1BUF0>ad_max) ad_max=ADC1BUF0;
	//	if(ADCValue<ad_min) ad_min=ADCValue;
	}
return (ad_max);
}
//*****************************
uint16 ad_220v_zhi(void)
{
	uint16 dy[5],ls; 
	uchar i,j;
	AD1CHSbits.CH0SA=10;
	for(i=0;i<5;i++)
	{
		dy[i]=ad_dycy();
	}
	for(j=0;j<4;j++)
	{
		for(i=j+1;i<5;i++)
		{
			if(dy[j]<dy[i])
			{
				ls=dy[i];
				dy[i]=dy[j];
				dy[j]=ls;
			}
		}
	}
	return(dy[1]+dy[2]+dy[3]);
}
//*****************************
uint16 ad_ADL_zhi(void)
{
	uint16 dy[5],ls; 
	uchar i,j;
   /*
	AD1PCFGbits.PCFG3=0;
	AD1PCFGbits.PCFG4=1;
	AD1PCFGbits.PCFG5=0;
	 TRISBbits.TRISB4=0;
	LATBbits.LATB4=0;
*/
	AD1CHSbits.CH0SA=3;
//	__delay32(400);
	for(i=0;i<5;i++)
	{
		dy[i]=ad_dycy();
	}
	for(j=0;j<4;j++)
	{
		for(i=j+1;i<5;i++)
		{
			if(dy[j]<dy[i])
			{
				ls=dy[i];
				dy[i]=dy[j];
				dy[j]=ls;
			}
		}
	}
	write_lcd_shuzi_sanwei(5,1,dy[0]);
	return(dy[1]+dy[2]+dy[3]);
}
//*****************************
uint16 ad_CDL_zhi(void)
{
	uint16 dy[5],ls; 
	uchar i,j;
   /*
	AD1PCFGbits.PCFG3=0;
	AD1PCFGbits.PCFG4=1;
	AD1PCFGbits.PCFG5=0;
	 TRISBbits.TRISB4=0;
	LATBbits.LATB4=0;
*/
	AD1CHSbits.CH0SA=5;
//	__delay32(400);
	for(i=0;i<5;i++)
	{
		dy[i]=ad_dycy();
	}
	for(j=0;j<4;j++)
	{
		for(i=j+1;i<5;i++)
		{
			if(dy[j]<dy[i])
			{
				ls=dy[i];
				dy[i]=dy[j];
				dy[j]=ls;
			}
		}
	}
	return(dy[1]+dy[2]+dy[3]);
}
//*****************************
uchar ad_Axdianliu(void)
{
	uchar bz=0;
	AD1PCFGbits.PCFG3=0;
	AD1PCFGbits.PCFG4=1;
	AD1PCFGbits.PCFG5=0;
	__delay32(20000);
	TRISBbits.TRISB4=0;
	LATBbits.LATB4=0;
	AD1CHSbits.CH0SA=3;

	bz=jifen_ad_caiyang(1);
	return(bz);
}
//*****************************
uchar ad_Cxdianliu(void)
{
	uchar bz=0;
	AD1PCFGbits.PCFG3=0;
	AD1PCFGbits.PCFG4=1;
	AD1PCFGbits.PCFG5=0;
	__delay32(20000);
	TRISBbits.TRISB4=0;
	LATBbits.LATB4=0;
	AD1CHSbits.CH0SA=5;

	bz=jifen_ad_caiyang(3);
	return(bz);
}
//*****************************
uchar ad_Bxdianliu(void)
{
	uchar bz=0;
	AD1PCFGbits.PCFG3=1;
	AD1PCFGbits.PCFG4=0;
	AD1PCFGbits.PCFG5=1;
	__delay32(20000);
	TRISBbits.TRISB3=0;
	LATBbits.LATB3=0;
	TRISBbits.TRISB5=0;
	LATBbits.LATB5=0;
	AD1CHSbits.CH0SA=4;

	bz=jifen_ad_caiyang(2);
	return(bz);

}

uchar ad_dianya(void)
{
	uchar bz=0;
	AD1CHSbits.CH0SA=10;
	bz=jifen_ad_caiyang(4);
	return(bz);
}

uchar jifen_ad_caiyang(uchar jcz)
{
	uint16 ADCValue,ad_count=0,ad_pj;
	unsigned long ad_zong=0;
	uchar cs_bz=0;
	uint16 ad_max=0;
	uint16 ADCValue1=0;
	TMR2=0;
	_T2IF=0;
	AD1CON1bits.SAMP = 1; // start sampling then...
//	after 31Tad go to conversion
//	__delay32(13);
//	AD1CON1bits.SAMP = 0; // start sampling then...
		while (!AD1CON1bits.DONE); // conversion done?
		ADCValue = ADC1BUF0; // yes then get ADC value
		while(ADCValue>0&&!_T2IF)
		{
			AD1CON1bits.SAMP = 1; // start sampling then...
			// after 31Tad go to conversion
	//		__delay32(13);
	//		AD1CON1bits.SAMP = 0; // start sampling then...
			while (!AD1CON1bits.DONE); // conversion done?
			ADCValue = ADC1BUF0; // yes then get ADC value
		}
		if(_T2IF)
		{
			cs_bz=cs_bz+1;
			return(cs_bz);
		}
	TMR2=0;
	_T2IF=0;

		while(ADCValue<1&&!_T2IF)
		{
			AD1CON1bits.SAMP = 1; // start sampling then...
	//		after 31Tad go to conversion
	//		__delay32(13);
	//		AD1CON1bits.SAMP = 0; // start sampling then...
			while (!AD1CON1bits.DONE); // conversion done?
			ADCValue = ADC1BUF0; // yes then get ADC value
			ADCValue1=ADCValue;
		}

		if(_T2IF)
		{
			cs_bz=cs_bz+2;
			return(cs_bz);
		}
	TMR2=0;
	_T2IF=0;

		ad_zong=ad_zong+ADCValue1*ADCValue1;
		ad_count++;
		while(ADCValue>0&&!_T2IF)
		{
			AD1CON1bits.SAMP = 1; // start sampling then...
	//		after 31Tad go to conversion
	//		__delay32(13);
	//		AD1CON1bits.SAMP = 0; // start sampling then...
			while (!AD1CON1bits.DONE); // conversion done?
			ADCValue = ADC1BUF0; // yes then get ADC value
			if(ADCValue>ad_max) ad_max=ADCValue;
		//	if(ADCValue<ad_min) ad_min=ADCValue;
			ad_zong=ad_zong+ADCValue*ADCValue;
			ad_count++;
			__delay32(100);
		}

		if(_T2IF)
		{
			cs_bz=cs_bz+4;
			return(cs_bz);
		}
		ad_pj=(sqrt(ad_zong/ad_count));
	switch (jcz)
	{
		case 1:
			ad_axdl=(sqrt(ad_zong/ad_count));
		break;
		case 2:
			ad_bxdl=(sqrt(ad_zong/ad_count));
		break;
		case 3:
			ad_cxdl=(sqrt(ad_zong/ad_count));
		break;
		case 4:
			ad_dy=(sqrt(ad_zong/ad_count));
		break;
	}

//		write_lcd_shuzi_sanwei(3,1,ad_max);
//		write_lcd_shuzi_sanwei(4,1,ad_pj);
//		write_lcd_shuzi_sanwei(5,1,ad_count);
//		write_lcd_shuzi_sanwei(5,1,ADCValue1);
//		write_lcd_shuzi_sanwei(6,1,(ad_zong));	
		return (cs_bz);	
}
//电压采样 启用中
void ad_zongduanDIANYAcaiyan(void)
{
	uint16 ls;
	uchar i,j;
long ls_dlz=0;
float ls_cs=0;
//	uint16 dyzhi=0;
	if(ad_1s&&ad_bz==0&&ad_tdbz==0)
	{
//	TRISBbits.TRISB14=1;
AD_DIANYA_DIR=1;
	AD1PCFGbits.PCFG12=0;
			__delay32(100);
//	DelayMS(5);
		IEC0bits.AD1IE=1;
		IFS0bits.AD1IF=0;
		AD1CHSbits.CH0SA=12;
		AD1CON1bits.ASAM=1;
		ad_lc=0;
		ad_bz=1;
	}
	if(ad_bz==1&&ad_cytimes==8&&ad_tdbz==0)
	{
		ad_bmax[ad_lc]=ad_amax;


		ad_amax=0;
		ad_bmin[ad_lc]=ad_amin;
		ad_amin=0xffff;
		ad_cytimes=0;
		ad_lc++;
		if(ad_lc==8)
		{
			for(j=0;j<7;j++)
			{
				for(i=j+1;i<8;i++)
				{
					if(ad_bmax[j]<ad_bmax[i])
					{
						ls=ad_bmax[i];
						ad_bmax[i]=ad_bmax[j];
						ad_bmax[j]=ls;
					}
					if(ad_bmin[j]>ad_bmin[i])
					{
						ls=ad_bmin[i];
						ad_bmin[i]=ad_bmin[j];
						ad_bmin[j]=ls;
					}
				}
			}

		//	dyzhi=(ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/9.5;
dyzhi=(ad_bmax[2]+ad_bmax[3]+ad_bmax[4]+ad_bmax[5]
-ad_bmin[2]-ad_bmin[3]-ad_bmin[4]-ad_bmin[5]);//*10/144;///set_ui_zhi[3]
if(dyzhi>20)dyzhi=dyzhi*10/set_ui_zhi[3];//set_ui_zhi[3]96
else dyzhi=0;
if(fengjiqishi_bz==1)dyzhi=dyzhi-0;//12
//ls_dlz=(ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3*set_ui_zhi[0];
//ad_dlz[0]=ls_dlz/100;
//ls_cs=(float)set_ui_zhi[3]/10;
//			write_lcd_shuzi_sanwei(4,1,ls_cs*10);
//		DelayMS(1000);
//dyzhi=(ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/ls_cs;
		//	write_lcd_shuzi_sanwei(7,1,dyzhi);
			ad_lc=0;
			ad_bz=0;
			IEC0bits.AD1IE=0;
			AD1CON1bits.ASAM=0;
	AD1PCFGbits.PCFG12=1;
//	TRISBbits.TRISB14=0;
AD_DIANYA_DIR=1;
//AD_DIANYA=0;
//	LATBbits.LATB14=0;
//	AD1PCFGbits.PCFG10=0;
			ad_tdbz=1;
	//		DelayMS(5);
		}
	}
}
//电流采样 启用中
void ad_zongduanAxiangcaiyan(void)
{
	uint16 ls;
	uchar i,j;
long ls_dlz=0;
float ls_cs=0;
	if(ad_1s==1&&ad_bz==0&&ad_tdbz==1)
	{
//	TRISCbits.TRISC1=1;
AD_ADIANLIU_DIR=1;
	AD1PCFGbits.PCFG1=0;
			__delay32(100);
	//	AD_ACCONTROL=0;
		IEC0bits.AD1IE=1;
		IFS0bits.AD1IF=0;
		AD1CHSbits.CH0SA=1;			//A项电流检测通道
//		AD1CHSbits.CH0SA=6;			//c项电流检测通道
		AD1CON1bits.ASAM=1;
		ad_lc=0;
		ad_bz=1;
	}
	if(ad_bz==1&&ad_cytimes==10&&ad_tdbz==1)
	{
		ad_bmax[ad_lc]=ad_amax;
		ad_amax=0;
		ad_bmin[ad_lc]=ad_amin;
		ad_amin=0xffff;
		ad_cytimes=0;
		ad_lc++;
		if(ad_lc==8)
		{
			for(j=0;j<7;j++)
			{
				for(i=j+1;i<8;i++)
				{
					if(ad_bmax[j]<ad_bmax[i])
					{
						ls=ad_bmax[i];
						ad_bmax[i]=ad_bmax[j];
						ad_bmax[j]=ls;
					}
					if(ad_bmin[j]>ad_bmin[i])
					{
						ls=ad_bmin[i];
						ad_bmin[i]=ad_bmin[j];
						ad_bmin[j]=ls;
					}
				}
			}
	AD1PCFGbits.PCFG1=1;
//	TRISCbits.TRISC1=0;
AD_ADIANLIU_DIR=1;
//AD_ADIANLIU=0;
//	LATCbits.LATC1=0;

//ad_dlz[0]=((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)*0.0996;
//ad_dlz[0]=((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3);
//ad_dlz[0]=((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)*0.11;
//////////ad_dlz[0]=(((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)*set_ui_zhi[0]/100);		//A项电流转换
//ls_dlz=(ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3*(set_ui_zhi[0]+san_dan_xz);
ls_dlz=(ad_bmax[2]+ad_bmax[3]+ad_bmax[4]+ad_bmax[5]
-ad_bmin[2]-ad_bmin[3]-ad_bmin[4]-ad_bmin[5]);///5*(set_ui_zhi[0]+san_dan_xz);
ls_dlz=ls_dlz*(set_ui_zhi[0]+140+san_dan_xz)/12;
//if(ls_dlz>20)ls_dlz=ls_dlz*(set_ui_zhi[0]+170+san_dan_xz)/17;//ls_dlz=ls_dlz/5*(set_ui_zhi[0]+san_dan_xz);
//else ls_dlz=0;
ad_dlz[0]=ls_dlz/100;
//ad_dlz[2]=((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)*set_ui_zhi[2]/100;		//C项电流转换
//ls_cs=set_ui_zhi[0]/1000;
//ad_dlz[0]=(((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)*ls_cs);
	//		write_lcd_shuzi_sanwei(3,1,(((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)+29)/9.241);
	//	write_lcd_shuzi_sanwei(3,1,(((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)+85.38)/24.789);
//			write_lcd_shuzi_sanwei(3,1,(((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)*0.0996));//*0.108
			ad_lc=0;
			ad_bz=0;
			IEC0bits.AD1IE=0;
			AD1CON1bits.ASAM=0;
			ad_tdbz=2;
	//		DelayMS(5);
		}
	}
}


void ad_zongduanCxiangcaiyan(void)
{
	uint16 ls;
	uchar i,j;
long ls_dlz=0;
float ls_cs=0;
	if(ad_1s==1&&ad_bz==0&&ad_tdbz==2)
	{
//	TRISCbits.TRISC0=1;
AD_CDIANLIU_DIR=1;
	AD1PCFGbits.PCFG11=0;
			__delay32(100);
	//	AD_ACCONTROL=0;
		IEC0bits.AD1IE=1;
		IFS0bits.AD1IF=0;
		AD1CHSbits.CH0SA=11;			//c项电流检测通道
//		AD1CHSbits.CH0SA=7;			//A项电流检测通道
		AD1CON1bits.ASAM=1;
		ad_lc=0;
		ad_bz=1;
	}
	if(ad_bz==1&&ad_cytimes==10&&ad_tdbz==2)
	{
		ad_bmax[ad_lc]=ad_amax;
		ad_amax=0;
		ad_bmin[ad_lc]=ad_amin;
		ad_amin=0xffff;
		ad_cytimes=0;
		ad_lc++;
		if(ad_lc==8)
		{
			for(j=0;j<7;j++)
			{
				for(i=j+1;i<8;i++)
				{
					if(ad_bmax[j]<ad_bmax[i])
					{
						ls=ad_bmax[i];
						ad_bmax[i]=ad_bmax[j];
						ad_bmax[j]=ls;
					}
					if(ad_bmin[j]>ad_bmin[i])
					{
						ls=ad_bmin[i];
						ad_bmin[i]=ad_bmin[j];
						ad_bmin[j]=ls;
					}
				}
			}
	AD1PCFGbits.PCFG11=1;
//	TRISCbits.TRISC0=0;
AD_CDIANLIU_DIR=1;
//AD_CDIANLIU=0;
//	LATCbits.LATC0=0;
//ad_dlz[2]=((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)*0.098;
//ad_dlz[2]=((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3);
//ad_dlz[2]=((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)*0.102;
//ad_dlz[0]=(((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)*set_ui_zhi[0]/100);		//A项电流转换
//////ad_dlz[2]=((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)*set_ui_zhi[2]/100;		//C项电流转换
//ls_dlz=(ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3*set_ui_zhi[2];
ls_dlz=(ad_bmax[2]+ad_bmax[3]+ad_bmax[4]+ad_bmax[5]
-ad_bmin[2]-ad_bmin[3]-ad_bmin[4]-ad_bmin[5]);///5*set_ui_zhi[2];
ls_dlz=ls_dlz*(set_ui_zhi[2]+140)/12;
//if(ls_dlz>20)ls_dlz=ls_dlz*(set_ui_zhi[2]+170)/17;//ls_dlz=ls_dlz/5*(set_ui_zhi[0]+san_dan_xz);
//else ls_dlz=0;
ad_dlz[2]=ls_dlz/100;
//ls_cs=set_ui_zhi[2]/1000;
//ad_dlz[2]=(((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)*ls_cs);
//			write_lcd_shuzi_sanwei(5,1,(((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)*0.098));//*0.108
	//		ad_1s=0;
			ad_lc=0;
			ad_bz=0;
			IEC0bits.AD1IE=0;
			AD1CON1bits.ASAM=0;
			ad_tdbz=3;
	//		DelayMS(5);
//	AD_ACCONTROL=1;
		}
	}
}

void ad_zongduanBxiangcaiyan(void)
{
	uint16 ls;
	uchar i,j;
long ls_dlz=0;
	if(ad_1s==1&&ad_bz==0&&ad_tdbz==3)
	{
//	TRISBbits.TRISB2=1;
	AD_BDIANLIU_DIR=1;
	AD1PCFGbits.PCFG10=0;
			__delay32(100);
//		AD_ACCONTROL=1;
		IEC0bits.AD1IE=1;
		IFS0bits.AD1IF=0;
		AD1CHSbits.CH0SA=10;
		AD1CON1bits.ASAM=1;
		ad_lc=0;
		ad_bz=1;

	}
	if(ad_bz==1&&ad_cytimes==10&&ad_tdbz==3)
	{
		ad_bmax[ad_lc]=ad_amax;
		ad_amax=0;
		ad_bmin[ad_lc]=ad_amin;
		ad_amin=0xffff;
		ad_cytimes=0;
		ad_lc++;
		if(ad_lc==8)
		{
			for(j=3;j<7;j++)
			{
				for(i=j+1;i<8;i++)
				{
					if(ad_bmax[j]<ad_bmax[i])
					{
						ls=ad_bmax[i];
						ad_bmax[i]=ad_bmax[j];
						ad_bmax[j]=ls;
					}
					if(ad_bmin[j]>ad_bmin[i])
					{
						ls=ad_bmin[i];
						ad_bmin[i]=ad_bmin[j];
						ad_bmin[j]=ls;
					}
				}
			}
	AD1PCFGbits.PCFG10=1;
//	TRISBbits.TRISB2=0;
	AD_BDIANLIU_DIR=1;
//	AD_BDIANLIU=0;
//	LATBbits.LATB2=0;
//ad_dlz[1]=((ad_bmax[4]+ad_bmax[5]+ad_bmax[6])/3)*0.176;
//ad_dlz[1]=((ad_bmax[4]+ad_bmax[5]+ad_bmax[6])/3);
//////////ad_dlz[1]=((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3)*set_ui_zhi[1]/100;
//ls_dlz=(ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3*set_ui_zhi[1];
ls_dlz=(ad_bmax[2]+ad_bmax[3]+ad_bmax[4]+ad_bmax[5]
-ad_bmin[2]-ad_bmin[3]-ad_bmin[4]-ad_bmin[5]);///5*set_ui_zhi[1];
ls_dlz=ls_dlz*(set_ui_zhi[1]+140)/12;
//if(ls_dlz>20)ls_dlz=ls_dlz*(set_ui_zhi[1]+170)/17;//ls_dlz=ls_dlz/5*(set_ui_zhi[0]+san_dan_xz);
//else ls_dlz=0;
ad_dlz[1]=ls_dlz/100;
//			write_lcd_shuzi_sanwei(4,1,(ad_bmax[4]+ad_bmax[5]+ad_bmax[6])/3);
			ad_lc=0;
			ad_bz=0;
			IEC0bits.AD1IE=0;
			AD1CON1bits.ASAM=0;
			ad_tdbz=4;
			ad_1s=0;
//	AD_ACCONTROL=0;
		}
	}
}

void ad_duzhanjiance(void)
{
uint16 ps_zong=0;
uchar i;
uint16 *p;
p=0x0300;
	if(ad_bz==0&&ad_ps_bz==1)
	{
	AD1PCFGbits.PCFG9=0;
		IEC0bits.AD1IE=1;
		IFS0bits.AD1IF=0;
		AD1CHSbits.CH0SA=9;
		AD1CON1bits.ASAM=1;
		ad_lc=0;
		ad_bz=1;
//LATEbits.LATE4=!LATEbits.LATE4;
//		dz_wc_bz=0;
	}

	if(ad_bz==1&&ad_cytimes==1&&ad_ps_bz==1)
	{	
		for(i=0;i<16;i++)
		{
			ps_zong=ps_zong+*p;
			p++;
		}
//LATEbits.LATE4=!LATEbits.LATE4;
		ps_dl=ps_zong/16;
//	write_lcd_shuzi_sanwei(1,1,ps_dl);
		dz_wc_bz=1;
		ad_cytimes=0;
	//	ad_bz=0;
		//	PCF8574_chose(5,0);
	}

}

void ad_dianchijiance(void)
{
	uint16 ls;
	uchar i,j;
//	static uchar bj_bz=0,bj_cs=0;
//float ls_cs=0;
	if(ad_1s==1&&ad_bz==0&&ad_tdbz==4)
	{
//	TRISBbits.TRISB15=1;
//	AD1PCFGbits.PCFG9=0;
			__delay32(100);
//		AD_ACCONTROL=0;
		IEC0bits.AD1IE=1;
		IFS0bits.AD1IF=0;
		AD1CHSbits.CH0SA=8;			//c项电流检测通道
//		AD1CHSbits.CH0SA=7;			//A项电流检测通道
		AD1CON1bits.ASAM=1;
		ad_lc=0;
		ad_bz=1;
	}
	if(ad_bz==1&&ad_cytimes==10&&ad_tdbz==4)
	{
		ad_bmax[ad_lc]=ad_amax;
		ad_amax=0;
		ad_cytimes=0;
		ad_lc++;
		if(ad_lc==5)
		{
			for(j=0;j<4;j++)
			{
				for(i=j+1;i<5;i++)
				{
					if(ad_bmax[j]<ad_bmax[i])
					{
						ls=ad_bmax[i];
						ad_bmax[i]=ad_bmax[j];
						ad_bmax[j]=ls;
					}
				}
			}

ad_dianchi=((ad_bmax[1]+ad_bmax[2]+ad_bmax[3])/3/1.55);		//C项电流转换

			ad_lc=0;
			ad_bz=0;
			IEC0bits.AD1IE=0;
			AD1CON1bits.ASAM=0;
			ad_tdbz=5;


			if(ad_dianchi<35)
			{
				if(bj_bz==0)
				{
					bj_bz=1;
					bj_cs=0;
					shengyingexiang_jiaru(4,66,25);
				}

				if(bj_bz==1)bj_cs++;

			}

			if(ad_dianchi>35&&bj_bz!=0)
			{
				shengyingexiang_huifu(4,66);
				bj_bz=0;
				bj_cs=0;
			}

			if(bj_cs>40 &&	bj_bz==1)//sound_all[4][2]
			{
				shengyingexiang_huifu(4,66);
				bj_bz=2;
				bj_cs=0;
			}
			if((ad_dianchi>570&&dyzhi>200)||dyzhi>200)gongdian_bz=0;
			if(ad_dianchi>570&&dyzhi<30)gongdian_bz=1;
			if(ad_dianchi<570&&ad_dianchi>50&&dyzhi<30)gongdian_bz=2;
//	write_lcd_shuzi_sanwei(3,1,bj_cs);
	//		DelayMS(5);
//	AD_ACCONTROL=1;
		}
	}
}

