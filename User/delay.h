#ifndef __DELAY_H
#define __DELAY_H 		

#include "sys.h"  



#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

void delay_init(void);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
uint32_t micros(void);
uint32_t millis(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif





























