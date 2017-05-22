/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;                                                                     
;                     Software License Agreement                      
;                                                                     
;     ?007 Microchip Technology Inc
;     Mirochip Technology Inc. ("Microchip") licenses this software to 
;     you solely for the use with Microchip Products. The software is
;     owned by Microchip and is protected under applicable copyright
;     laws. All rights reserved.
;
;     SOFTWARE IS PROVIDED "AS IS." MICROCHIP EXPRESSLY DISCLAIMS ANY
;     WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING BUT NOT
;     LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
;     PARTICULAR PURPOSE, OR NON-INFRINGEMENT. IN NO EVENT SHALL MICROCHIP
;     BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL
;     DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF
;     PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
;     BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
;     ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS.
;     
;                                                                
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;	Filename:			    i2c_Func.c            
;	Date:				    February 21, 2007          
;	File Version:		  	1.0                             
;	Assembled using:		MPLAB IDE 7.51.00.0               
; 	Author:		  	    	Martin Bowman              
;	Company:			    Microchip Technology, Inc.
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "p24FJ64GA006.h"
#include "i2c.h"
#include "delay.h"

void __delay32(unsigned long cycles);

/*********************************************************************
* Function:        InitI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Initialises the I2C(1) peripheral
*
* Note:			Sets up Master mode, No slew rate control, 100Khz
*初始化i2c
********************************************************************/
void InitI2C(void)
{	
	//This function will initialize the I2C(1) peripheral.
	//First set the I2C(1) BRG Baud Rate.

	//Consult the dSPIC Data Sheet for information on how to calculate the
	//Baud Rate.
	TRISBbits.TRISB8=1;
	TRISBbits.TRISB9=1;
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
}


/*********************************************************************
* Function:        StartI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates an I2C Start Condition
*
* Note:			None
*
*开始i2c
********************************************************************/
void StartI2C(void)
{
	//This function generates an I2C start condition and returns status 
	//of the Start.

	I2C1CONbits.SEN = 1;		//Generate Start COndition
	while (I2C1CONbits.SEN);	//Wait for Start COndition
	//return(I2C1STATbits.S);	//Optionally return status
}


/*********************************************************************
* Function:        RestartI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates a restart condition and optionally returns status
*
* Note:			None
*
*重启i2c
********************************************************************/
void RestartI2C(void)
{
	//This function generates an I2C Restart condition and returns status 
	//of the Restart.

	I2C1CONbits.RSEN = 1;		//Generate Restart		
	while (I2C1CONbits.RSEN);	//Wait for restart	
	//return(I2C1STATbits.S);	//Optional - return status
}


/*********************************************************************
* Function:        StopI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates a bus stop condition
*
* Note:			None
*
*停止i2c
********************************************************************/
void StopI2C(void)
{
	//This function generates an I2C stop condition and returns status 
	//of the Stop.

	I2C1CONbits.PEN = 1;		//Generate Stop Condition
	while (I2C1CONbits.PEN);	//Wait for Stop
	//return(I2C1STATbits.P);	//Optional - return status
}


/*********************************************************************
* Function:        WriteI2C()
*
* Input:		Byte to write.
*
* Output:		None.
*
* Overview:		Writes a byte out to the bus
*
* Note:			None
*
*把数据放入i2c传输寄存器
********************************************************************/
unsigned int WriteI2C(unsigned char byte)
{
	//This function transmits the byte passed to the function
	//while (I2C1STATbits.TRSTAT);	//Wait for bus to be idle
	I2C1TRN = byte;					//Load byte to I2C1 Transmit buffer
	while (I2C1STATbits.TBF);		//wait for data transmission
	return (0);
}


/*********************************************************************
* Function:        IdleI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Waits for bus to become Idle
*
* Note:			None
*
*等待i2c空闲
********************************************************************/
void IdleI2C(void)
{
	while (I2C1STATbits.TRSTAT);		//Wait for bus Idle
}


/*********************************************************************
* Function:        HDByteWriteI2C()
*
* Input:		ControlByte, HighAddr, LowAddr, Data.
*
* Output:		None.
*
* Overview:		perform a high density byte write of data byte, Data.
*				starting at the address formed from HighAdd and LowAdd
*
* Note:			None
*
*2字节地址的i2c写入
********************************************************************/
unsigned int HDByteWriteI2C(unsigned char ControlByte, unsigned char HighAdd, unsigned char LowAdd, unsigned char data)
{
	unsigned int ErrorCode;

//e
	StartI2C();						//Generate Start COndition
	IdleI2C();						//Ensure Module is Idle
	WriteI2C(ControlByte);			//Write Control byte
	IdleI2C();

	ErrorCode = ACKStatus();		//Return ACK Status
	
	WriteI2C(HighAdd);
	IdleI2C();						//Write High Address
	WriteI2C(LowAdd);				//Write Low Address
	IdleI2C();

	ErrorCode = ACKStatus();		//Return ACK Status

	WriteI2C(data);					//Write Data
	IdleI2C();
	StopI2C();						//Initiate Stop Condition
//	EEAckPolling(ControlByte);		//perform Ack Polling
	return(ErrorCode);
}

unsigned int LDByteWriteI2C(unsigned char ControlByte,  unsigned char data)
{
	unsigned int ErrorCode;

//e
	StartI2C();						//Generate Start COndition
	IdleI2C();						//Ensure Module is Idle
	WriteI2C(ControlByte);			//Write Control byte
	IdleI2C();

	ErrorCode = ACKStatus();		//Return ACK Status
	



	WriteI2C(data);					//Write Data
	IdleI2C();
	StopI2C();						//Initiate Stop Condition
//	EEAckPolling(ControlByte);		//perform Ack Polling
	return(ErrorCode);
}

/*********************************************************************
* Function:        HDByteReadI2C()
*
* Input:		Control Byte, HighAdd, LowAdd, *Data, Length.
*
* Output:		None.
*
* Overview:		Performs a low density read of Length bytes and stores in *Data array
*				starting at Address formed from HighAdd and LowAdd.
*
* Note:			None
*
*2字节地址的读取可以连续读取多个
********************************************************************/
unsigned char HDByteReadI2C(unsigned char ControlByte, unsigned char HighAdd, unsigned char LowAdd)
{
//
uchar retur;
	StartI2C();						//Generate Start condition
	IdleI2C();						//Wait for bus Idle
	WriteI2C(ControlByte);			//send control byte for write
	IdleI2C();						//Wait for bus Idle

	WriteI2C(HighAdd);				//Send High Address
	IdleI2C();						//Wait for bus Idle
	WriteI2C(LowAdd);				//Send Low Address
	IdleI2C();						//Wait for bus Idle

	RestartI2C();					//Generate Restart
	WriteI2C(ControlByte | 0x01);	//send control byte for Read
	IdleI2C();						//Wait for bus Idle

//	getsI2C(Data, Length);			//Read Length number of bytes to Data
retur=getI2C();
	NotAckI2C();					//send Not Ack
	StopI2C();						//Send Stop Condition
	return(retur);
}


/*********************************************************************
* Function:        HDPageWriteI2C()
*
* Input:		ControlByte, HighAdd, LowAdd, *wrptr.
*
* Output:		None.
*
* Overview:		Write a page of data from array pointed to be wrptr
*				starting at address from HighAdd and LowAdd
*
* Note:			Address must start on a page boundary
*
*2字节地址的页写入
********************************************************************/
unsigned int HDPageWriteI2C(unsigned char ControlByte, unsigned char HighAdd, unsigned char LowAdd, unsigned char *wrptr)
{
	IdleI2C();				//wait for bus Idle
	StartI2C();				//Generate Start condition
	WriteI2C(ControlByte);	//send controlbyte for a write
	IdleI2C();				//wait for bus Idle
	WriteI2C(HighAdd);		//send High Address
	IdleI2C();				//wait for bus Idle
	WriteI2C(LowAdd);		//send Low Address
	IdleI2C();				//wait for bus Idle
	putstringI2C(wrptr);	//Send data
	IdleI2C();				//wait for bus Idle
	StopI2C();				//Generate a stop
	return(0);
}

unsigned int HDduanWriteI2C(unsigned char ControlByte, unsigned char HighAdd, unsigned char LowAdd, unsigned char *wrptr,unsigned char chang)
{
	IdleI2C();				//wait for bus Idle
	StartI2C();				//Generate Start condition
	WriteI2C(ControlByte);	//send controlbyte for a write
	IdleI2C();				//wait for bus Idle
	WriteI2C(HighAdd);		//send High Address
	IdleI2C();				//wait for bus Idle
	WriteI2C(LowAdd);		//send Low Address
	IdleI2C();				//wait for bus Idle
	putstringI2C_chang(wrptr,chang);	//Send data
	IdleI2C();				//wait for bus Idle
	StopI2C();				//Generate a stop
	return(0);
}


/*********************************************************************
* Function:        HDSequentialReadI2C()
*
* Input:		ControlByte, HighAdd, LowAdd, *rdptr, length.
*
* Output:		None.
*
* Overview:		Performs a sequential read of length bytes starting at address
*				and places data in array pointed to by *rdptr
*
* Note:			None
*
*i2c的连续读
********************************************************************/
unsigned int HDSequentialReadI2C(unsigned char ControlByte, unsigned char HighAdd, unsigned char LowAdd, unsigned char *rdptr, unsigned char length)
{
	IdleI2C();						//Ensure Module is Idle
	StartI2C();						//Initiate start condition
	WriteI2C(ControlByte);			//write 1 byte
	IdleI2C();						//Ensure module is Idle
	WriteI2C(HighAdd);				//Write High word address
	IdleI2C();						//Ensure module is idle
	WriteI2C(LowAdd);				//Write Low word address
	IdleI2C();						//Ensure module is idle
	RestartI2C();					//Generate I2C Restart Condition
	WriteI2C(ControlByte | 0x01);	//Write 1 byte - R/W bit should be 1 for read
	IdleI2C();						//Ensure bus is idle
	getsI2C(rdptr, length);			//Read in multiple bytes
	NotAckI2C();					//Send Not Ack
	StopI2C();						//Send stop condition
	return(0);
}


/*********************************************************************
* Function:        ACKStatus()
*
* Input:		None.
*
* Output:		Acknowledge Status.
*
* Overview:		Return the Acknowledge status on the bus
*
* Note:			None
*
*应答信号寄存器
********************************************************************/
unsigned int ACKStatus(void)
{
	return (!I2C1STATbits.ACKSTAT);		//Return Ack Status
}


/*********************************************************************
* Function:        NotAckI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates a NO Acknowledge on the Bus
*
* Note:			None
*
*无应答信号
********************************************************************/
void NotAckI2C(void)
{
	I2C1CONbits.ACKDT = 1;			//Set for NotACk
	I2C1CONbits.ACKEN = 1;
	while(I2C1CONbits.ACKEN);		//wait for ACK to complete
	I2C1CONbits.ACKDT = 0;			//Set for NotACk
}


/*********************************************************************
* Function:        AckI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates an Acknowledge.
*
* Note:			None
*
*应答信号
********************************************************************/
void AckI2C(void)
{
	I2C1CONbits.ACKDT = 0;			//Set for ACk
	I2C1CONbits.ACKEN = 1;
	while(I2C1CONbits.ACKEN);		//wait for ACK to complete
}


/*********************************************************************
* Function:       getsI2C()
*
* Input:		array pointer, Length.
*
* Output:		None.
*
* Overview:		read Length number of Bytes into array
*
* Note:			None
*
*连续读取寄存器中的传回的值
********************************************************************/
unsigned int getsI2C(unsigned char *rdptr, unsigned char Length)
{
	while (Length --)
	{
		*rdptr++ = getI2C();		//get a single byte
		
		if(I2C1STATbits.BCL)		//Test for Bus collision
		{
			return(-1);
		}

		if(Length)
		{
			AckI2C();				//Acknowledge until all read
		}
	}
	return(0);
}


/*********************************************************************
* Function:        getI2C()
*
* Input:		None.
*
* Output:		contents of I2C1 receive buffer.
*
* Overview:		Read a single byte from Bus
*
* Note:			None
*
*单次读取传回的值
********************************************************************/
unsigned int getI2C(void)
{
	I2C1CONbits.RCEN = 1;			//Enable Master receive
	Nop();
//	while(!I2C1STATbits.RBF);		//Wait for receive bufer to be full
//while(!I2C1STATbits.TBF);		//Wait for receive bufer to be full
//		DelayMS(1);
__delay32(200);
	return(I2C1RCV);				//Return data in buffer
}


/*********************************************************************
* Function:        EEAckPolling()
*
* Input:		Control byte.
*
* Output:		error state.
*
* Overview:		polls the bus for an Acknowledge from device
*
* Note:			None
********************************************************************/
unsigned int EEAckPolling(unsigned char control)
{
	IdleI2C();				//wait for bus Idle
	StartI2C();				//Generate Start condition
	
	if(I2C1STATbits.BCL)
	{
		return(-1);			//Bus collision, return
	}

	else
	{
		if(WriteI2C(control))
		{
			return(-3);		//error return
		}

		IdleI2C();			//wait for bus idle
		if(I2C1STATbits.BCL)
		{
			return(-1);		//error return
		}

		while(ACKStatus())
		{
			RestartI2C();	//generate restart
			if(I2C1STATbits.BCL)
			{
				return(-1);	//error return
			}

			if(WriteI2C(control))
			{
				return(-3);
			}

			IdleI2C();
		}
	}
	StopI2C();				//send stop condition
	if(I2C1STATbits.BCL)
	{
		return(-1);
	}
	return(0);
}


/*********************************************************************
* Function:        putstringI2C()
*
* Input:		pointer to array.
*
* Output:		None.
*
* Overview:		writes a string of data upto PAGESIZE from array
*
* Note:			None
********************************************************************/
unsigned int putstringI2C(unsigned char *wrptr)
{
	unsigned char x;

	for(x = 0; x < PAGESIZE; x++)		//Transmit Data Until Pagesize
	{	
		if(WriteI2C(*wrptr))			//Write 1 byte
		{
			return(-3);				//Return with Write Collision
		}
		IdleI2C();					//Wait for Idle bus
		if(I2C1STATbits.ACKSTAT)
		{
			return(-2);				//Bus responded with Not ACK
		}
		wrptr++;
	}
	return(0);
}

unsigned int putstringI2C_chang(unsigned char *wrptr,unsigned char chang)
{
	unsigned char x;

	for(x = 0; x < chang; x++)		//Transmit Data Until Pagesize
	{	
		if(WriteI2C(*wrptr))			//Write 1 byte
		{
			return(-3);				//Return with Write Collision
		}
		IdleI2C();					//Wait for Idle bus
		if(I2C1STATbits.ACKSTAT)
		{
			return(-2);				//Bus responded with Not ACK
		}
		wrptr++;
	}
	return(0);
}
