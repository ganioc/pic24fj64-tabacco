#include "p24FJ64GA006.h"
#include "lcd.h"
#include "key.h"
#include "delay.h"
#include "Pin_Definitions.h"
#include "rtcc.h"
#include "i2c.h"
#include "PCF8574.h"
#include "wenduquxian.h"
#include "chaxun.h"

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

extern uchar time_1s,ad_1s;
extern uchar ad_tdbz;
extern uchar yushewendu[10];
extern uint16 yusheshidu[10];

extern uchar yusheshidu1[10];
extern uchar yushetime[19];
extern uint16 sd_count,wd_count,wd_yd,sd_yd,hw_time,wenduxielv,shiduxielv;
extern uchar ad_ps_bz,ad_count,ad_kgd,psm_wz;//,ps_dl
extern uchar paishimenys;
extern uchar bz;
extern uchar quxianweizhi,time_weizhi;
extern	uchar key_mid;
extern	uchar set_key;
extern uchar time_tab[8];
//extern uint16 time_zong;				//总时间
extern uchar time_sec;
//extern uchar gzzt;						//工作状态
//extern uchar hkdw;						//烘烤段位
extern uint16 hw_shijian;
//extern uint16 time_dqd;					//当前段的时间计数
extern uint16 WD[4];
extern uchar gongzuo[9];
extern uchar set_bz;
extern uchar sound_duanl;					//声音段数
extern uchar key256;
extern uchar dwxcbc;

extern uchar paishimencanshu[6];		//排湿门各项参数内容
extern uchar set_psmcs;	


extern unsigned char zishe_sector[39];
extern unsigned char xiabu_sector[39];
extern unsigned char zhongbu_sector[39];
extern unsigned char shangbu_sector[39];
extern uchar ok_bz;
extern uchar kc_bz;					//烤次增加标志
extern uint16 pianwenjishi;				//偏温报警计时延时
extern uint16 fengjigzjishi;				//风机故障恢复计时
extern uchar pianwencanshu[5];
extern uchar pianwencanshugd[5];
extern uchar set_pwcs;


extern uchar fengjibaohucanshu[4];
extern uchar fengjibaohucanshugd[4];
extern uchar set_fjbhcs;

extern uint16 dianyabaohucanshu[4];		//电压保护各项参数内容
extern uint16 dianyabaohucanshugd[4];		//电压保护各项参数内容
extern uchar set_dybhcs;								//电压参数选择
extern uchar ls_dy[6];

extern uchar guzhanghuifucanshu[2];		//故障恢复各项参数内容
extern uchar guzhanghuifucanshugd[2];		//故障恢复各项参数内容
extern uchar set_gzhfcs;								//故障恢复参数选择

extern uchar paishimencanshu[6];		//排湿门各项参数内容
extern uchar paishimencanshugd[6];		//排湿门各项参数内容
extern uchar set_psmcs;	
extern uchar zsjs_bz;
extern uchar move_sign;
extern uchar fjqh_sign;														//段位选择移动标志
//extern uchar kzbz;
extern uchar ls_jf,ls_js,ls_jfz,ls_jsz;													//临时分钟，小时计时

extern uint16 chauxnwzcs[10][3];//前一个下标代表烤次 其中两个参数前一个为首地址次一个为尾地址,最后长度
extern uchar zhuanhuanfanhui[2];				//16位转化8位返回的两个8位值
//亮点是直线方程(y-y1)/(y2-y1)=(x-x1)/(x2-x1)
//x代表温度、湿度y代表时间 时间换算成秒 温度湿度扩大10倍为了得到小数点后一位
//精确度到0.1度
extern uchar gongdian_bz;				//供电标志
extern uchar ljkc;
extern uchar fengjiqishi_bz;				//风机起始开关标志
void xielvjisuan (uchar duan)
{
//	uint16 xielv;
	if(yushewendu[duan+1]>yushewendu[duan])
		wenduxielv=(yushetime[duan*2+1]*360/(yushewendu[duan+1]-yushewendu[duan]));
	else
		wenduxielv=0;
	if(yusheshidu[duan+1]>yusheshidu[duan])
		shiduxielv=(yushetime[duan*2+1]*3600/(yusheshidu[duan+1]-yusheshidu[duan]));
	else
		shiduxielv=0;
}
//y=kx-kx1+y1,k代表斜率 是y2-y1/x2-x1的值
//x代表温度、湿度y代表时间因为 温度湿度都是扩大了10被的值所以每次增加0.1即为增加1
//所以更具公式可以得出 斜率既是 每增加0.1度所需要的时间
/*
uchar shengwenshijian(uchar duan)
{
	uchar jgtime,xl;
	xl=xielvjisuan (duan,0);
	jgtime=xl;
	return jgtime;
}
*/


uint16 shiduyingyongzhuanhuan_2to1(uchar zhi)
{
	return(zhi*10/2);
}
uchar shiduyingyongzhuanhuan_1to2(uint16 zhi)
{
	return(zhi*2/10);
}



void yudingwendu(uchar duan,uint16 xlwd)
{
//xielvjisuan (duan,0)
	if(wd_count==xlwd&&wd_yd<yushewendu[duan+1]*10&&wenduxielv!=0)
	{
		wd_count=0;
		wd_yd++;
		write_lcd_shuzi_sanwei(5,1,wd_yd);
		write_lcd_point(13,1);
//	write_lcd_point(14,0);
	}
	
}

void yudingshidu(uchar duan,uint16 xlsd)
{
//xielvjisuan (duan,1)
	if(sd_count==xlsd&&sd_yd<yusheshidu[duan+1]&&shiduxielv!=0)
	{
		sd_count=0;
		sd_yd++;
		write_lcd_shuzi_sanwei(6,1,sd_yd);
		write_lcd_point(14,1);
	}
}
//曲线跟踪每个段的控制
void duanwei(uchar wsd_duan)
{
	uchar duan;
	uchar ls_mbsj=0,ls_mbtimes=0;
//	uint16 hw_shijian=0;
	duan=wsd_duan/2;

//	if(hw_time==0&&wsd_duan%2==1&&time_sec<2)
	if(gongzuo[5]==0&&gongzuo[6]==0&&wsd_duan%2==1&&time_sec<2&&zsjs_bz!=1)
	{
	//	sd_count=0;	
		wd_yd=yushewendu[duan]*10;
		sd_yd=yusheshidu[duan];	
		hw_shijian=yushetime[wsd_duan-1]*60;
		write_lcd_shuzi_sanwei(5,1,wd_yd);
		write_lcd_point(13,1);
	//	write_lcd_shuzi_sanwei(5,1,333);
		write_lcd_shuzi_sanwei(6,1,sd_yd);
		write_lcd_point(14,1);
	//	write_lcd_shuzi_sanwei(6,1,444);
	//	write_lcd_shuzi_sanwei(4,1,hw_shijian);
	}
	
	if(bz==1)			//判断是否有段数进位
	{
		wd_count=0;
		sd_count=0;

			xielvjisuan (duan-1);
		if(wenduxielv!=0)
			wd_yd=yushewendu[duan-1]*10+1;
		else
			wd_yd=yushewendu[duan]*10;
		if(shiduxielv!=0)
			sd_yd=yusheshidu[duan-1]+1;
		else
			sd_yd=yusheshidu[duan];
		write_lcd_shuzi_sanwei(5,1,wd_yd);
		write_lcd_point(13,1);
		write_lcd_shuzi_sanwei(6,1,sd_yd);
		write_lcd_point(14,1);
		bz=0;
	}
	if(bz==2)
	{
			xielvjisuan (((gongzuo[1]+1)/2)-1);
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

		//	while(ls_mbsj>0);
				wd_count=ls_mbsj;
				wd_yd=yushewendu[(gongzuo[1]+1)/2-1]*10+ls_mbtimes;
			}
			else
			{
				wd_yd=yushewendu[(gongzuo[1]+1)/2]*10;

			}
			write_lcd_shuzi_sanwei(5,1,wd_yd);
		write_lcd_point(13,1);
		//	ls_mbsj=gongzuo[5]*60;
		//	ls_mbtimes=1;
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
		//		gongzuo[1]++;
			}
			write_lcd_shuzi_sanwei(6,1,sd_yd);
		write_lcd_point(14,1);
			ls_mbtimes=0;
		bz=0;
	}

	if(wsd_duan%2==0&&zsjs_bz!=1)
	{
//	write_lcd_shuzi_sanwei(4,1,234);
		yudingwendu(duan-1,wenduxielv);
		yudingshidu(duan-1,shiduxielv);
	}
	if(zsjs_bz==1)
	{
		if(wsd_duan%2==1)
		{
			wd_yd=yushewendu[duan]*10;
			sd_yd=yusheshidu[duan];	
		//	hw_shijian=yushetime[wsd_duan-1]*60;
			write_lcd_shuzi_sanwei(5,1,wd_yd);
			write_lcd_point(13,1);
			write_lcd_shuzi_sanwei(6,1,sd_yd);
			write_lcd_point(14,1);
		}
		if(wsd_duan%2==0)
		{
			wd_yd=yushewendu[duan+1]*10;
			sd_yd=yusheshidu[duan+1];	
		//	hw_shijian=yushetime[wsd_duan-1]*60;
			write_lcd_shuzi_sanwei(5,1,wd_yd);
			write_lcd_point(13,1);
			write_lcd_shuzi_sanwei(6,1,sd_yd);
			write_lcd_point(14,1);
			write_lcd_shuzi_sanwei(3,1,0);
			write_lcd_point(12,1);
		}
		zsjs_bz=2;
	}
}
//运行段位选择
void duanweixuanze(void)
{
	uchar weizhi[19]={3,4,7,8,11,12,15,16,19,20,23,24,27,28,31,32,35,36,39};
	uchar lsfw=0;
	uchar lskaoci_huifu[6]={0,0,0,0,0,0};
	if(gongzuo[0]==10)	lsfw=gongzuo[8];
	else lsfw=18;
	if(gongzuo[2]==0)
	{

		if(key_mid==2&&gongzuo[1]>0)
		{
move_sign=1;
			write_lcd_kuang(weizhi[gongzuo[1]],0);
		//	gongzuo[1]=HDByteReadI2C(0xa0,0x01,0x09);
			DelayMS(40);
			gongzuo[1]--;
			HDByteWriteI2C(0xa0,0x01,0x09,gongzuo[1]);
			DelayMS(400);
					if(gongzuo[1]%2)	{write_lcd_zi(16,1);	write_lcd_zi(17,0);}
					else 	{write_lcd_zi(17,1);	write_lcd_zi(16,0);}
		}
		if(key_mid==4&&gongzuo[1]<lsfw)
		{
move_sign=1;
			write_lcd_kuang(weizhi[gongzuo[1]],0);
		//	gongzuo[1]=HDByteReadI2C(0xa0,0x01,0x09);
			DelayMS(40);
			gongzuo[1]++;
			HDByteWriteI2C(0xa0,0x01,0x09,gongzuo[1]);
			DelayMS(400);
					if(gongzuo[1]%2)	{write_lcd_zi(16,1);	write_lcd_zi(17,0);}
					else 	{write_lcd_zi(17,1);	write_lcd_zi(16,0);}
		}
		write_lcd_kuang(weizhi[gongzuo[1]],1);
//			HDByteWriteI2C(0xa0,0x00,0x29,hkdw);
		if(key_mid==32&&key_down_count<5)
		{
//			HDByteWriteI2C(0xa0,0x00,0x29,hkdw);
			sound_duanl=37;
	//		pianwenjishi=0;
		pianwenjishi=0;			//偏温报警计时
		fengjigzjishi=0;		//风机故障计时
			if(gongzuo[1]%2==1&&move_sign==1)bz=1;
			if(gongzuo[1]%2==1&&move_sign!=1)bz=2;
			time_sec=0;
		//	gongzuo[4]=0;
		//	gongzuo[3]=0;
			hw_time=0;
			sd_count=0;
			if(move_sign)
			{
				gongzuo[5]=0;
				gongzuo[6]=0;
		//		gongzuo[3]=0;
		//		gongzuo[4]=0;
			}	
			else 
			{
				move_sign=0;
				gongzuo[6]=ls_jf;
				gongzuo[5]=ls_js;
			}
				gongzuo[4]=ls_jfz;
				gongzuo[3]=ls_jsz;
			gongzuo[2]=1;
		//	PCF8574_chose(6,0);
LED_RUN_ON;
if(fengjiqishi_bz==1)
{
fengjiqishi_bz=0;
fengjigzjishi=0;
}
		//	chaxun_chunchu();
					if(gongzuo[1]%2)	{write_lcd_zi(16,1);	write_lcd_zi(17,0);}
					else 	{write_lcd_zi(17,1);	write_lcd_zi(16,0);}
/*
if(gongzuo[7]<9&&((kc_bz==1&&wd_yd<420)||kc_bz==3))
	{gongzuo[7]++;kc_bz=0;
				gongzuo[5]=0;
				gongzuo[6]=0;
			gongzuo[4]=0;
			gongzuo[3]=0;}
else if((kc_bz==1&&WD[0]<420)||kc_bz==3)
	{gongzuo[7]=0;kc_bz=0;
				gongzuo[5]=0;
				gongzuo[6]=0;
			gongzuo[4]=0;
			gongzuo[3]=0;}

*/
kc_bz=HDByteReadI2C(0xa0,0x01,0x14);
		DelayMS(10);
if((kc_bz==1&&WD[0]<420)||kc_bz==3)
{
			if(gongzuo[7]<8)gongzuo[7]++;
			else gongzuo[7]=0;
			kc_bz=0;
chauxnwzcs[gongzuo[7]][1]=chauxnwzcs[gongzuo[7]][0];
chauxnwzcs[gongzuo[7]][2]=0;
HDByteWriteI2C(0xa0,0x01,0x14,kc_bz);
		DelayMS(10);
			zhuanhuan_16to8 (chauxnwzcs[gongzuo[7]][0]);
			lskaoci_huifu[0]=zhuanhuanfanhui[0];
			lskaoci_huifu[1]=zhuanhuanfanhui[1];
			zhuanhuan_16to8 (chauxnwzcs[gongzuo[7]][1]);
			lskaoci_huifu[2]=zhuanhuanfanhui[0];
			lskaoci_huifu[3]=zhuanhuanfanhui[1];
			zhuanhuan_16to8 (chauxnwzcs[gongzuo[7]][2]);
			lskaoci_huifu[4]=zhuanhuanfanhui[0];
			lskaoci_huifu[5]=zhuanhuanfanhui[1];
		HDduanWriteI2C(0xa0,0x01,(0x80+gongzuo[7]*6),lskaoci_huifu,6);
		DelayMS(20);
			gongzuo[5]=0;
			gongzuo[6]=0;
			gongzuo[4]=0;
			gongzuo[3]=0;
	//	time_sec=0;
		//	chaxun_chunchu();
}
		//	chaxun_chunchu();
write_lcd_shuzi_yiwei(1,gongzuo[7]+1);
		}
	}
}
//运行停止
void stop_run(void)
{
	if((key_mid==32&&gongzuo[2]==1&&key_down_count>30)||kc_bz==3)
	{
		zsjs_bz=0;
		gongzuo[2]=0;
	//	PCF8574_chose(6,1);
LED_RUN_OFF;
//	PCF8574_chose(4,0);
JDQ_ZHURAN_OFF;
	write_lcd_zi(1,0);
	write_lcd_zi(2,0);
		sound_duanl=38;
		write_lcd_zi(1,0);
		paishimen_kaiguan(2,5);
		write_lcd_zi(1,0);
		write_lcd_zi(2,0);
		move_sign=0;
		ls_jf=gongzuo[6];
		ls_js=gongzuo[5];
		ls_jfz=gongzuo[4];
		ls_jsz=gongzuo[3];
	}
}
//助燃排湿控制
void fengjipaishi_kongzhi(void)
{

	if(WD[1]!=65534)
	{
		if((sd_yd<WD[1]&&psm_wz==0)||(sd_yd<WD[1]&&(paishimenys==(paishimencanshu[4]*60))))		//实际采用的
		{
//		PCF8574_chose(1,1);
	paishimenys=0;
			paishimen_kaiguan(1,paishimencanshu[0]);
			write_lcd_zi(2,1);
		}
		if(sd_yd>=WD[1]&&(paishimenys==(paishimencanshu[4]*60)))

		{
	paishimenys=0;
			paishimen_kaiguan(2,paishimencanshu[1]);
			write_lcd_zi(2,0);
		}
	}
	else	write_lcd_zi(2,0);
}
void fengjizhuran_kongzhi(void)
{
	if(WD[0]!=65534)
	{
		if(wd_yd>WD[0])
		{
		//	PCF8574_chose(4,1);
JDQ_ZHURAN_ON;
				write_lcd_zi(1,1);
		//		PCF8574_chose(5,1);
		}
		else
			{
				write_lcd_zi(1,0);
			//	PCF8574_chose(4,0);	
JDQ_ZHURAN_OFF;	
	//	PCF8574_chose(5,0);
			}
		}
		else	write_lcd_zi(1,0);
}

/*
//曲线运行开始
void quxian_run_star(void)
{
	uchar hkduan=1,pdls=0,hkfs=0,time_y[19],i=0;

	hkfs=HDByteReadI2C(0xa0,0x00,0x28);
	DelayMS(5);
	hkfs=(gongzuo[0]-10)*64;
	HDSequentialReadI2C(0xa0,0x00,(0x14+hkfs),time_y,19);
	DelayMS(10);

	do
	{
		pdls=time_zong-time_y[i];
		i++;
	}
	while(pdls>=0);

		pdls=time_zong;
	while((pdls-time_y[i])>=0)
	{
		pdls=pdls-time_y[i];
		hkduan++;
		i++;
	}
		hkduan=0;
}
*/
void time_temp_choose(void)
{
uchar key_mid1;
//key_mid1=key();
	if(key_mid==4&&quxianweizhi<39)
{
if(quxianweizhi%4==1)
{
	write_lcd_shuzi_erwei(quxianweizhi,1, yushewendu[quxianweizhi/4]);
write_lcd_kuang(quxianweizhi,0);
	quxianweizhi++;
	shidukongzhi(yusheshidu[quxianweizhi/4],quxianweizhi,2);
write_lcd_kuang(quxianweizhi,2);
//	write_lcd_shuzi_erwei(quxianweizhi,2, (yusheshidu[quxianweizhi/4]/10));
}
else if(quxianweizhi%4==2)
{
	shidukongzhi(yusheshidu[quxianweizhi/4],quxianweizhi,1);
write_lcd_kuang(quxianweizhi,0);
//	write_lcd_shuzi_erwei(quxianweizhi,1, (yusheshidu[quxianweizhi/4]/10));
	quxianweizhi++;

	write_lcd_shuzi_erwei(quxianweizhi,2, yushetime[quxianweizhi/2-1]);
write_lcd_kuang(quxianweizhi,2);
sound_duanl=72;			//设置稳温时间
}
else if(quxianweizhi%4==3)
{
	write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
write_lcd_kuang(quxianweizhi,0);
	quxianweizhi++;

	write_lcd_shuzi_erwei(quxianweizhi,2, yushetime[quxianweizhi/2-1]);
	write_lcd_kuang(quxianweizhi,2);
sound_duanl=71;			//设置升温速率
	if(gongzuo[0]==10&&gongzuo[8]<18)
	{
//		++gongzuo[8];
		gongzuo[8]=(quxianweizhi+3)/2;
		write_lcd_shuzi_erwei(quxianweizhi+1,1, yushewendu[(quxianweizhi+1)/4]);
		shidukongzhi(yusheshidu[(quxianweizhi+2)/4],(quxianweizhi+2),1);
		write_lcd_shuzi_erwei((quxianweizhi+3),1, yushetime[(quxianweizhi+3)/2-1]);
	}
}
else if(quxianweizhi%4==0)
{
	write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
write_lcd_kuang(quxianweizhi,0);
	quxianweizhi++;
	write_lcd_shuzi_erwei(quxianweizhi,2, yushewendu[quxianweizhi/4]);
write_lcd_kuang(quxianweizhi,2);
}

//	LATDbits.LATD10=!LATDbits.LATD10;

	DelayMS(400);


}

if(key_mid==2&&quxianweizhi>1)
{
if(quxianweizhi%4==1)
{

	write_lcd_shuzi_erwei(quxianweizhi,1, yushewendu[quxianweizhi/4]);
write_lcd_kuang(quxianweizhi,0);
	quxianweizhi--;
	write_lcd_shuzi_erwei(quxianweizhi,2, yushetime[quxianweizhi/2-1]);
write_lcd_kuang(quxianweizhi,2);
sound_duanl=71;			//设置升温速率
}
else if(quxianweizhi%4==2)
{
	shidukongzhi(yusheshidu[quxianweizhi/4],quxianweizhi,1);
write_lcd_kuang(quxianweizhi,0);
//	write_lcd_shuzi_erwei(quxianweizhi,1, (yusheshidu[quxianweizhi/4]/10));
	quxianweizhi--;

	write_lcd_shuzi_erwei(quxianweizhi,2, yushewendu[quxianweizhi/4]);
write_lcd_kuang(quxianweizhi,2);
}
else if(quxianweizhi%4==3)
{

	write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
write_lcd_kuang(quxianweizhi,0);
	quxianweizhi--;
//	write_lcd_shuzi_erwei(quxianweizhi,2, (yusheshidu[quxianweizhi/4]/10));
	shidukongzhi(yusheshidu[quxianweizhi/4],quxianweizhi,2);
write_lcd_kuang(quxianweizhi,2);
}
else if(quxianweizhi%4==0)
{

	write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
write_lcd_kuang(quxianweizhi,0);
	quxianweizhi--;
	write_lcd_shuzi_erwei(quxianweizhi,2, yushetime[quxianweizhi/2-1]);
write_lcd_kuang(quxianweizhi,2);
sound_duanl=72;			//设置稳温时间
	if(gongzuo[0]==10&&gongzuo[8]>0)
	{
		gongzuo[8]=quxianweizhi/2-1;
		yushetime[(quxianweizhi+1)/2-1]=0;
		yushetime[(quxianweizhi+4)/2-1]=0;
		write_lcd_shuzi_erwei((quxianweizhi+1),0, yushetime[(quxianweizhi+1)/2-1]);
		write_lcd_shuzi_erwei(quxianweizhi+2,0, yushewendu[(quxianweizhi+2)/4]);
		shidukongzhi(yusheshidu[(quxianweizhi+3)/4],(quxianweizhi+3),0);
		write_lcd_shuzi_erwei((quxianweizhi+4),0, yushetime[(quxianweizhi+4)/2-1]);
	}
}

//	LATDbits.LATD11=!LATDbits.LATD11;

	DelayMS(400);

//quxianweizhi--;
}
}

void temp_time_tiaozheng(void)
{
uint16 fanweih=0,fanweil=0;
//uint16 bhzhi=0;
uchar bchang=0;
uchar weizhi_pd=0;
	if(key_mid==1&&quxianweizhi!=0)
	{
		ok_bz=0;
		if(quxianweizhi>0&&quxianweizhi<40)
		{
			if(quxianweizhi%4==1)
			{

	//			bhzhi=yushewendu[quxianweizhi/4];
				write_lcd_shuzi_erwei(quxianweizhi,1, yushewendu[quxianweizhi/4]);
				fanweih=99;

			//	fanweil=0;
				bchang=1;
				if(yushewendu[quxianweizhi/4]<99)
				yushewendu[quxianweizhi/4]++;
				write_lcd_shuzi_erwei(quxianweizhi,2, yushewendu[quxianweizhi/4]);
		//		kzbz=1;
			}
			if(quxianweizhi%4==2)
			{
		//		bhzhi=yusheshidu[quxianweizhi/4];
			//	write_lcd_shuzi_erwei(quxianweizhi,1, yusheshidu[quxianweizhi/4]/10);
	shidukongzhi(yusheshidu[quxianweizhi/4],quxianweizhi,1);
				fanweih=995;
		//		fanweil=0;
				bchang=5;
				if(yusheshidu[quxianweizhi/4]<995)
				yusheshidu[quxianweizhi/4]=yusheshidu[quxianweizhi/4]+5;
		//		write_lcd_shuzi_erwei(quxianweizhi,2, yusheshidu[quxianweizhi/4]/10);
	shidukongzhi(yusheshidu[quxianweizhi/4],quxianweizhi,2);
		//		kzbz=1;

			}
			if(quxianweizhi%4==3)
			{
//				bhzhi=yushetime[quxianweizhi/2-1];
				write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
				fanweih=99;
	//			fanweil=0;
				bchang=1;
				if(yushetime[quxianweizhi/2-1]<99)
				yushetime[quxianweizhi/2-1]++;
				write_lcd_shuzi_erwei(quxianweizhi,2, yushetime[quxianweizhi/2-1]);
		//		kzbz=1;
			}
			if(quxianweizhi%4==0)
			{
//				bhzhi=yushetime[quxianweizhi/2-1];
				write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
				fanweih=99;
		//		fanweil=0;
				bchang=1;
				if(yushetime[quxianweizhi/2-1]<99)
				yushetime[quxianweizhi/2-1]++;
				write_lcd_shuzi_erwei(quxianweizhi,2, yushetime[quxianweizhi/2-1]);
		//		kzbz=1;
			}
		}
	DelayMS(400);
	}
	if(key_mid==16&&quxianweizhi!=0)
	{
		ok_bz=0;
		if(quxianweizhi>0&&quxianweizhi<40)
		{
			if(quxianweizhi%4==1)
			{

	//			bhzhi=yushewendu[quxianweizhi/4];
				write_lcd_shuzi_erwei(quxianweizhi,1, yushewendu[quxianweizhi/4]);
				fanweih=99;

			//	fanweil=0;
				bchang=1;
				if(yushewendu[quxianweizhi/4]>0)
				yushewendu[quxianweizhi/4]--;
				write_lcd_shuzi_erwei(quxianweizhi,2, yushewendu[quxianweizhi/4]);
		//		kzbz=1;
			}
			if(quxianweizhi%4==2)
			{
		//		bhzhi=yusheshidu[quxianweizhi/4];
		//		write_lcd_shuzi_erwei(quxianweizhi,1, yusheshidu[quxianweizhi/4]/10);
	shidukongzhi(yusheshidu[quxianweizhi/4],quxianweizhi,1);
				fanweih=995;
		//		fanweil=0;
				bchang=5;
				if(yusheshidu[quxianweizhi/4]>0)
				yusheshidu[quxianweizhi/4]=yusheshidu[quxianweizhi/4]-5;
		//		write_lcd_shuzi_erwei(quxianweizhi,2, yusheshidu[quxianweizhi/4]/10);
	shidukongzhi(yusheshidu[quxianweizhi/4],quxianweizhi,2);
		//		kzbz=1;

			}
			if(quxianweizhi%4==3)
			{
//				bhzhi=yushetime[quxianweizhi/2-1];
				write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
				fanweih=99;
	//			fanweil=0;
				bchang=1;
			//	if(yushetime[quxianweizhi/2-1]>0)

		if(quxianweizhi/2-1==gongzuo[1])weizhi_pd=(gongzuo[5]+1);
		else weizhi_pd=0;
		if(gongzuo[2]==0) weizhi_pd=0;
				if(yushetime[quxianweizhi/2-1]>weizhi_pd)
				yushetime[quxianweizhi/2-1]--;
				write_lcd_shuzi_erwei(quxianweizhi,2, yushetime[quxianweizhi/2-1]);
		//		kzbz=1;
			}
			if(quxianweizhi%4==0)
			{
//				bhzhi=yushetime[quxianweizhi/2-1];
				write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
				fanweih=99;
		//		fanweil=0;
				bchang=1;
			//	if(yushetime[quxianweizhi/2-1]>0)
		if(quxianweizhi/2-1==gongzuo[1])weizhi_pd=(gongzuo[5]+1);
		else weizhi_pd=0;
		if(gongzuo[2]==0) weizhi_pd=0;
				if(yushetime[quxianweizhi/2-1]>weizhi_pd)
				yushetime[quxianweizhi/2-1]--;
				write_lcd_shuzi_erwei(quxianweizhi,2, yushetime[quxianweizhi/2-1]);
		//		kzbz=1;
			}
		}
	DelayMS(400);
	}
}
void set_all(void)
{
	uchar i;
	uchar zb[5]={6,5,4,2,1};
	uchar weizhi[19]={3,4,7,8,11,12,15,16,19,20,23,24,27,28,31,32,35,36,39};
	if(set_key!=0)
	{
		if(set_bz==1) {write_lcd_kuang(weizhi[gongzuo[1]],0);set_bz=0;}
		if(key_up_count>200)
		{

			PCF8574_chose(5,1);
LED_SET_OFF;
			if(set_key==1)
			{
				if(quxianweizhi!=0)
				{


					if(quxianweizhi%4==0)
					{
						write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
						write_lcd_kuang(quxianweizhi,0);
					}
					if(quxianweizhi%4==1)
					{
						write_lcd_shuzi_erwei(quxianweizhi,1, yushewendu[quxianweizhi/4]);
						write_lcd_kuang(quxianweizhi,0);
					}
					if(quxianweizhi%4==2)
					{
						shidukongzhi(yusheshidu[quxianweizhi/4],quxianweizhi,1);
						write_lcd_kuang(quxianweizhi,0);
					}
					if(quxianweizhi%4==3)
					{
						write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
						write_lcd_kuang(quxianweizhi,0);
					}
					quxianweizhi=0;

				}
				set_key=0;
			}

			if(set_key==2)
			{
				write_lcd_zi(gongzuo[0],0);
				write_lcd_kuang(gongzuo[0]+30,0);
				set_key=0;
			}

			gongzuo[0]=HDByteReadI2C(0xa0,0x01,0x08);//读取所选烘烤方式的当前方式
			DelayMS(5);
/*
			HDSequentialReadI2C(0xa0,0x00,(0x00+lsi2c),yushewendu,10);
			DelayMS(10);
			HDSequentialReadI2C(0xa0,0x00,(0x0a+lsi2c),yusheshidu1,10);
			DelayMS(10);
			HDSequentialReadI2C(0xa0,0x00,(0x14+lsi2c),yushetime,19);
			DelayMS(10);
			for(i=0;i<10;i++)
			{
				yusheshidu[i]=shiduyingyongzhuanhuan_2to1(yusheshidu1[i]);
			}

	//		for(i=0;i<10;i++)
	//		{
	//			write_lcd_shuzi_erwei((i*4+1),1,yushewendu[i]);
	//			write_lcd_shuzi_erwei((i*4+2),1,yusheshidu[i]/10);
	//			if(yusheshidu[i]%10==5)	write_lcd_point(i+1,1);
	//			else write_lcd_point(i+1,0);
	//			write_lcd_shuzi_erwei((i*4+3),1,yushetime[i*2]);
	//			write_lcd_shuzi_erwei((i*4+4),1,yushetime[i*2+1]);
	//		}

	if(gongzuo[0]!=11)
	{
		for(i=0;i<10;i++)
		{
			write_lcd_shuzi_erwei((i*4+1),1,yushewendu[i]);
			write_lcd_shuzi_erwei((i*4+2),1,yusheshidu[i]/10);
			if(yusheshidu[i]%10==5)	write_lcd_point(i+1,1);
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
			if(yusheshidu[i]%10==5)	write_lcd_point(i+1,1);
			else write_lcd_point(i+1,0);
			write_lcd_shuzi_erwei((i*4+3),1,yushetime[i*2]);
			if(i*4+4!=40&&i>0)
			write_lcd_shuzi_erwei(((i-1)*4+4),1,yushetime[(i-1)*2+1]);
		}	
	}
*/
lcd_xiepingmu(1);
				write_lcd_zi(gongzuo[0],1);
				write_lcd_kuang(gongzuo[0]+30,1);
			if(set_key==3)
			{
				write_lcd_shuzi_erwei(time_weizhi,1,time_tab[zb[time_weizhi-40]]);
		//		set_key=0;
			}
			set_key=0;
write_lcd_kuang(weizhi[gongzuo[1]],1);
		}

		if(key_mid==64)			//以下为确认保存
		{
			DelayMS(400);
			if(ok_bz==1)
			{
			//	PCF8574_chose(5,1);
LED_SET_OFF;
			if(quxianweizhi!=0)
			{
				
				if(quxianweizhi%4==0)
				{
					write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
					write_lcd_kuang(quxianweizhi,0);
				}
				if(quxianweizhi%4==1)
				{
					write_lcd_shuzi_erwei(quxianweizhi,1, yushewendu[quxianweizhi/4]);
					write_lcd_kuang(quxianweizhi,0);
				}
				if(quxianweizhi%4==2)
				{
					shidukongzhi(yusheshidu[quxianweizhi/4],quxianweizhi,1);
					write_lcd_kuang(quxianweizhi,0);
				}
				if(quxianweizhi%4==3)
				{
					write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
					write_lcd_kuang(quxianweizhi,0);
				}
				quxianweizhi=0;
			}

			write_lcd_zi(gongzuo[0],1);
			write_lcd_kuang(gongzuo[0]+30,1);
			gongzuo[1]=dwxcbc;
			write_lcd_kuang(weizhi[gongzuo[1]],1);
			danqianduan_tiaozhenpd();
				set_key=0;
			}
			lcd_xiepingmu(0);
			if(ok_bz==0)
			{
				if(gongzuo[0]==10)					//判断自设曲线舍去和保留的段数
				{
					for(i=19;i>0;--i)
					{
						if(yushetime[i-1]>0)
						{
							if(i%2==1)
							{
								gongzuo[8]=i-1;
					//			break;
							}
							else
							{
								gongzuo[8]=i;
					//			break;
							}
							HDByteWriteI2C(0xa0,0x01,0x10,gongzuo[8]);
							break;
						}
					}
				}

				ok_bz=1;
			}
		}

	//	set_key=0;
	}

	switch (set_key)
	{
		case 1:
	time_weizhi=0;
			if(quxianweizhi==0)
			{
				if(gongzuo[1]%2==0)
				quxianweizhi=(gongzuo[1]+1)*2+1;
				else 	quxianweizhi=(gongzuo[1]+1)*2;
			//	write_lcd_shuzi_erwei(quxianweizhi,2, yushewendu[quxianweizhi/4]);
				write_lcd_shuzi_erwei(quxianweizhi,2, yushetime[quxianweizhi/2-1]);
				write_lcd_kuang(quxianweizhi,2);
			}
			time_temp_choose();
			temp_time_tiaozheng();
		break;
		case 2:
	time_weizhi=0;
		if(quxianweizhi!=0)
		{
			if(quxianweizhi%4==0)
			{
				write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
				write_lcd_kuang(quxianweizhi,0);
			}
			if(quxianweizhi%4==1)
			{
				write_lcd_shuzi_erwei(quxianweizhi,1, yushewendu[quxianweizhi/4]);
				write_lcd_kuang(quxianweizhi,0);
			}
			if(quxianweizhi%4==2)
			{
				shidukongzhi(yusheshidu[quxianweizhi/4],quxianweizhi,1);
				write_lcd_kuang(quxianweizhi,0);
			}
			if(quxianweizhi%4==3)
			{
				write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
				write_lcd_kuang(quxianweizhi,0);
			}
			quxianweizhi=0;
			write_lcd_zi(gongzuo[0],2);
			write_lcd_kuang(gongzuo[0]+30,2);
		}
		if(key_mid==1)
		{
			DelayMS(400);
			ok_bz=0;
			if(gongzuo[0]<13)
			{
				write_lcd_zi(gongzuo[0],0);
				write_lcd_kuang(gongzuo[0]+30,0);
				gongzuo[0]++;
				write_lcd_zi(gongzuo[0],2);
				write_lcd_kuang(gongzuo[0]+30,2);
/*
				//	gongzuo[0]=HDByteReadI2C(0xa0,0x00,0x28);
					DelayMS(5);
					lsi2c=(gongzuo[0]-10)*64;
					HDSequentialReadI2C(0xa0,0x00,(0x00+lsi2c),yushewendu,10);
					DelayMS(10);
					HDSequentialReadI2C(0xa0,0x00,(0x0a+lsi2c),yusheshidu1,10);
					DelayMS(10);
					HDSequentialReadI2C(0xa0,0x00,(0x14+lsi2c),yushetime,19);
					DelayMS(10);
					for(i=0;i<10;i++)
					{
						yusheshidu[i]=shiduyingyongzhuanhuan_2to1(yusheshidu1[i]);
					}
	for(i=0;i<10;i++)
	{
		write_lcd_shuzi_erwei((i*4+1),1,yushewendu[i]);
		write_lcd_shuzi_erwei((i*4+2),1,yusheshidu[i]/10);
		if(yusheshidu[i]%10==5)	write_lcd_point(i+1,1);
		else write_lcd_point(i+1,0);
		write_lcd_shuzi_erwei((i*4+3),1,yushetime[i*2]);
		write_lcd_shuzi_erwei((i*4+4),1,yushetime[i*2+1]);
	}
*/
lcd_xiepingmu(1);
			}
			else
			{
				write_lcd_zi(gongzuo[0],0);
				write_lcd_kuang(gongzuo[0]+30,0);
				gongzuo[0]=10;
				write_lcd_zi(gongzuo[0],2);
				write_lcd_kuang(gongzuo[0]+30,2);
/*
			//		gongzuo[0]=HDByteReadI2C(0xa0,0x00,0x28);
					DelayMS(5);
					lsi2c=(gongzuo[0]-10)*64;
					HDSequentialReadI2C(0xa0,0x00,(0x00+lsi2c),yushewendu,10);
					DelayMS(10);
					HDSequentialReadI2C(0xa0,0x00,(0x0a+lsi2c),yusheshidu1,10);
					DelayMS(10);
					HDSequentialReadI2C(0xa0,0x00,(0x14+lsi2c),yushetime,19);
					DelayMS(10);
					for(i=0;i<10;i++)
					{
						yusheshidu[i]=shiduyingyongzhuanhuan_2to1(yusheshidu1[i]);
					}
	for(i=0;i<10;i++)
	{
		write_lcd_shuzi_erwei((i*4+1),1,yushewendu[i]);
		write_lcd_shuzi_erwei((i*4+2),1,yusheshidu[i]/10);
		if(yusheshidu[i]%10==5)	write_lcd_point(i+1,1);
		else write_lcd_point(i+1,0);
		write_lcd_shuzi_erwei((i*4+3),1,yushetime[i*2]);
		write_lcd_shuzi_erwei((i*4+4),1,yushetime[i*2+1]);
	}
*/
lcd_xiepingmu(1);
			}
		}
		if(key_mid==16)
		{
			ok_bz=0;
			DelayMS(400);
			if(gongzuo[0]>10)
			{
				write_lcd_zi(gongzuo[0],0);
				write_lcd_kuang(gongzuo[0]+30,0);
				gongzuo[0]--;
				write_lcd_zi(gongzuo[0],2);
				write_lcd_kuang(gongzuo[0]+30,2);
/*
			//		gongzuo[0]=HDByteReadI2C(0xa0,0x00,0x28);
					DelayMS(5);
					lsi2c=(gongzuo[0]-10)*64;
					HDSequentialReadI2C(0xa0,0x00,(0x00+lsi2c),yushewendu,10);
					DelayMS(10);
					HDSequentialReadI2C(0xa0,0x00,(0x0a+lsi2c),yusheshidu1,10);
					DelayMS(10);
					HDSequentialReadI2C(0xa0,0x00,(0x14+lsi2c),yushetime,19);
					DelayMS(10);
					for(i=0;i<10;i++)
					{
						yusheshidu[i]=shiduyingyongzhuanhuan_2to1(yusheshidu1[i]);
					}
	for(i=0;i<10;i++)
	{
		write_lcd_shuzi_erwei((i*4+1),1,yushewendu[i]);
		write_lcd_shuzi_erwei((i*4+2),1,yusheshidu[i]/10);
		if(yusheshidu[i]%10==5)	write_lcd_point(i+1,1);
		else write_lcd_point(i+1,0);
		write_lcd_shuzi_erwei((i*4+3),1,yushetime[i*2]);
		write_lcd_shuzi_erwei((i*4+4),1,yushetime[i*2+1]);
	}
*/
lcd_xiepingmu(1);
			}
			else
			{
				write_lcd_zi(gongzuo[0],0);
				write_lcd_kuang(gongzuo[0]+30,0);
				gongzuo[0]=13;
				write_lcd_zi(gongzuo[0],2);
				write_lcd_kuang(gongzuo[0]+30,2);
/*
			//		gongzuo[0]=HDByteReadI2C(0xa0,0x00,0x28);
					DelayMS(5);
					lsi2c=(gongzuo[0]-10)*64;
					HDSequentialReadI2C(0xa0,0x00,(0x00+lsi2c),yushewendu,10);
					DelayMS(10);
					HDSequentialReadI2C(0xa0,0x00,(0x0a+lsi2c),yusheshidu1,10);
					DelayMS(10);
					HDSequentialReadI2C(0xa0,0x00,(0x14+lsi2c),yushetime,19);
					DelayMS(10);
					for(i=0;i<10;i++)
					{
						yusheshidu[i]=shiduyingyongzhuanhuan_2to1(yusheshidu1[i]);
					}
	for(i=0;i<10;i++)
	{
		write_lcd_shuzi_erwei((i*4+1),1,yushewendu[i]);
		write_lcd_shuzi_erwei((i*4+2),1,yusheshidu[i]/10);
		if(yusheshidu[i]%10==5)	write_lcd_point(i+1,1);
		else write_lcd_point(i+1,0);
		write_lcd_shuzi_erwei((i*4+3),1,yushetime[i*2]);
		write_lcd_shuzi_erwei((i*4+4),1,yushetime[i*2+1]);
	}
*/
lcd_xiepingmu(1);
			}
		}
		break;
		case 3:


		if(quxianweizhi!=0)
		{
			if(quxianweizhi%4==0)
			{
				write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
				write_lcd_kuang(quxianweizhi,0);
			}
			if(quxianweizhi%4==1)
			{
				write_lcd_shuzi_erwei(quxianweizhi,1, yushewendu[quxianweizhi/4]);
				write_lcd_kuang(quxianweizhi,0);
			}
			if(quxianweizhi%4==2)
			{
				shidukongzhi(yusheshidu[quxianweizhi/4],quxianweizhi,1);
				write_lcd_kuang(quxianweizhi,0);
			}
			if(quxianweizhi%4==3)
			{
				write_lcd_shuzi_erwei(quxianweizhi,1, yushetime[quxianweizhi/2-1]);
				write_lcd_kuang(quxianweizhi,0);
			}
			quxianweizhi=0;
			write_lcd_zi(gongzuo[0],2);
			write_lcd_kuang(gongzuo[0]+30,2);
		}


			if(time_weizhi==0)
			{
				write_lcd_zi(gongzuo[0],1);
				write_lcd_kuang(gongzuo[0]+30,1);
time_weizhi=40;
				write_lcd_shuzi_erwei(time_weizhi,2,time_tab[6]);
			}
			set_time();
		break;
	//	case 0:
	//		time_weizhi=0;
	//	break;
	}
	
}

void huifuchuchangzhi(void)											//回复出厂值
{
uchar i;
	if(key_mid==10&&key_down_count>30)
	{

		gongzuo[0]=11;
		for(i=1;i<9;i++)
		{
			gongzuo[i]=0;
		}
	//	HDByteWriteI2C(0xa0,0x00,0xff,0x55);
	//	DelayMS(5);
		HDduanWriteI2C(0xa0,0x00,0x00,zishe_sector,39);
		DelayMS(10);
		HDduanWriteI2C(0xa0,0x00,0x40,xiabu_sector,39);
		DelayMS(10);
		HDduanWriteI2C(0xa0,0x00,0x80,zhongbu_sector,39);
		DelayMS(10);
		HDduanWriteI2C(0xa0,0x00,0xc0,shangbu_sector,39);
		DelayMS(10);
		HDduanWriteI2C(0xa0,0x01,0x08,gongzuo,9);				//记录为哪种烘烤模式1：自设2；下部3：中部4：上部;记录当前烘烤所在段位
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
HDByteWriteI2C(0xa0,0x01,0x13,0);
		DelayMS(10);
HDByteWriteI2C(0xa0,0x01,0x14,0);
		DelayMS(10);
		HDSequentialReadI2C(0xa0,0x01,0x00,time_tab,8);		//0x00,0x75
		DelayMS(10);
		time_write(time_tab);
		HDSequentialReadI2C(0xa0,0x01,0x08,gongzuo,9);		//0x00,0x28  
		DelayMS(10);

		HDSequentialReadI2C(0xa0,0x01,0x40,pianwencanshu,5);
		DelayMS(10);
		HDSequentialReadI2C(0xa0,0x01,0x45,fengjibaohucanshu,4);
		DelayMS(10);
		HDSequentialReadI2C(0xa0,0x01,0x49,ls_dy,6);
		dianyan_zhuanhuan_i2ctomain();
		DelayMS(10);
		HDSequentialReadI2C(0xa0,0x01,0x4f,guzhanghuifucanshu,2);
		DelayMS(10);
		HDSequentialReadI2C(0xa0,0x01,0x51,paishimencanshu,6);
		DelayMS(10);
fjqh_sign=HDByteReadI2C(0xa0,0x01,0x13);
		DelayMS(10);
		time_write(time_tab);
	write_lcd_zi(9,1);
	write_lcd_zi(3,1);
//	PCF8574_chose(6,1);
LED_RUN_OFF;
//	PCF8574_chose(5,1);
LED_SET_OFF;
	DelayMS(400);
	write_lcd_point(10,0);
	write_lcd_point(11,0);
	write_lcd_point(13,0);
	write_lcd_point(14,0);
write_lcd_shuzi_sanwei(3,1,((yushetime[gongzuo[1]]*10)-(gongzuo[5]*60+gongzuo[6])/6));
write_lcd_shuzi_sanwei(4,1,gongzuo[3]);
write_lcd_shuzi_sanwei(5,1,0);
write_lcd_shuzi_sanwei(6,1,0);
//	write_lcd_shuzi_erwei(5,1,148);
//	write_lcd_shuzi_sanwei(3,1,1576);
//write_lcd_kuang(gongzuo[1],1);
lcd_xiepingmu(1);
			write_lcd_zi(8,1);
//	DelayMS(3000);
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
	//	write_lcd_zi(14,1);
//write_lcd_kuang(44,1);
//write_lcd_zi(gongzuo[0],1);
write_lcd_kuang(gongzuo[0]+30,1);
write_lcd_shuzi_yiwei(1,gongzuo[7]+1);
__asm__ volatile ("RESET");
	}
}

void danqianduan_tiaozhenpd(void)
{
	uchar ls_mbsj=0,ls_mbtimes=0;
		if((gongzuo[1]+1)%2==0)
		{
			if(((gongzuo[5]*60+gongzuo[6]))>yushetime[gongzuo[1]]*60)
			{
		//		++gongzuo[1];
				wd_yd=yushewendu[(gongzuo[1]+2)/2]*10;
				sd_yd=yusheshidu[(gongzuo[1]+2)/2];
				jinduanchushitiaozheng();
			}
			else
			{
				xielvjisuan (((gongzuo[1]+1)/2)-1);
				if(wenduxielv!=0)
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
	
			//	while(ls_mbsj>0);
					wd_count=ls_mbsj;
					wd_yd=yushewendu[(gongzuo[1]+1)/2-1]*10+ls_mbtimes;
				}
				else
				{
					wd_yd=yushewendu[(gongzuo[1]+1)/2]*10;
	
				}

		//	ls_mbsj=gongzuo[5]*60;
		//	ls_mbtimes=1;
				if(shiduxielv!=0)
				{
					ls_mbsj=((gongzuo[5]*60+gongzuo[6])*60)%shiduxielv;
					ls_mbtimes=((gongzuo[5]*60)+gongzuo[6])*60/shiduxielv+1;
					sd_count=ls_mbsj;
					sd_yd=yusheshidu[(gongzuo[1]+1)/2-1]+ls_mbtimes;
				}
				else
				{	

					sd_yd=yusheshidu[(gongzuo[1]+1)/2];	
				}
			}
			write_lcd_shuzi_sanwei(5,1,wd_yd);
			write_lcd_point(13,1);
			write_lcd_shuzi_sanwei(6,1,sd_yd);
			write_lcd_point(14,1);
			ls_mbtimes=0;

//write_lcd_shuzi_sanwei(3,1,(gongzuo[5]));
//write_lcd_shuzi_sanwei(4,1,shiduxielv);
		}
		else
		{
			if(((gongzuo[5]*60+gongzuo[6]))>yushetime[gongzuo[1]]*60)
			{
		//		gongzuo[1]++;
				jinduanchushitiaozheng();
			}
			wd_yd=yushewendu[(gongzuo[1]+1)/2]*10;
			sd_yd=yusheshidu[(gongzuo[1]+1)/2];	
		//	hw_shijian=yushetime[gongzuo[1]-1]*60;
			write_lcd_shuzi_sanwei(5,1,wd_yd);
			write_lcd_point(13,1);
			write_lcd_shuzi_sanwei(6,1,sd_yd);
			write_lcd_point(14,1);

		}
}

void jinduanchushitiaozheng(void)
{
	uchar weizhi[19]={3,4,7,8,11,12,15,16,19,20,23,24,27,28,31,32,35,36,39};
	uchar lscdbz=0;
	write_lcd_kuang(weizhi[gongzuo[1]],0);
	time_sec=0;
	gongzuo[1]++;
	gongzuo[5]=0;
	gongzuo[6]=0;
	if(gongzuo[0]==10) {lscdbz=HDByteReadI2C(0xa0,0x01,0x10)+1;	DelayMS(5);}//gongzuo[8]+1;HDByteWriteI2C(0xa0,0x01,0x10,gongzuo[8]);

	else lscdbz=19;
//	write_lcd_shuzi_sanwei(4,1,lscdbz);
//		DelayMS(5000);
	if(gongzuo[1]<lscdbz)
	{
		write_lcd_kuang(weizhi[gongzuo[1]],1);
		if(gongzuo[1]%2==1)	bz=1;

	}
	else
	{
		gongzuo[2]=0;
		gongzuo[1]=0;
		write_lcd_kuang(weizhi[gongzuo[1]],1);
		HDByteWriteI2C(0xa0,0x01,0x0a,0);
		DelayMS(5);
		HDByteWriteI2C(0xa0,0x01,0x09,0);
		DelayMS(5);
	//	PCF8574_chose(6,1);
LED_RUN_OFF;
		write_lcd_shuzi_yiwei(1,gongzuo[7]+1);
	}
}

void close_system(void)
{
uchar yucunls[19],i,wendu_c1=0;
	if(gongdian_bz==2)
	{
		write_all_lcd(0);
		LED_SET_OFF;
		LED_RUN_OFF;
		for(i=0;i<8;i++)
		{
			yucunls[i]=time_tab[i];
		}
		for(i=8;i<17;i++)
		{
			yucunls[i]=gongzuo[i-8];
		}
			yucunls[17]=psm_wz;
			yucunls[18]=ljkc;
			HDduanWriteI2C(0xa0,0x01,0x00,yucunls,19);
		while(gongdian_bz==2)
		{
			if(time_1s==1)wendu_c1++;
			if(wendu_c1%2==1)//&&ad_ps_bz==0
			{
				ad_zongduanDIANYAcaiyan();							//ad采样
				ad_zongduanAxiangcaiyan();
				ad_zongduanCxiangcaiyan();
				ad_zongduanBxiangcaiyan();
				ad_dianchijiance();
				if(ad_tdbz==5)
				{
					ad_tdbz=0;
			//		write_lcd_shuzi_sanwei(7,1,dyzhi);
				}
				ClrWdt();
			}
			if(wendu_c1==6)
			{
				wendu_c1=0;
			}
			time_1s=0;
		}
		__asm__ volatile ("RESET");
	}
}
