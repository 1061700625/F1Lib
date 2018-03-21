#include "PWM.h"




BasicPWM::BasicPWM(TIMER & tim, uint16_t channel) :
	_tim(tim),
	_channel(channel)
{
	_TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 				//PWM ����ģʽ 1
	_TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	//�Ƚ����ʹ��
	_TIM_OCInitStructure.TIM_Pulse = 0; 							//��ʼ�Ƚ�ֵ
	_TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		//�������
	//�߼���ʱ���Ż�ʹ��
	_TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	_TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	_TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	_TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
}

void BasicPWM::set_oc_polarity(uint16_t polarity)
{
	_TIM_OCInitStructure.TIM_OCPolarity = polarity;
	switch (_channel)
	{

	case TIMER::Channel_1:
		TIM_OC1PolarityConfig(_tim._timx, polarity);
		break;
	case TIMER::Channel_2:
		TIM_OC2PolarityConfig(_tim._timx, polarity);
		break;
	case TIMER::Channel_3:
		TIM_OC3PolarityConfig(_tim._timx, polarity);
		break;
	case TIMER::Channel_4:
		TIM_OC4PolarityConfig(_tim._timx, polarity);
		break;
	default:
		break;
	}

}

void BasicPWM::start_output(uint16_t initial_compare,uint16_t polarity)
{

	set_pulse(initial_compare);		//��ʼ�Ƚ�ֵ
	set_oc_polarity(polarity);		//����
	//����OC���
	switch (_channel)
	{
	case TIMER::Channel_1:
		if (_tim._setup_pin_ch1())
		{
			TIM_OC1Init(_tim._timx, &_TIM_OCInitStructure);
			TIM_OC1PreloadConfig(_tim._timx, TIM_OCPreload_Enable); //ʹ��CCRԤװ�ؼĴ���
		}
		else return;
		break;
	case TIMER::Channel_2:
		if (_tim._setup_pin_ch2())
		{
			TIM_OC2Init(_tim._timx, &_TIM_OCInitStructure);
			TIM_OC2PreloadConfig(_tim._timx, TIM_OCPreload_Enable); 				//ʹ��CCR1Ԥװ�ؼĴ���
		}
		else return;
		break;
	case TIMER::Channel_3:
		if (_tim._setup_pin_ch3())
		{
			TIM_OC3Init(_tim._timx, &_TIM_OCInitStructure);
			TIM_OC3PreloadConfig(_tim._timx, TIM_OCPreload_Enable); 				//ʹ��CCR1Ԥװ�ؼĴ���

		}
		else return;
		break;
	case TIMER::Channel_4:
		if (_tim._setup_pin_ch4())
		{
			TIM_OC4Init(_tim._timx, &_TIM_OCInitStructure);
			TIM_OC4PreloadConfig(_tim._timx, TIM_OCPreload_Enable); 				//ʹ��CCR1Ԥװ�ؼĴ���
		}
		else return;
		break;
	default:
		return;
		//break;
	}

	//�߼���ʱ����Ҫʹ�����
	if (_tim._timx == TIM1 || _tim._timx == TIM8)	TIM_CtrlPWMOutputs(_tim._timx, ENABLE);
	TIM_ARRPreloadConfig(_tim._timx, ENABLE);
}

void BasicPWM::set_compare(uint32_t compare)
{
	switch (_channel)
	{

	case TIMER::Channel_1:
			TIM_SetCompare1(_tim._timx, compare);
		break;
	case TIMER::Channel_2:
		TIM_SetCompare2(_tim._timx, compare);
		break;
	case TIMER::Channel_3:
		TIM_SetCompare3(_tim._timx, compare);
		break;
	case TIMER::Channel_4:
		TIM_SetCompare4(_tim._timx, compare);
		break;
	default:
		break;
	}
}
