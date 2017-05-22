#include <p24FJ32GA002.h>
#define uchar unsigned char
#define uint16 unsigned int
#define I2C_SDA PORTBbits.RB9 //I2C数据
#define I2C_SCL LATBbits.LATB8 //I2C时钟
#define I2C_SDAio TRISBbits.TRISB9
#define I2C_SCLio TRISBbits.TRISB8

uchar AT2402_Read(uchar address);
void AT2402_Write(uchar add,uchar val);
//uchar I2C_READ_DATA(uchar address);//随机读，给出存储地址，返回存储值

extern void DelayMS(uint16 ms);
extern void __delay32(unsigned long cycles);


void I2C_INIT(void);
void I2C_START(void);
void I2C_STOP(void);
void I2C_ACK(void);
void I2C_NACK(void);
void I2C_Send_Byte(uchar);


//uchar I2C_READ_DATA(uchar address);//随机读，给出存储地址，返回存储值

void AT2402_Write(uchar address,uchar val)
{
	 I2C_START();
     I2C_Send_Byte(0xa0);//写24c02地址和读写选择；
     I2C_ACK();
     I2C_Send_Byte(address);//写24C256高内部数据存储地址
     I2C_ACK();        //  
    
 
     I2C_Send_Byte(val);//写用户数据；
     I2C_ACK();

     I2C_STOP();
     DelayMS(10);// 延时10MS
}
//读数据函数，一个字节分8位；AT24C256_address读的地址
uchar AT2402_Read(uchar address)
{
 uchar i;
 uchar k = 0; 
 I2C_START();
 I2C_Send_Byte(0xa0);//伪写（写地址）
 I2C_ACK();
 I2C_Send_Byte(address);//写24C256高内部数据存储地址
 I2C_ACK();           //
  //********************
 I2C_START();
 I2C_Send_Byte(0xa1);
 I2C_ACK();
__delay32(11);
  I2C_SDAio = 1;   //RB9设为输入口
 // I2C_SCL = 1;
 //__delay32(11);
 //I2C_SCL = 0;
 __delay32(11);
 for(i = 0;i < 8;++i)
 {
    I2C_SCL = 1;
    __delay32(15);
    k = (k<<1) | I2C_SDA;//RB9送K
    I2C_SCL = 0;
    __delay32(15);
 }
  I2C_NACK();
  I2C_STOP();
  
  return k;
 }

//初始化函数，让读出的数据显示在PORTD口的LED上
void I2C_INIT()
{
 I2C_SDAio = 0;
 I2C_SCLio = 0;	
 //TRISD = 0x00;
// LATD=0;
 I2C_SDA = 1;
 __delay32(11);
 I2C_SCL = 1;
 __delay32(11);

}
//开始信号
void I2C_START()
{
 I2C_SDAio = 0;
 I2C_SDA = 1;
  __delay32(11);
 I2C_SCL = 1;
 __delay32(11);
 I2C_SDA = 0;
 __delay32(11);
 I2C_SCL = 0;
 __delay32(11);

}
//停止信号
void I2C_STOP()
{
 I2C_SDAio = 0;
 I2C_SDA = 0;
  __delay32(11);
 I2C_SCL = 1;
 __delay32(11);
 I2C_SDA = 1;
  __delay32(11);
 
}
//响应（确认）信号
void I2C_ACK()
{	
 uint16 i=0;
 I2C_SDAio = 1;   //RC4设为输入口
 I2C_SCL = 1;      //
 while(I2C_SDA == 1 && i <250)//这个I2C_SDA信号是由从器件发出的；
  i++;
 __delay32(11);
 I2C_SCL = 0;
 __delay32(11);
}
void I2C_NACK()
{	
// uint16 i=0;
 I2C_SDAio = 1;
 I2C_SDA = 1;
 I2C_SCL = 1;      //
 __delay32(11);
 I2C_SCL = 0;
 __delay32(11);
//i=i+1;
}
//写数据函数，一个字节分8位；
void I2C_Send_Byte(uchar data)
{
 uchar i;
 I2C_SDAio = 0;
 for(i = 0;i < 8;i++)
 {
  I2C_SCL = 0;
__delay32(11);
  if(data&0x80)
   I2C_SDA = 1;
  else
   I2C_SDA = 0;
  data = data << 1;
 __delay32(11);
  I2C_SCL = 1;
 __delay32(11);
 }
 I2C_SCL = 0;
__delay32(11);

}
