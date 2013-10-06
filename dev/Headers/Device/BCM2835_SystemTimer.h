#ifndef _DEVICE_BCM2835_SYSTEMTIMER_H
#define _DEVICE_BCM2835_SYSTEMTIMER_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void           systemtimerInit();
extern UnsignedWord64 systemtimerGetCounterValue(void);
extern void           systemtimerWait(UnsignedWord64 microSecondDelay);
extern void           systemtimerWaitUntil(UnsignedWord64 microSecondCounterValue);

extern void systemtimerDebug(void);

#endif