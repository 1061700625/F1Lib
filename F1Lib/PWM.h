#ifndef _PWM_H_
#define _PWM_H_
#include "sys.h"
#include "TIMER.h"




class BasicPWM
{
public:
	BasicPWM(TIMER& tim, uint16_t channel);

	void set_oc_mode(uint16_t ocmode) { _TIM_OCInitStructure.TIM_OCMode = ocmode; }
	void set_output_state(uint16_t output_state) { _TIM_OCInitStructure.TIM_OutputState = output_state; }
	void set_oc_polarity(uint16_t polarity);
	void set_pulse(uint16_t pulse) { _TIM_OCInitStructure.TIM_Pulse = pulse; }




// 	void set_output_n_state(uint16_t output_nstate) { _TIM_OCInitStructure.TIM_OutputNState = output_nstate; }
// 	void set_ocn_polarity(uint16_t n_polarity) { _TIM_OCInitStructure.TIM_OCNPolarity = n_polarity; }
// 	void set_oc_idle_state(uint16_t idle_state) { _TIM_OCInitStructure.TIM_OCIdleState = idle_state; }
// 	void set_ocn_idle_state(uint16_t n_idle_state) { _TIM_OCInitStructure.TIM_OCNIdleState = n_idle_state; }


	void start_output(uint16_t initial_compare = 0, uint16_t polarity = TIMER::OCPolarity_High);
	void set_compare(uint32_t compare);







protected:
	TIMER& _tim;
	uint16_t _channel;
	TIM_OCInitTypeDef _TIM_OCInitStructure;
};

#endif


