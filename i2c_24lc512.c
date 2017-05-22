#include <p24FJ64GA006.h>
#include "Pin_Definitions.h"
#include <i2c.h>
#include "stdio.h"

//#define USE_AND_OR // To enable AND_OR mask setting for I2C.

//#define I2C_BRG 37 //400k
#define I2C_BRG 4 //400k

void i2c_init(void);
uchar Read_24lc512(uint16 address);
void Write_24lc512(uint16 address,uchar val);
void __delay32(unsigned long cycles);

void i2c_init(void)
{
	TRISGbits.TRISG2=1;
	TRISGbits.TRISG3=1;
	TRISFbits.TRISF6=0;
	LATFbits.LATF6=0;
//	ConfigIntI2C1(SI2C_INT_OFF);
	OpenI2C1( I2C_ON & I2C_SLW_DIS,I2C_BRG);
//I2C1BRG=37;
}
//¶Á24lc512,·µ»Ø¼Ä´æÆ÷µØÖ·µÄÖµ****************************************
uchar Read_24lc512(uint16 address )  //RX8025¼Ä´æÆ÷µØÖ·0-12h
{
 uchar ret;
	uchar add_h,add_l;
add_h=address>>8;
add_l=address;
    StartI2C1();        	//Send the Start Bit
     IdleI2C1();	    	//Wait to complete

   MasterWriteI2C1(0xa0);    // addresses the chip      
    IdleI2C1();
  MasterWriteI2C1(add_h);    // addresses the chip      
    IdleI2C1();
    MasterWriteI2C1(add_l);     // mem address
        IdleI2C1();
 RestartI2C1();	//Send the Restart condition     
__delay32(100);
      IdleI2C1();
  MasterWriteI2C1(0XA1);    // addresses the chip  

     IdleI2C1();

    ret = MasterReadI2C1();	// read one byte

//IdleI2C1();
//NotAckI2C1();
//IdleI2C1();
  StopI2C1();	//Send the Stop condition
	IdleI2C1();	//Wait to complete

  return ret; 

}
//Ð´24lc512£¬ÖµÐ´µ½Ö¸¶¨µÄ¼Ä´æÆ÷
void Write_24lc512(uint16 address,uchar val)  //DS3231¼Ä´æÆ÷µØÖ·0-12h
{
	uchar add_h,add_l;
add_h=address>>8;
add_l=address;
    StartI2C1();        	//Send the Start Bit
//	I2C1CONbits.SEN=1;
//add_h=address>>8;
     IdleI2C1();	    	//Wait to complete
//add_h=address>>8;
    MasterWriteI2C1(0XA0);    // addresses the chip      
       IdleI2C1();
    MasterWriteI2C1(add_h);     // mem address
        IdleI2C1();
    MasterWriteI2C1(add_l);     // mem address
        IdleI2C1();
    MasterWriteI2C1( val );    // write value into minutes register
        IdleI2C1();
   StopI2C1();	//Send the Stop condition
        IdleI2C1();
}

