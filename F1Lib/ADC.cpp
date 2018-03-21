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
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//分频因子要确保 ADC1 的时钟（ ADCCLK）不要超过 14Mhz。当前72/6=12MHz	
	
	
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;						//双模式选择，
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;							//是否多通道模拟输入，
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;						//是否是连续转换，
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//外部触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  				//数据对齐方式
    ADC_InitStructure.ADC_NbrOfChannel = 1; //规则组通道数，ADC规则序列寄存器 1(ADC_SQR1)的第23：20位：L[3:0]：规则通道序列长度 (Regular channel sequence length)；
	ADC_Init(adcx, &ADC_InitStructure);
	ADC_Cmd(adcx, ENABLE);//开启 AD 转换器
	
	
	//校准
	ADC_ResetCalibration(adcx); //复位ADC校准。
    while(ADC_GetResetCalibrationStatus(adcx)); //等待复位完成
    ADC_StartCalibration(adcx);  //校准
    while(ADC_GetCalibrationStatus(adcx));   //等待校准完成
	
	

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
		ADC_TempSensorVrefintCmd(ENABLE);//使能内部温度传感器
	}
	else if(_channel == 17)
	{
		//ADC_VBATCmd(ENABLE);				//内部参考电压
	}

}


void ADCx::start_conv()
{
	ADC_RegularChannelConfig(_adcx, _channel, 1, _time);
	ADC_SoftwareStartConvCmd(_adcx,ENABLE); 							//使能指定的 ADC1 的软件转换启动功能

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
	float temperate=(float)val*(3.3f/4096); 		//电压值
	temperate=(temperate-0.76f)/0.0025f+25.0f;
	return temperate*100;
}




