#ifndef _DEVICE_BCM2835_TIMER_H
#define _DEVICE_BCM2835_TIMER_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void timerInit(UnsignedWord16 predivide, UnsignedWord32 load, Boolean enabled);
extern void timerEnable(void); 
extern void timerDisable(void);
extern void timerClearInterruptRequest(void);

extern void timerDebug(void);

#endif
