#include "sys.h"
#include "HAL_F1.h"

Param_Float paf(0);
void display_loop()
{
//	static uint16_t i = 0;
	//printf("dis = %i\r\n",i);
}


GPIO led(PC13);
void flash_loop()
{
	led = !led;
}








void tim2_callback()
{
	static uint16_t i = 0;
	if (++i >= 10)
	{
		i = 0;
		puts("tim2 callback");
	}
}

void usart_callback(uint16_t c)
{
	hal.usart1.putc(c);
}

void setup()
{

	//硬件配置
	hal.usart1.begin(500000,usart_callback);

	ParameterBase::Setup();

	led.mode_out();

	//hal.tim2.start_micros(50000,tim2_callback);//50ms定时器中断
	hal.tim2.open(72, 2500);
	hal.pwm1.start_output(1200);
	hal.pwm1.set_oc_polarity(TIMER::OCPolarity_Low);

}


const scheduler_tasks_t scheduler_tasks[] =
{
	{ display_loop,	1000000,	1000 },	//1000ms,1Hz
	{ flash_loop,	1000,	1000 },	//1ms,1kHz

};
int main()
{
	hal.Setup();
	setup();
	
	hal.scheduler.init(scheduler_tasks,sizeof(scheduler_tasks)/sizeof(scheduler_tasks[0]));
	hal.scheduler.run();
	
}

