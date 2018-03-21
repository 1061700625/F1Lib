#ifndef _SPIFLASH_H_
#define _SPIFLASH_H_


#include "HAL_F1.h"
#include "Flash.h"

#define W25X40  0XEF12	
#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
#define W25Q128	0XEF17




//W25Qxx������СΪ4KB


class SPIFlash:FlashClass
{
public:
	SPIFlash(SPIDriver& spi,GPIO cs):_spi(spi),_cs(cs){};
	virtual ~SPIFlash(){};
	
	uint8_t status();
	void status(uint8_t sta);
		

	
	void init();	
	bool is_ready(){return !((status()&0x01)==0x01); }  
	void wait_busy(){while((status()&0x01)==0x01); }


	virtual void write_enable();
	virtual void write_disable();
	virtual void erase_chip();
	virtual void erase_sector(uint32_t sec_index);		//ÿ������4K
	virtual void read(uint32_t address, void *buf, uint32_t len);
	virtual uint32_t  write_sector(uint32_t address, void *buf, uint32_t len); //��һ�������ڶ�д,����ʱ�Զ��׶�

	void write_page(uint32_t address,void *buf, uint32_t len);		//һҳ256�ֽ�
	void write_nocheck(uint32_t address,void *buf,uint32_t len);	
	
	//void write(uint32_t address,const void *buf,uint32_t len) ;
	
	virtual uint32_t sector_size()const	{		return _sector_size;	}
	uint32_t flash_size()const	{		return _flash_size;		}
	uint16_t id()const			{		return _id;				}
	
	
private:
	SPIDriver& _spi;
	GPIO	  _cs;

	
	uint32_t	_sector_size;	//FLASHһ��������С,in byte
	uint32_t 	_flash_size;	//FLASH�ܴ�С	    ,in byte
	uint16_t 	_id;


	//static uint8_t write_buffer[4096];	//static uint8_t *write_buffer = new uint8_t[sector_size()];
	uint16_t read_id();
};




#endif

