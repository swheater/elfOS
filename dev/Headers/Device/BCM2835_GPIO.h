#ifndef _DEVICE_BCM2835_GPIO_H
#define _DEVICE_BCM2835_GPIO_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

#define GPIO_FUNCSELECT_INPUT    (0x00)
#define GPIO_FUNCSELECT_OUTPUT   (0x01)
#define GPIO_FUNCSELECT_ALTFUNC0 (0x04)
#define GPIO_FUNCSELECT_ALTFUNC1 (0x05)
#define GPIO_FUNCSELECT_ALTFUNC2 (0x06)
#define GPIO_FUNCSELECT_ALTFUNC3 (0x07)
#define GPIO_FUNCSELECT_ALTFUNC4 (0x03)
#define GPIO_FUNCSELECT_ALTFUNC5 (0x02)

#define GPIO_PULL_OFF  (0x00)
#define GPIO_PULL_DOWN (0x01)
#define GPIO_PULL_UP   (0x02)

extern void    gpioInit(void);
extern void    gpioFuncSelect(UnsignedByte gpioIndex, UnsignedByte funcSelect);
extern void    gpioSetPullControl(UnsignedByte gpioIndex, UnsignedByte pullControl);
extern Boolean gpioGetInput(UnsignedByte gpioIndex);
extern void    gpioSetOutput(UnsignedByte gpioIndex);
extern void    gpioClearOutput(UnsignedByte gpioIndex);
extern void    gpioShutdown(void);

#endif
