#ifndef _EXTI_H_
#define _EXTI_H_
#include "sys.h"

#include "GPIO.h"
//GPIO��Ҫ����Ϊ����ģʽ
//ʹ��AFIOʱ��

class EXTIx
{
public:
	EXTIx(GPIO io){}

	void open();
	void close();
	void suspend();
	void resume();

private:

	EXTI_InitTypeDef _EXTI_InitStructure;

};

#endif

