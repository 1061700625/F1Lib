#include "EXTI.h"



void EXTIx::open()
{
	_EXTI_InitStructure.EXTI_Line = EXTI_Line2; //中断线的标号 取值范围为EXTI_Line0~EXTI_Line15
	_EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断模式，可选值为中断 EXTI_Mode_Interrupt 和事件 EXTI_Mode_Event。
	_EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//触发方式，可以是下降沿触发 EXTI_Trigger_Falling，上升沿触发 EXTI_Trigger_Rising，或者任意电平（上升沿和下降沿）触发EXTI_Trigger_Rising_Falling
	_EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&_EXTI_InitStructure);//根据结构体信息进行初始化

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
