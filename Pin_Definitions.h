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

//以下是LCD的4根数据线
//#define LCD_CS1			PORTFbits.RF0    
//#define LCD_CS2  		PORTFbits.RF1
//#define LCD_WR			PORTGbits.RG6
//#define LCD_DATA		PORTGbits.RG7
//一下为LCD显示器定义
/*
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

#define LCD_BG_EN   	LATEbits.LATE4=1; //背光点亮
#define LCD_BG_DIS   	LATEbits.LATE4=0; //背光黑
#define LCD_BG2_EN   	LATEbits.LATE1=1; //背光点亮
#define LCD_BG2_DIS   	LATEbits.LATE1=0; //背光黑
*/

//#define LCD_CS0_DIR		TRISBbits.TRISB4
#define LCD_CS1_DIR		TRISEbits.TRISE0
#define LCD_CS2_DIR  	TRISFbits.TRISF1
#define LCD_BG_DIR   	TRISBbits.TRISB6
#define LCD_BG2_DIR   	TRISBbits.TRISB7
#define LCD_WR_DIR		TRISEbits.TRISE2
#define LCD_DATA_DIR	TRISEbits.TRISE3

//#define LCD_CS0			LATBbits.LATB4
#define LCD_CS1			LATEbits.LATE0    
#define LCD_CS2  		LATFbits.LATF1
#define LCD_WR			LATEbits.LATE2
#define LCD_DATA		LATEbits.LATE3

#define LCD_BG_EN 			LATBbits.LATB6=1;
#define LCD_BG2_EN 			LATBbits.LATB7=1;
#define LCD_BG_DIS			LATBbits.LATB6=0;
#define LCD_BG2_DIS			LATBbits.LATB7=0;


/* 以下是按键定义 */
/*
#define KEY_ROW1			LATCbits.LATC6  //加号键
#define KEY_ROW2			LATCbits.LATC5  
#define KEY_ROW3			LATCbits.LATC4  


#define KEY_COLUMN1			PORTBbits.RB11 
#define KEY_COLUMN2			PORTBbits.RB10
#define KEY_COLUMN3			PORTCbits.RC3


#define KEY_COLUMN1_O			LATBbits.LATB11 
#define KEY_COLUMN2_O			LATBbits.LATB10
#define KEY_COLUMN3_O			LATCbits.LATC3

#define KEY_ROW1_DIR			TRISCbits.TRISC6//加号键的方向寄存器
#define KEY_ROW2_DIR			TRISCbits.TRISC5
#define KEY_ROW3_DIR			TRISCbits.TRISC4

#define KEY_COLUMN1_DIR			TRISBbits.TRISB11
#define KEY_COLUMN2_DIR			TRISBbits.TRISB10
#define KEY_COLUMN3_DIR			TRISCbits.TRISC3
*/

#define KEY_ADD			PORTDbits.RD7  //加号键
#define KEY_LEFT		PORTGbits.RG7  //向左键
#define KEY_RIGHT		PORTDbits.RD5  //向右键
#define KEY_SET			PORTGbits.RG6  //设置键
#define KEY_DEL 		PORTDbits.RD6  //减号键
#define KEY_RUN			PORTDbits.RD4  //运行键
#define KEY_OK			PORTBbits.RB3  //确认键
#define KEY_QUERY		PORTBbits.RB2  //查询键

#define KEY_ADD_DIR			TRISDbits.TRISD7  //加号键的方向寄存器
#define KEY_LEFT_DIR		TRISGbits.TRISG7  //左键的方向寄存器
#define KEY_RIGHT_DIR		TRISDbits.TRISD5
#define KEY_SET_DIR			TRISGbits.TRISG6
#define KEY_DEL_DIR 		TRISDbits.TRISD6
#define KEY_RUN_DIR			TRISDbits.TRISD4
#define KEY_OK_DIR			TRISBbits.TRISB3
#define KEY_QUERY_DIR		TRISBbits.TRISB2

//LED
#define LED_SET_DIR			TRISEbits.TRISE1  //设置灯方向寄存器，DIR:方向
#define LED_RUN_DIR			TRISFbits.TRISF0  //运行灯方向寄存器
#define LED_SET_ON			LATEbits.LATE1=0   //设置灯亮
#define LED_SET_OFF			LATEbits.LATE1=1   //设置灯灭
#define LED_RUN_ON			LATFbits.LATF0=0   //运行灯亮
#define LED_RUN_OFF			LATFbits.LATF0=1   //运行灯灭

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
//排湿门
#define PAISHIMEN_FX_DIR		TRISDbits.TRISD10		//方向
#define PAISHIMEN_KG_DIR		TRISDbits.TRISD11		//开关

#define PAISHIMEN_FX_OPEN		LATDbits.LATD10=1
#define PAISHIMEN_FX_CLOSE		LATDbits.LATD10=0

#define PAISHIMEN_KG_ON			LATDbits.LATD11=1
#define PAISHIMEN_KG_OFF		LATDbits.LATD11=0
*/

//AD，abc电流采样切换通道

//#define AD_ACCONTROL_DIR		TRISAbits.TRISA10
//#define AD_ACCONTROL			LATAbits.LATA10
#define AD_ADIANLIU_DIR			TRISBbits.TRISB1
#define AD_BDIANLIU_DIR			TRISBbits.TRISB10
#define AD_CDIANLIU_DIR			TRISBbits.TRISB11
#define AD_ADIANLIU				LATBbits.LATB1
#define AD_BDIANLIU				LATBbits.LATB10
#define AD_CDIANLIU				LATBbits.LATB11

//AD电压通道
#define AD_DIANYA_DIR			TRISBbits.TRISB12
#define AD_DIANYA				LATBbits.LATB12

//上下棚切换
#define SHANGXIAP_DIR		TRISGbits.TRISG8
#define SHANGXIAP		PORTGbits.RG8

//键盘锁切换
#define JIANPANSUO_DIR		TRISGbits.TRISG9
#define JIANPANSUO		PORTGbits.RG9

//I2C通道
#define I2C_SDA1_DIR			TRISGbits.TRISG3
#define I2C_SDA1				LATGbits.LATG3
#define I2C_SCL1_DIR			TRISGbits.TRISG2
#define I2C_SCL1				LATGbits.LATG2

//比较器（掉电检测）
#define AD_DIAODIAN_DIR			TRISBbits.TRISB5
#define AD_DIAODIAN				LATBbits.LATB5

//AD高低速检测
#define AD_GAODISU_DIR			TRISBbits.TRISB15
#define AD_GAODISU				LATBbits.LATB15

//232串口通信
#define U1TX_232_DIR			TRISFbits.TRISF3
#define U1TX_232				LATFbits.LATF3
#define U1RX_232_DIR			TRISFbits.TRISF2
#define U1RX_232				LATFbits.LATF2

//风机继电器控制
#define JDQ_FENGJI_DIR			TRISDbits.TRISD9
#define JDQ_FENGJI_ON				LATDbits.LATD9=1
#define JDQ_FENGJI_OFF				LATDbits.LATD9=0
 
//排湿门继电器控制
/*
#define JDQ_PAISHI_BIG_DIR			TRISDbits.TRISD10
#define JDQ_PAISHI_BIG_ON				LATDbits.LATD10=1
#define JDQ_PAISHI_BIG_OFF				LATDbits.LATD10=0
#define JDQ_PAISHI_MIN_DIR			TRISDbits.TRISD11
#define JDQ_PAISHI_MIN_ON				LATDbits.LATD11=1
#define JDQ_PAISHI_MIN_OFF				LATDbits.LATD11=0
*/
#define Wet_exhaust_ONE_DIR			TRISDbits.TRISD10
#define Wet_exhaust_ONE				LATDbits.LATD10

#define Wet_exhaust_TWO_DIR			TRISDbits.TRISD11
#define Wet_exhaust_TWO				LATDbits.LATD11



//助燃继电器控制
#define JDQ_ZHURAN_DIR			TRISDbits.TRISD0
#define JDQ_ZHURAN_ON				LATDbits.LATD0=1
#define JDQ_ZHURAN_OFF				LATDbits.LATD0=0

//外接报警器
#define BAOJINGQI_DIR			TRISBbits.TRISB14
#define BAOJINGQI				LATBbits.LATB14

//电池检测
#define DIANCHI_CHICK_DIR			TRISBbits.TRISB8
#define DIANCHI_CHICK				LATBbits.LATB8

//堵转检测
#define DUZHUAN_CHICK_DIR			TRISBbits.TRISB9
#define DUZHUAN_CHICK				LATBbits.LATB9

//485网络
#define WANGLUO2_485U2TX_DIR			TRISFbits.TRISF5
#define WANGLUO2_485U2TX				LATFbits.LATF5
#define WANGLUO2_485U2RX_DIR			TRISFbits.TRISF4
#define WANGLUO2_485U2RX				LATFbits.LATF4
/*
//LTC1446
#define DA_LTC1446_CLK_DIR			TRISBbits.TRISB13
#define DA_LTC1446_CLK				LATBbits.LATB13
#define DA_LTC1446_CS_DIR			TRISDbits.TRISD1
#define DA_LTC1446_CS				LATDbits.LATD1
#define DA_LTC1446_DIN_DIR			TRISDbits.TRISD2
#define DA_LTC1446_DIN				LATDbits.LATD2
*/
//电流环PWM腿
#define PWM_DLH_DIR			TRISDbits.TRISD3
#define PWM_DLH				LATDbits.LATD3


//燃烧机控制
#define RSJ_GF_DIR			TRISBbits.TRISB13
#define RSJ_GF				LATBbits.LATB13
#define RSJ_DH_DIR			TRISBbits.TRISB4
#define RSJ_DH_ON				LATBbits.LATB4=1
#define RSJ_DH_OFF				LATBbits.LATB4=0
#define RSJ_JL_DIR			TRISDbits.TRISD1
#define RSJ_JL				LATDbits.LATD1
#define QPS_DIR			TRISDbits.TRISD2
#define QPS				LATDbits.LATD2
/*
//单、三相跳线
#define SAN_DAN_DIR			TRISDbits.TRISD0
#define SAN_DAN_IN				PORTDbits.RD0
*/
