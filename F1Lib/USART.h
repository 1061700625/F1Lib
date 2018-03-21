#ifndef _USART_H_
#define _USART_H_

#include "sys.h"
#include "stdarg.h"


class USART
{
public:
	USART(USART_TypeDef* USARTx):
		receive_event(NULL),
		idle_event(NULL),
		_usartx(USARTx)
	{
		_USART_InitStructure.USART_BaudRate = 115200;									//
		_USART_InitStructure.USART_WordLength = USART_WordLength_8b; 					//字长为 8 位
		_USART_InitStructure.USART_StopBits = USART_StopBits_1;							//一个停止位
		_USART_InitStructure.USART_Parity = USART_Parity_No;								//无奇偶校验位
		_USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
		_USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//收发

	};
			
	~USART(){};
		
	enum
	{
		WordLength_8b = USART_WordLength_8b,
		WordLength_9b = USART_WordLength_9b,
	};
	enum 
	{
		StopBits_1 = USART_StopBits_1,
		StopBits_0_5 = USART_StopBits_0_5,
		StopBits_2 = USART_StopBits_2,
		StopBits_1_5 = USART_StopBits_1_5
	};
	enum
	{
		Parity_No = USART_Parity_No,
		Parity_Even = USART_Parity_Even,
		Parity_Odd = USART_Parity_Odd
	};
	enum 
	{
		Mode_Rx = USART_Mode_Rx,
		Mode_Tx = USART_Mode_Tx
	};
	enum 
	{
		HardwareFlowControl_None = USART_HardwareFlowControl_None,
		HardwareFlowControl_RTS = USART_HardwareFlowControl_RTS,
		HardwareFlowControl_CTS = USART_HardwareFlowControl_CTS,
		HardwareFlowControl_RTS_CTS = USART_HardwareFlowControl_RTS_CTS
	};
	
	enum
	{
		IT_PE = USART_IT_PE,		//校验错误
		IT_TXE = USART_IT_TXE,		//发送区为空
		IT_TC = USART_IT_TC,		//发送完成
		IT_RXNE = USART_IT_RXNE,		//接收到数据
		IT_IDLE = USART_IT_IDLE,		//空闲
		IT_LBD = USART_IT_LBD,
		IT_CTS = USART_IT_CTS,
		IT_ERR = USART_IT_ERR,
		IT_ORE = USART_IT_ORE, /* In case interrupt is generated if the EIE bit is set */
		IT_NE = USART_IT_NE,
		IT_FE = USART_IT_FE,
	};
	enum
	{
		FLAG_CTS = USART_FLAG_CTS,
		FLAG_LBD = USART_FLAG_LBD,
		FLAG_TXE = USART_FLAG_TXE,		//发送区为空
		FLAG_TC = USART_FLAG_TC,		//发送完成
		FLAG_RXNE = USART_FLAG_RXNE,		//接收到数据
		FLAG_IDLE = USART_FLAG_IDLE,		//空闲
		FLAG_ORE = USART_FLAG_ORE, /* In case interrupt is generated if the RXNEIE bit is set */
		FLAG_NE = USART_FLAG_NE,
		FLAG_PE = USART_FLAG_PE,		//校验错误
		FLAG_FE = USART_FLAG_FE,
	};


	static void Setup(USART_TypeDef* usartx);
			
	//////////////////////////////////////////////////////////////////////////////////
	//初始化配置
	//////////////////////////////////////////////////////////////////////////////////
	void set_baudrate(uint32_t baudrate) { _USART_InitStructure.USART_BaudRate = baudrate; }
	void set_wordlength(uint16_t wl){ _USART_InitStructure.USART_WordLength = wl; }
	void set_stopbits(uint16_t stopbits){ _USART_InitStructure.USART_StopBits = stopbits; }
	void set_parity(uint16_t parity)			{_USART_InitStructure.USART_Parity = parity;		}
	void set_mode(uint16_t mode)				{_USART_InitStructure.USART_Mode = mode;			}
	void set_hardwareflow_control(uint16_t hf)	{_USART_InitStructure.USART_HardwareFlowControl = hf;}
	

	uint16_t read_status() {
		return _usartx->SR;
	}
	void add_interrupt(uint16_t it){
		USART_ITConfig(_usartx,it,ENABLE);
	}
	void remove_interrupt(uint16_t it){
		USART_ITConfig(_usartx,it,DISABLE);
	}
	bool check_interrupt(uint16_t it){
		return USART_GetITStatus(_usartx, it) == SET?true:false;
	}
	bool check_flag(uint16_t flag){
		return USART_GetFlagStatus(_usartx, flag) == SET ? true : false;
	}
	void clear_flag(uint16_t flag) {
		 USART_ClearFlag(_usartx, flag);
	}



	//////////////////////////////////////////////////////////////////////////////////
	//应用函数
	//////////////////////////////////////////////////////////////////////////////////
	void open();
	void begin(uint32_t baudrate, void(*receive_callback)(uint16_t c) = NULL,void(*idle_callback)(void) = NULL);		//打开普通串口
	void close();

	uint16_t wait_byte()
	{
		while (USART_GetFlagStatus(_usartx, USART::FLAG_RXNE) == RESET);
		return USART_ReceiveData(_usartx);
	}
	uint16_t read_byte()
	{
		return USART_ReceiveData(_usartx);
	}

	void write(uint8_t c);
	void write(uint8_t *buffer, uint16_t len);	

	void putc(uint8_t c){ write(c); }
	void printf(const char *fmt,...);
	void puts(const char *s);
	
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	void (*receive_event)(uint16_t c);
	void(*idle_event)(void);
private:
	
	void _vprintf(const char* fmt,va_list ap);

	USART_TypeDef* _usartx;
	USART_InitTypeDef _USART_InitStructure;	


};









#endif
