#ifndef __STEP_MOTOR_H__
#define __STEP_MOTOR_H__

#include "stm32f2xx.h"

#define MOTOR_DIR_UP      1
#define MOTOR_DIR_DOWN    0

#define MOTOR_WATER_PUT    0
#define MOTOR_WATER_GET    1

#define MOTOR_WATER_01ML   194

extern int stepmotor_init(void);
extern void stepmotor_run(int dir, int step);
extern void relay_ctrl(int ctrl);


#endif