#include "p24FJ64GA006.h"
#include "delay.h"
#include "Pin_Definitions.h"
#include "sound.h"

void init_main(void);

//void init_T3(void);
//void init_OSC(void);

//void init_sound(void);
//void init_lcd_io(void);
//void init_key();
//void init_led_io(void);
//void i2c_port_init(void);

void init_main(void)
{
//TIME3 200us*******************************************************************
	T3CONbits.TON=1;       //time3 on
	T3CONbits.TCS=0;       //�ڲ�ʱ�ӣ�FOSC/2��
//	T3CONbits.TCKPS=0B10;  //10 = 1:64
	T3CONbits.TCKPS=0B00;  //00 = 1:1
	PR3=403;                //Timer3 ���ڼĴ�  0.1���ж� 0.125*256*3125=0.1��
//	TRISFbits.TRISF4=0;
	_T3IE=0;               //�����ж�
	_T3IP=5;              //�ж����ȼ�=5 ��
//TIME2 30ms*******************************************************************
	T2CONbits.TON=0;       //time3 on
	T2CONbits.TCS=0;       //�ڲ�ʱ�ӣ�FOSC/2��
	T2CONbits.TCKPS=0B01;  //11 = 1:64
	PR2=50000;                //Timer3 ���ڼĴ�  0.1���ж� 0.125*256*3125=0.1��
	//200ms

	_T2IE=1;               //�����ж�
//	_T2IP=2;              //�ж����ȼ�=2 ��
//}
//TIME5 100ms*******************************************************************
	T5CONbits.TON=1;       //time3 on
	T5CONbits.TCS=0;       //�ڲ�ʱ�ӣ�FOSC/2��
	T5CONbits.TCKPS=0B10;  //11 = 1:64
	PR5=3125;                //Timer3 ���ڼĴ�  0.1���ж� 0.125*256*3125=0.1��

	_T5IE=1;               //�����ж�
	_T5IP=2;              //�ж����ȼ�=2 ��

//void init_OSC(void)
//{
//��ʱ��Ƶ��*******************************************************************
	CLKDIVbits.DOZEN=1;
	CLKDIVbits.DOZE=0b000;
	CLKDIVbits.RCDIV=0b001;
//}

//void init_sound(void)
//{
//��������оƬ�˿�����*******************************************************************
//	AD1PCFGbits.PCFG2=1;
//	AD1PCFGbits.PCFG3=1;
//	AD1PCFGbits.PCFG4=1;
//TRISEbits.TRISE7=0;
//TRISEbits.TRISE5=0;
//TRISEbits.TRISE6=1;
	SOUND_RST_DIR=0;
	SOUND_DATA_DIR=0;
	ODCEbits.ODE6=1;
	ODCEbits.ODE7=1;
//	SOUND_CS_DIR=0;
//	SOUND_BUSY_DIR=0;
//	SOUND_CS=0;
//LATEbits.LATE7=0;
//LATEbits.LATE5=0;
	SOUND_RST=0;
	SOUND_DATA=0;
	_CN4PUE=1;
//	SOUND_BUSY=0;
	SOUND_BUSY_DIR=1;
//	sound_send_data(3);
//	while(SOUND_BUSY);
	Delay10US(10);
//}

	//PWM*****************************************************************************

//	T4CONbits.TON=1;       //time3 on
//	T4CONbits.TCS=0;       //�ڲ�ʱ�ӣ�FOSC/2��
//	T4CONbits.TCKPS=0B00;  //11 = 1:64
//	PR4=250;
PWM_DLH_DIR=0;
PWM_DLH=0;
OC4R=0;
OC4RS=10;
OC4CON=0x00;

//DS18B20
//	AD1PCFGbits.PCFG13=1;
//	AD1PCFGbits.PCFG14=1;

	ODCCbits.ODC15=1;
	ODCCbits.ODC12=1;
	ODCFbits.ODF6=1;
	ODCDbits.ODD8=1;
//	AD1PCFGbits.PCFG2=1;
//	AD1PCFGbits.PCFG3=1;
//	_CN2PUE=1;
//	_CN3PUE=1;
//	_CN4PUE=1;
//	_CN5PUE=1;
//void init_key()
//{

//��������*******************************************************************
/*
KEY_ROW1_DIR=0;
KEY_ROW2_DIR=0;
KEY_ROW3_DIR=0;

KEY_COLUMN1_DIR=1;
KEY_COLUMN2_DIR=1;
KEY_COLUMN3_DIR=1;

KEY_ROW1=1;
KEY_ROW2=1;
KEY_ROW3=1;

	_CN15PUE=1;
	_CN16PUE=1;
	_CN28PUE=1;

	_CN25PUE=1;
	_CN26PUE=1;
	_CN18PUE=1;
*/
	AD1PCFGbits.PCFG2=1;
	AD1PCFGbits.PCFG3=1;

_CN8PUE=1;
_CN9PUE=1;
_CN4PUE=1;
_CN5PUE=1;
_CN13PUE=1;
_CN14PUE=1;
_CN15PUE=1;
_CN16PUE=1;
	KEY_QUERY_DIR=1;
	KEY_OK_DIR=1;
	KEY_DEL_DIR=1;
	KEY_ADD_DIR=1;
	KEY_RIGHT_DIR=1;
	KEY_LEFT_DIR=1;
	KEY_SET_DIR=1;
	KEY_RUN_DIR=1;
//}



//void init_lcd_io(void)
//{
//Һ�����˿ڳ�ʼ��*******************************************************************
//	uchar i;
/*
	LCD_BG_DIR=0;
	LCD_BG2_DIR=0;
	LCD_CS1_DIR=0;
	LCD_CS2_DIR=0;
	LCD_WR_DIR=0;
	LCD_DATA_DIR=0;
//	LCD_RD_DIR=0;	

//	LCD_CS1_OD=1;
//	LCD_CS2_OD=1;
//	LCD_WR_OD=1;

//	LCD_DATA_OD=1;
	LCD_BG_EN; 
	LCD_BG2_DIS;
	AD1PCFGbits.PCFG8=1;
*/
//	AD1PCFGbits.PCFG4=1;		//LCDƬѡ0��Ϊ���ֿ�
	AD1PCFGbits.PCFG6=1;		//LCD����1��Ϊ���ֿ�
	AD1PCFGbits.PCFG7=1;		//LCD����2��Ϊ���ֿ�

//	LCD_CS0_DIR=0;
	LCD_CS1_DIR=0;
	LCD_CS2_DIR=0;
	LCD_BG_DIR=0;
	LCD_BG2_DIR=0;
	LCD_WR_DIR=0;
	LCD_DATA_DIR=0;


//	LCD_CS0=1;
	LCD_CS1=1;
	LCD_CS2=1;
	LCD_BG_EN; 
	LCD_BG2_DIS;

//}

//void init_led_io(void)
//{
//ָʾ������*******************************************************************
	LED_SET_DIR=0;
	LED_RUN_DIR=0;
//	ODCDbits.ODD3=1;
	ODCEbits.ODE1=1;
	ODCFbits.ODF0=1;
//}

//void time_init(void)
//{
//rtccģ���ʼ��*******************************************************************
	asm("mov #OSCCON,W1");  
	asm("mov.b	#0x02, W0");
	asm("mov.b	#0x46, W2");
	asm("mov.b	#0x57, W3");
	asm("mov.b	W2, [W1]");
	asm("mov.b	W3, [W1]");
	asm("mov.b	W0, [W1]");

		asm volatile("disi	#5");
	asm volatile("mov	#0x55, w7");
	asm volatile("mov	w7, _NVMKEY");
	asm volatile("mov	#0xAA, w8");
	asm volatile("mov	w8, _NVMKEY");
    asm volatile("bset	_RCFGCAL, #13");
	asm volatile("nop");
	asm volatile("nop");
//	_NOSC=4;
//	OSCCONbits.SOSCEN=1;
	RCFGCALbits.RTCEN=1;
	RCFGCALbits.RTCOE=0;
	ALCFGRPTbits.ALRMEN=1;
	ALCFGRPTbits.AMASK=1;
_ARPT=1;
_CHIME=1;
	_RTCIF=0;
	IEC3bits.RTCIE=1;
	IPC15bits.RTCIP=0b001;
//RTCPWC=0x0100;
//ALCFGRPT=0xc300;                                                                                                  //�����ж�һ�Σ�LEDÿ�������仯һ��

//}

//I2Cinit***********************************************
//	TRISBbits.TRISB8=1;
//	TRISBbits.TRISB9=1;
I2C_SDA1_DIR=1;
I2C_SCL1_DIR=1;
//	TRISBbits.TRISB10=0;
//	LATBbits.LATB10=0;
	I2C1BRG = 18; 

	//Now we will initialise the I2C peripheral for Master Mode, No Slew Rate
	//Control, and leave the peripheral switched off.
	
	I2C1CON = 0x1200;
	
	I2C1RCV = 0x0000;
	I2C1TRN = 0x0000;
	//Now we can enable the peripheral
	
	I2C1CON = 0x9200;
//*****************************************

//void ad_init(void)
//{
//ad������ʼ��*******************************************************************
//	_PCFG2=0;
//	AD1CON1bits.SSRC=0B111;		//�ڲ���������������������ת�� ���Զ�ת����
	AD1CON1bits.SSRC=0B010;		// Timer3�Ƚ�ƥ��ʱ��������������ת��
	AD1CON1bits.FORM=0B00;		//���������ʽλ 00:����
	AD1CON1bits.ADON=1;
	AD1CON1bits.ASAM=0;
	AD1CON2bits.SMPI=0B1111;
	AD1CON1bits.ADSIDL=0;
	AD1CON2bits.VCFG=0B001;
	AD1CON3bits.SAMC=31;
	AD1CON3bits.ADCS=3;
//	AD1CON3bits.SAMC=3;
//	AD1CON3bits.ADCS=200;
	IEC0bits.AD1IE=1;
	IFS0bits.AD1IF=0;
	IPC3bits.AD1IP=7;
//	AD_ACCONTROL_DIR=0;				//ad����ͨ���л�����
//	AD_ACCONTROL=1;
	
//��ʪ�Ŷ�ת���
	DUZHUAN_CHICK_DIR=1;
//��ʪ�ų�ʼ��
//PAISHIMEN_FX_DIR=0;		//����
//PAISHIMEN_KG_DIR=0;		//����

//}

//void i2c_port_init(void)
//{
//i2c�˿ڳ���*******************************************************************
//TRISGbits.TRISG2=0;   //I2C1 SDA
//TRISGbits.TRISG3=1;   //I2C1 SCL

//ʱ�����
//TRISEbits.TRISE6=0;
//LATEbits.LATE6=0;

//�Ƚ�����ʼ��
//	AD1PCFGbits.PCFG5=1;
//	TRISBbits.TRISB3=1;
AD_DIAODIAN_DIR=1;
_CMIF=0;
//_CMIE=1;
_CMIP=7;

//_C1EN=0;
_C1EN=1;
_CMIDL=0;
_C1OUTEN=0;
_C1INV=1;			//1 = C1�����ת
_C1NEG=1;			//�������ӵ�VIN+
_C1POS=0;			//�������ӵ�CVREF

_CVREN=1;			//����CVREF ��·
_CVROE=0;			//1 = CVREF ��ѹΪCVREF ���ŵ����
_CVRR=0;			//0 = CVRSRC ��ΧӦ�� 0.25 ��0.719 CVRSRC������ΪCVRSRC/32
_CVRSS=0;			//0 = �Ƚ����ο���ѹԴCVRSRC = AVDD �C AVSS
//_CVR=7;				//12v����6.5v�����ж�
_CVR=9;				//12v����7.43v�����ж�
//�˿��߼������ǲ�����
//TRISCbits.TRISC8=0;

//�ߵ��ټ��

	AD1PCFGbits.PCFG12=1;
//	TRISBbits.TRISB12=1;
AD_GAODISU_DIR=1;
//	TRISBbits.TRISB12=0;
//	LATBbits.LATB12=0;
_CN14PUE=1;
_CNIE=1;
_CN14IE=1;
_CNIF=0;
_CNIP=1;

//�������л�
SHANGXIAP_DIR=1;
_CN11PUE=1;

//�������л�
JIANPANSUO_DIR=1;
_CN10PUE=1;

//232
//RPOR11bits.RP23R = 3;  //3���ܺ�(UART1 ����)ӳ�䵽 RP23��3�ţ�
//RPINR18bits.U1RXR=24;  //24���ź�(U1RX ����)ӳ�䵽 RP24��4�ţ�
//TRISCbits.TRISC7=0;
//TRISCbits.TRISC8=1;
U1TX_232_DIR=0;
U1RX_232_DIR=1;
U1MODEbits.UARTEN=0;       //����1ʹ��
//U1MODEbits.RTSMD=1��
//U1BRG=25;      //19200
U1BRG=12;            //9600 ((FCY/ Ŀ�겨����)/16) �C 1
                     //((2000000/9600)/16)-1
U1STAbits.UTXEN=1;        //������

U1STAbits.URXISEL=0b00;   //�յ�1���ַ��ж�
U1STAbits.UTXISEL1=1;		//��һ���ַ������͵�������λ�Ĵ�����TSR�����·��ͻ�����Ϊ��ʱ�������ж�
U1STAbits.UTXISEL0=0;
IEC0bits.U1RXIE=1;                 //��������ж�
//IEC0bits.U1TXIE=1; 
IPC2bits.U1RXIP=3;            //����3��
IPC3bits.U1TXIP=1;            //����3��
//i=U1STAbits.OERR;

//�����ʱ������
_DOZEN=0;					//������ʹ��λ(1)  1 = DOZE2:DOZE0 λָ��CPU �������ʱ�ӱ�
//_DOZE=0b010;				//��CPU �������ʱ�ӱ�ѡ��λ
							//111 = 1:128
							//110 = 1:64
 
//����̵�������
JDQ_FENGJI_DIR=0;
JDQ_FENGJI_OFF;

//��ʪ�ż̵�������
/*
JDQ_PAISHI_BIG_DIR=0;
JDQ_PAISHI_BIG_OFF;
JDQ_PAISHI_MIN_DIR=0;
JDQ_PAISHI_MIN_OFF;
*/
Wet_exhaust_ONE_DIR=0;
Wet_exhaust_TWO_DIR=0;
Wet_exhaust_ONE=0;
Wet_exhaust_TWO=0;

//��ȼ�̵�������
JDQ_ZHURAN_DIR=0;
JDQ_ZHURAN_OFF;

//��ӱ�����
	AD1PCFGbits.PCFG14=1;
BAOJINGQI_DIR=0;
BAOJINGQI=0;

//��ؼ��
DIANCHI_CHICK_DIR=1;
	AD1PCFGbits.PCFG8=0;

//485����
WANGLUO2_485U2TX_DIR=0;
	WANGLUO2_485U2TX=0;
WANGLUO2_485U2RX_DIR=0;
	WANGLUO2_485U2RX=0;
_CN18PUE=1;
_CN17PUE=1;
/*
//����
	AD1PCFGbits.PCFG2=1;
	AD1PCFGbits.PCFG3=1;
	AD1PCFGbits.PCFG4=1;
KONGXIAN_NO3_DIR=0;
KONGXIAN_NO2_DIR=0;
KONGXIAN_NO1_DIR=0;
KONGXIAN_NO3=0;
KONGXIAN_NO3=0;
KONGXIAN_NO3=0;
*/
//ȼ�ջ����ƿ�
AD1PCFGbits.PCFG13=1;
	AD1PCFGbits.PCFG4=1;		//���̵�����Ϊ���ֿ�
RSJ_GF_DIR=0;
RSJ_DH_DIR=0;
RSJ_JL_DIR=0;
RSJ_GF=0;
RSJ_DH_OFF;
RSJ_JL=0;

//������������
/*
	AD1PCFGbits.PCFG13=1;
SAN_DAN_DIR=1;
	AD1PCFGbits.PCFG9=0;
*/
}


