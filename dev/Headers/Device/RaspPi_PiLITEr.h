#ifndef _DEVICE_RASPPI_PILITER_H
#define _DEVICE_RASPPI_PILITER_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

#define PILITER_LED_0 (4)
#define PILITER_LED_1 (17)
#define PILITER_LED_2 (21)
#define PILITER_LED_3 (18)
#define PILITER_LED_4 (22)
#define PILITER_LED_5 (23)
#define PILITER_LED_6 (24)
#define PILITER_LED_7 (25)

extern void piliterInit(void);
extern void piliterSetLED(UnsignedByte ledNumber, Boolean on);
extern void piliterShutdown(void);

#endif
