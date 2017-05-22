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

extern uchar ret_18B20;						//18B20��λ��־
extern uchar SWD_Z,SWD_X,SSD_Z,SSD_X,XWD_Z,XWD_X,XSD_Z,XSD_X ;  //�¶ȡ�ʪ�ȵ�������С��
extern uint16 WD[4];
extern uchar key256;
extern uchar chaxunbz;
extern uchar key_mid;
extern uchar ds18b20_1bz;

	uchar D_D1=0,D_D2=0,D_D3=0,D_D4=0,G_D1=0,G_D2=0,G_D3=0,G_D4=0;       //�����¶�

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

//****************д18b20д�ֽں���*****************************
//������������д�������һ���ģ���ͬʱд
//��������д����1���Ȱ��������ͣ�Ȼ����15us���ͷ�����
//��������д����0����������������60us
//дһλ����������Ҫ60us
//��λ����֮��������ʱ1us
void Write_byte_18B20(uchar val)
{
	uchar i,t; 
	for(i=8;i>0;i--)
	{
		t=val&0x01;                            //���λ�Ƴ�
		DQ_LOW();
		__delay32(11);                                 //��������5us
		if(t==1)  DQ_HIGH_HANDS(); //DQ_HIGH();                  //���д1,���ߵ�ƽ
		__delay32(60);                             //��ʱ30us  
DQ_HIGH_HANDS();
	//	DQ_HIGH(); 
		asm("nop");                              //����λ֮�����3us��ʱ
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		__delay32(11);
		__delay32(20); 
		val=val>>1;                               //����һλ
	}
}

uchar reset_18B20(void)
{
	uchar ret=0;
	DQ_LOW() ;                              //���������͵�ƽ
	__delay32(1200);                        //��ʱ480us  
DQ_HIGH_HANDS();
//	DQ_HIGH();                              //�ͷ����ߵȵ�����������,������15~60us
//	__delay32(80);                //��ʱ40us
//	if(DS18B20_ONE_IN==1) ret=1;                     //û�н��յ�Ӧ���źţ���λʧ��
//	if(DS18B20_TWO_IN==1) ret=ret+2;                 //û�н��յ�Ӧ���źţ���λʧ��
//	if(DS18B20_THR_IN==1) ret=ret+4;                     //û�н��յ�Ӧ���źţ���λʧ��
//	if(DS18B20_FOU_IN==1) ret=ret+8;                 //û�н��յ�Ӧ���źţ���λʧ��
__delay32(140); 
	if(DS18B20_ONE_IN==1) ret=1;                     //û�н��յ�Ӧ���źţ���λʧ��
	if(DS18B20_TWO_IN==1) ret=ret+2;                 //û�н��յ�Ӧ���źţ���λʧ��
	if(DS18B20_THR_IN==1) ret=ret+4;                     //û�н��յ�Ӧ���źţ���λʧ��
	if(DS18B20_FOU_IN==1) ret=ret+8;                 //û�н��յ�Ӧ���źţ���λʧ��

	__delay32(880);                      //��ʱ440us
	return(ret);
}

//****************18b20���ֽں���********************************
//�����¶�����ǰ��׼���ú��ж���ʱ600��Ms��ִ��
//�����������Ķ����������ǲ�ͬ�ģ�4�ηֱ�������ȶ����¶ȡ�ʪ�ȵĵ�8λ
//�ٶ����¶ȡ�ʪ�ȵĸ�8λ�����ղ���WD_Z,WD_X,SD_Z,SD_X�¶ȡ�ʪ�ȵ�������С��
//����������������������1US��Ȼ���ͷ�
//��������������1��18B20��������״̬����
//��������������0��18B20��⵽�������ͺ����������������60ms
//�����������������ߺ��15us��ȡ�����ϵ�״̬
//��ȡ1λ����������Ҫ60us
void Read_byte_18B20(void)
{
	uchar i;


	//�����¶ȡ�ʪ�ȵĵ�8λ
	for(i=8;i>0;i--)
	{
		D_D1>>=1;   //�¶ȵ�8λ
		D_D2>>=1;   //ʪ�ȵ�8λ
		D_D3>>=1;   //�¶ȵ�8λ
		D_D4>>=1;   //ʪ�ȵ�8λ
		DQ_LOW();
		asm("nop");								//������������3us
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");								//����λ֮�����3us��ʱ
		asm("nop");
//		__delay32(20); 
DQ_HIGH_HANDS();
	//	DQ_HIGH();                               //�����ߵ�ƽ
		__delay32(17);							//�ͷ����ߺ󱣳�7us�ٶ�ȡ����
		if(DS18B20_ONE_IN) D_D1|=0x80;
		if(DS18B20_TWO_IN) D_D2|=0x80;
		if(DS18B20_THR_IN) D_D3|=0x80;
		if(DS18B20_FOU_IN) D_D4|=0x80;
		__delay32(100);							//��ʱ50us����֤ÿ1λ��60us��ʱ
	}
//�����¶ȡ�ʪ�ȵĸ�8λ
	for(i=8;i>0;i--)
	{
		G_D1>>=1;   //�¶ȸ�8λ
		G_D2>>=1;   //ʪ�ȸ�8λ
		G_D3>>=1;   //�¶ȸ�8λ
		G_D4>>=1;   //ʪ�ȸ�8λ
		DQ_LOW();
		asm("nop");									//������������3us
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");									//����λ֮�����3us��ʱ
		asm("nop");
//		__delay32(20); 
DQ_HIGH_HANDS();
	//	DQ_HIGH();                               //�����ߵ�ƽ
		__delay32(17);							//�ͷ����ߺ󱣳�7us�ٶ�ȡ����
		if(DS18B20_ONE_IN) G_D1|=0x80;
		if(DS18B20_TWO_IN) G_D2|=0x80;
		if(DS18B20_THR_IN) G_D3|=0x80;
		if(DS18B20_FOU_IN) G_D4|=0x80;
		__delay32(100);							//��ʱ50us����֤ÿ1λ��60us��ʱ
	}

}
/*
//����18B20��ʼת��,���һ�俪��ʱ�ж�
void Start_18B20(void)
{
	DQ_HIGH();

    
//    TMR3L=0xaf;
  //  TMR3H=0x3c;
//	PIE2bits.TMR3IE=1;   //����TMR3����ж�
}
*/
//-------------------------------------------------
//ʱ���ж�600MS����¶Ⱥ�ʪ�ȣ�����18B20��ʼת��
void get_star_temp(void)
{ 
//LATEbits.LATE6=!LATEbits.LATE6;
uchar lsdebz=0;
	uchar SWX,SSX,XWX,XSX;
	uint16 wdyz1_g,wdyz2_g,wdyz1_d,wdyz2_d;
  //����������Ҫ��ʱ600��MS
	_T5IE=0; 
	IEC3bits.RTCIE=0;
	IEC0bits.AD1IE=0;
//_CMIE=0;
	ret_18B20=reset_18B20();                //�ٴθ�λ���ȴ��ӻ�Ӧ�� 
//	if(ret_18B20==0)
//	{
//	if(ret_18B20!=0){sound_read_num(ret_18B20);	DelayMS(1000);}
	Write_byte_18B20(0XCC);                 //����ROMƥ�� 
	Write_byte_18B20(0XBE);                 //���Ͷ��¶����� 

	Read_byte_18B20();                      //�����¶�
	wdyz1_d=D_D1+D_D2+D_D3+D_D4;
	wdyz1_g=G_D1+G_D2+G_D3+G_D4;

	ret_18B20=reset_18B20();                //�ٴθ�λ���ȴ��ӻ�Ӧ�� 
//	if(ret_18B20!=0){sound_read_num(ret_18B20);	DelayMS(1000);}
	Write_byte_18B20(0XCC);                 //����ROMƥ�� 
	Write_byte_18B20(0XBE);                 //���Ͷ��¶����� 

	Read_byte_18B20();                      //�����¶�
	wdyz2_d=D_D1+D_D2+D_D3+D_D4;
	wdyz2_g=G_D1+G_D2+G_D3+G_D4;

DQ_HIGH_HANDS();
//	DQ_HIGH();                              //�ͷ�����  
	ret_18B20=reset_18B20();           //��λ�ȴ��ӻ�Ӧ�� 
//����0��RE1������1��RE2������2������������3                    
	Write_byte_18B20(0XCC);           //����ROMƥ�� 
	Write_byte_18B20(0X44);           //�����¶�ת������ 
 
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
		SWD_Z=((D_D1>>4)|(G_D1<<4))&0X7f;              //�¶��������֣���7λ��Ч
		SSD_Z=((D_D2>>4)|(G_D2<<4))&0X7f;               //ʪ���������֣���7λ��Ч
		XWD_Z=((D_D3>>4)|(G_D3<<4))&0X7f;              //�¶��������֣���7λ��Ч
		XSD_Z=((D_D4>>4)|(G_D4<<4))&0X7f;               //ʪ���������֣���7λ��Ч
		SWX=D_D1<<4;                               //�¶�С������
		SSX=D_D2<<4;                               //ʪ��С������
		XWX=D_D3<<4;                               //�¶�С������
		XSX=D_D4<<4;                               //ʪ��С������
	//LATEbits.LATE6=!LATEbits.LATE6;
		SWD_X=0;   //�¶�С������
		//���±���һλС��
		if (SWX & 0x80) SWD_X=SWD_X+50;//С��ʮλ
		if (SWX & 0x40) SWD_X=SWD_X+25;//С����λ
		if (SWX & 0x20) SWD_X=SWD_X+12;
		if (SWX & 0x10) SWD_X=SWD_X+6;     
		SWD_X=SWD_X / 10;          //����1λ
	
		SSD_X=0;    //ʪ��С������
		if (SSX & 0x80) SSD_X=SSD_X+50;//С��ʮλ
		if (SSX & 0x40) SSD_X=SSD_X+25;//С����λ
		if (SSX & 0x20) SSD_X=SSD_X+12;
		if (SSX & 0x10) SSD_X=SSD_X+6;      
		SSD_X=SSD_X / 10;             //����1λ
	
		XWD_X=0;   //�¶�С������
		//���±���һλС��
		if (XWX & 0x80) XWD_X=XWD_X+50;//С��ʮλ
		if (XWX & 0x40) XWD_X=XWD_X+25;//С����λ
		if (XWX & 0x20) XWD_X=XWD_X+12;
		if (XWX & 0x10) XWD_X=XWD_X+6;     
		XWD_X=XWD_X / 10;          //����1λ
	
		XSD_X=0;    //ʪ��С������
		if (XSX & 0x80) XSD_X=XSD_X+50;//С��ʮλ
		if (XSX & 0x40) XSD_X=XSD_X+25;//С����λ
		if (XSX & 0x20) XSD_X=XSD_X+12;
		if (XSX & 0x10) XSD_X=XSD_X+6;      
		XSD_X=XSD_X / 10;             //����1λ
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

