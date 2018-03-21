#include "GPIO.h"



//GPIO�˿ڶ���
GPIO_TypeDef* const GPIO_PORTS[] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG};

//GPIO���Ŷ���
const uint16_t  GPIO_PINS[]= {
GPIO_Pin_0,	GPIO_Pin_1,	GPIO_Pin_2,		GPIO_Pin_3,		GPIO_Pin_4,		GPIO_Pin_5,		GPIO_Pin_6,		GPIO_Pin_7,
GPIO_Pin_8,	GPIO_Pin_9,	GPIO_Pin_10,	GPIO_Pin_11,	GPIO_Pin_12,	GPIO_Pin_13,	GPIO_Pin_14,	GPIO_Pin_15};
//GPIOʱ�Ӷ���
const uint32_t  GPIO_PINS_CLOCK[]= {
RCC_APB2Periph_GPIOA,RCC_APB2Periph_GPIOB,RCC_APB2Periph_GPIOC,
RCC_APB2Periph_GPIOD,RCC_APB2Periph_GPIOE,RCC_APB2Periph_GPIOF,
RCC_APB2Periph_GPIOG,
};



////GPIOSource����
//const uint16_t  GPIO_PINS_SOURCE[]= {
//GPIO_PinSource0,	GPIO_PinSource1,	GPIO_PinSource2,	GPIO_PinSource3,	GPIO_PinSource4,	GPIO_PinSource5,	GPIO_PinSource6,	GPIO_PinSource7,
//GPIO_PinSource8,	GPIO_PinSource9,	GPIO_PinSource10,	GPIO_PinSource11,	GPIO_PinSource12,	GPIO_PinSource13,	GPIO_PinSource14,	GPIO_PinSource15};



GPIO::GPIO(GPIO_PIN_T pin):
	_port(GPIO_PORTS[pin>>4]),
	_pin(GPIO_PINS[pin&0x0F])
{}




void GPIO::mode_in(uint8_t in_mode,uint8_t speed)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = _pin;	 
	GPIO_InitStructure.GPIO_Mode = (GPIOMode_TypeDef)in_mode;
	GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)speed;
	GPIO_Init(_port, &GPIO_InitStructure);
	_mode_out = false;
}


void GPIO::mode_out(uint8_t out_mode,uint8_t speed)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = _pin;	 
	GPIO_InitStructure.GPIO_Mode = (GPIOMode_TypeDef)out_mode;
	GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)speed;
	GPIO_Init(_port, &GPIO_InitStructure);
	_mode_out = true;
}



//��ʱ�ӣ�IO��ʼ��������ӳ��
void GPIO::ModeAF(GPIO_PIN_T pin,uint8_t af_mode,uint8_t speed)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	uint16_t portn = pin>>4;
	uint16_t pinn = pin&0x0F;
	
	//��ʱ��
	RCC_APB2PeriphClockCmd(GPIO_PINS_CLOCK[portn],ENABLE);
	//��������
	GPIO_InitStructure.GPIO_Pin = GPIO_PINS[pinn];	 
	GPIO_InitStructure.GPIO_Mode = (GPIOMode_TypeDef)af_mode;
	GPIO_InitStructure.GPIO_Speed = (GPIOSpeed_TypeDef)speed;
	GPIO_Init(GPIO_PORTS[portn], &GPIO_InitStructure);
	
	
}

//��ʱ�ӣ�IO��ʼ��������ӳ��
void GPIO::ModeADC(GPIO_PIN_T pin)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	uint16_t portn = pin>>4;
	uint16_t pinn = pin&0x0F;
	
	RCC_APB2PeriphClockCmd(GPIO_PINS_CLOCK[portn],ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PINS[pinn];	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_PORTS[portn], &GPIO_InitStructure);

}



