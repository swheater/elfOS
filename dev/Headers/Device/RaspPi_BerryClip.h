#ifndef _DEVICE_RASPPI_BERRYCLIP_H
#define _DEVICE_RASPPI_BERRYCLIP_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

#define BERRYCLIP_LED_1 (4)
#define BERRYCLIP_LED_2 (17)
#define BERRYCLIP_LED_3 (22)
#define BERRYCLIP_LED_4 (10)
#define BERRYCLIP_LED_5 (9)
#define BERRYCLIP_LED_6 (11)

extern void    berryclipInit(void);
extern void    berryclipSetLED(UnsignedByte ledNumber, Boolean on);
extern void    berryclipSetBuzzer(Boolean on);
extern Boolean berryclipGetSwitch(void);
extern void    berryclipShutdown(void);

#endif
