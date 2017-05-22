#include <p24FJ32GA002.h>
#define uchar unsigned char
#define uint16 unsigned int
#define I2C_SDA PORTBbits.RB9 //I2C����
#define I2C_SCL LATBbits.LATB8 //I2Cʱ��
#define I2C_SDAio TRISBbits.TRISB9
#define I2C_SCLio TRISBbits.TRISB8

uchar AT2402_Read(uchar address);
void AT2402_Write(uchar add,uchar val);
//uchar I2C_READ_DATA(uchar address);//������������洢��ַ�����ش洢ֵ

extern void DelayMS(uint16 ms);
extern void __delay32(unsigned long cycles);


void I2C_INIT(void);
void I2C_START(void);
void I2C_STOP(void);
void I2C_ACK(void);
void I2C_NACK(void);
void I2C_Send_Byte(uchar);


//uchar I2C_READ_DATA(uchar address);//������������洢��ַ�����ش洢ֵ

void AT2402_Write(uchar address,uchar val)
{
	 I2C_START();
     I2C_Send_Byte(0xa0);//д24c02��ַ�Ͷ�дѡ��
     I2C_ACK();
     I2C_Send_Byte(address);//д24C256���ڲ����ݴ洢��ַ
     I2C_ACK();        //  
    
 
     I2C_Send_Byte(val);//д�û����ݣ�
     I2C_ACK();

     I2C_STOP();
     DelayMS(10);// ��ʱ10MS
}
//�����ݺ�����һ���ֽڷ�8λ��AT24C256_address���ĵ�ַ
uchar AT2402_Read(uchar address)
{
 uchar i;
 uchar k = 0; 
 I2C_START();
 I2C_Send_Byte(0xa0);//αд��д��ַ��
 I2C_ACK();
 I2C_Send_Byte(address);//д24C256���ڲ����ݴ洢��ַ
 I2C_ACK();           //
  //********************
 I2C_START();
 I2C_Send_Byte(0xa1);
 I2C_ACK();
__delay32(11);
  I2C_SDAio = 1;   //RB9��Ϊ�����
 // I2C_SCL = 1;
 //__delay32(11);
 //I2C_SCL = 0;
 __delay32(11);
 for(i = 0;i < 8;++i)
 {
    I2C_SCL = 1;
    __delay32(15);
    k = (k<<1) | I2C_SDA;//RB9��K
    I2C_SCL = 0;
    __delay32(15);
 }
  I2C_NACK();
  I2C_STOP();
  
  return k;
 }

//��ʼ���������ö�����������ʾ��PORTD�ڵ�LED��
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
//��ʼ�ź�
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
//ֹͣ�ź�
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
//��Ӧ��ȷ�ϣ��ź�
void I2C_ACK()
{	
 uint16 i=0;
 I2C_SDAio = 1;   //RC4��Ϊ�����
 I2C_SCL = 1;      //
 while(I2C_SDA == 1 && i <250)//���I2C_SDA�ź����ɴ����������ģ�
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
//д���ݺ�����һ���ֽڷ�8λ��
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