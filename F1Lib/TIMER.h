#ifndef _TIMER_H_
#define _TIMER_H_
#include "sys.h"

class BasicPWM;


class TIMER
{
	friend BasicPWM;
public:

	
	TIMER(TIM_TypeDef* timx):
		update_event(NULL),
		_timx(timx)
	{
		_TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; 		//向上计数模式
		_TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	}

	static void Setup(TIM_TypeDef* timx);	
		
	enum
	{
		IT_Update 	= TIM_IT_Update,
		IT_CC1 		= TIM_IT_CC1,
		IT_CC2 		= TIM_IT_CC2,
		IT_CC3 		= TIM_IT_CC3,
		IT_COM 		= TIM_IT_COM,
		IT_Trigger 	= TIM_IT_Trigger,
		IT_Break 	= TIM_IT_Break,
	};
	enum
	{
		FLAG_Update = TIM_FLAG_Update,
		FLAG_CC1 	= TIM_FLAG_CC1,
		FLAG_CC2 	= TIM_FLAG_CC2,
		FLAG_CC3 	= TIM_FLAG_CC3,
		FLAG_CC4 	= TIM_FLAG_CC4,
		FLAG_COM 	= TIM_FLAG_COM,
		FLAG_Break 	= TIM_FLAG_Break,
		FLAG_CC1OF 	= TIM_FLAG_CC1OF,
		FLAG_CC2OF 	= TIM_FLAG_CC2OF,
		FLAG_CC3OF 	= TIM_FLAG_CC3OF,
		FLAG_CC4OF 	= TIM_FLAG_CC4OF,	
	};


	//////TIMER_Base
	enum
	{
		CounterMode_Up = TIM_CounterMode_Up,
		CounterMode_Down = TIM_CounterMode_Down,
		CounterMode_CenterAligned1 = TIM_CounterMode_CenterAligned1,
		CounterMode_CenterAligned2 = TIM_CounterMode_CenterAligned2,
		CounterMode_CenterAligned3 = TIM_CounterMode_CenterAligned3
	};
	enum
	{
		CKD_DIV1 = TIM_CKD_DIV1,
		CKD_DIV2 = TIM_CKD_DIV2,
		CKD_DIV4 = TIM_CKD_DIV4
	};
	enum
	{
		Channel_1 = TIM_Channel_1,
		Channel_2 = TIM_Channel_2,
		Channel_3 = TIM_Channel_3,
		Channel_4 = TIM_Channel_4
	};

	//////TIMER_OC
	enum
	{
		OCMode_Timing = TIM_OCMode_Timing,
		OCMode_Active = TIM_OCMode_Active,
		OCMode_Inactive = TIM_OCMode_Inactive,
		OCMode_Toggle = TIM_OCMode_Toggle,
		OCMode_PWM1 = TIM_OCMode_PWM1,
		OCMode_PWM2 = TIM_OCMode_PWM2,
	};
	enum
	{
		OCPolarity_High = TIM_OCPolarity_High,
		OCPolarity_Low = TIM_OCPolarity_Low
	};
	enum
	{
		OutputState_Disable = TIM_OutputState_Disable,
		OutputState_Enable = TIM_OutputState_Enable
	};
	//////TIMER_OCN
	enum
	{
		OutputNState_Disable = TIM_OutputNState_Disable,
		OutputNState_Enable = TIM_OutputNState_Enable
	};
	enum
	{
		OCNPolarity_High = TIM_OCNPolarity_High,
		OCNPolarity_Low = TIM_OCNPolarity_Low
	};
	enum
	{
		OCIdleState_Set = TIM_OCIdleState_Set,
		OCIdleState_Reset = TIM_OCIdleState_Reset
	};
	enum
	{
		OCNIdleState_Set = TIM_OCNIdleState_Set,
		OCNIdleState_Reset = TIM_OCNIdleState_Reset
	};
	//////TIMER_IC
	enum
	{
		ICPolarity_Rising = TIM_ICPolarity_Rising,
		ICPolarity_Falling = TIM_ICPolarity_Falling,
		ICPolarity_BothEdge = TIM_ICPolarity_BothEdge
	};
	enum
	{
		ICSelection_DirectTI = TIM_ICSelection_DirectTI,
		ICSelection_IndirectTI = TIM_ICSelection_IndirectTI
	};
	enum
	{
		ICPSC_DIV1 = TIM_ICPSC_DIV1,
		ICPSC_DIV2 = TIM_ICPSC_DIV2,
		ICPSC_DIV4 = TIM_ICPSC_DIV4
	};


	//////////////////////////////////////////////////////////////////////////////////
	//初始化配置
	//////////////////////////////////////////////////////////////////////////////////
		
		

	void set_prescaler(uint16_t pre) { _TIM_TimeBaseInitStructure.TIM_Prescaler = pre; }
	void set_counter_mode(uint16_t counter_mode) { _TIM_TimeBaseInitStructure.TIM_CounterMode = counter_mode; }
	void set_period(uint16_t period) { _TIM_TimeBaseInitStructure.TIM_Period = period; }
	void set_clock_division(uint16_t cd) { _TIM_TimeBaseInitStructure.TIM_ClockDivision = cd; }
	void set_repetition_counter(uint16_t rc) { _TIM_TimeBaseInitStructure.TIM_RepetitionCounter = rc; }


	void set_counter(uint32_t cnt)	{TIM_SetCounter(_timx, cnt);}
	uint32_t get_counter()	{ return TIM_GetCounter(_timx);}
	
	
	void add_interrupt(uint16_t it) {
		TIM_ITConfig(_timx, it, ENABLE);
	}
	void remove_interrupt(uint16_t it) {
		TIM_ITConfig(_timx,it, DISABLE);
	}
	bool check_interrupt(uint16_t it) {
		return TIM_GetITStatus(_timx,it) == SET ? true : false;
	}
	bool check_flag(uint16_t flag) {
		return TIM_GetFlagStatus(_timx,flag) == SET ? true : false;
	}
	void clear_flag(uint16_t flag) {
		TIM_ClearFlag(_timx,flag);
	}

	//////////////////////////////////////////////////////////////////////////////////
	//定时器
	//////////////////////////////////////////////////////////////////////////////////
	void start_micros(uint16_t interval_micros,void(*update_callback)(void) = NULL);	//微妙级定时器	
	void start(uint16_t psc, uint16_t arr,void (*update_callback)(void) = NULL);		//普通定时器
	void stop();
	void suspend();
	void resume();
	void open(uint16_t psc, uint16_t arr);
				
// 			//////////////////////////////////////////////////////////////////////////////////
// 			//Capture
// 			//////////////////////////////////////////////////////////////////////////////////
// 			void setup_capture1(uint16_t Polarity = TIM_ICPolarity_Rising,\
// 						uint16_t Selection = TIM_ICSelection_DirectTI,\
// 						uint16_t Prescaler	= TIM_ICPSC_DIV1,
// 						uint16_t Filter	=  0x0);
// 			void setup_capture2(uint16_t Polarity = TIM_ICPolarity_Rising,\
// 						uint16_t Selection = TIM_ICSelection_DirectTI,\
// 						uint16_t Prescaler	= TIM_ICPSC_DIV1,
// 						uint16_t Filter	=  0x0);
// 			void setup_capture3(uint16_t Polarity = TIM_ICPolarity_Rising,\
// 						uint16_t Selection = TIM_ICSelection_DirectTI,\
// 						uint16_t Prescaler	= TIM_ICPSC_DIV1,
// 						uint16_t Filter	=  0x0);
// 			void setup_capture4(uint16_t Polarity = TIM_ICPolarity_Rising,\
// 						uint16_t Selection = TIM_ICSelection_DirectTI,\
// 						uint16_t Prescaler	= TIM_ICPSC_DIV1,
// 						uint16_t Filter	=  0x0);
// 				
// 			void set_capture1_polarity(uint16_t Polarity)	{TIM_OC1PolarityConfig(_timx,Polarity);}
// 			void set_capture2_polarity(uint16_t Polarity)	{TIM_OC2PolarityConfig(_timx,Polarity);}
// 			void set_capture3_polarity(uint16_t Polarity)	{TIM_OC3PolarityConfig(_timx,Polarity);}
// 			void set_capture4_polarity(uint16_t Polarity)	{TIM_OC4PolarityConfig(_timx,Polarity);}
// 				
// 				
// 				
// 			uint32_t get_capture1()	{return TIM_GetCapture1(_timx);}
// 			uint32_t get_capture2()	{return TIM_GetCapture2(_timx);}
// 			uint32_t get_capture3()	{return TIM_GetCapture3(_timx);}
// 			uint32_t get_capture4()	{return TIM_GetCapture4(_timx);}
	
	
	
	

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
	void(*update_event)(void);
private:
	TIM_TimeBaseInitTypeDef _TIM_TimeBaseInitStructure;
	TIM_TypeDef	*_timx;


	bool _setup_pin_ch1();
	bool _setup_pin_ch2();
	bool _setup_pin_ch3();
	bool _setup_pin_ch4();


};



#endif
