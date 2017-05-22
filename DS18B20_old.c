#include "p24FJ64GA006.h"
#include "Pin_Definitions.h"
#include "sound.h"
#include "delay.h"
#include "lcd.h"

void DQ_LOW(void);
void DQ_HIGH(void);
void DQ_HIGH_HANDS(void);
//void Start_18B20(void);
//void get_temp(void);
void get_star_temp(void);
void Write_byte_18B20(uchar val);
uchar reset_18B20(void);

void __delay32(unsigned long cycles);

extern uchar ret_18B20;						//18B20复位标志
extern uchar SWD_Z,SWD_X,SSD_Z,SSD_X,XWD_Z,XWD_X,XSD_Z,XSD_X ;  //温度、湿度的整数和小数
extern uint16 WD[4];
extern uchar key256;
extern uchar chaxunbz;
extern uchar key_mid;
extern uchar ds18b20_1bz;

	uchar D_D1=0,D_D2=0,D_D3=0,D_D4=0,G_D1=0,G_D2=0,G_D3=0,G_D4=0;       //读出温度

void DQ_LOW(void)
{
	DS18B20_ONE_DIR=0;
	DS18B20_ONE_OT=0;
	DS18B20_TWO_DIR=0;
	DS18B20_TWO_OT=0;
	DS18B20_THR_DIR=0;
	DS18B20_THR_OT=0;
	DS18B20_FOU_DIR=0;
	DS18B20_FOU_OT=0;

}

void DQ_HIGH_HANDS(void)
{
	DS18B20_ONE_DIR=0;
	DS18B20_ONE_OT=1;
	DS18B20_TWO_DIR=0;
	DS18B20_TWO_OT=1;
	DS18B20_THR_DIR=0;
	DS18B20_THR_OT=1;
	DS18B20_FOU_DIR=0;
	DS18B20_FOU_OT=1;

}

void DQ_HIGH(void)
{
	DS18B20_ONE_DIR=1;
		asm("nop");
		asm("nop");
	DS18B20_TWO_DIR=1;
		asm("nop");
		asm("nop");
	DS18B20_THR_DIR=1;
		asm("nop");
		asm("nop");
	DS18B20_FOU_DIR=1;
//	DS18B20_ONE_OT=0;
//	DS18B20_TWO_OT=0;
//	DS18B20_THR_OT=0;
//	DS18B20_FOU_OT=0;
}

//****************写18b20写字节函数*****************************
//两个传感器的写入参数是一样的，故同时写
//主控制器写数据1：先把总线拉低，然后在15us内释放总线
//主控制器写数据0：把总线拉低至少60us
//写一位数据至少需要60us
//两位数据之间至少延时1us
void Write_byte_18B20(uchar val)
{
	uchar i,t; 
	for(i=8;i>0;i--)
	{
		t=val&0x01;                            //最低位移出
		DQ_LOW();
		__delay32(11);                                 //保持拉低5us
		if(t==1)  DQ_HIGH_HANDS(); //DQ_HIGH();                  //如果写1,拉高电平
		__delay32(60);                             //延时30us  
DQ_HIGH_HANDS();
	//	DQ_HIGH(); 
		asm("nop");                              //在两位之间插入3us延时
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		__delay32(11);
		__delay32(20); 
		val=val>>1;                               //右移一位
	}
}

uchar reset_18B20(void)
{
	uchar ret=0;
	DQ_LOW() ;                              //主机拉至低电平
	__delay32(1200);                        //延时480us  
DQ_HIGH_HANDS();
//	DQ_HIGH();                              //释放总线等电阻拉高总线,并保持15~60us
//	__delay32(80);                //延时40us
//	if(DS18B20_ONE_IN==1) ret=1;                     //没有接收到应答信号，复位失败
//	if(DS18B20_TWO_IN==1) ret=ret+2;                 //没有接收到应答信号，复位失败
//	if(DS18B20_THR_IN==1) ret=ret+4;                     //没有接收到应答信号，复位失败
//	if(DS18B20_FOU_IN==1) ret=ret+8;                 //没有接收到应答信号，复位失败
__delay32(140); 
	if(DS18B20_ONE_IN==1) ret=1;                     //没有接收到应答信号，复位失败
	if(DS18B20_TWO_IN==1) ret=ret+2;                 //没有接收到应答信号，复位失败
	if(DS18B20_THR_IN==1) ret=ret+4;                     //没有接收到应答信号，复位失败
	if(DS18B20_FOU_IN==1) ret=ret+8;                 //没有接收到应答信号，复位失败

	__delay32(880);                      //延时440us
	return(ret);
}

//****************18b20读字节函数********************************
//读出温度是在前期准备好后中断延时600个Ms后执行
//两个传感器的读出的数据是不同的，4次分别读出，先读出温度、湿度的低8位
//再读出温度、湿度的高8位，最终产生WD_Z,WD_X,SD_Z,SD_X温度、湿度的整数和小数
//主控制器把总线拉低至少1US，然后释放
//主控制器读数据1：18B20保持总线状态不变
//主控制器读数据0：18B20检测到总线拉低后继续拉低总线至少60ms
//主控制器在拉低总线后的15us读取总线上的状态
//读取1位数据至少需要60us
void Read_byte_18B20(void)
{
	uchar i;


	//读出温度、湿度的低8位
	for(i=8;i>0;i--)
	{
		D_D1>>=1;   //温度低8位
		D_D2>>=1;   //湿度低8位
		D_D3>>=1;   //温度低8位
		D_D4>>=1;   //湿度低8位
		DQ_LOW();
		asm("nop");								//保持总线拉低3us
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");								//在两位之间插入3us延时
		asm("nop");
//		__delay32(20); 
DQ_HIGH_HANDS();
	//	DQ_HIGH();                               //拉至高电平
		__delay32(17);							//释放总线后保持7us再读取数据
		if(DS18B20_ONE_IN) D_D1|=0x80;
		if(DS18B20_TWO_IN) D_D2|=0x80;
		if(DS18B20_THR_IN) D_D3|=0x80;
		if(DS18B20_FOU_IN) D_D4|=0x80;
		__delay32(100);							//延时50us，保证每1位的60us延时
	}
//读出温度、湿度的高8位
	for(i=8;i>0;i--)
	{
		G_D1>>=1;   //温度高8位
		G_D2>>=1;   //湿度高8位
		G_D3>>=1;   //温度高8位
		G_D4>>=1;   //湿度高8位
		DQ_LOW();
		asm("nop");									//保持总线拉低3us
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");									//在两位之间插入3us延时
		asm("nop");
//		__delay32(20); 
DQ_HIGH_HANDS();
	//	DQ_HIGH();                               //拉至高电平
		__delay32(17);							//释放总线后保持7us再读取数据
		if(DS18B20_ONE_IN) G_D1|=0x80;
		if(DS18B20_TWO_IN) G_D2|=0x80;
		if(DS18B20_THR_IN) G_D3|=0x80;
		if(DS18B20_FOU_IN) G_D4|=0x80;
		__delay32(100);							//延时50us，保证每1位的60us延时
	}

}
/*
//启动18B20开始转换,最后一句开延时中断
void Start_18B20(void)
{
	DQ_HIGH();

    
//    TMR3L=0xaf;
  //  TMR3H=0x3c;
//	PIE2bits.TMR3IE=1;   //允许TMR3溢出中断
}
*/
//-------------------------------------------------
//时间中断600MS后读温度和湿度，启动18B20开始转换
void get_star_temp(void)
{ 
//LATEbits.LATE6=!LATEbits.LATE6;
uchar lsdebz=0;
	uchar SWX,SSX,XWX,XSX;
	uint16 wdyz1_g,wdyz2_g,wdyz1_d,wdyz2_d;
  //两线制最少要延时600个MS
	_T5IE=0; 
	IEC3bits.RTCIE=0;
	IEC0bits.AD1IE=0;
//_CMIE=0;
	ret_18B20=reset_18B20();                //再次复位，等待从机应答 
//	if(ret_18B20==0)
//	{
//	if(ret_18B20!=0){sound_read_num(ret_18B20);	DelayMS(1000);}
	Write_byte_18B20(0XCC);                 //忽略ROM匹配 
	Write_byte_18B20(0XBE);                 //发送读温度命令 

	Read_byte_18B20();                      //读出温度
	wdyz1_d=D_D1+D_D2+D_D3+D_D4;
	wdyz1_g=G_D1+G_D2+G_D3+G_D4;

	ret_18B20=reset_18B20();                //再次复位，等待从机应答 
//	if(ret_18B20!=0){sound_read_num(ret_18B20);	DelayMS(1000);}
	Write_byte_18B20(0XCC);                 //忽略ROM匹配 
	Write_byte_18B20(0XBE);                 //发送读温度命令 

	Read_byte_18B20();                      //读出温度
	wdyz2_d=D_D1+D_D2+D_D3+D_D4;
	wdyz2_g=G_D1+G_D2+G_D3+G_D4;

DQ_HIGH_HANDS();
//	DQ_HIGH();                              //释放总线  
	ret_18B20=reset_18B20();           //复位等待从机应答 
//正常0，RE1不正常1，RE2不正常2，两个不正常3                    
	Write_byte_18B20(0XCC);           //忽略ROM匹配 
	Write_byte_18B20(0X44);           //发送温度转化命令 
 
//	DS18B20_ONE_DIR=0;
//	DS18B20_TWO_DIR=0;
//	DS18B20_THR_DIR=0;
//	DS18B20_FOU_DIR=0;
//	DS18B20_ONE_OT=1;
//	DS18B20_TWO_OT=1;
//	DS18B20_THR_OT=1;
//	DS18B20_FOU_OT=1;
	_T5IE=1; 
	IEC3bits.RTCIE=1;
	IEC0bits.AD1IE=1;
//_CMIE=1;
	if(wdyz1_g==wdyz2_g&&wdyz1_d==wdyz2_d)
	{
		SWD_Z=((D_D1>>4)|(G_D1<<4))&0X7f;              //温度整数部分，低7位有效
		SSD_Z=((D_D2>>4)|(G_D2<<4))&0X7f;               //湿度整数部分，低7位有效
		XWD_Z=((D_D3>>4)|(G_D3<<4))&0X7f;              //温度整数部分，低7位有效
		XSD_Z=((D_D4>>4)|(G_D4<<4))&0X7f;               //湿度整数部分，低7位有效
		SWX=D_D1<<4;                               //温度小数部分
		SSX=D_D2<<4;                               //湿度小数部分
		XWX=D_D3<<4;                               //温度小数部分
		XSX=D_D4<<4;                               //湿度小数部分
	//LATEbits.LATE6=!LATEbits.LATE6;
		SWD_X=0;   //温度小数部分
		//以下保留一位小数
		if (SWX & 0x80) SWD_X=SWD_X+50;//小数十位
		if (SWX & 0x40) SWD_X=SWD_X+25;//小数个位
		if (SWX & 0x20) SWD_X=SWD_X+12;
		if (SWX & 0x10) SWD_X=SWD_X+6;     
		SWD_X=SWD_X / 10;          //保留1位
	
		SSD_X=0;    //湿度小数部分
		if (SSX & 0x80) SSD_X=SSD_X+50;//小数十位
		if (SSX & 0x40) SSD_X=SSD_X+25;//小数个位
		if (SSX & 0x20) SSD_X=SSD_X+12;
		if (SSX & 0x10) SSD_X=SSD_X+6;      
		SSD_X=SSD_X / 10;             //保留1位
	
		XWD_X=0;   //温度小数部分
		//以下保留一位小数
		if (XWX & 0x80) XWD_X=XWD_X+50;//小数十位
		if (XWX & 0x40) XWD_X=XWD_X+25;//小数个位
		if (XWX & 0x20) XWD_X=XWD_X+12;
		if (XWX & 0x10) XWD_X=XWD_X+6;     
		XWD_X=XWD_X / 10;          //保留1位
	
		XSD_X=0;    //湿度小数部分
		if (XSX & 0x80) XSD_X=XSD_X+50;//小数十位
		if (XSX & 0x40) XSD_X=XSD_X+25;//小数个位
		if (XSX & 0x20) XSD_X=XSD_X+12;
		if (XSX & 0x10) XSD_X=XSD_X+6;      
		XSD_X=XSD_X / 10;             //保留1位
	//	_T5IE=1; 
//		if()
		if(SHANGXIAP==0)
		{
			WD[0]=SWD_Z*10+SWD_X;
			WD[1]=SSD_Z*10+SSD_X;
			WD[2]=XWD_Z*10+XWD_X;
			WD[3]=XSD_Z*10+XSD_X;
			if(chaxunbz==0)
			{
				write_lcd_zi(14,1);
				write_lcd_kuang(44,1);
				write_lcd_zi(15,0);
				write_lcd_kuang(45,0);
			}
		}
		else
		{
			WD[0]=XWD_Z*10+XWD_X;
			WD[1]=XSD_Z*10+XSD_X;
			WD[2]=SWD_Z*10+SWD_X;
			WD[3]=SSD_Z*10+SSD_X;
			if(chaxunbz==0)
			{
				write_lcd_zi(14,0);
				write_lcd_kuang(44,0);
				write_lcd_zi(15,1);
				write_lcd_kuang(45,1);
			}
		}

	}
//	}
//	else
//	{
		if(ds18b20_1bz==1&&ret_18B20<15)
		{
			ds18b20_1bz=2;
		}
		if(ds18b20_1bz==0)
		{
			WD[0]=65534;
			WD[1]=65534;
			WD[2]=65534;
			WD[3]=65534;
			ds18b20_1bz=1;
		}
		if(ret_18B20==15)
		{
			ds18b20_1bz=0;
		}
		if(ret_18B20-8>0)
		{
			WD[3]=65534;
			ret_18B20=ret_18B20-8;
		}
		if(ret_18B20-4>0)
		{
			WD[2]=65534;
			ret_18B20=ret_18B20-4;
		}
		if(ret_18B20-2>0)
		{
			WD[1]=65534;
			ret_18B20=ret_18B20-2;
		}
		if(ret_18B20-1==0)
		{
			WD[0]=65534;
			ret_18B20=ret_18B20-1;
		}
/*
if(key_mid==80)
{
//if(lsdebz==0)
lsdebz=1;
//else lsdebz=0;
}
if(lsdebz==1)
{
			WD[1]=655;
			WD[0]=460;
			WD[3]=655;
			WD[4]=460;
}
*/

//	}
}

