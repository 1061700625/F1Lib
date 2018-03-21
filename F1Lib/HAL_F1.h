#ifndef	_HAL_F4_H_
#define _HAL_F4_H_

#include "sys.h"
#include "HAL.h"			//³éÏó½Ó¿Ú


#include "RCCX.h"
#include "GPIO.h"			
#include "USART.h"
#include "TIMER.h"
#include "SPIDriver.h"

#include "ADC.h"
#include "PWM.h"

#include "StmFlash.h"

#include "Parameter.h"
#include "Scheduler.h"





class HAL_F1:public HAL
{
public:
	HAL_F1();


	virtual void Setup();
		
		
	
		
	USART& console;
	USART usart1;
	USART usart2;
	USART usart3;
	USART uart4;
	USART uart5;


	SPIDriver spi1;
	SPIDriver spi2;
	SPIDriver spi3;


	TIMER tim1;
	TIMER tim8;
	
	TIMER tim2;
	TIMER tim3;
	TIMER tim4;
	TIMER tim5;
	TIMER tim6;
	TIMER tim7;

	BasicPWM pwm1;

	Scheduler scheduler;

		
	
};

extern HAL_F1 hal;

#endif

