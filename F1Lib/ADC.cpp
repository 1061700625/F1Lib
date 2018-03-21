#include "ADC.h"
#include "RCCX.h"
#include "GPIO.h"



void ADCx::Setup(ADC_TypeDef* adcx)
{
	if(adcx == ADC1)
	{
		RCCX.ADC1_.Enable();
	}
	else if(adcx == ADC2)
	{
		RCCX.ADC2_.Enable();
	}
	else if(adcx == ADC3)
	{
		RCCX.ADC3_.Enable();
	}
	else
	{
		return ;
	}
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//��Ƶ����Ҫȷ�� ADC1 ��ʱ�ӣ� ADCCLK����Ҫ���� 14Mhz����ǰ72/6=12MHz	
	
	
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;						//˫ģʽѡ��
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;							//�Ƿ��ͨ��ģ�����룬
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;						//�Ƿ�������ת����
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//�ⲿ����
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  				//���ݶ��뷽ʽ
    ADC_InitStructure.ADC_NbrOfChannel = 1; //������ͨ������ADC�������мĴ��� 1(ADC_SQR1)�ĵ�23��20λ��L[3:0]������ͨ�����г��� (Regular channel sequence length)��
	ADC_Init(adcx, &ADC_InitStructure);
	ADC_Cmd(adcx, ENABLE);//���� AD ת����
	
	
	//У׼
	ADC_ResetCalibration(adcx); //��λADCУ׼��
    while(ADC_GetResetCalibrationStatus(adcx)); //�ȴ���λ���
    ADC_StartCalibration(adcx);  //У׼
    while(ADC_GetCalibrationStatus(adcx));   //�ȴ�У׼���
	
	

}



void ADCx::init()
{
	
	if(_channel <= 7)
	{
		GPIO::ModeADC((GPIO_PIN_T)((uint16_t)PA0+_channel));
	}
	else if(_channel == 8)
	{
		GPIO::ModeADC(PB0);
	}
	else if(_channel == 9)
	{
		GPIO::ModeADC(PB1);
	}
	else if(_channel <= 15)
	{
		GPIO::ModeADC((GPIO_PIN_T)((uint16_t)PC0+_channel-10));
	}
	else if(_channel == 16)
	{
		ADC_TempSensorVrefintCmd(ENABLE);//ʹ���ڲ��¶ȴ�����
	}
	else if(_channel == 17)
	{
		//ADC_VBATCmd(ENABLE);				//�ڲ��ο���ѹ
	}

}


void ADCx::start_conv()
{
	ADC_RegularChannelConfig(_adcx, _channel, 1, _time);
	ADC_SoftwareStartConvCmd(_adcx,ENABLE); 							//ʹ��ָ���� ADC1 �����ת����������

}
uint16_t ADCx::wait_result()
{
	while(!ADC_GetFlagStatus(_adcx, ADC_FLAG_EOC));
	return ADC_GetConversionValue(_adcx);
}	
uint16_t ADCx::read_result()
{
	return ADC_GetConversionValue(_adcx);
}
	

uint16_t ADCx::to_temprature(uint16_t val)
{
	float temperate=(float)val*(3.3f/4096); 		//��ѹֵ
	temperate=(temperate-0.76f)/0.0025f+25.0f;
	return temperate*100;
}




