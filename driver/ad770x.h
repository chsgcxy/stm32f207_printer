#ifndef __AD770X_H__
#define __AD770X_H__

#include "stm32f2xx.h"

extern int ad770x_init(void);
extern int ad770x_read_val(u16 *val);
extern void ad7705_test(void);

#endif



















