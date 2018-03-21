#ifndef _FTOA_ENGINE_H_
#define _FTOA_ENGINE_H_


#include "stdint.h"


int16_t ftoa_engine(float val, char *buf,
		    uint8_t precision, uint8_t maxDecimals);

/* '__ftoa_engine' return next flags (in buf[0]):	*/
#define	FTOA_MINUS	1
#define	FTOA_ZERO	2
#define	FTOA_INF	4
#define	FTOA_NAN	8
#define	FTOA_CARRY	16	/* Carry was to master position.	*/



#endif


