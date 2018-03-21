#include "StmFlash.h"






void StmFlash::read(uint32_t address,void *buffer,uint32_t len)
{
	__IO uint16_t *pbuf = (uint16_t *)buffer;
	vu16 *psrc;
	uint16_t i;
	
	address = get_absolute_address(address);
	
	psrc = (vu16*)address;
	
	for (i = 0; i < len/2 ; i++)
	{
		*pbuf++ = *psrc++;
	}
	
	if(len%2)
	{
		*((uint8_t*)pbuf) = *((uint8_t*)psrc);
	}

}


void StmFlash::erase_sector(uint32_t sector_index)
{
	uint32_t address = STM32_FLASH_BASE + _address_offset + sector_index*sector_size();
	FLASH_Unlock();
	FLASH_ErasePage(address);
	FLASH_Lock();
}


uint32_t StmFlash::write_sector(uint32_t address,void *buffer,uint32_t len)
{
	__IO uint16_t *pbuf = (uint16_t *)buffer;
	uint16_t i;
	uint16_t secremain;	   
	
	address = get_absolute_address(address);
	len += len%2;
   
	secremain = sector_size() - address%sector_size();	//扇区剩余空间大小
	secremain -= secremain%2;
	
	if(len<=secremain)secremain=len;					//不大于扇区剩余空间大小
	

	FLASH_Unlock();
	for (i = 0; i < secremain/2 ; i++)
	{
		FLASH_ProgramHalfWord(address,*pbuf++);
		address+=2;
	}
	
	FLASH_Lock();
	return secremain;

}







