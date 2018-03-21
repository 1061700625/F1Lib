#include "xtoa_fast.h"


char * ultoa_invert (uint32_t val, char *s, uint8_t base)
{
	if (base == 8) 
	{
		do 
		{
			*s = '0' + (val & 0x7);
			val >>= 3;
		} while(val);
		return s;
	}

	if (base == 16) 
	{
		do 
		{
			uint8_t digit = '0' + (val & 0xf);
#if XTOA_UPPER == 0
			if (digit > '0' + 9)
				digit += ('a' - '0' - 10);
#else
			if (digit > '0' + 9)
				digit += ('A' - '0' - 10);
#endif
			*s++ = digit;
			val >>= 4;
		} while(val);
		return s;
	}

	// Every base which in not hex and not oct is considered decimal.

	// 33 bits would have been enough.
	uint64_t xval = val;
	do {
		uint8_t saved = xval;
		xval &= ~1;
		xval += 2;
		xval += xval >> 1;		// *1.5
		xval += xval >> 4;		// *1.0625
		xval += xval >> 8;		// *1.00390625
		xval += xval >> 16;		// *1.000015259
		xval += xval >> 32;		// it all amounts to *1.6
		xval >>= 4;				// /16 ... so *1.6/16 is /10, fraction truncated.
		*s++ = '0' + saved - 10 * (uint8_t)xval;
	} while (xval);
	return s;
}

