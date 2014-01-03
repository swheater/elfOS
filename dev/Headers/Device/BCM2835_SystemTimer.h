#ifndef _DEVICE_BCM2835_SYSTEMTIMER_H
#define _DEVICE_BCM2835_SYSTEMTIMER_H 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void           systemtimerInit();
extern UnsignedWord64 systemtimerGetCounterValue(void);
extern void           systemtimerSetCompareValue(UnsignedByte comparitor, UnsignedWord32 compareValue);
extern Boolean        systemtimerTestComparitorMatch(UnsignedByte comparitor);
extern void           systemtimerClearComparitorMatch(UnsignedByte comparitor);
extern void           systemtimerWait(UnsignedWord64 microSecondDelay);
extern void           systemtimerWaitUntil(UnsignedWord64 microSecondCounterValue);
extern void           systemtimerShutdown(void);

extern void systemtimerDebug(void);

#endif
