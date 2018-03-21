#ifndef _EXTI_H_
#define _EXTI_H_
#include "sys.h"

#include "GPIO.h"
//GPIO需要配置为输入模式
//使能AFIO时钟

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

