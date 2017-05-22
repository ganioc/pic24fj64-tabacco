#include "p24FJ64GA006.h"

#include "Pin_Definitions.h"
#include "lcd.h"
#include "delay.h"

extern uchar sound_ds[58];
extern uchar sound_kz[23][2];
extern uchar sound_lsjs,sound_duanl;
extern uchar sound_numjs;
extern uchar sound_num,sound_numx;
extern uchar shenyinpaixu[5];			//�������������������
extern uchar leijishenyinduanshu;				//�ۼƻ��ж��ٶ�����Ҫ��
extern uchar sound_i;							//�����ۼ�
extern uchar sound_qdbz;
void __delay32(unsigned long cycles);

void sound_send_data(uchar se_data);

/*
void sound_send_data(uchar se_data)
{
	uchar temp,data_coun=8;
	uchar mask=0x01;
	SOUND_RST=0;
//	SOUND_CS=1;
	temp=0x55;
	for(;data_coun>0;data_coun--)
	{
		SOUND_DATA=0;
		if(temp&mask)
			SOUND_DATA=1;
		SOUND_RST=1;
		Delay10US(10);
		SOUND_RST=0;
		Delay10US(10);
		mask<<=1;	
	}
	temp=se_data;
	mask=0x01;
	data_coun=8;
	for(;data_coun>0;data_coun--)
	{
		SOUND_DATA=0;
		if(temp&mask)
			SOUND_DATA=1;
		SOUND_RST=1;
		Delay10US(10);
		SOUND_RST=0;
		Delay10US(10);
		mask<<=1;	
	}
//	SOUND_CS=0;
}


void sound_send_data(uchar se_data)
{
uchar i;
while(SOUND_BUSY);
	SOUND_RST=0;
//	Delay10US(10);
//__delay32(200);
		DelayMS(25);
	SOUND_RST=1;
//__delay32(200);
		DelayMS(25);
	for(i=0;i<se_data;i++)
	{
	//	Delay10US(10);

		SOUND_DATA=1;
	//	Delay10US(10);
		__delay32(200);
		SOUND_DATA=0;
		__delay32(200);
	}
	//	Delay10US(22);
//__delay32(400);
//	while(SOUND_BUSY);
}
*/

void sound_send_data(uchar se_data)
{
uchar i;
//	while(!SOUND_BUSY);
//if(SOUND_BUSY)
//{
	SOUND_RST=1;
	__delay32(400);
	SOUND_RST=0;
	__delay32(400);

		for(i=0;i<se_data;i++)
		{
			SOUND_DATA=1;
			__delay32(200);
			SOUND_DATA=0;
			__delay32(200);
		}
//}
}
/*
void sound_duan(uchar duan)
{
	if(duan<53)
	{
		sound_send_data(duan);
	}
	switch(duan)
	{
		case 53:				//���ȴ򿪼�����
		sound_send_data(15);
		sound_send_data(39);
		break;
		case 54:				//�洢�����ݴ��󣬻ָ�����ֵ
		sound_send_data(50);
		sound_send_data(27);
		sound_send_data(28);
		sound_send_data(51);
		break;
		case 55:				//���Ƶ��ͨѶʧ��
		sound_send_data(48);
		sound_send_data(34);
		break;
		case 56:				//���ȱ��
		sound_send_data(31);
		sound_send_data(32);
		break;
		case 57:				//�������
		sound_send_data(31);
		sound_send_data(33);
		break;
		case 58:				//����޵���
		sound_send_data(31);
		sound_send_data(35);
		break;
		case 59:				//��ѹƫ��
		sound_send_data(19);
		sound_send_data(18);
		break;
		case 60:				//��ѹƫ�ߣ���ر�ϵͳ��Դ
		sound_send_data(19);
		sound_send_data(17);
		sound_send_data(15);
		sound_send_data(43);
		break;
		case 61:				//����������
		sound_send_data(36);
		sound_send_data(26);
		break;
		case 62:				//�����¶�ƫ��
		sound_send_data(21);
		sound_send_data(20);
		sound_send_data(17);
		break;
		case 63:				//�����¶�ƫ��
		sound_send_data(21);
		sound_send_data(20);
		sound_send_data(18);
		break;
		case 64:				//ʪ���¶�ƫ��
		sound_send_data(22);
		sound_send_data(20);
		sound_send_data(17);
		break;
		case 65:				//ʪ���¶�ƫ��
		sound_send_data(22);
		sound_send_data(20);
		sound_send_data(18);
		break;
		case 66:				//�밲װ��������
		sound_send_data(15);
		sound_send_data(44);
		break;
		case 67:				//����ʪ�򴫸�����ˮ��
		sound_send_data(15);
		sound_send_data(45);
		break;
		case 68:				//���³�ʱ��������������
		sound_send_data(46);
		sound_send_data(27);
		break;
		case 69:				//����ͨ������ʧ��
		sound_send_data(49);
		sound_send_data(34);
		break;
		case 70:				//�������ô���
		sound_send_data(27);
		sound_send_data(16);
		sound_send_data(28);
		break;
		case 71:				//������������
		sound_send_data(16);
		sound_send_data(40);
		break;
		case 72:				//��������ʱ��
		sound_send_data(16);
		sound_send_data(41);
		break;
		case 73:				//����ȷ����������ʱ��
		sound_send_data(15);
		sound_send_data(30);
		sound_send_data(16);
		sound_send_data(47);
		break;
		case 74:				//�������óɹ�
		sound_send_data(27);
		sound_send_data(16);
		sound_send_data(29);
		break;
		case 75:				//�ָ�����ֵ�ɹ�
		sound_send_data(51);
		sound_send_data(29);
		break;
	}
}
*/
/*
void sound_number(uchar num)
{
	if(num<11)
		sound_send_data(num+1);
//	if(num==10)
//		sound_send_data(num+1);
	if(num>10&&num%10==0)
	{
		sound_send_data(num/10+1);
		sound_send_data(11);
	}
	if(num>10&&num%10!=0)
	{
		sound_send_data(num/10+1);
		sound_send_data(11);
		sound_send_data(num%10+1);
	}
}
*/
void sound_duan(void)
{
uchar ls;
if(SOUND_BUSY)
{
	if(sound_duanl<53&&sound_duanl>0)
	{
		sound_send_data(sound_duanl);
		sound_duanl=0;
	}
	if(sound_duanl>52)//&&sound_duanl<200
	{
		ls=sound_duanl-53;
//		sound_ds[sound_lsjs]
//		sound_kz[ls][]
		sound_send_data(sound_ds[sound_kz[ls][1]+sound_lsjs]);
		sound_lsjs++;
		if(sound_kz[ls][0]==sound_lsjs)
		{
			sound_duanl=0;
			sound_lsjs=0;
			if(leijishenyinduanshu!=0&&sound_qdbz==1)
			{
			//	shenyinpaixu[leijishenyinduanshu]=0;
				sound_i++;
			//	leijishenyinduanshu--;
				sound_qdbz=1;
			}
		}
	}
}
}

void sound_read(uint16 duan)
{
//	sound_lsjs=0;
	sound_duanl=duan;

	SOUND_RST=1;
	__delay32(400);
	SOUND_RST=0;
	__delay32(400);

}

void sound_read_num(float duan)
{
	uint16 lsnum;
	lsnum=(int)duan;
	sound_numjs=0;
	if(lsnum==duan)
	{
		sound_num=duan;
		sound_numx=0;
	}
	else
	{
		sound_num=lsnum;
		lsnum=((int)(duan*10))%10;
		sound_numx=lsnum;
	}
	SOUND_RST=1;
	__delay32(400);
	SOUND_RST=0;
	__delay32(400);
}

void sound_number(void)
{
//	uchar lsnum;
	if(SOUND_BUSY)
	{

		if(sound_num<11)
		{
			sound_send_data(sound_num+1);
			sound_numjs=5;
			sound_num=100;
			return;
		}
		if((sound_num>10)&&((sound_num%10)==0)&&(sound_num<100))
		{

			if(sound_numjs==0)
			{
				sound_send_data(sound_num/10+1);
				sound_numjs=1;
				return;
			}
			if(sound_numjs==1)
			{
				sound_send_data(11);
				sound_numjs=5;
				sound_num=100;
				return;
			}

		}

		if(sound_num>10&&sound_num<20&&sound_num<100)
		{

			if(sound_numjs==0)
			{
				sound_send_data(11);
				sound_numjs=1;
				return;
			}
			if(sound_numjs==1)
			{

				sound_send_data(sound_num%10+1);
				sound_numjs=5;
				sound_num=100;
				return;
			}
		}

		if(sound_num>10&&sound_num%10!=0&&sound_num<100)
		{

			if(sound_numjs==0)
			{
				sound_send_data(sound_num/10+1);
				sound_numjs=1;
				return;
			}
			if(sound_numjs==1)
			{
				sound_send_data(11);
				sound_numjs=2;
				return;
			}
			if(sound_numjs==2)
			{
				sound_send_data(sound_num%10+1);
				sound_numjs=5;
				sound_num=100;
				return;
			}
		}

		if(sound_numjs==5&&sound_numx==0) 
		{
			sound_numjs=0;
			return;
		}
		else if(sound_numjs==5&&sound_numx!=0)
		{
			sound_send_data(13);
			sound_numjs=6;
			return;
		}
		if(sound_numjs==6)
		{
			sound_send_data(sound_numx+1);
			sound_numx=0;
			sound_numjs=0;
		}

	}
}

void sound_shunxuduqu(void)
{
	if(SOUND_BUSY&&leijishenyinduanshu!=0&&sound_qdbz==1)
	{		
		sound_duanl=shenyinpaixu[leijishenyinduanshu-1];
		sound_qdbz=0;
//leijishenyinduanshu--;
	}
	else if(leijishenyinduanshu-sound_i==0&&sound_qdbz==1)
	{
		sound_qdbz=0;
		 sound_i=0;
	}
}


