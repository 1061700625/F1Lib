#include "EXTI.h"



void EXTIx::open()
{
	_EXTI_InitStructure.EXTI_Line = EXTI_Line2; //�ж��ߵı�� ȡֵ��ΧΪEXTI_Line0~EXTI_Line15
	_EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж�ģʽ����ѡֵΪ�ж� EXTI_Mode_Interrupt ���¼� EXTI_Mode_Event��
	_EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//������ʽ���������½��ش��� EXTI_Trigger_Falling�������ش��� EXTI_Trigger_Rising�����������ƽ�������غ��½��أ�����EXTI_Trigger_Rising_Falling
	_EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&_EXTI_InitStructure);//���ݽṹ����Ϣ���г�ʼ��

}

void EXTIx::close()
{

}

void EXTIx::suspend()
{
	_EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&_EXTI_InitStructure);
}

void EXTIx::resume()
{
	_EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&_EXTI_InitStructure);
}
