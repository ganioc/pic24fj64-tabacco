/*
16-03-24��1.18b20ʱ�������2.18b20�������������3.���ⱨ������
*/
#include "p24FJ64GA006.h"

#include "Pin_Definitions.h"
//#include "lcd_guding.h"
#include "lcd.h"
#include "delay.h"
#include "key.h"
#include "sound.h"
#include "init.h"
#include "rtcc.h"
#include "DS18B20.h"
#include "i2c.h"
#include "i2c_24lc512.h"
#include "wenduquxian.h"
#include "PCF8574.h"
#include "gongnengcanshushezhi.h"
#include "guzhangbaojing.h"
#include "chaxun.h"

//#include "lcdPmp.h"
//#include "lcd_guding.h"
//extern void I2C_INIT(void);
//extern uchar AT2402_Read(uint16 address);
//extern void AT2402_Write(uint16 address,uchar val);

extern uint16 ad_dycy(void);
extern uint16 ad_Adlcy(void);

//extern uchar ad_dianya(void);
extern uchar ad_Axdianliu(void);
extern uchar ad_Bxdianliu(void);
extern uchar ad_Cxdianliu(void);
extern uint16 ad_220v_zhi(void);
extern uint16 ad_ADL_zhi(void);
extern uint16 ad_CDL_zhi(void);
extern uchar ad_dianya(void);
//extern void ad_zongduancaiyan(void);
extern void ad_zongduanDIANYAcaiyan(void);
extern void ad_zongduanAxiangcaiyan(void);
extern void ad_zongduanCxiangcaiyan(void);
extern void ad_zongduanBxiangcaiyan(void);
extern void ad_duzhanjiance(void);
extern void ad_dianchijiance(void);
void __delay32(unsigned long cycles);

//_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_OFF & ICS_PGx2)
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & FWDTEN_ON & FWPSA_PR32 & WDTPS_PS2048 & ICS_PGx2)
_CONFIG2(FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_NONE)    //OSCO/CLKO/Rc5 �����˿�I/O��Rc5��
//��ҪFNOSC_FRCPLL
//_CONFIG2(FCKSM_CSECMD & OSCIOFNC_ON   & FNOSC_FRCPLL )FRCPLL  //OSCO/CLKO/Rc5 �����˿�I/O��Rc5��

//#define USE_AND_OR // To enable AND_OR mask setting for I2C.


uchar lcd_RAM[4][32];
uchar time_1s=0,ad_1s=0;
uchar time_100ms=0;
uchar time_tab[8]= {0,22,5,3,18,12,13,0}; //�룬�֣�ʱ�����ڣ��գ��£���
uint16 ss_tab[5][3];
//��˸������Դ洢5����˸ ÿ����˸��𣬺���������3������
uchar ss_js=0,ss_count=0;
//  uchar time_seting=1;
uchar key_down_count,key_up_count;

uchar ret_18B20;                //18B20��λ��־
uchar SWD_Z,SWD_X,SSD_Z,SSD_X,XWD_Z,XWD_X,XSD_Z,XSD_X;   //�¶ȡ�ʪ�ȵ�������С��
uint16 WD[4]= {0,0,0,0};
unsigned char zishe_sector[39]  = {0x26,0x26,0x26,0x26,0x26,0x26,0x26,0x26,0x26,0x26,       //36,38,40,42,46,48,50,54,60,68
                                   0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x48,0x48,      //68,72,74,75,76,76,78,78,80,84
                                   0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,      //2,2,15,4,2,4,2,8,4,4
                                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                                  };          //2,4,2,5,5,6,2,8,12,0
unsigned char xiabu_sector[39]  = {0x24,0x26,0x28,0x2A,0x2E,0x30,0x32,0x36,0x3C,0x44,
                                   0x44,0x48,0x4A,0x4B,0x4C,0x4C,0x4E,0x4E,0x50,0x54,
                                   0x02,0x02,0x0F,0x04,0x02,0x04,0x02,0x08,0x04,0x04,
                                   0x02,0x04,0x02,0x05,0x05,0x06,0x02,0x08,0x0C
                                  };
unsigned char zhongbu_sector[39]= {0x24,0x26,0x28,0x2A,0x2E,0x30,0x32,0x36,0x3C,0x44,
                                   0x44,0x48,0x4B,0x4C,0x4C,0x4D,0x4E,0x4E,0x50,0x54,
                                   0x04,0x04,0x12,0x04,0x04,0x04,0x04,0x08,0x03,0x04,
                                   0x06,0x04,0x02,0x08,0x06,0x06,0x02,0x08,0x12
                                  };
unsigned char shangbu_sector[39]= {0x24,0x26,0x28,0x2A,0x2E,0x30,0x32,0x36,0x3C,0x44,
                                   0x44,0x48,0x4B,0x4D,0x4D,0x4D,0x4E,0x4E,0x50,0x52,
                                   0x04,0x04,0x12,0x04,0x04,0x04,0x06,0x08,0x04,0x04,
                                   0x08,0x04,0x04,0x08,0x08,0x06,0x04,0x08,0x16
                                  };
uchar yushewendu[10]= {20,24,25,33,35,40,43,50,54,61};
uint16 yusheshidu[10]= {200,215,250,275,285,335,370,390,445,460};
uchar yusheshidu1[10];
uchar yushetime[19]= {10,1,6,20,3,7,16,32,8,2,5,4,15,17,26,30,1,10,9};
uint16 sd_count,wd_count,wd_yd,sd_yd,hw_time=0,wenduxielv,shiduxielv;
uchar bz=0;
uint16 ad_axdl,ad_bxdl,ad_cxdl,ad_dy;
uint16 ad_amax=0,ad_amin=0xffff;//,ad_bmax[5]
//long ad_bmax[5];
long ad_bmax[8],ad_bmin[8];
uchar ad_bz=0,ad_wzbz=0,ad_cytimes=0,ad_lc=0;
//uchar wsd_duan=1;
uchar ad_tdbz=0;
const uchar sound_ds[58]= {15,39,50,27,28,51,48,34,31,32,
                           31,33,31,35,19,18,19,17,15,43,
                           36,26,21,20,17,21,20,18,22,20,
                           17,22,20,18,15,44,15,45,46,27,
                           49,34,27,16,28,16,40,16,41,15,
                           30,16,47,27,16,29,51,29
                          };
const uchar sound_kz[23][2]= {   {2,0},{4,2},{2,6},{2,8},{2,10},{2,12},
    {2,14},{4,16},{2,20},{3,22},{3,25},{3,28},
    {3,31},{2,34},{2,36},{2,38},{2,40},{3,42},
    {2,45},{2,47},{4,49},{3,53},{2,56},
};

uchar sound_lsjs=0,sound_duanl=0;                   //��������
uchar sound_numjs=0;
uchar sound_num=100,sound_numx=0;
uchar quxianweizhi=0,time_weizhi=0;         //yeshequxian:��ǰ�ĺ濾ģʽ
uchar key_mid;
uchar key_zhi=0;
uchar set_key=0;
uchar PCF8574=0;
uchar key256=0;
//uint16 time_zong=0;               //��ʱ��
uchar time_sec=0;       //ÿ���ӣ�ÿСʱ,ÿ��
//uchar gzzt=0;                     //����״̬
//uchar hkdw=0;                     //�濾��λ
uint16 hw_shijian=0;                //����ʱ�䳤��
//uint16 time_dqd=0;                    //��ǰ�ε�ʱ�����
uchar gongzuo[9]= {11,0,0,0,0,0,0,0,0};     //0:������ʽ1:��λ2���Ƿ�����3����ʱ��4:��ʱ���5����ǰ��ʱ��ʱ6:��ǰ��ʱ���7������8:�����
uchar set_bz=0;
uchar ad_ps_bz=0,ad_count=0,ad_kgd=0,psm_wz=0;              //ad��ʪ��־��ad���ؼ�ʱ,��ʪ�ŵ��ʿ��ش�С����ʪ�ŵ�������ʪ��λ��
uint16 ps_dl=100;
uint16 ad_dlz[3]= {0,0,0};
uchar ad_tzbz=0;    //ad��ʪֹͣ��ʱ��־
uchar chaxunbz=0;       //��ǰ������ѯ��־
uchar lssound=53;
uchar dwxcbc=0;         //��ǰ�����жε�λ�ñ���
uchar ok_bz=0;          //����ȷ�ϱ�־
uchar ok_bz_cs=0;       //���ܲ���ȷ�ϱ�־

uchar pianwencanshu[5]= {20,20,10,10,28};       //ƫ�����ò���
uchar pianwencanshugd[5]= {20,20,10,10,28};     //ƫ�����ò���
uchar set_pwcs=0;           //ƫ�²���ѡ������
/*
uchar fengjibaohucanshu[4]={85,55,75,15};       //��������������
uchar fengjibaohucanshugd[4]={85,55,75,15};     //��������������
uchar set_fjbhcs=0;                             //�������ѡ��
*/


uchar fengjibaohucanshu[4]= {65,35,45,15};      //��������������
uchar fengjibaohucanshugd[4]= {65,35,45,15};    //��������������
uchar set_fjbhcs=0;                             //�������ѡ��


uint16 dianyabaohucanshu[4]= {270,170,3,300};       //��ѹ���������������
uint16 dianyabaohucanshugd[4]= {270,170,3,300};     //��ѹ���������������
uchar set_dybhcs=0;                             //��ѹ����ѡ��
uchar ls_dy[6]= {0,0,0,0,0,0};                  //��ʱ��ѹת��ֵ

uchar guzhanghuifucanshu[2]= {10,3};    //���ϻָ������������
uchar guzhanghuifucanshugd[2]= {10,3};      //���ϻָ������������
uchar set_gzhfcs=0;                             //���ϻָ�����ѡ��

//uchar paishimencanshu[4]={1,1,230,6};     //��ʪ�Ÿ����������
//uchar paishimencanshugd[4]={1,1,230,6};       //��ʪ�Ÿ����������
uchar paishimencanshu[6]= {1,1,130,6,1,7};      //��ʪ�Ÿ����������
uchar paishimencanshugd[6]= {1,1,130,6,1,7};    //��ʪ�Ÿ����������
uchar set_psmcs=0;

uchar set_gncs_all=0;           //���ܲ���ѡ�� ƫ�£������
uchar gncs_set_bz=0;
uchar kc_bz=0;                  //�������ӱ�־
uint16 kc_js=0;                 //���μ�ʱ
uint16 baojingbz[3]= {0,0,0};               //������־
uint16 pianwenjishi=0;              //ƫ�±�����ʱ��ʱ
uchar pianwanbaojingbz=0;           //ƫ�±�����־
uchar fjsd=0;                       //����ٶ�
uint16 fengjigzjishi=0,fengjihuifucs=0;             //������ϻָ���ʱ,����ָ�����
uchar fengjikgbz=0;                             //������ر�־
uint16 dyzhi=0;                                 //��ѹֵ
uint16 dianyachaoxianjishi=0;                   //��ѹ���޼�ʱ

uchar ls_zddl[3]= {22,22,22};
uchar ls_zddl1[3]= {40,40,40};
uchar ls_zddl2[3]= {40,4,40};
uchar ls_zddl3[3]= {50,40,44};
uchar ls_dlbz=0;
uchar fengjigzjs=0,fengjigzbhsj=0;          //������ؼ�ʱ��������ر���ʱ��
uchar chucunkc=0;                           //���浽�Ŀ���
uchar chaxunkc=0;                           //��ѯ���Ŀ���
uint16 chauxnwzcs[10][3]= {{0x0200,0x0200,0},{0x0e80,0x0e80,0},{0x1b00,0x1b00,0},
    {0x2780,0x2780,0},{0x3400,0x3400,0},{0x4080,0x4080,0},
    {0x4d00,0x4d00,0},{0x5980,0x5980,0},{0x6600,0x6600,0},{0x7280,0x7280,0},
};
uint16 chaxuncs=0;                          //��ѯ������������
uchar chaxun_bz=0;                          //��ѯ��־ �Ƿ��ڲ�ѯ��
//ǰһ���±������ ������������ǰһ��Ϊ�׵�ַ��һ��β��ַ���Ϊ����

uchar lskc=0;
uchar zhuanhuanfanhui[2]= {0,0};            //16λת��8λ���ص�����8λֵ
//uchar kzbz=0;



//uchar set_ui_zhi[4]={90,109,84,104};          //��ѹ������������
uchar set_ui_zhi[4]= {126,126,126,131};         //��ѹ������������
uchar baojingjishizong=0;                       //�������ʱ��
uchar shenyinpaixu[5]= {0,0,0,0,0};         //���������������������
uchar leijishenyinduanshu=0;                //�ۼƻ��ж��ٶ�����Ҫ��
uchar sound_qdbz=0;
uint16 fengjiqxcs=0;                            //���ȱ�����
uchar paishimenys=60,zsjs_bz=0;             //��ʪ�ſ�����ʱ��ʱ������ģʽ�Ľ�����ĺ��±�־
uchar ds18b20_1bz=0;
uchar xianshi_bz[5]= {0,0,0,0,0};               //��ʾ�ı�־ �������Ƶ�һ����ʾ�Ͳ��ظ���ʾ
uchar dz_wc_bz=0;                               //��ת������һ�α�־
uchar sound_i=0;                            //�����ۼ�
uchar sound_all[5][4]= {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},};
//���������Ԥ������ֱ𡾷�� �¶� ʪ�� ��ѹ������Ӧ ���� ���ʱ�� �������� �첻�졿
uchar soundtime=0,sound_qsbz=0,leiji=0;     //������ʱ������������ʼ��־��ÿ���ۼƱ�������
uchar soundbusytime=0;
//uchar abc[5][1300];
uchar fengjigaodi_100msbz=0,fengjigaodi_zdjs=0,fengjigaodi_bz=0;        //����ߵ���100�����־������ߵ����жϼ���
uchar move_sign=0;                                                      //��λѡ���ƶ���־
uchar ss_tihuan_count=0;                                                //��������ʾ��ʱ
uint16 fa_232[10]= {0,1,2,3,4,5,6,7,8,9};
uchar chang_232=0,sign_232=0;

uchar ljkc=0;

uchar fjqh_sign=0;
uchar ls_jf=0,ls_js=0,ls_jfz=0,ls_jsz=0;                                                    //��ʱ���ӣ�Сʱ��ʱ
uchar san_dan_sign=1;               //������������־1�����࣬0����
uchar san_dan_xz=0;                 //��������������ֵ
uint16 ad_dianchi=0;                //��ص�ѹadֵ
uchar bj_bz=0,bj_cs=0;              //������־ ����
uint16 ad_dichi_dy=0;
uchar gongdian_bz=0;                //�����־
uchar fengjiqishi_bz=0;             //�����ʼ���ر�־
uchar rtccgz_jishu=0;               //rtcc���ϼ���
uchar bg_bj_count=0,bg_bj_bz=0;                 //���ⱨ����ʱ���ⱨ����־
int main(void)
{
    uchar ls_kaociduanwei=0;
    uint16 ls_WD[4]= {0,0,0,0};
    uchar tihuan_sign=0;
//  uchar set_key=0;
    uchar i,j;
    uint16 k;
    uchar wendu_c=0;
    uchar ls_cvr=0;
    uint16 time_dqmb=0;//��ǰ���жε�����ʱ��
    uchar weizhi[19]= {3,4,7,8,11,12,15,16,19,20,23,24,27,28,31,32,35,36,39};
    uint16 ls_mbsj=0;
    uchar lsdzcs[60];
    uchar ls_mbtimes=1;
    uchar chaxuncunchu_bz=0;

    uchar kcshanshuobz=0,shanshuokc;                                        //���ڿ�����˸
    uchar ss_min_bz=0;
    uchar lscdbz=0;
    uchar yucunls[19];
//  uchar sound_count=0;
    init_main();
//  InitI2C();
    //  DelayMS(3000);
    /*
        for(i=0;i<7;i++)
        {
            for(j=0;j<16;j++)
            {
                lcd_RAM[i][j]=0x00;
            }
        }
    */
    init_lcd(2);
    __delay32(12);
    init_lcd(1);
    __delay32(12);
    init_lcd(2);
    __delay32(12);
    init_lcd(3);
    __delay32(12);
    init_lcd(4);
    __delay32(12);
    init_lcd(2);
    init_lcd(1);
    init_lcd(2);
    init_lcd(3);
    init_lcd(4);
    write_all_lcd(0);
    key_mid=key();
    if(key_mid==4)
    {
        for(k=0; k<256; k++)
        {
            for(j=0; j<4; j++)
            {
                HDPageWriteI2C(0xa0,k,(j*64),0xff);
                DelayMS(20);
            }
            ClrWdt();
        }
    }

    for(i=0; i<4; i++)
    {
        for(j=0; j<32; j++)
        {
            lcd_RAM[i][j]=0x00;
        }
    }
    LDByteWriteI2C(0X40,0X00);
    //      DelayMS(20);
//if(SAN_DAN_IN==0)san_dan_sign=0;
//if(SAN_DAN_IN==1)san_dan_sign=1;
    /*
    for(i=0;i<5;i++)
    {

    HDPageWriteI2C(0xa0,i,0,p);
    DelayMS(10);
    HDPageWriteI2C(0xa0,i,128,p);
    DelayMS(10);
    }
    */
    DelayMS(2000);
//if(SAN_DAN_IN==0)san_dan_sign=0;
//if(SAN_DAN_IN==1)san_dan_sign=1;
    ClrWdt();
    if(HDByteReadI2C(0xa0,0x00,0xfe)==0xaa)
    {
        //      HDduanWriteI2C(0xa0,0x01,0x55,set_ui_zhi,4);
        //      DelayMS(10);
        HDSequentialReadI2C(0xa0,0x01,0x00,time_tab,8);     //0x00,0x75
        DelayMS(10);
        time_write(time_tab);
        HDSequentialReadI2C(0xa0,0x01,0x08,gongzuo,9);      //0x00,0x28
        DelayMS(10);
        HDSequentialReadI2C(0xa0,0x01,0x40,pianwencanshu,5);
        DelayMS(10);
        HDSequentialReadI2C(0xa0,0x01,0x45,fengjibaohucanshu,4);
        DelayMS(10);
        ljkc=HDByteReadI2C(0xa0,0x01,0x12);
        DelayMS(10);
        fjqh_sign=HDByteReadI2C(0xa0,0x01,0x13);
        DelayMS(10);
        kc_bz=HDByteReadI2C(0xa0,0x01,0x14);
        DelayMS(10);
        HDSequentialReadI2C(0xa0,0x01,0x49,ls_dy,6);
        dianyan_zhuanhuan_i2ctomain();
        DelayMS(10);
        HDSequentialReadI2C(0xa0,0x01,0x4f,guzhanghuifucanshu,2);
        DelayMS(10);
        HDSequentialReadI2C(0xa0,0x01,0x51,paishimencanshu,6);
        DelayMS(10);
        HDSequentialReadI2C(0xa0,0x00,(0x00+(gongzuo[0]-10)*64),yushewendu,10);
        DelayMS(10);
        HDSequentialReadI2C(0xa0,0x00,(0x0a+(gongzuo[0]-10)*64),yusheshidu1,10);
        DelayMS(10);
        HDSequentialReadI2C(0xa0,0x00,(0x14+(gongzuo[0]-10)*64),yushetime,19);
        DelayMS(10);
        HDSequentialReadI2C(0xa0,0x01,0x57,set_ui_zhi,4);
        DelayMS(10);
        chucunkc=HDByteReadI2C(0xa0,0x01,0xbf);
        DelayMS(5);
        HDSequentialReadI2C(0xa0,0x01,0x80,lsdzcs,60);
        DelayMS(10);
        for(i=0; i<10; i++)
        {
            chauxnwzcs[i][0]=zhuanhuan_8to16(lsdzcs[i*6+0],lsdzcs[i*6+1]);
            chauxnwzcs[i][1]=zhuanhuan_8to16(lsdzcs[i*6+2],lsdzcs[i*6+3]);
            chauxnwzcs[i][2]=zhuanhuan_8to16(lsdzcs[i*6+4],lsdzcs[i*6+5]);
        }
    }

    else
    {

        /*
                time_tab[1]=HDByteReadI2C(0xa0,0x00,0xff);
        __delay32(2000);
                time_tab[2]=HDByteReadI2C(0xa0,0x01,0x00);
        __delay32(2000);
                time_tab[4]=HDByteReadI2C(0xa0,0x01,0x01);
        __delay32(2000);
                time_tab[5]=HDByteReadI2C(0xa0,0x01,0x02);
        __delay32(2000);
                time_tab[6]=HDByteReadI2C(0xa0,0x01,0x03);
        __delay32(2000);
        */
        DelayMS(1200);
        ClrWdt();
        HDByteWriteI2C(0xa0,0x00,0xfe,0xaa);
        DelayMS(5);
        HDduanWriteI2C(0xa0,0x00,0x00,zishe_sector,39);
        DelayMS(10);
        HDduanWriteI2C(0xa0,0x00,0x40,xiabu_sector,39);
        DelayMS(10);
        HDduanWriteI2C(0xa0,0x00,0x80,zhongbu_sector,39);
        DelayMS(10);
        HDduanWriteI2C(0xa0,0x00,0xc0,shangbu_sector,39);
        DelayMS(10);
        HDduanWriteI2C(0xa0,0x01,0x08,gongzuo,9);               //��¼Ϊ���ֺ濾ģʽ1������2���²�3���в�4���ϲ�;��¼��ǰ�濾���ڶ�λ
        DelayMS(10);
        HDByteWriteI2C(0xa0,0x01,0x13,fjqh_sign);
        DelayMS(10);
        HDByteWriteI2C(0xa0,0x01,0x14,kc_bz);
        DelayMS(10);
        HDduanWriteI2C(0xa0,0x01,0x40,pianwencanshugd,5);
        DelayMS(10);
        HDduanWriteI2C(0xa0,0x01,0x45,fengjibaohucanshugd,4);
        DelayMS(10);
        dianyan_zhuanhuan_maintoi2c();
        HDduanWriteI2C(0xa0,0x01,0x49,ls_dy,6);
        DelayMS(10);
        HDduanWriteI2C(0xa0,0x01,0x4f,guzhanghuifucanshugd,2);
        DelayMS(10);
        HDduanWriteI2C(0xa0,0x01,0x51,paishimencanshugd,6);
        DelayMS(10);
        HDduanWriteI2C(0xa0,0x01,0x57,set_ui_zhi,4);
        DelayMS(10);
        huihuchaxunzhi();

//      HDByteWriteI2C(0xa0,0x01,0x40,0x01);                    //��¼Ϊ���ֺ濾ģʽ1������2���²�3���в�4���ϲ�
//      DelayMS(5);
//      HDByteWriteI2C(0xa0,0x00,0x29,(hkdw));                  //��¼��ǰ�濾���ڶ�λ
//      DelayMS(5);
        time_write(time_tab);
    }
//      HDByteWriteI2C(0xa0,0x00,0x28,0x0a);                    //��¼Ϊ���ֺ濾ģʽa������b���²�c���в�d���ϲ�
//      DelayMS(5);
//      DelayMS(600);
//HDduanWriteI2C(0xa0,0x00,0x00,yushewendu,10);
//  write_lcd_shuzi_erwei(44,1,time_tab[1]);
//      DelayMS(600);

//  time_write_bety(2,22);
//  write_lcd_shuzi_yiwei(1,6);


//  write_lcd_shuzi_erwei(1,1,34);
//  write_lcd_shuzi_erwei(6,1,18);
//  write_lcd_shuzi_erwei(9,1,0);
//set_ui_zhi[3]=95;
    if(san_dan_sign==0)san_dan_xz=0;//24
    if(san_dan_sign==1)san_dan_xz=0;
    ClrWdt();
    DS18B20_err_disp();             //��ʾ�¶ȴ������������
    rtccgz_jishu=HDByteReadI2C(0xa0,0x00,0xfd);
    DelayMS(5);
    write_lcd_shuzi_sanwei(4,1,rtccgz_jishu);
    write_lcd_shuzi_sanwei(3,1,set_ui_zhi[0]);
    write_lcd_shuzi_sanwei(5,1,set_ui_zhi[1]);
    write_lcd_shuzi_sanwei(6,1,set_ui_zhi[2]);
    write_lcd_shuzi_sanwei(7,1,set_ui_zhi[3]);
    DelayMS(1000);
    ClrWdt();
    DelayMS(1000);
    ClrWdt();
    write_lcd_zi(9,1);
    write_lcd_zi(3,1);
    DelayMS(300);
    ClrWdt();
//  key_mid=HDByteReadI2C(0xa0,0x00,0x02);
//  HDByteWriteI2C(0xa0,0x32,0x20,125);
//  HDPageWriteI2C(0xa0,0x00,0x00,yushewendu);

//  PCF8574_chose(6,1);
    LED_RUN_OFF;
    PCF8574_chose(5,1);
    LED_SET_OFF;
//  PCF8574_chose(0,0);             //ѭ�������
    JDQ_FENGJI_OFF;
    DelayMS(300);
    write_lcd_point(10,1);
    write_lcd_point(11,0);
    write_lcd_point(13,0);
    write_lcd_point(14,0);
//  write_lcd_shuzi_erwei(5,1,148);
//  write_lcd_shuzi_sanwei(3,1,1576);
    write_lcd_shuzi_sanwei(3,1,((yushetime[gongzuo[1]]*10)-(gongzuo[5]*60+gongzuo[6])/6));
    write_lcd_shuzi_sanwei(4,1,gongzuo[3]);
    write_lcd_shuzi_sanwei(5,1,0);
    write_lcd_shuzi_sanwei(6,1,0);

    //  DelayMS(50000);
//  key_mid=HDByteReadI2C(0xa0,0x00,0x02);
//  write_lcd_shuzi_sanwei(4,1,key_mid);
    /*
            HDSequentialReadI2C(0xa0,0x00,(0x00+(gongzuo[0]-10)*64),yushewendu,10);
            DelayMS(10);
            HDSequentialReadI2C(0xa0,0x00,(0x0a+(gongzuo[0]-10)*64),yusheshidu1,10);
            DelayMS(10);
            HDSequentialReadI2C(0xa0,0x00,(0x14+(gongzuo[0]-10)*64),yushetime,19);
            DelayMS(10);
        for(i=0;i<10;i++)
        {
            yusheshidu[i]=shiduyingyongzhuanhuan_2to1(yusheshidu1[i]);
        }
        if(gongzuo[0]!=11)
        {
            for(i=0;i<10;i++)
            {
                write_lcd_shuzi_erwei((i*4+1),1,yushewendu[i]);
                write_lcd_shuzi_erwei((i*4+2),1,yusheshidu[i]/10);
                if(yusheshidu[i]%10==5) write_lcd_point(i+1,1);
                else write_lcd_point(i+1,0);
                write_lcd_shuzi_erwei((i*4+3),1,yushetime[i*2]);
                if(i*4+4!=40)
                write_lcd_shuzi_erwei((i*4+4),1,yushetime[i*2+1]);
            }
        }
        else
        {
            for(i=0;i<gongzuo[8];i++)
            {
                write_lcd_shuzi_erwei((i*4+1),1,yushewendu[i]);
                write_lcd_shuzi_erwei((i*4+2),1,yusheshidu[i]/10);
                if(yusheshidu[i]%10==5) write_lcd_point(i+1,1);
                else write_lcd_point(i+1,0);
                write_lcd_shuzi_erwei((i*4+3),1,yushetime[i*2]);
                if(i*4+4!=40&&i>0)
                write_lcd_shuzi_erwei((i-1)*4+4),1,yushetime[(i-1)*2+1]);
            }
        }
    */

    lcd_xiepingmu(1);
//gongzuo[0]=gongzuo[0];
    /*
    LATCbits.LATC8=1;
                DelayMS(3000);
    LATCbits.LATC8=0;
    //LCD_BG_DIS;

                DelayMS(3000);
    */
    _CMIF=0;
    _CMIE=1;
    paishimen_kaiguan(1,1);
    DelayMS(2000);
    ClrWdt();
    paishimen_kaiguan(0,0);
    DelayMS(100);
    //  paishimen_kaiguan(2,10);
    ClrWdt();
    ad_bz=0;
    ad_ps_bz=1;
    ad_cytimes=0;
    //  PCF8574_chose(1,0);
//JDQ_PAISHI_BIG_OFF;
    //  PCF8574_chose(2,1);
//JDQ_PAISHI_MIN_ON;
    Discharge_wet_ON_right();
//      ad_duzhanjiance();
    DelayMS(1500);
    ClrWdt();
    DelayMS(1500);
    ClrWdt();
    time_sec=0;
//  DelayMS(1000);
    do
    {
//      if(dz_wc_bz==1)dz_wc_bz=0;

        ad_duzhanjiance();
        if(dz_wc_bz==1&&(ps_dl>800||ps_dl<10))dz_wc_bz=2;//
        if(ps_dl<800&&ps_dl>10&&dz_wc_bz==1)dz_wc_bz=0;
//  write_lcd_shuzi_sanwei(1,1,ps_dl);
        ClrWdt();
//  DelayMS(40);
    }
    while(dz_wc_bz!=2&&time_sec<6);//
    /*
        do
        {
    //      if(dz_wc_bz==1)dz_wc_bz=0;

            ad_duzhanjiance();

        }
        while((ps_dl<200&&ps_dl>40)&&dz_wc_bz!=1);//

    //  ad_duzhanjiance();
        while(ps_dl<180&&ps_dl>10&&ad_cytimes!=1)
        {
            ad_duzhanjiance();
        }
    */
    psm_wz=0;
    paishimen_kaiguan(0,0);

//_C1EN=1;
//  __delay32(200);
//      SOUND_RST=0;
//  __delay32(200);
//for(i=0;i<50;i++)
//{

//}

    get_star_temp();
    DelayMS(1500);
    ClrWdt();
    get_star_temp();
    DelayMS(1500);
    ClrWdt();
    get_star_temp();
    DelayMS(1500);

    ClrWdt();
    if(WD[0]==65534&&WD[1]==65534&&WD[2]==65534&&WD[3]==65534&&gongzuo[2]==0)
    {
        fengjiqishi_bz=1;
    }
    else fengjiqishi_bz=0;
    if(gongzuo[2]==1)
    {
        write_lcd_kuang(weizhi[gongzuo[1]],1);
        //  PCF8574_chose(6,0);
        LED_RUN_ON;
        pianwenjishi=0;
        fengjigzjishi=0;
        if((gongzuo[1]+1)%2==0)
        {
            xielvjisuan(((gongzuo[1]+1)/2)-1);
            if(wenduxielv!=0&&((gongzuo[5]*60+gongzuo[6]))<yushetime[gongzuo[1]]*60)
            {
                ls_mbsj=((gongzuo[5]*60+gongzuo[6])*60)%wenduxielv;
                ls_mbtimes=((gongzuo[5]*60)+gongzuo[6])*60/wenduxielv+1;

                /*
                while(ls_mbsj>wenduxielv)
                    {
                        ls_mbsj=ls_mbsj-wenduxielv;
                        ls_mbtimes++;
                    }
                */

                //  while(ls_mbsj>0);
                wd_count=ls_mbsj;
                wd_yd=yushewendu[(gongzuo[1]+1)/2-1]*10+ls_mbtimes;
            }
            else
            {
                wd_yd=yushewendu[(gongzuo[1]+1)/2]*10;

            }
            write_lcd_shuzi_sanwei(5,1,wd_yd);
            write_lcd_point(13,1);
            //  ls_mbsj=gongzuo[5]*60;
            //  ls_mbtimes=1;
            if(shiduxielv!=0&&((gongzuo[5]*60+gongzuo[6]))<yushetime[gongzuo[1]]*60)
            {
                ls_mbsj=((gongzuo[5]*60+gongzuo[6])*60)%shiduxielv;
                ls_mbtimes=((gongzuo[5]*60)+gongzuo[6])*60/shiduxielv+1;
                sd_count=ls_mbsj;
                sd_yd=yusheshidu[(gongzuo[1]+1)/2-1]+ls_mbtimes;
            }
            else
            {

                sd_yd=yusheshidu[(gongzuo[1]+1)/2];
                //      gongzuo[1]++;
            }
            write_lcd_shuzi_sanwei(6,1,sd_yd);
            write_lcd_point(14,1);
            ls_mbtimes=0;

//write_lcd_shuzi_sanwei(3,1,(gongzuo[5]));
//write_lcd_shuzi_sanwei(4,1,shiduxielv);
        }
        else
        {

            wd_yd=yushewendu[(gongzuo[1]+1)/2]*10;
            sd_yd=yusheshidu[(gongzuo[1]+1)/2];
            //  hw_shijian=yushetime[gongzuo[1]-1]*60;
            write_lcd_shuzi_sanwei(5,1,wd_yd);
            write_lcd_point(13,1);
            write_lcd_shuzi_sanwei(6,1,sd_yd);
            write_lcd_point(14,1);
        }
//      if(chaxun_bz!=1)
//      {
        if(gongzuo[1]%2)
        {
            write_lcd_zi(16,1);
            write_lcd_zi(17,0);
        }
        else
        {
            write_lcd_zi(17,1);
            write_lcd_zi(16,0);
        }
//      }
    }
    write_lcd_zi(8,1);
//  DelayMS(3000);
    key();
    if(SHANGXIAP==0)
    {
        write_lcd_zi(14,1);
        write_lcd_kuang(44,1);
        write_lcd_zi(15,0);
        write_lcd_kuang(45,0);
    }
    else
    {
        write_lcd_zi(14,0);
        write_lcd_kuang(44,0);
        write_lcd_zi(15,1);
        write_lcd_kuang(45,1);
    }
    write_lcd_zi(gongzuo[0],1);

    write_lcd_kuang(gongzuo[0]+30,1);
    write_lcd_shuzi_yiwei(1,gongzuo[7]+1);
    fengjigzjishi=0;
//  while(1){ClrWdt();}

/*********************************************************************************/


    yy_init();

    while(1)
    {
        yy_check();
        
        close_system();     //��ص�������ֹͣϵͳ
        huifuchuchangzhi();
        key_mid=key();
//write_lcd_shuzi_sanwei(4,1,key_mid);
        if(key_mid==18)
        {
//  PCF8574_chose(5,0);
            I_U_SET();
        }

        /*
                if(key_mid==1&&ls_cvr<15)
                {
        //ls_cvr=_CVR;

                    DelayMS(300);
        //  LATCbits.LATC8=!LATCbits.LATC8;
                    ls_cvr++;
            write_lcd_shuzi_sanwei(6,1,ls_cvr);
                    _CVR=ls_cvr;
                }
                if(key_mid==16&&ls_cvr>0)
                {
        //ls_cvr=_CVR;
                    DelayMS(300);
        //  LATCbits.LATC8=!LATCbits.LATC8;
                    ls_cvr--;
            write_lcd_shuzi_sanwei(6,1,ls_cvr);
                    _CVR=ls_cvr;
                }

        if(key_mid==1)
        {
        hw_time++;
        gongzuo[5]++;
        write_lcd_shuzi_sanwei(4,1,hw_time);
        write_lcd_shuzi_sanwei(3,1,time_dqd);
        }
        */
//if(key_mid==16)
//{/

//}
        if(key_mid==128&&key_down_count<5)
        {
            chaxunbz=1;
            write_lcd_shuzi_sanwei(3,1,(ad_dlz[0]/10+1000));
//write_lcd_shuzi_sanwei(3,1,(ad_dlz[0]));
            write_lcd_point(12,1);
            write_lcd_shuzi_sanwei(5,1,(ad_dlz[1]/10+1100));
//write_lcd_shuzi_sanwei(5,1,(ad_dlz[1]));
            write_lcd_point(13,1);
            write_lcd_shuzi_sanwei(6,1,(ad_dlz[2]/10+1200));
//write_lcd_shuzi_sanwei(6,1,(ad_dlz[2]));
            write_lcd_point(14,1);
            if(SHANGXIAP==0)
            {
                write_lcd_zi(14,0);
                write_lcd_kuang(44,0);
                write_lcd_zi(15,1);
                write_lcd_kuang(45,1);
            }
            else
            {
                write_lcd_zi(14,1);
                write_lcd_kuang(44,1);
                write_lcd_zi(15,0);
                write_lcd_kuang(45,0);
            }
            key_up_count=0;
            write_lcd_shuzi_sanwei(1,1,WD[2]);
            write_lcd_shuzi_sanwei(2,1,WD[3]);
        }
        anjianhuifuchaxun();                //�����ָ���ѯ�б�
        if(chaxunbz==1&&key_up_count>100)
        {
            chaxunbz=0;
            if(SHANGXIAP==0)
            {
                write_lcd_zi(14,1);
                write_lcd_kuang(44,1);
                write_lcd_zi(15,0);
                write_lcd_kuang(45,0);
            }
            else
            {
                write_lcd_zi(14,0);
                write_lcd_kuang(44,0);
                write_lcd_zi(15,1);
                write_lcd_kuang(45,1);
            }
            write_lcd_shuzi_sanwei(1,1,WD[0]);
            write_lcd_shuzi_sanwei(2,1,WD[1]);
            write_lcd_shuzi_sanwei(3,1,((yushetime[gongzuo[1]]*10)-(gongzuo[5]*60+gongzuo[6])/6));
            write_lcd_point(12,1);
            //      write_lcd_shuzi_sanwei(4,1,(gongzuo[3]));
//if(baojingbz[1]==3&&ss_tihuan_count==5)
//{
//  write_lcd_shuzi_sanwei(5,1,1506);
//}
//else if(baojingbz[1]!=3||ss_tihuan_count==0)
//{
            write_lcd_shuzi_sanwei(5,1,wd_yd);
            write_lcd_point(13,1);
//}
            write_lcd_shuzi_sanwei(6,1,sd_yd);
            write_lcd_point(14,1);

        }
        if(chaxun_bz!=1&&chaxunbz!=1&&fjqh_sign==0&&gncs_set_bz!=1)                                 //����޵���E06������ʾ
        {
            if(baojingbz[1]==3&&ss_tihuan_count==15)
            {
                tihuan_sign=1;
                write_lcd_shuzi_sanwei(5,1,1406);
                write_lcd_point(13,0);
            }
            else if(baojingbz[1]==3&&ss_tihuan_count==5)
            {
                tihuan_sign=1;
                write_lcd_shuzi_sanwei(5,1,wd_yd);
                write_lcd_point(13,1);
            }
        }
        if(tihuan_sign==1&&baojingbz[1]!=3)
        {
            tihuan_sign=0;
            write_lcd_shuzi_sanwei(5,1,wd_yd);
            write_lcd_point(13,1);
        }
        if(key_mid==8&&set_key<3&&gncs_set_bz==0&&chaxun_bz==0)
        {
            //  PCF8574_chose(5,0);         //���õ�����
            LED_SET_ON;
//paishimen_kaiguan(1,7);
            if(gongzuo[2]!=1)
            {
                if(set_key==0)
                    dwxcbc=gongzuo[1];
                set_key++;
            }

            else if(set_key==0)
            {
                set_key=1;
                dwxcbc=gongzuo[1];
            }
            else if(set_key==1)
                set_key=3;
            set_bz=1;
            time_weizhi=0;
            DelayMS(400);
            ok_bz=0;
        }
        else if(key_mid==8&&gncs_set_bz==0&&chaxun_bz==0)
        {
            //  PCF8574_chose(5,0);
            LED_SET_ON;
            set_key=1;
            ok_bz=0;
//set_bz=0;
            DelayMS(400);
        }
//      set_all(set_key);
        set_all();
//      if(key_mid==8&&key_down_count>20)   set_time();

        sound_duan();
        sound_number();

        if(key_mid==17&&key_down_count==30)                         //���⹦�ܲ�������
        {
            //  PCF8574_chose(5,0);
            LED_SET_ON;
            set_gncs_all=0;
            ok_bz_cs=0;
            set_pwcs=0;
            write_lcd_shuzi_sanwei(5,1,set_gncs_all+1500);
            write_lcd_point(13,0);
            write_lcd_shuzi_sanwei(1,2,pianwencanshu[0]);
            write_lcd_point(10,2);
            write_lcd_shuzi_sanwei(6,1,set_pwcs);
            write_lcd_point(14,0);
            write_lcd_shuzi_sanwei(2,1,65532);
            write_lcd_point(11,0);
            gncs_set_bz=1;
        }
        if(gncs_set_bz==1)
        {
            gongnengchanshu_set_all();
        }
        if(set_key==0&&gncs_set_bz==0&&chaxun_bz==0)    duanweixuanze();
        stop_run();
        fengjikongzhi_qiehuan();
        fengjikaikongzhi();
        if(fjqh_sign==0)
        {
            if(san_dan_sign==1)fengjiguankongzhi();
            if(san_dan_sign==0)fengjiguankongzhi_two();
        }
//      chuxun_xuanze();

        if(gongzuo[2]==1&&gongdian_bz==0)
        {
            baojing();

        }

//0 sound_shunxuduqu();         //�������˳���ȡ
        if(gongdian_bz==0)shengyinbaojing();    //
        huifu();
        /******************************ȡ���ֶ����ӿ���***********************************
                if(key_mid==16&&key_down_count>30&&kc_bz==3&&chaxun_bz!=1&&gncs_set_bz==0&&set_bz==0)
                {
                    kc_bz=0;        //�ֶ�������ӷ���
        HDByteWriteI2C(0xa0,0x01,0x14,kc_bz);
                DelayMS(10);
                    write_lcd_kuang(weizhi[gongzuo[1]],0);
                    gongzuo[1]=ls_kaociduanwei;
                    write_lcd_kuang(weizhi[gongzuo[1]],1);
                    write_lcd_shuzi_yiwei(1,gongzuo[7]+1);
                }
        ******************************ȡ���ֶ����ӿ���***********************************/
        if(time_1s)
        {
            wendu_c++;
            /*
            //uchar kcshanshuobz,shanshuokc;                                        //���ڿ�����˸
            if(kcshanshuobz>0)kcshanshuobz=0;else kcshanshuobz=1;
            if(kc_bz==3)shanshuokc=gongzuo[7]+1;else shanshuokc=gongzuo[7];
            write_lcd_shuzi_yiwei(kcshanshuobz,shanshuokc);
            */
            if(gongzuo[4]==0&&time_sec==40)                     //ÿСʱ��һ��
            {





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
                DelayMS(5);
            }
            if(wendu_c==3)
            {
                /*
                if(lssound<75)
                {
                lssound++;
                sound_duanl=lssound;
                }
                else
                {
                lssound=0;
                sound_duanl=lssound;
                }
                */
//sound_duanl=60;
                get_star_temp();                //��ȡ�¶�
                if(chaxunbz==0&&gncs_set_bz==0&&chaxun_bz==0)
                {
                    write_lcd_shuzi_sanwei(1,1,WD[0]);
                    write_lcd_shuzi_sanwei(2,1,WD[1]);
                    if(WD[0]!=65534)    write_lcd_point(10,1);
                    else write_lcd_point(10,0);
                    if(WD[1]!=65534)    write_lcd_point(11,1);
                    else write_lcd_point(11,0);
                }
                else if(gncs_set_bz==0&&chaxun_bz==0)
                {
                    write_lcd_shuzi_sanwei(1,1,WD[2]);
                    write_lcd_shuzi_sanwei(2,1,WD[3]);
                    if(WD[2]!=65534)    write_lcd_point(10,1);
                    else write_lcd_point(10,0);
                    if(WD[3]!=65534)    write_lcd_point(11,1);
                    else write_lcd_point(11,0);

                }
                pianwenpanduan();               //�¶��ж�
                DS18B20_err_baocun();                       //�¶ȳ����жϼ���

                //      fengjipaishi_kongzhi();
                /*
                                for(i=0;i<4;i++)
                                {
                                    if(ls_WD[i]>WD[i])
                                    {
                                        if(ls_WD[i]-WD[i]>5)
                                        sound_read(20);
                                    }
                                    else
                                    {
                                        if(WD[i]-ls_WD[i]>5)
                                        sound_read(20);
                                    }
                                }
                */
                ls_WD[0]=WD[0];
                ls_WD[1]=WD[1];
                ls_WD[2]=WD[2];
                ls_WD[3]=WD[3];
            }
            if(gongzuo[2]==1)       //�ж��Ƿ���������
            {
//uchar kcshanshuobz,shanshuokc;
//if(kcshanshuobz>0)kcshanshuobz=0;else kcshanshuobz=1;
//if(kc_bz==3)shanshuokc=gongzuo[7]+1;else shanshuokc=gongzuo[7];
//write_lcd_shuzi_yiwei(kcshanshuobz,shanshuokc);
                if(gongzuo[4]==0&&time_sec==55&&chaxuncunchu_bz==0)     //��ʱ����Ӽ����ĸ�λ�Ƿ�Ϊ0�����Ƿ�Ϊ��һ��%15%5
                {
                    chaxun_chunchu();

                    chaxuncunchu_bz=1;
                }
                if(gongzuo[4]!=0&&chaxuncunchu_bz==1)chaxuncunchu_bz=0;//%15%5
                /*
                                if(time_sec==0)
                                {
                                    shenyinpaixu[0]=62;
                                    shenyinpaixu[1]=63;
                                    shenyinpaixu[2]=60;
                                    leijishenyinduanshu=3;
                                }
                */
                //  if((paishimenys==(paishimencanshu[4]*60))||psm_wz==0)       //��ʪ���Ƿ����������Ƿ���1���Ӽ��
                //  {
                //  paishimenys=0;
                fengjipaishi_kongzhi();
                //  }
                fengjizhuran_kongzhi();
                if(chaxun_bz==0)
                {
                    if(chaxunbz==0)
                    {
                        if(zsjs_bz!=2)
                        {
                            write_lcd_shuzi_sanwei(3,1,((yushetime[gongzuo[1]]*10)-(gongzuo[5]*60+gongzuo[6])/6));
                            write_lcd_point(12,1);
                        }
                        else    write_lcd_shuzi_sanwei(3,1,0);
                        write_lcd_shuzi_sanwei(4,1,(gongzuo[3]));
                    }
                    else
                    {
                        write_lcd_shuzi_sanwei(3,1,(ad_dlz[0]/10+1000));
                        write_lcd_point(12,1);
                        write_lcd_shuzi_sanwei(5,1,(ad_dlz[1]/10+1100));
                        write_lcd_point(13,1);
                        write_lcd_shuzi_sanwei(6,1,(ad_dlz[2]/10+1200));
                        write_lcd_point(14,1);
                    }
                }
                //write_lcd_shuzi_sanwei(7,1,dyzhi);
                //  time_dqmb=HDByteReadI2C(0xa0,0x00,(0x14+gongzuo[1]+((gongzuo[0]-10)*64)));
                time_dqmb=yushetime[gongzuo[1]];                                    //////////12.01ʵ��
                DelayMS(5);
                //  time_dqmb=time_dqmb*60;
                //      write_lcd_shuzi_sanwei(3,1,gonguo[5]);
                //      DelayMS(5);
                if(wd_yd>=650&&kc_bz==0)
                {
                    kc_js=0;
                    kc_bz=2;
                    HDByteWriteI2C(0xa0,0x01,0x14,kc_bz);
                    DelayMS(10);
                }
                if(kc_bz==2&&kc_js>=7100)//3500
                {
                    kc_bz=1;
                    HDByteWriteI2C(0xa0,0x01,0x14,kc_bz);
                    DelayMS(10);
                }
                /******************************�ֶ����ӿ���***********************************
                                if(key_mid==1&&key_down_count>30&&kc_bz==0&&chaxun_bz!=1&&gncs_set_bz==0&&set_bz==0&&set_key==0)
                                {
                                    kc_bz=3;                    //�ֶ����ӿ���
                HDByteWriteI2C(0xa0,0x01,0x14,kc_bz);
                        DelayMS(10);
                            write_lcd_kuang(weizhi[gongzuo[1]],0);
                                    ls_kaociduanwei=gongzuo[1];
                                    gongzuo[1]=0;
                                    write_lcd_kuang(weizhi[gongzuo[1]],1);
                                    write_lcd_shuzi_yiwei(1,(gongzuo[7]+2));
                                }
                ******************************�ֶ����ӿ���***********************************/
                //          if(key_mid==4&&key_down_count>30&&kc_bz==3) kc_bz=0;        //�ֶ�������ӷ���
                if((gongzuo[5]*60+gongzuo[6])>time_dqmb*60&&zsjs_bz==0)
                {
                    gongzuo[5]=time_dqmb;
                    gongzuo[6]=0;
                }
                if((((gongzuo[5]*60+gongzuo[6])==(time_dqmb*60)&&time_sec==0)||time_dqmb==0)&&zsjs_bz==0)       //�ж��Ƿ񵽵�ǰ�ν���ʱ��&&gongzuo[4]==0
                {
                    write_lcd_kuang(weizhi[gongzuo[1]],0);
                    time_sec=0;
                    gongzuo[1]++;
                    if(gongzuo[1]%2)
                    {
                        write_lcd_zi(16,1);
                        write_lcd_zi(17,0);
                    }
                    else
                    {
                        write_lcd_zi(17,1);
                        write_lcd_zi(16,0);
                    }
                    gongzuo[5]=0;
                    gongzuo[6]=0;
                    if(gongzuo[0]==10) lscdbz=gongzuo[8]+1;
                    else lscdbz=19;
                    if(gongzuo[1]<lscdbz)                           //���е��м�ν���
                    {
                        write_lcd_kuang(weizhi[gongzuo[1]],1);
                        bz=1;

                    }
                    else if(gongzuo[1]==lscdbz&&lscdbz==19)         //�����е����һ�ν���
                    {

                        gongzuo[2]=0;
                        gongzuo[1]=0;
                        write_lcd_kuang(weizhi[gongzuo[1]],1);
                        HDByteWriteI2C(0xa0,0x01,0x0a,0);
                        DelayMS(5);
                        HDByteWriteI2C(0xa0,0x01,0x09,0);
                        DelayMS(5);
                        //  PCF8574_chose(6,1);
                        LED_RUN_OFF;
//  PCF8574_chose(4,0);
                        JDQ_ZHURAN_OFF;
                        write_lcd_zi(1,0);
                        write_lcd_zi(2,0);
                        write_lcd_shuzi_yiwei(1,gongzuo[7]+1);

                    }
                    else if(gongzuo[1]==lscdbz&&lscdbz<19)
                    {
                        zsjs_bz=1;
                        gongzuo[1]--;
                        write_lcd_kuang(weizhi[gongzuo[1]],1);
                    }
                }
//write_lcd_shuzi_sanwei(4,1,hkdw+1);
                duanwei(gongzuo[1]+1);                                      //�¶ȶε��жϼ��

            }
            time_read();

            if(set_key!=3&&chaxun_bz==0)
            {
                lcd_time_write();
                if(ss_min_bz==0)ss_min_bz=1;
                else ss_min_bz=0;
                write_lcd_shuzi_erwei(44,ss_min_bz,time_tab[1]);
            }
            //      write_lcd_shuzi_sanwei(6,1,time_tab[1]);

            if(wendu_c==6)
            {
                //      sound_read_num(12.5);

//sound_send_data(sound_count);
//if(sound_count<50)sound_count++;
                wendu_c=0;
            }
            beiguang_baojing();     //���ⱨ��
            /*
            if(baojingbz[0]!=0||baojingbz[1]!=0||baojingbz[2]!=0)//
            {
                LCD_BG2_EN;
                LCD_BG_DIS;
            }
            else
            {
                LCD_BG_EN;
                LCD_BG2_DIS;
            }
            */
            time_1s=0;
        }
        if(wendu_c%2==1&&ad_ps_bz==0)
        {
            ad_zongduanDIANYAcaiyan();                          //ad����
            ad_zongduanAxiangcaiyan();
            ad_zongduanCxiangcaiyan();
            ad_zongduanBxiangcaiyan();
            ad_dianchijiance();
            if(ad_tdbz==5)
            {
                ad_tdbz=0;
//if(fengjiqishi_bz==1)
//write_lcd_shuzi_sanwei(7,1,dyzhi-12);
//else
                write_lcd_shuzi_sanwei(7,1,dyzhi);
            }
            /*
            if(ls_dlbz==1||key_mid==1)
            {
            ls_dlbz=1;
            ad_dlz[0]=ls_zddl[0]*10;
            ad_dlz[2]=ls_zddl[2]*10;
            ad_dlz[1]=ls_zddl[1]*10;
            }
            if(ls_dlbz==2||key_mid==16)
            {
            ls_dlbz=2;
            ad_dlz[0]=ls_zddl1[0]*10;
            ad_dlz[2]=ls_zddl1[2]*10;
            ad_dlz[1]=ls_zddl1[1]*10;
            }
            if(ls_dlbz==3||key_mid==5)
            {
            ls_dlbz=3;
            ad_dlz[0]=ls_zddl2[0]*10;
            ad_dlz[2]=ls_zddl2[2]*10;
            ad_dlz[1]=ls_zddl2[1]*10;
            }
            if(ls_dlbz==4||key_mid==3)
            {
            ls_dlbz=4;
            ad_dlz[0]=ls_zddl3[0]*10;
            ad_dlz[2]=ls_zddl3[2]*10;
            ad_dlz[1]=ls_zddl3[1]*10;
            }
            */
            dianyapanduan();
            if(fjqh_sign==0&&gongdian_bz==0)
            {
                if(san_dan_sign==1)fengjibaojing();
                if(san_dan_sign==0)fengjibaojing_two();
            }
        }
        chuxun_xuanze();
        ad_duzhanjiance();
        ad_ps_ds_stop();
        ad_ps_cl_stop();
/////////////////////////////////////
//  if(ss_js>0&&key_mid==0&&time_100ms==1)
        if(ss_js>0&&time_100ms==1)
        {
//LATEbits.LATE6=!LATEbits.LATE6;
            shanshuo();
//LATEbits.LATE6=!LATEbits.LATE6;
            //  ss_count++;
            time_100ms=0;
        }
        if(san_dan_sign==1)
        {
            if(fengjigaodi_100msbz==1)
            {

                fengjigaodi_100msbz=0;
                if(baojingbz[1]!=3)
                {
                    if(fengjigaodi_zdjs>5)
                    {
                        fengjigaodi_bz=1;       //Ϊ1�ǵ�ת��
                        fjsd=1;
                        //      write_lcd_zi(6,0);
                        //      write_lcd_zi(7,1);
                    }
                    else
                    {
                        fjsd=0;
                        //      write_lcd_zi(6,1);
                        //      write_lcd_zi(7,0);
                    }
                }
                else//(baojingbz[1]==3)
                {
                    fjsd=3;
                }
                fengjigaodi_zdjs=0;
                //  LATAbits.LATA3=!LATAbits.LATA3;
            }
        }
        if(san_dan_sign==0)fjsd=0;

        ClrWdt();
//  write_lcd_shuzi_sanwei(4,1,chauxnwzcs[0][2]);
//  write_lcd_shuzi_erwei(25,1,ljkc);
/////////////////////////////////////
    }
}


//end main
