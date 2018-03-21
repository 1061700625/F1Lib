#ifndef	_XTOA_FAST_H_
#define _XTOA_FAST_H_

#include "stdint.h"


/* Internal function for use from `printf'.	*/
char *ultoa_invert (uint32_t val, char *s, uint8_t base);

/* Next flags are to use with `base'. Unused fields are reserved.	*/
#define XTOA_PREFIX	0x0100	/* put prefix for octal or hex	*/
#define XTOA_UPPER	0x0200	/* use upper case letters	*/

#endif	/* _XTOA_FAST_H_ */
