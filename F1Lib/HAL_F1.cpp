#include "HAL_F1.h"




NVIC_InitTypeDef NVIC_InitStructureTable[] = 
{
/*NVIC_IRQChannel|PreemptionPriority|SubPriority|***Cmd*********/

//=========USART====================================
{ USART1_IRQn,		0,					1,			ENABLE},
{ USART2_IRQn,		0,					1,			ENABLE },
{ USART3_IRQn,		0,					1,			ENABLE },

#if defined (STM32F10X_HD) || (defined STM32F10X_XL) || (defined STM32F10X_HD_VL) || (defined STM32F10X_CL)
{ UART4_IRQn,		0,					1,			ENABLE },
{ UART5_IRQn,		0,					1,			ENABLE },
#endif


//=========TIMER====================================
{TIM2_IRQn,			1,					1,			ENABLE},

//=========EXTI====================================
{ EXTI0_IRQn,		1,					2,			ENABLE},
{ EXTI1_IRQn,		1,					2,			ENABLE },
{ EXTI2_IRQn,		1,					2,			ENABLE },
{ EXTI3_IRQn,		1,					2,			ENABLE },
{ EXTI4_IRQn,		1,					2,			ENABLE },
{ EXTI9_5_IRQn,		1,					2,			ENABLE },
{ EXTI15_10_IRQn,	1,					2,			ENABLE },



};




/****************************************************************************************************************/
void NVIC_Setup()
{
	uint16_t i;
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);
	for(i=0;i < sizeof(NVIC_InitStructureTable)/sizeof(NVIC_InitStructureTable[0]);i++)
	{
		NVIC_Init(NVIC_InitStructureTable+i);
	}

}




HAL_F1::HAL_F1():
		console(usart1),
		usart1(USART1),
		usart2(USART2),
		usart3(USART3),
		uart4(UART4),
		uart5(UART5),
	
		spi1(SPI1),
		spi2(SPI2),
		spi3(SPI3),

		tim1(TIM1),
		tim8(TIM8),
		tim2(TIM2),
		tim3(TIM3),
		tim4(TIM4),
		tim5(TIM5),
		tim6(TIM6),
		tim7(TIM7),
		pwm1(tim2,TIMER::Channel_1)

{
	
	
}



void HAL_F1::Setup()
{
	NVIC_Setup();			//中断初始化
	delay_init();			//系统定时器初始化
	
	//外设初始化:打开时钟，配置引脚
	
	RCCX.GPIOA_.Enable();
	RCCX.GPIOB_.Enable();
	RCCX.GPIOC_.Enable();
	RCCX.AFIO_.Enable();		//AFIO时钟，外部中断EXTI模块使用      
	
	
	USART::Setup(USART1);

	SPIDriver::Setup(SPI1);
	
	TIMER::Setup(TIM2);

	



	
	
	
	//tim2.start_timer_micros(1000);
// 	tim2.setup_timebase(72,2500);
// 	tim2.setup_pwm1();
// 	tim2.start();
	
//	SPIDriver::Setup(SPI1);
//	TIMER::Setup(TIM3);
//	TIMER::Setup(TIM4);
//	ADCx::Setup(ADC1);

//	spiflash.init();
//	ParameterBase::Setup();
}

HAL_F1 hal;




