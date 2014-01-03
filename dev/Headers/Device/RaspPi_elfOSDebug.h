#ifndef _DEVICE_RASPPI_ELFOSDEBUG_H
#define _DEVICE_RASPPI_ELFOSDEBUG_H 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

#define ELFOSDEBUG_YELLOW_LED_1 (17)
#define ELFOSDEBUG_YELLOW_LED_2 (18)
// define ELFOSDEBUG_YELLOW_LED_3 (21)
#define ELFOSDEBUG_YELLOW_LED_3 (27)
#define ELFOSDEBUG_YELLOW_LED_4 (22)
#define ELFOSDEBUG_YELLOW_LED_5 (23)
#define ELFOSDEBUG_YELLOW_LED_6 (24)
#define ELFOSDEBUG_GREEN_LED    (25)
#define ELFOSDEBUG_RED_LED      (4)

extern void elfosdebugInit(void);
extern void elfosdebugSetLED(UnsignedByte ledNumber, Boolean on);
extern void elfosdebugShutdown(void);

#endif
