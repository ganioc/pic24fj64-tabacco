/*******************************
Frame definition:

0xfe | dest (1 byte) | type (1 byte) |


***********************************/

#include "yy_new.h"
#include "p24FJ64GA006.h"
#include "yy_protocol.h"

#define UART1_TX_FIFO_SIZE 32
#define UART1_RX_FIFO_SIZE 32



unsigned char bMark=0;
uint16             iCounter = 0;

volatile uint8 au8_rxFifo1[UART1_RX_FIFO_SIZE];
volatile uint16 u16_rxFifo1Head = 0;
volatile uint16 u16_rxFifo1Tail = 0;

volatile uint8 au8_txFifo1[UART1_TX_FIFO_SIZE];
volatile uint16 u16_txFifo1Head = 0;
volatile uint16 u16_txFifo1Tail = 0;


uint8 parseState = STATE_IDLE;
uint8 parseIndex = 0;
uint8 parseBuf[128];


void toggle(unsigned char bMark)
{

    if(bMark == 1)
    {
        _LATF3 = 0;
        //_LATF2 = 0;

    }
    else
    {
        _LATF3 = 1;
        //_LATF2 = 1;

    }

}

void outChar1(uint8 u8_c)
{
    uint16 u16_tmp;

    u16_tmp = u16_txFifo1Head;
    u16_tmp++;

    if(u16_tmp == UART1_TX_FIFO_SIZE)
    {
        u16_tmp = 0; //wrap if needed
    }

    while(u16_tmp == u16_txFifo1Tail)
        ;

    au8_txFifo1[u16_tmp] = u8_c; //write to buffer
    u16_txFifo1Head = u16_tmp;  //update head
    _U1TXIE = 1;               //enable interrupt
}

void outStr(char * str, uint8 len)
{
    uint16 u16_tmp;
    uint8 i;

    u16_tmp = u16_txFifo1Head;

    for(i=0; i< len; i++)
    {
        u16_tmp++;

        if(u16_tmp == UART1_TX_FIFO_SIZE)
        {
            u16_tmp = 0; //wrap if needed
        }

        //while(u16_tmp == u16_txFifo1Tail)
        //    ;

        au8_txFifo1[u16_tmp] = str[i];
        u16_txFifo1Head = u16_tmp;
    }
    _U1TXIE = 1;               //enable interrupt



}
uint8 bRxCharAvail(void)
{
    if(u16_rxFifo1Head == u16_rxFifo1Tail)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

uint8 inChar1(void)
{
    //while(u16_rxFifo1Head == u16_rxFifo1Tail)
    //    ;
    u16_rxFifo1Tail++;

    if(u16_rxFifo1Tail == UART1_RX_FIFO_SIZE)
    {
        u16_rxFifo1Tail=0;  //wrap
    }

    return au8_rxFifo1[u16_rxFifo1Tail]; //return the character
}

void yy_init()
{

    _TRISF3 = 0;
    _TRISF2 = 1;

    // _LATF3 = 1;
    U1MODEbits.UARTEN= 1;       //n???1?1??

    U1STAbits.UTXEN= 1;        //??D?????

    U1BRG = 12; //compute_brg(FCY, 0, UART1_BAUDRATE);

    U1STAbits.URXISEL=0b00;   //????1???????D??
    U1STAbits.UTXISEL1=0;       //????????????n???????????????n??¯?“TSR???????????o3??¯?a??????2????D??
    U1STAbits.UTXISEL0=0;

    _U1RXIF = 0;
    IEC0bits.U1RXIE=1;

    IEC0bits.U1TXIE=1;

    IPC2bits.U1RXIP=1;            //????3??
    IPC3bits.U1TXIP=1;            //????3??

    // Timer2 init
    T2CONbits.TON=1;       //time3 on
    T2CONbits.TCS=0;       //ÄÚ²¿Ê±ÖÓ£¨FOSC/2£©
    T2CONbits.TCKPS=0B01;  //11 = 1:64
    PR2=50000;                //Timer3 ÖÜÆÚ¼Ä´æ  0.1ÃëÖÐ¶Ï 0.125*256*3125=0.1Ãë
    //200ms

    _T2IE=1;               //ÔÊÐíÖÐ¶Ï
    _T2IP=2;              //ÖÐ¶ÏÓÅÏÈ¼¶=2 µÍ

}



void yy_check()
{
    uint8 ch;

    if(bRxCharAvail() == 1)
    {
        // read out from rxBuffer  at one time
        while(bRxCharAvail() == 1)
        {

            ch = inChar1();
            
            //outChar1(ch);
            parse_frame(ch);

        }

    }

    if(bMark == 1){

        
        outStr("hello\n", 6);
        bMark = 0;

    }
}


void __attribute__((__interrupt__,no_auto_psv)) _U1RXInterrupt(void)
{
    uchar u8_c;

    _U1RXIF=0;

    u8_c = U1RXREG;     //read character

    u16_rxFifo1Head++;   //increment head pointer

    if(u16_rxFifo1Head == UART1_RX_FIFO_SIZE)
        u16_rxFifo1Head = 0; //wrap if needed

    if(u16_rxFifo1Head == u16_rxFifo1Tail)
    {
        //FIFO overrun!, report error
        //reportError("UART1 RX Interrupt FIFO overrun!");
    }
    au8_rxFifo1[u16_rxFifo1Head] = u8_c; //place in buffer
}

void __attribute__((__interrupt__,no_auto_psv)) _U1TXInterrupt(void)
{
    if(u16_txFifo1Head == u16_txFifo1Tail)
    {
        //empty TX buffer, disable the interrupt, do not clear the flag
        _U1TXIE = 0;
    }
    else
    {
        //at least one free spot in the TX buffer!
        u16_txFifo1Tail++;   //increment tail pointer
        if(u16_txFifo1Tail == UART1_TX_FIFO_SIZE)
            u16_txFifo1Tail = 0; //wrap if needed
        _U1TXIF = 0; //clear the interrupt flag
        //transfer character from software buffer to transmit buffer
        U1TXREG =  au8_txFifo1[u16_txFifo1Tail];
    }
}
void __attribute__((__interrupt__,no_auto_psv)) _T2Interrupt(void)
{

    _T2IF = 0;      // ÇåÁãTIMER1µÄÖÐ¶Ï±êÊ¶


    if(bMark == 1){
        return;
    }


    iCounter++;

    if(iCounter == PERIOD_COLLECT_DATA){

        bMark = 1;
        iCounter = 0;

    }

    //toggle(bMark);
    //outStr("hi\n",3);

}



