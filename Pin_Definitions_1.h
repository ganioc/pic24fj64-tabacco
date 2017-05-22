#include "p24FJ64GA006.h"

#define uint16 unsigned int
#define uchar unsigned char

#define FCY 8000000UL

#define SOUND_RST			LATEbits.LATE7
#define SOUND_DATA			LATEbits.LATE6
//#define SOUND_CS			LATBbits.LATB2
#define SOUND_BUSY			PORTEbits.RE5
#define SOUND_RST_DIR		TRISEbits.TRISE7
#define SOUND_DATA_DIR		TRISEbits.TRISE6
//#define SOUND_CS_DIR		TRISBbits.TRISB2
#define SOUND_BUSY_DIR		TRISEbits.TRISE5

//������LCD��4��������
//#define LCD_CS1			PORTFbits.RF0    
//#define LCD_CS2  		PORTFbits.RF1
//#define LCD_WR			PORTGbits.RG6
//#define LCD_DATA		PORTGbits.RG7
//һ��ΪLCD��ʾ������
#define LCD_CS1			LATEbits.LATE0    
#define LCD_CS2  		LATFbits.LATF1
#define LCD_WR			LATEbits.LATE2
#define LCD_DATA		LATEbits.LATE3
//#define LCD_RD			LATEbits.LATE6

//#define LCD_DATA_IN		PORTGbits.RG7

#define LCD_BG_DIR   	TRISEbits.TRISE4
#define LCD_BG2_DIR   	TRISEbits.TRISE1
#define LCD_CS1_DIR		TRISEbits.TRISE0
#define LCD_CS2_DIR  	TRISFbits.TRISF1
#define LCD_WR_DIR		TRISEbits.TRISE2
//#define LCD_RD_DIR		TRISEbits.TRISE6
#define LCD_DATA_DIR	TRISEbits.TRISE3



//#define LCD_BG_OD   	ODCEbits.ODE2
#define LCD_CS1_OD		ODCEbits.ODE0
#define LCD_CS2_OD  	ODCFbits.ODF1
#define LCD_WR_OD		ODCEbits.ODE2
//#define LCD_RD_OD		ODCEbits.ODE6
#define LCD_DATA_OD		ODCEbits.ODE3

#define LCD_BG_EN   	LATEbits.LATE4=1; //�������
#define LCD_BG_DIS   	LATEbits.LATE4=0; //�����
#define LCD_BG2_EN   	LATEbits.LATE1=1; //�������
#define LCD_BG2_DIS   	LATEbits.LATE1=0; //�����
/* �����ǰ������� */
/*
#define KEY_ROW1			LATCbits.LATC6  //�Ӻż�
#define KEY_ROW2			LATCbits.LATC5  
#define KEY_ROW3			LATCbits.LATC4  


#define KEY_COLUMN1			PORTBbits.RB11 
#define KEY_COLUMN2			PORTBbits.RB10
#define KEY_COLUMN3			PORTCbits.RC3


#define KEY_COLUMN1_O			LATBbits.LATB11 
#define KEY_COLUMN2_O			LATBbits.LATB10
#define KEY_COLUMN3_O			LATCbits.LATC3

#define KEY_ROW1_DIR			TRISCbits.TRISC6//�Ӻż��ķ���Ĵ���
#define KEY_ROW2_DIR			TRISCbits.TRISC5
#define KEY_ROW3_DIR			TRISCbits.TRISC4

#define KEY_COLUMN1_DIR			TRISBbits.TRISB11
#define KEY_COLUMN2_DIR			TRISBbits.TRISB10
#define KEY_COLUMN3_DIR			TRISCbits.TRISC3
*/

#define KEY_ADD			PORTDbits.RD7  //�Ӻż�
#define KEY_LEFT		PORTDbits.RD2  //�����
#define KEY_RIGHT		PORTDbits.RD5  //���Ҽ�
#define KEY_SET			PORTDbits.RD1  //���ü�
#define KEY_DEL 		PORTDbits.RD6  //���ż�
#define KEY_RUN			PORTDbits.RD4  //���м�
#define KEY_OK			PORTGbits.RG7  //ȷ�ϼ�
#define KEY_QUERY		PORTGbits.RG6  //��ѯ��

#define KEY_ADD_DIR			TRISDbits.TRISD7  //�Ӻż��ķ���Ĵ���
#define KEY_LEFT_DIR		TRISDbits.TRISD2  //����ķ���Ĵ���
#define KEY_RIGHT_DIR		TRISDbits.TRISD5
#define KEY_SET_DIR			TRISDbits.TRISD1
#define KEY_DEL_DIR 		TRISDbits.TRISD6
#define KEY_RUN_DIR			TRISDbits.TRISD4
#define KEY_OK_DIR			TRISGbits.TRISG7
#define KEY_QUERY_DIR		TRISGbits.TRISG6

//LED
#define LED_SET_DIR			TRISDbits.TRISD3  //���õƷ���Ĵ�����DIR:����
#define LED_RUN_DIR			TRISFbits.TRISF0  //���еƷ���Ĵ���
#define LED_SET_ON			LATDbits.LATD3=0   //���õ���
#define LED_SET_OFF			LATDbits.LATD3=1   //���õ���
#define LED_RUN_ON			LATFbits.LATF0=0   //���е���
#define LED_RUN_OFF			LATFbits.LATF0=1   //���е���

//DS18B20
#define DS18B20_ONE_DIR			TRISCbits.TRISC15
#define DS18B20_TWO_DIR			TRISCbits.TRISC12
#define DS18B20_THR_DIR			TRISFbits.TRISF6
#define DS18B20_FOU_DIR			TRISDbits.TRISD8

#define DS18B20_ONE_OT			LATCbits.LATC15
#define DS18B20_TWO_OT			LATCbits.LATC12
#define DS18B20_THR_OT			LATFbits.LATF6
#define DS18B20_FOU_OT			LATDbits.LATD8

#define DS18B20_ONE_IN			PORTCbits.RC15
#define DS18B20_TWO_IN			PORTCbits.RC12
#define DS18B20_THR_IN			PORTFbits.RF6
#define DS18B20_FOU_IN			PORTDbits.RD8
/*
//��ʪ��
#define PAISHIMEN_FX_DIR		TRISDbits.TRISD10		//����
#define PAISHIMEN_KG_DIR		TRISDbits.TRISD11		//����

#define PAISHIMEN_FX_OPEN		LATDbits.LATD10=1
#define PAISHIMEN_FX_CLOSE		LATDbits.LATD10=0

#define PAISHIMEN_KG_ON			LATDbits.LATD11=1
#define PAISHIMEN_KG_OFF		LATDbits.LATD11=0
*/

//AD��abc���������л�ͨ��

//#define AD_ACCONTROL_DIR		TRISAbits.TRISA10
//#define AD_ACCONTROL			LATAbits.LATA10
#define AD_ADIANLIU_DIR			TRISBbits.TRISB1
#define AD_BDIANLIU_DIR			TRISBbits.TRISB10
#define AD_CDIANLIU_DIR			TRISBbits.TRISB11
#define AD_ADIANLIU				LATBbits.LATB1
#define AD_BDIANLIU				LATBbits.LATB10
#define AD_CDIANLIU				LATBbits.LATB11

//AD��ѹͨ��
#define AD_DIANYA_DIR			TRISBbits.TRISB12
#define AD_DIANYA				LATBbits.LATB12

//�������л�
#define SHANGXIAP_DIR		TRISGbits.TRISG9
#define SHANGXIAP		PORTGbits.RG9

//�������л�
#define JIANPANSUO_DIR		TRISGbits.TRISG8
#define JIANPANSUO		PORTGbits.RG8

//I2Cͨ��
#define I2C_SDA1_DIR			TRISGbits.TRISG3
#define I2C_SDA1				LATGbits.LATG3
#define I2C_SCL1_DIR			TRISGbits.TRISG2
#define I2C_SCL1				LATGbits.LATG2

//�Ƚ����������⣩
#define AD_DIAODIAN_DIR			TRISBbits.TRISB5
#define AD_DIAODIAN				LATBbits.LATB5

//AD�ߵ��ټ��
#define AD_GAODISU_DIR			TRISBbits.TRISB15
#define AD_GAODISU				LATBbits.LATB15

//232����ͨ��
#define U1TX_232_DIR			TRISFbits.TRISF3
#define U1TX_232				LATFbits.LATF3
#define U1RX_232_DIR			TRISFbits.TRISF2
#define U1RX_232				LATFbits.LATF2

//����̵�������
#define JDQ_FENGJI_DIR			TRISDbits.TRISD9
#define JDQ_FENGJI_ON				LATDbits.LATD9=1
#define JDQ_FENGJI_OFF				LATDbits.LATD9=0

//��ʪ�ż̵�������
#define JDQ_PAISHI_BIG_DIR			TRISDbits.TRISD10
#define JDQ_PAISHI_BIG_ON				LATDbits.LATD10=1
#define JDQ_PAISHI_BIG_OFF				LATDbits.LATD10=0
#define JDQ_PAISHI_MIN_DIR			TRISDbits.TRISD11
#define JDQ_PAISHI_MIN_ON				LATDbits.LATD11=1
#define JDQ_PAISHI_MIN_OFF				LATDbits.LATD11=0

//��ȼ�̵�������
#define JDQ_ZHURAN_DIR			TRISDbits.TRISD0
#define JDQ_ZHURAN_ON				LATDbits.LATD0=1
#define JDQ_ZHURAN_OFF				LATDbits.LATD0=0

//��ӱ�����
#define BAOJINGQI_DIR			TRISBbits.TRISB14
#define BAOJINGQI				LATBbits.LATB14

//��ؼ��
#define DIANCHI_CHICK_DIR			TRISBbits.TRISB8
#define DIANCHI_CHICK				LATBbits.LATB8

//��ת���
#define DUZHUAN_CHICK_DIR			TRISBbits.TRISB9
#define DUZHUAN_CHICK				LATBbits.LATB9

//485����
#define WANGLUO2_485U2TX_DIR			TRISFbits.TRISF5
#define WANGLUO2_485U2TX				LATFbits.LATF5
#define WANGLUO2_485U2RX_DIR			TRISFbits.TRISF4
#define WANGLUO2_485U2RX				LATFbits.LATF4

//����
#define KONGXIAN_NO3_DIR			TRISBbits.TRISB2
#define KONGXIAN_NO3				LATBbits.LATB2
#define KONGXIAN_NO2_DIR			TRISBbits.TRISB3
#define KONGXIAN_NO2				LATBbits.LATB3
#define KONGXIAN_NO1_DIR			TRISBbits.TRISB4
#define KONGXIAN_NO1				LATBbits.LATB4

//������������
#define SAN_DAN_DIR			TRISBbits.TRISB13
#define SAN_DAN_IN				PORTBbits.RB13
