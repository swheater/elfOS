#ifndef _DEVICE_BCM2835_PWM_H
#define _DEVICE_BCM2835_PWM_H 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void pwmInit(void);
extern void pwmSetRange(UnsignedByte servoNumber, UnsignedWord32 range);
extern void pwmSetMark(UnsignedByte servoNumber, UnsignedWord32 mark);
extern void pwmShutdown(void);

#endif
