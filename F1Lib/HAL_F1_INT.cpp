#include "HAL_F1.h"


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

extern "C" void TIM1_UP_IRQHandler(void)
{
	if (hal.tim1.update_event != NULL && hal.tim1.check_flag(TIMER::FLAG_Update))
	{
		hal.tim1.clear_flag(TIMER::FLAG_Update);
		hal.tim1.update_event();
	}

}
extern "C" void TIM8_UP_IRQHandler(void)
{

	if (hal.tim8.update_event != NULL && hal.tim8.check_flag(TIMER::FLAG_Update))
	{
		hal.tim8.clear_flag(TIMER::FLAG_Update);
		hal.tim8.update_event();
	}

}
extern "C" void TIM2_IRQHandler(void)
{


	if (hal.tim2.update_event!=NULL && hal.tim2.check_flag(TIMER::FLAG_Update))
	{
		hal.tim2.clear_flag(TIMER::FLAG_Update);
		hal.tim2.update_event();
	}

}
extern "C" void TIM3_IRQHandler(void)
{

	if (hal.tim3.update_event != NULL && hal.tim3.check_flag(TIMER::FLAG_Update))
	{
		hal.tim3.clear_flag(TIMER::FLAG_Update);
		hal.tim3.update_event();
	}

}
extern "C" void TIM4_IRQHandler(void) 
{
	if (hal.tim4.update_event != NULL && hal.tim4.check_flag(TIMER::FLAG_Update))
	{
		hal.tim4.clear_flag(TIMER::FLAG_Update);	
		hal.tim4.update_event();
	}
	
}
extern "C" void TIM5_IRQHandler(void)
{
	if (hal.tim5.update_event != NULL && hal.tim5.check_flag(TIMER::FLAG_Update))
	{
		hal.tim5.clear_flag(TIMER::FLAG_Update);
		hal.tim5.update_event();
	}

}
extern "C" void TIM6_IRQHandler(void)
{
	if (hal.tim6.update_event != NULL && hal.tim6.check_flag(TIMER::FLAG_Update))
	{
		hal.tim6.clear_flag(TIMER::FLAG_Update);
		hal.tim6.update_event();
	}

}
extern "C" void TIM7_IRQHandler(void)
{
	if (hal.tim7.update_event != NULL && hal.tim7.check_flag(TIMER::FLAG_Update))
	{
		hal.tim7.clear_flag(TIMER::FLAG_Update);
		hal.tim7.update_event();
	}

}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
extern "C" void USART1_IRQHandler(void)
{

	if (hal.usart1.receive_event != NULL && hal.usart1.check_interrupt(USART::IT_RXNE))
	{
		hal.usart1.receive_event(hal.usart1.read_byte());
	}

	if (hal.usart1.idle_event != NULL && hal.usart1.check_interrupt(USART::IT_IDLE))
	{
		uint8_t Clear;

		Clear = hal.usart1.read_status();
		Clear = hal.usart1.read_byte();
		Clear = Clear;
		hal.usart1.idle_event();	
	}
}

extern "C" void USART2_IRQHandler(void)
{

	if (hal.usart2.receive_event != NULL && hal.usart2.check_interrupt(USART::IT_RXNE))
	{
		hal.usart2.receive_event(hal.usart2.read_byte());
	}

	if (hal.usart2.idle_event != NULL && hal.usart2.check_interrupt(USART::IT_IDLE))
	{
		uint8_t Clear;

		Clear = hal.usart2.read_status();
		Clear = hal.usart2.read_byte();
		Clear = Clear;
		hal.usart2.idle_event();
	}
}
extern "C" void USART3_IRQHandler(void)
{

	if (hal.usart3.receive_event != NULL && hal.usart3.check_interrupt(USART::IT_RXNE))
	{
		hal.usart3.receive_event(hal.usart3.read_byte());
	}

	if (hal.usart3.idle_event != NULL && hal.usart3.check_interrupt(USART::IT_IDLE))
	{
		uint8_t Clear;

		Clear = hal.usart3.read_status();
		Clear = hal.usart3.read_byte();
		Clear = Clear;
		hal.usart3.idle_event();
	}
}
extern "C" void UART4_IRQHandler(void)
{

	if (hal.uart4.receive_event != NULL && hal.uart4.check_interrupt(USART::IT_RXNE))
	{
		hal.uart4.receive_event(hal.uart4.read_byte());
	}

	if (hal.uart4.idle_event != NULL && hal.uart4.check_interrupt(USART::IT_IDLE))
	{
		uint8_t Clear;

		Clear = hal.uart4.read_status();
		Clear = hal.uart4.read_byte();
		Clear = Clear;
		hal.uart4.idle_event();
	}
}
extern "C" void UART5_IRQHandler(void)
{

	if (hal.uart5.receive_event != NULL && hal.uart5.check_interrupt(USART::IT_RXNE))
	{
		hal.uart5.receive_event(hal.uart5.read_byte());
	}

	if (hal.uart5.idle_event != NULL && hal.uart5.check_interrupt(USART::IT_IDLE))
	{
		uint8_t Clear;

		Clear = hal.uart5.read_status();
		Clear = hal.uart5.read_byte();
		Clear = Clear;
		hal.uart5.idle_event();
	}
}


extern "C" void EXTI0_IRQHandler()
{

}

extern "C" void EXTI1_IRQHandler()
{

}

extern "C" void EXTI2_IRQHandler()
{

}

extern "C" void EXTI3_IRQHandler()
{

}
extern "C" void EXTI4_IRQHandler()
{

}

extern "C" void EXTI9_5_IRQHandler()
{

}
extern "C" void EXTI15_10_IRQHandler()
{


}
