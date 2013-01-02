#ifndef _DEVICE_RASPPI_GPIO_H
#define _DEVICE_RASPPI_GPIO_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

extern void gpioInit(void);
extern void gpioSetOutput(int gpioIndex);
extern void gpioClearOutput(int gpioIndex);

#endif
