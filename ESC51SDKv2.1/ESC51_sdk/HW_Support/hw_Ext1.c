#include "hw_Ext1.h"

#ifdef EXT1_CONFIG





static int (*pointer_interupt_ext1)(void *arg);

static int interupt_ext1_function (void *arg) 
{
	return 0;
}

/*******************************************************************************
* �� �� ��         : Ext1Init
* ��������		   : 1��ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Ext1Init(EXT1_MODE mode, void *pfunc)
{
	EX0   = 0;//�ر��ж�����
	switch (mode)
	{
		case EXT1_MODE_LEVEL:IT0 = 0;
		                     break;
		case EXT1_MODE_FEDGE:IT0 = 1;
		                     break;
		default:return ;     break;
	}
	
	if (pfunc == NULL) {
		pointer_interupt_ext1 = interupt_ext1_function;
	} else {
		pointer_interupt_ext1 = pfunc;
	}

	EX0   = 1;//�ر��ж�����
	EA    = 1;//�����ж�
}


void Ext1Init_NoOpen(EXT1_MODE mode, void *pfunc)
{
	EX0   = 0;//�ر��ж�����
	switch (mode)
	{
		case EXT1_MODE_LEVEL:IT0 = 0;
		                     break;
		case EXT1_MODE_FEDGE:IT0 = 1;
		                     break;
		default:return ;     break;
	}
	
	if (pfunc == NULL) {
		pointer_interupt_ext1 = interupt_ext1_function;
	} else {
		pointer_interupt_ext1 = pfunc;
	}

	EX0   = 0;//�ر��ж�����
	EA    = 1;//�����ж�
}

void Ext1Open(void)
{
	EX0 = 1;
}
void Ext1Close(void)
{
	EX0 = 0;
}
void Ext1Pause(void)
{
	
}
void Ext1Start(void)
{
	
}



/*******************************************************************************
* �� �� ��         : void Ext1() interrupt 2
* ��������		   : 1�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Ext1() interrupt 2
{
	pointer_interupt_ext1(NULL);
}



#endif /* TIMER0_CONFIG */