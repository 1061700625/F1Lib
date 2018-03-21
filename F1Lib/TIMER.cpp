#include "TIMER.h"
#include "RCCX.h"
#include "GPIO.h"



	
void TIMER::Setup(TIM_TypeDef* timx)
{
	//�߼���ʱ��
	if(timx == TIM1)		RCCX.TIM1_.Enable();
	else if(timx == TIM8)	RCCX.TIM8_.Enable();
	//������ʱ��
	else if(timx == TIM6)	RCCX.TIM6_.Enable();
	else if(timx == TIM7)	RCCX.TIM7_.Enable();
	//ͨ�ö�ʱ��
	else if(timx == TIM2)	RCCX.TIM2_.Enable();
	else if(timx == TIM3)	RCCX.TIM3_.Enable();
	else if(timx == TIM4)	RCCX.TIM4_.Enable();
	else if(timx == TIM5)	RCCX.TIM5_.Enable();
	//û���ж�??
	else if(timx == TIM9)	RCCX.TIM9_.Enable();
	else if(timx == TIM10)	RCCX.TIM10_.Enable();
	else if(timx == TIM11)	RCCX.TIM11_.Enable();
	else if(timx == TIM12)	RCCX.TIM12_.Enable();
	else if(timx == TIM13)	RCCX.TIM13_.Enable();
	else if(timx == TIM14)	RCCX.TIM14_.Enable();
	else if(timx == TIM15)	RCCX.TIM14_.Enable();
	else if(timx == TIM16)	RCCX.TIM14_.Enable();
	else if(timx == TIM17)	RCCX.TIM14_.Enable();
	else
	{
		return;
	}
}
bool TIMER::_setup_pin_ch1()
{

	if (_timx == TIM1)		GPIO::ModeAF(PA8);			//CH1
	else if (_timx == TIM8)	GPIO::ModeAF(PC6);			//CH1
	else if (_timx == TIM2)	GPIO::ModeAF(PA0);			//CH1
	else if (_timx == TIM3)	GPIO::ModeAF(PA6);			//CH1
	else if (_timx == TIM4)	GPIO::ModeAF(PB6);			//CH1
	else if (_timx == TIM5)	GPIO::ModeAF(PA0);			//CH1
	else
	{
		return false;
	}
	return true;

}
bool TIMER::_setup_pin_ch2()
{
	if (_timx == TIM1)		GPIO::ModeAF(PA9);		//CH2
	else if (_timx == TIM8)	GPIO::ModeAF(PC7);		//CH2
	else if (_timx == TIM2)	GPIO::ModeAF(PA1);		//CH2
	else if (_timx == TIM3)	GPIO::ModeAF(PA7);		//CH2
	else if (_timx == TIM4)	GPIO::ModeAF(PB7);		//CH2
	else if (_timx == TIM5)	GPIO::ModeAF(PA1);		//CH2
	else
	{
		return false;
	}
	return true;
}
bool TIMER::_setup_pin_ch3()
{
	if (_timx == TIM1)			GPIO::ModeAF(PA10);	//CH3
	else if (_timx == TIM8)		GPIO::ModeAF(PC8);		//CH3
	else if (_timx == TIM2)		GPIO::ModeAF(PA2);	//CH3
	else if (_timx == TIM3)		GPIO::ModeAF(PB0);		//CH3
	else if (_timx == TIM4)		GPIO::ModeAF(PB8);		//CH3
	else if (_timx == TIM5)		GPIO::ModeAF(PA2);		//CH3
	else
	{
		return false;
	}

	return true;
}
bool TIMER::_setup_pin_ch4()
{
	if (_timx == TIM1)			GPIO::ModeAF(PA11);	//CH4
	else if (_timx == TIM8)		GPIO::ModeAF(PC9);		//CH4
	else if (_timx == TIM2)		GPIO::ModeAF(PA3);	//CH4
	else if (_timx == TIM3)		GPIO::ModeAF(PB1);		//CH4
	else if (_timx == TIM4)		GPIO::ModeAF(PB9);		//CH4
	else if (_timx == TIM5)		GPIO::ModeAF(PA3);		//CH4
	else
	{
		return false;
	}

	return true;
}

//psc ��Ƶֵ
//arr ����ֵ
void TIMER::open(uint16_t psc, uint16_t arr)
{
	set_prescaler(psc-1);
	set_period(arr-1);
	TIM_TimeBaseInit(_timx, &_TIM_TimeBaseInitStructure);				//��ʼ����ʱ��

	TIM_Cmd(_timx, ENABLE);
}

void TIMER::start_micros(uint16_t interval_micros, void(*update_callback)(void))
{
	start(SystemCoreClock/1000000,interval_micros,update_callback);
}
void TIMER::start(uint16_t psc,uint16_t arr,void(*update_callback)(void))
{
	open(psc, arr);
	if(update_callback != NULL)
	{
		update_event = update_callback;
		add_interrupt(TIMER::IT_Update);
	}

}
void TIMER::stop()
{
	TIM_Cmd(_timx, DISABLE);

	if (update_event != NULL)
	{
		update_event = NULL;
		remove_interrupt(TIMER::IT_Update);
	}
}

void TIMER::suspend()
{
	TIM_Cmd(_timx, DISABLE);
}
void TIMER::resume()
{
	TIM_Cmd(_timx, ENABLE);
}









// 
// 
// 
// void TIMER::setup_pwm1(uint16_t Mode,uint16_t OutputState,uint16_t Polarity,\
// 							uint16_t OutputNState, uint16_t NPolarity,uint16_t IdleState,uint16_t NIdleState)
// {
// 
// 
// 	if(!_setup_pin_ch1())return;
// 	
// 	TIM_OCInitTypeDef TIM_OCInitStructure;
// 	TIM_OCInitStructure.TIM_OCMode = Mode; 				//PWM ����ģʽ 1
// 	TIM_OCInitStructure.TIM_OutputState = OutputState; 	//�Ƚ����ʹ��
// 	TIM_OCInitStructure.TIM_Pulse = 0; 					//��ʼ�Ƚ�ֵ
// 	TIM_OCInitStructure.TIM_OCPolarity = Polarity; 		//�������
// 	
// 	TIM_OCInitStructure.TIM_OutputNState = OutputNState;
// 	TIM_OCInitStructure.TIM_OCNPolarity = NPolarity;
// 	TIM_OCInitStructure.TIM_OCIdleState = IdleState;
// 	TIM_OCInitStructure.TIM_OCNIdleState = NIdleState;
// 	TIM_OC1Init(_timx, &TIM_OCInitStructure); 			//��ʼ������
// 
// 	if(_timx == TIM1 || _timx == TIM8)	TIM_CtrlPWMOutputs(_timx, ENABLE);
// 
// 	
// 	TIM_OC1PreloadConfig(_timx, TIM_OCPreload_Enable); 				//ʹ��CCR1Ԥװ�ؼĴ���
// 	TIM_ARRPreloadConfig(_timx, ENABLE);
// }
// 
// 
// 
// void TIMER::setup_pwm2(uint16_t Mode,uint16_t OutputState,uint16_t Polarity,\
// 							uint16_t OutputNState, uint16_t NPolarity,uint16_t IdleState,uint16_t NIdleState)
// {
// 
// 	if(!_setup_pin_ch2())return;
// 	
// 	TIM_OCInitTypeDef TIM_OCInitStructure;
// 	TIM_OCInitStructure.TIM_OCMode = Mode; 				//PWM ����ģʽ 1
// 	TIM_OCInitStructure.TIM_OutputState = OutputState; 	//�Ƚ����ʹ��
// 	TIM_OCInitStructure.TIM_Pulse = 0; 					//��ʼ�Ƚ�ֵ
// 	TIM_OCInitStructure.TIM_OCPolarity = Polarity; 		//�������
// 	
// 	TIM_OCInitStructure.TIM_OutputNState = OutputNState;
// 	TIM_OCInitStructure.TIM_OCNPolarity = NPolarity;
// 	TIM_OCInitStructure.TIM_OCIdleState = IdleState;
// 	TIM_OCInitStructure.TIM_OCNIdleState = NIdleState;
// 	TIM_OC2Init(_timx, &TIM_OCInitStructure); 			//��ʼ������
// 
// 	if (_timx == TIM1 || _timx == TIM8)	TIM_CtrlPWMOutputs(_timx, ENABLE);
// 
// 	TIM_OC2PreloadConfig(_timx, TIM_OCPreload_Enable); 				//ʹ��CCR1Ԥװ�ؼĴ���
// 	TIM_ARRPreloadConfig(_timx, ENABLE);
// }
// 
// 
// void TIMER::setup_pwm3(uint16_t Mode,uint16_t OutputState,uint16_t Polarity,\
// 							uint16_t OutputNState, uint16_t NPolarity,uint16_t IdleState,uint16_t NIdleState)
// {
// 
// 	if(!_setup_pin_ch3())return;
// 	
// 	TIM_OCInitTypeDef TIM_OCInitStructure;
// 	TIM_OCInitStructure.TIM_OCMode = Mode; 				//PWM ����ģʽ 1
// 	TIM_OCInitStructure.TIM_OutputState = OutputState; 	//�Ƚ����ʹ��
// 	TIM_OCInitStructure.TIM_Pulse = 0; 					//��ʼ�Ƚ�ֵ
// 	TIM_OCInitStructure.TIM_OCPolarity = Polarity; 		//�������
// 	
// 	TIM_OCInitStructure.TIM_OutputNState = OutputNState;
// 	TIM_OCInitStructure.TIM_OCNPolarity = NPolarity;
// 	TIM_OCInitStructure.TIM_OCIdleState = IdleState;
// 	TIM_OCInitStructure.TIM_OCNIdleState = NIdleState;
// 	TIM_OC3Init(_timx, &TIM_OCInitStructure); 			//��ʼ������
// 	
// 	if (_timx == TIM1 || _timx == TIM8)	TIM_CtrlPWMOutputs(_timx, ENABLE);
// 
// 	TIM_OC3PreloadConfig(_timx, TIM_OCPreload_Enable); 				//ʹ��CCR1Ԥװ�ؼĴ���
// 	TIM_ARRPreloadConfig(_timx, ENABLE);
// }
// 
// 
// void TIMER::setup_pwm4(uint16_t Mode,uint16_t OutputState,uint16_t Polarity,\
// 							uint16_t OutputNState, uint16_t NPolarity,uint16_t IdleState,uint16_t NIdleState)
// {
// 	
// 	if(!_setup_pin_ch4())return;
// 	
// 	TIM_OCInitTypeDef TIM_OCInitStructure;
// 	TIM_OCInitStructure.TIM_OCMode = Mode; 				//PWM ����ģʽ 1
// 	TIM_OCInitStructure.TIM_OutputState = OutputState; 	//�Ƚ����ʹ��
// 	TIM_OCInitStructure.TIM_Pulse = 0; 					//��ʼ�Ƚ�ֵ
// 	TIM_OCInitStructure.TIM_OCPolarity = Polarity; 		//�������
// 	
// 	TIM_OCInitStructure.TIM_OutputNState = OutputNState;
// 	TIM_OCInitStructure.TIM_OCNPolarity = NPolarity;
// 	TIM_OCInitStructure.TIM_OCIdleState = IdleState;
// 	TIM_OCInitStructure.TIM_OCNIdleState = NIdleState;
// 	TIM_OC4Init(_timx, &TIM_OCInitStructure); 			//��ʼ������
// 	
// 	if (_timx == TIM1 || _timx == TIM8)	TIM_CtrlPWMOutputs(_timx, ENABLE);
// 
// 	TIM_OC4PreloadConfig(_timx, TIM_OCPreload_Enable); 				//ʹ��CCR1Ԥװ�ؼĴ���
// 	TIM_ARRPreloadConfig(_timx, ENABLE);
// }
// 
// 
// 
// 
// 
// void TIMER::setup_capture1(uint16_t Polarity,uint16_t Selection,uint16_t Prescale,uint16_t Filter)
// {
// 	if(!_setup_pin_ch1())return;
// 	
// 	TIM_ICInitTypeDef TIM_ICInitStructure;
// 	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; 					//ѡ������� IC1 ӳ�䵽 TI1 ��
// 	TIM_ICInitStructure.TIM_ICPolarity = Polarity; 		//�����ز���
// 	TIM_ICInitStructure.TIM_ICSelection = Selection; 	//ӳ�䵽 TI1 ��
// 	TIM_ICInitStructure.TIM_ICPrescaler = Prescale; 				//���������Ƶ,����Ƶ
// 	TIM_ICInitStructure.TIM_ICFilter = Filter;							//IC1F=0000 ���������˲��� ���˲�
// 	TIM_ICInit(_timx, &TIM_ICInitStructure); 							//��ʼ�� TIM5 ���벶�����
// 	
// 	TIM_ITConfig(_timx,TIM_IT_Update|TIM_IT_CC1,ENABLE);					//������ºͲ����ж�
// }	
// 
// 
// void TIMER::setup_capture2(uint16_t Polarity,uint16_t Selection,uint16_t Prescale,uint16_t Filter)
// {
// 	if(!_setup_pin_ch2())return;
// 	
// 	TIM_ICInitTypeDef TIM_ICInitStructure;
// 	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; 					//ѡ������� IC1 ӳ�䵽 TI1 ��
// 	TIM_ICInitStructure.TIM_ICPolarity = Polarity; 		//�����ز���
// 	TIM_ICInitStructure.TIM_ICSelection = Selection; 	//ӳ�䵽 TI1 ��
// 	TIM_ICInitStructure.TIM_ICPrescaler = Prescale; 				//���������Ƶ,����Ƶ
// 	TIM_ICInitStructure.TIM_ICFilter = Filter;							//IC1F=0000 ���������˲��� ���˲�
// 	TIM_ICInit(_timx, &TIM_ICInitStructure); 							//��ʼ�� TIM5 ���벶�����
// 	
// 	TIM_ITConfig(_timx,TIM_IT_Update|TIM_IT_CC2,ENABLE);					//������ºͲ����ж�
// }	
// 
// 
// void TIMER::setup_capture3(uint16_t Polarity,uint16_t Selection,uint16_t Prescale,uint16_t Filter)
// {
// 	if(!_setup_pin_ch3())return;
// 	
// 	TIM_ICInitTypeDef TIM_ICInitStructure;
// 	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3; 					//ѡ������� IC1 ӳ�䵽 TI1 ��
// 	TIM_ICInitStructure.TIM_ICPolarity = Polarity; 		//�����ز���
// 	TIM_ICInitStructure.TIM_ICSelection = Selection; 	//ӳ�䵽 TI1 ��
// 	TIM_ICInitStructure.TIM_ICPrescaler = Prescale; 				//���������Ƶ,����Ƶ
// 	TIM_ICInitStructure.TIM_ICFilter = Filter;							//IC1F=0000 ���������˲��� ���˲�
// 	TIM_ICInit(_timx, &TIM_ICInitStructure); 							//��ʼ�� TIM5 ���벶�����
// 	
// 	TIM_ITConfig(_timx,TIM_IT_Update|TIM_IT_CC3,ENABLE);					//������ºͲ����ж�
// }	
// 
// 
// void TIMER::setup_capture4(uint16_t Polarity,uint16_t Selection,uint16_t Prescale,uint16_t Filter)
// {
// 	if(!_setup_pin_ch4())return;
// 	
// 	TIM_ICInitTypeDef TIM_ICInitStructure;
// 	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4; 					//ѡ������� IC1 ӳ�䵽 TI1 ��
// 	TIM_ICInitStructure.TIM_ICPolarity = Polarity; 		//�����ز���
// 	TIM_ICInitStructure.TIM_ICSelection = Selection; 	//ӳ�䵽 TI1 ��
// 	TIM_ICInitStructure.TIM_ICPrescaler = Prescale; 				//���������Ƶ,����Ƶ
// 	TIM_ICInitStructure.TIM_ICFilter = Filter;							//IC1F=0000 ���������˲��� ���˲�
// 	TIM_ICInit(_timx, &TIM_ICInitStructure); 							//��ʼ�� TIM5 ���벶�����
// 	
// 	TIM_ITConfig(_timx,TIM_IT_Update|TIM_IT_CC4,ENABLE);					//������ºͲ����ж�
// }	
// 



















