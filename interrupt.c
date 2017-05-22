#include "p24FJ64GA006.h"
#include "Pin_Definitions.h"
#include "lcd.h"
#include "key.h"
#include "PCF8574.h"
#include "delay.h"

#include "yy_new.h"

extern uchar time_1s,ad_1s;
extern uint16 ss_tab[5][3];
extern uchar ss_js,ss_count;
extern uint16 sd_count,wd_count;
extern uint16 ad_amax,ad_amin;
extern uchar ad_bz,ad_wzbz,ad_cytimes,ad_lc;
extern  uchar key_mid;
extern uchar time_100ms;
extern uchar time_tab[8];
//extern uint16 time_zong;              //��ʱ��
extern uchar gongzuo[9];
extern uchar time_miu,time_sec;
extern uchar ad_ps_bz,ad_count;
extern uchar psm_wz;
extern uint16 pianwenjishi;             //ƫ�±�����ʱ��ʱ
extern uint16 fengjigzjishi;                //������ϻָ���ʱ
extern uchar fengjigzjs;
extern uint16 dianyachaoxianjishi;                  //��ѹ���޼�ʱ
//extern uint16 time_dqd;                   //��ǰ�ε�ʱ�����
extern uint16 kc_js;                    //���μ�ʱ
extern uchar baojingjishizong;                      //�������ʱ��
extern uchar paishimenys;
extern uchar soundtime;
extern uchar soundbusytime;
extern uchar fengjigaodi_100msbz,fengjigaodi_zdjs;      //����ߵ���100�����־������ߵ����жϼ���
extern uchar ss_tihuan_count;                                               //��������ʾ��ʱ
extern uchar chang_232,sign_232;
extern uint16 fa_232[10];
extern uchar ljkc;
extern uchar rtccgz_jishu;              //rtcc���ϼ���
extern uchar bg_bj_count,bg_bj_bz;                  //���ⱨ����ʱ
uchar diaodianbz=0;
uchar rtccchaoshijishu=0;

extern unsigned char bMark;

void __delay32(unsigned long cycles);

//extern uchar key_down_count,key_up_count;

void __attribute__((__interrupt__,no_auto_psv)) _T5Interrupt(void); //0.1��
//void __attribute__((__interrupt__,no_auto_psv)) _T3Interrupt(void);
void __attribute__((__interrupt__,no_auto_psv)) _RTCCInterrupt(void); //1��
void __attribute__((__interrupt__,no_auto_psv)) _ADC1Interrupt(void);   //AD�ж�
void __attribute__((__interrupt__,no_auto_psv)) _CompInterrupt(void); //�Ƚ����ж�
void __attribute__((__interrupt__,no_auto_psv)) _CNInterrupt(void); //��ƽ�仯�ж�
void __attribute__((__interrupt__,no_auto_psv)) _U1RXInterrupt(void);
void __attribute__((__interrupt__,no_auto_psv)) _U1TXInterrupt(void);


void __attribute__((__interrupt__)) _T2Interrupt(void)
{

    _T2IF = 0;      // ����TIMER1���жϱ�ʶ

    bMark = (bMark ==1)?0:1;
    
    //toggle(bMark);

}

void __attribute__((__interrupt__)) _T5Interrupt(void)
{
//uchar keym;

    _T5IF = 0;      // ����TIMER1���жϱ�ʶ
//  LATEbits.LATE4=!LATEbits.LATE4;
//********************
    if(ss_js>0) //&&key_mid==0
    {
//LATEbits.LATE6=!LATEbits.LATE6;
//      shanshuo();
//LATEbits.LATE6=!LATEbits.LATE6;
        ss_count++;
        time_100ms=1;

    }
    diaodianbz=0;
    ss_tihuan_count++;
    //  ss_count++;
    if(ss_tihuan_count>20)ss_tihuan_count=0;
//*/
//
    fengjigaodi_100msbz=1;
    soundbusytime++;
    ad_count++;
    key_down_count++;
    key_up_count++;
    rtccchaoshijishu++;
    if(rtccchaoshijishu==40)    RCFGCALbits.RTCEN=0;
    if(rtccchaoshijishu==45)    RCFGCALbits.RTCEN=1;
    if(rtccchaoshijishu==50)BAOJINGQI=1;
    if(rtccchaoshijishu==55)BAOJINGQI=0;
    if(rtccchaoshijishu==60)    RCFGCALbits.RTCEN=0;
    if(rtccchaoshijishu==65)    RCFGCALbits.RTCEN=1;
    if(rtccchaoshijishu>80)
    {
        rtccgz_jishu++;
        HDByteWriteI2C(0xa0,0x00,0xfd,rtccgz_jishu);
        DelayMS(5);
        while(1);
    }
//I_U_set_time++;
}

void __attribute__((__interrupt__)) _RTCCInterrupt(void)
{
    _RTCIF=0;
//  LATDbits.LATD3=!LATDbits.LATD3;
//LATEbits.LATE7=!LATEbits.LATE7;
//LATEbits.LATE5=!LATEbits.LATE5;
    rtccchaoshijishu=0;
    time_1s=1;
    ad_1s=1;
    if(sign_232==1)
    {
        IEC0bits.U1TXIE=1;
        chang_232=0;

        U1TXREG=fa_232[0]/16;
        U1TXREG=fa_232[0]%16;
    }
    /*
    if(sd_count%2)
    PCF8574_chose(5,1);
    else PCF8574_chose(5,0);
    */
    sd_count++;
    wd_count++;
    time_sec++;
    soundtime++;
    if(time_sec>59)
    {
        gongzuo[6]++;
        gongzuo[4]++;
        time_sec=0;

    }
    if(gongzuo[4]>59)
    {
//  gongzuo[6]=0;
//  gongzuo[5]++;
        gongzuo[4]=0;
        gongzuo[3]++;
    }
    if(gongzuo[6]>59)
    {
        gongzuo[6]=0;
        gongzuo[5]++;

    }
    pianwenjishi++;
    fengjigzjishi++;

    dianyachaoxianjishi++;
    fengjigzjs++;
    kc_js++;
    baojingjishizong++;
//if(psm_wz==0) paishimenys=0;
//else paishimenys++;
    paishimenys++;
    bg_bj_count++;//���ⱨ����ʱ
//  ss_count;
//ALRMEN=
}

void __attribute__((__interrupt__)) _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0;
//  LATFbits.LATF4=!LATFbits.LATF4;
    if(ad_amax<ADC1BUF0)        ad_amax=ADC1BUF0;
    if(ad_amin>ADC1BUF0)        ad_amin=ADC1BUF0;
    if(ad_amax<ADC1BUF1)        ad_amax=ADC1BUF1;
    if(ad_amin>ADC1BUF1)        ad_amin=ADC1BUF1;
    if(ad_amax<ADC1BUF2)        ad_amax=ADC1BUF2;
    if(ad_amin>ADC1BUF2)        ad_amin=ADC1BUF2;
    if(ad_amax<ADC1BUF3)        ad_amax=ADC1BUF3;
    if(ad_amin>ADC1BUF3)        ad_amin=ADC1BUF3;
    if(ad_amax<ADC1BUF4)        ad_amax=ADC1BUF4;
    if(ad_amin>ADC1BUF4)        ad_amin=ADC1BUF4;
    if(ad_amax<ADC1BUF5)        ad_amax=ADC1BUF5;
    if(ad_amin>ADC1BUF5)        ad_amin=ADC1BUF5;
    if(ad_amax<ADC1BUF6)        ad_amax=ADC1BUF6;
    if(ad_amin>ADC1BUF6)        ad_amin=ADC1BUF6;
    if(ad_amax<ADC1BUF7)        ad_amax=ADC1BUF7;
    if(ad_amin>ADC1BUF7)        ad_amin=ADC1BUF7;
    if(ad_amax<ADC1BUF8)        ad_amax=ADC1BUF8;
    if(ad_amin>ADC1BUF8)        ad_amin=ADC1BUF8;
    if(ad_amax<ADC1BUF9)        ad_amax=ADC1BUF9;
    if(ad_amin>ADC1BUF9)        ad_amin=ADC1BUF9;
    if(ad_amax<ADC1BUFA)        ad_amax=ADC1BUFA;
    if(ad_amin>ADC1BUFA)        ad_amin=ADC1BUFA;
    if(ad_amax<ADC1BUFB)        ad_amax=ADC1BUFB;
    if(ad_amin>ADC1BUFB)        ad_amin=ADC1BUFB;
    if(ad_amax<ADC1BUFC)        ad_amax=ADC1BUFC;
    if(ad_amin>ADC1BUFC)        ad_amin=ADC1BUFC;
    if(ad_amax<ADC1BUFD)        ad_amax=ADC1BUFD;
    if(ad_amin>ADC1BUFD)        ad_amin=ADC1BUFD;
    if(ad_amax<ADC1BUFE)        ad_amax=ADC1BUFE;
    if(ad_amin>ADC1BUFE)        ad_amin=ADC1BUFE;
    if(ad_amax<ADC1BUFF)        ad_amax=ADC1BUFF;
    if(ad_amin>ADC1BUFF)        ad_amin=ADC1BUFF;
//
    ad_cytimes++;

}

void __attribute__((__interrupt__,no_auto_psv)) _CompInterrupt(void) //�Ƚ����ж�
{

//  LATCbits.LATC8=!LATCbits.LATC8;
//  LATCbits.LATC8=1;
//      LATAbits.LATA3=!LATAbits.LATA3;

    uchar yucunls[19],i;
    /*
    if(diaodianbz==0)
    {
        diaodianbz=1;

    //  __delay32(4000);
    //  TMR5=2800;
        TMR5=0;
    //  PR5=344;

        __delay32(40000);
        __delay32(40000);
        __delay32(40000);
        __delay32(40000);
        __delay32(38000);
    _CMIF=0;
    }
    */
//if(diaodianbz==1)
//{

    for(i=0; i<8; i++)
    {
        yucunls[i]=time_tab[i];
    }
    for(i=8; i<17; i++)
    {
        yucunls[i]=gongzuo[i-8];
    }
    yucunls[17]=psm_wz;
    yucunls[18]=ljkc;
    HDduanWriteI2C(0xa0,0x01,0x00,yucunls,19);

    //  HDduanWriteI2C(0xa0,0x00,0x75,time_tab,8);
    //  DelayMS(10);
//      HDByteWriteI2C(0xa0,0x00,0x28,(hkdw));                  //��¼��ǰ�濾���ڶ�λ
//      DelayMS(5);
//      HDByteWriteI2C(0xa0,0x00,0x29,(hkdw));                  //��¼��ǰ�濾���ڶ�λ
//      DelayMS(5);
//      HDByteWriteI2C(0xa0,0x00,0x2a,(gzzt));                  //��¼��ǰ�濾���ڶ�λ
//      DelayMS(5);
//      HDByteWriteI2C(0xa0,0x00,0x2b,(hkdw));                  //��¼��ǰ�濾���ڶ�λ
//      DelayMS(5);
    //  HDduanWriteI2C(0xa0,0x00,0x28,gongzuo,8);               //��¼Ϊ���ֺ濾ģʽ1������2���²�3���в�4���ϲ�;��¼��ǰ�濾���ڶ�λ
    //  DelayMS(10);
    /*
        HDByteWriteI2C(0xa0,0x00,0xff,time_tab[1]);
    __delay32(4000);
        HDByteWriteI2C(0xa0,0x01,0x00,time_tab[2]);
    __delay32(4000);
        HDByteWriteI2C(0xa0,0x01,0x01,time_tab[4]);
    __delay32(4000);
        HDByteWriteI2C(0xa0,0x01,0x02,time_tab[5]);
    __delay32(4000);
        HDByteWriteI2C(0xa0,0x01,0x03,time_tab[6]);
    */
//HDByteWriteI2C(0xa0,0x00,0xff,0xff);
    _CMIE=1;
    __delay32(40000);
//  __delay32(38000);
    _CMIF=0;
//while(1);
//}
//  HDByteWriteI2C(0xa0,0x01,0x00,time_tab[2]);

}

void __attribute__((__interrupt__,no_auto_psv)) _CNInterrupt(void)
{
    _CNIF=0;
//  LATAbits.LATA3=!LATAbits.LATA3;
    fengjigaodi_zdjs++;
}

//232�����ж�*******************************************************
/*

void __attribute__((__interrupt__)) _U1RXInterrupt(void)
{
//  U1TXREG=U1RXREG;
//  U1TXREG=U1RXREG;
//  U1TXREG=U1RXREG;
//  U1TXREG=U1RXREG;
    _U1RXIF=0;
    switch(U1RXREG)
    {
        case 0:
            sign_232=0;
            break;
        case 1:             //ÿ����������
            sign_232=1;
            break;
    }
}
*/

/*
void __attribute__((__interrupt__)) _U1TXInterrupt(void)
{
    chang_232++;
    _U1TXIF=0;
    if(chang_232!=10)
    {

        U1TXREG=fa_232[chang_232]/16;
        U1TXREG=fa_232[chang_232]%16;
    }
    else
    {
        //  U1TXREG=asc(10);
        //  sign_232=0;
        IEC0bits.U1TXIE=0;
    }
}
*/


