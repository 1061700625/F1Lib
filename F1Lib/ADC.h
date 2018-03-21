#ifndef _ADC_H_
#define _ADC_H_

#include "sys.h"



class ADCx
{
public:
	
	ADCx(ADC_TypeDef* adcx,uint8_t channel)
		:_adcx(adcx),_channel(channel)
	{
		_time = ADCx::SampleTime_239Cycles5;
	}
	
	
	enum
	{
		SampleTime_1Cycles5 = ADC_SampleTime_1Cycles5,
		SampleTime_7Cycles5 = ADC_SampleTime_7Cycles5,
		SampleTime_13Cycles5 = ADC_SampleTime_13Cycles5,
		SampleTime_28Cycles5 = ADC_SampleTime_28Cycles5,
		SampleTime_41Cycles5 = ADC_SampleTime_41Cycles5,
		SampleTime_55Cycles5 = ADC_SampleTime_55Cycles5,
		SampleTime_71Cycles5 = ADC_SampleTime_71Cycles5,	
		SampleTime_239Cycles5 = ADC_SampleTime_239Cycles5,	
	};
	
	
	
	static void Setup(ADC_TypeDef* adcx);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	void init();
	void set_sample_time(uint8_t sampletime)	{_time = sampletime;}


	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	void start_conv();
	uint16_t wait_result();
	uint16_t read_result();
	uint16_t to_temprature(uint16_t val);
	
		

private:
	ADC_TypeDef* _adcx;
	uint8_t _channel;
	uint8_t _time;




};












#endif





