#ifndef _DEVICE_RASPPI_MOTORPITX_H
#define _DEVICE_RASPPI_MOTORPITX_H 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

#define MOTORPITX_OUTPUT1 (1)
#define MOTORPITX_OUTPUT2 (2)
#define MOTORPITX_INPUT1  (1)
#define MOTORPITX_INPUT2  (2)
#define MOTORPITX_SERVO1  (1)
#define MOTORPITX_SERVO2  (2)

extern void    motorpitxInit(void);
extern void    motorpitxSetReadyLED(Boolean on);
extern void    motorpitxSetOutput(UnsignedByte outputNumber, Boolean on);
extern Boolean motorpitxGetInput(UnsignedByte inputNumber);
extern void    motorpitxSetServo(UnsignedByte servoNumber, UnsignedWord32 mark);
extern void    motorpitxShutdown(void);

#endif
