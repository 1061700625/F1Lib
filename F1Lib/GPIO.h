#ifndef _F4_GPIO_H_
#define _F4_GPIO_H_

#include "sys.h"



typedef enum
{
	PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,//PAx
	PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,//PBx
	PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,//PCx
	PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,//PDx
	PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,//PEx
	PF0,PF1,PF2,PF3,PF4,PF5,PF6,PF7,PF8,PF9,PF10,PF11,PF12,PF13,PF14,PF15,//PFx
	PG0,PG1,PG2,PG3,PG4,PG5,PG6,PG7,PG8,PG9,PG10,PG11,PG12,PG13,PG14,PG15,//PGx
}GPIO_PIN_T;




class GPIO
{
public:
	
	
	GPIO(GPIO_PIN_T pin);
	GPIO(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin):
		_port(GPIOx),_pin(GPIO_Pin){};
			
			
	//输入模式		
	enum 
	{
		IN_Down = GPIO_Mode_IPD,					//下拉
		IN_Up = GPIO_Mode_IPU,						//上拉
		IN_Floating = GPIO_Mode_IN_FLOATING,		//浮空
	};
	//输出模式
	enum
	{
		OUT_OD = GPIO_Mode_Out_OD,	//开漏
		OUT_PP = GPIO_Mode_Out_PP,	//推挽
	};
	//复用模式
	enum
	{
		AF_OD = GPIO_Mode_AF_OD,	//开漏
		AF_PP = GPIO_Mode_AF_PP,	//推挽
	};
	//速度
	enum
	{
		  Speed_10MHz = GPIO_Speed_10MHz,
		  Speed_2MHz = GPIO_Speed_2MHz, 
		  Speed_50MHz = GPIO_Speed_50MHz		
	};
	//Pin
	enum 
	{
		Pin_0 = GPIO_Pin_0,
		Pin_1 = GPIO_Pin_1,
		Pin_2 = GPIO_Pin_2,
		Pin_3 = GPIO_Pin_3, 
		Pin_4 = GPIO_Pin_4, 
		Pin_5 = GPIO_Pin_5, 
		Pin_6 = GPIO_Pin_6, 
		Pin_7 = GPIO_Pin_7,
		Pin_8 = GPIO_Pin_8, 
		Pin_9 = GPIO_Pin_9, 
		Pin_10 = GPIO_Pin_10, 
		Pin_11 = GPIO_Pin_11, 
		Pin_12 = GPIO_Pin_12, 
		Pin_13 = GPIO_Pin_13, 
		Pin_14 = GPIO_Pin_14, 
		Pin_15 = GPIO_Pin_15,
	};
		
	
	//设置为输入模式
	void mode_in(uint8_t in_mode		= 	GPIO::IN_Up,				//上拉
					uint8_t speed = 	GPIO::Speed_50MHz);
	
	//设置为输出模式
	void mode_out(uint8_t out_mode 	=	GPIO::OUT_PP,				//推挽输出
					uint8_t speed = 	GPIO::Speed_50MHz);
	
	
		
	static void ModeAF(GPIO_PIN_T pin,
							uint8_t af_mode 	=	GPIO::AF_PP,			//推挽输出
							uint8_t speed = 	GPIO::Speed_50MHz);
	
	
	static void ModeADC(GPIO_PIN_T pin);
	
	
	
	
	//写入
	void operator =(uint8_t level)const
	{
		if(level)		GPIO_SetBits(_port,_pin);
		else			GPIO_ResetBits(_port,_pin);
	}
	
	
	//读取
	operator uint8_t() const
	{
		if(_mode_out)
			return GPIO_ReadOutputDataBit(_port,_pin);
		else
			return GPIO_ReadInputDataBit(_port,_pin);
	}
	
	
private:
	GPIO_TypeDef* const _port;
	const uint32_t 	 _pin;
	bool _mode_out;


	 //禁止取地址
	GPIO* operator&() { return this;};
	const GPIO* operator&() const {return this;};
};


#endif
