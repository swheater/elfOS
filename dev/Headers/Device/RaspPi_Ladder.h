#ifndef _DEVICE_RASPPI_LADDER_H
#define _DEVICE_RASPPI_LADDER_H 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

#define LADDER_SMALLRED_LED   (0)
#define LADDER_SMALLGREEN_LED (1)
#define LADDER_RED_LED_1      (17)
#define LADDER_RED_LED_2      (18)
#define LADDER_YELLOW_LED_1   (21)
#define LADDER_YELLOW_LED_2   (22)
#define LADDER_GREEN_LED_1    (23)
#define LADDER_GREEN_LED_2    (24)
#define LADDER_BLUE_LED_1     (25)
#define LADDER_BLUE_LED_2     (4)
#define LADDER_SWITCH_1       (7)
#define LADDER_SWITCH_2       (8)
#define LADDER_SWITCH_3       (10)
#define LADDER_SWITCH_4       (9)


extern void    ladderInit(void);
extern void    ladderSetLED(UnsignedByte ledNumber, Boolean on);
extern Boolean labberGetSwitch(UnsignedByte switchNumber);
extern void    ladderShutdown(void);

#endif
