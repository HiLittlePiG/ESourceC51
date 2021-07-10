#include "hw_Timer0.h"

#ifdef TIMER0_CONFIG


static u8 timer_h;
static u8 timer_l;

static u8 timer_mode;



static int (*pointer_interupt_timer0)(void *arg);

static int interupt_timer_function (void *arg) 
{
	return 0;
}

/*******************************************************************************
* �� �� ��         : Timer0Init
* ��������		   : ��ʱ��0��ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Timer0Init(TIMER0_MODE mode, uint16_t us, void *callback)
{
	timer_mode = mode;
	switch (mode)
	{
		case TIMER0_MODE_0:TMOD   |= 0X00;
		                   timer_h = (8192-us) / 8;
		                   timer_l = (8192-us) % 8;
		                   break;
		case TIMER0_MODE_1:TMOD   |= 0X01;
		                   timer_h = (65536-us) / 256;
		                   timer_l = (65536-us) % 256;
		                   break;
		case TIMER0_MODE_2:TMOD   |= 0X02;
		                   timer_h = (256-us) % 256;
		                   timer_l = timer_h;
		                   break;
		case TIMER0_MODE_3:TMOD   |= 0X03;
		                   timer_h = (8192-us) / 8;
		                   timer_l = (8192-us) % 8;
		                   break;
		default:return ;   break;
	}
	
	if (callback == NULL) {
		pointer_interupt_timer0 = interupt_timer_function;
	} else {
		pointer_interupt_timer0 = callback;
	}
	
	TH0   = timer_h;	//����ʱ������ֵ����ʱ1ms
	TL0   = timer_l;	
	ET0   = 1;//�򿪶�ʱ��0�ж�����
	EA    = 1;//�����ж�
	TR0   = 1;//�򿪶�ʱ��
}

void Timer0Init_NoOpen(TIMER0_MODE mode, uint16_t us, void *callback)
{
	timer_mode = mode;
	TR0   = 0;//�رն�ʱ��
	ET0   = 0;//�رն�ʱ��0�ж�����
	switch (mode)
	{
		case TIMER0_MODE_0:TMOD   |= 0X00;
		                   timer_h = (8192-us) / 8;
		                   timer_l = (8192-us) % 8;
		                   break;
		case TIMER0_MODE_1:TMOD   |= 0X01;
		                   timer_h = (65536-us) / 256;
		                   timer_l = (65536-us) % 256;
		                   break;
		case TIMER0_MODE_2:TMOD   |= 0X02;
		                   timer_h = (256-us) % 256;
		                   timer_l = timer_h;
		                   break;
		case TIMER0_MODE_3:TMOD   |= 0X03;
		                   timer_h = (8192-us) / 8;
		                   timer_l = (8192-us) % 8;
		                   break;
		default:return ;   break;
	}
	
	if (callback == NULL) {
		pointer_interupt_timer0 = interupt_timer_function;
	} else {
		pointer_interupt_timer0 = callback;
	}
	
	TH0   = timer_h;	//����ʱ������ֵ����ʱ1ms
	TL0   = timer_l;	
	ET0   = 0;//�رն�ʱ��0�ж�����
	EA    = 1;//�����ж�
	TR0   = 0;//�򿪶�ʱ��
}

void Timer0Settime(uint16_t us)
{
	TR0 = 0;
	switch (timer_mode)
	{
		case TIMER0_MODE_0:TMOD   |= 0X00;
		                   timer_h = (8192-us) / 8;
		                   timer_l = (8192-us) % 8;
		                   break;
		case TIMER0_MODE_1:TMOD   |= 0X01;
		                   timer_h = (65536-us) / 256;
		                   timer_l = (65536-us) % 256;
		                   break;
		case TIMER0_MODE_2:TMOD   |= 0X02;
		                   timer_h = (256-us) % 256;
		                   timer_l = timer_h;
		                   break;
		case TIMER0_MODE_3:TMOD   |= 0X03;
		                   timer_h = (8192-us) / 8;
		                   timer_l = (8192-us) % 8;
		                   break;
		default:return ;   break;
	}
	TR0 = 1;
}

void Timer0Open(void)
{
	ET0   = 1;//�򿪶�ʱ��0�ж�����
	TR0   = 1;//�򿪶�ʱ��
}

void Timer0Close(void)
{
	TR0   = 0;//�رն�ʱ��
	ET0   = 0;//�رն�ʱ��0�ж�����
	TH0   = timer_h;	//����ʱ������ֵ����ʱ1ms
	TL0   = timer_l;	
}



/*******************************************************************************
* �� �� ��         : void Timer0() interrupt 1
* ��������		   : ��ʱ��0�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Timer0() interrupt 1
{
	if (timer_mode != TIMER0_MODE_2) {
		TH0 = timer_h;	//����ʱ������ֵ
		TL0 = timer_l;
	}
	pointer_interupt_timer0(NULL);
}



#endif /* TIMER0_CONFIG */