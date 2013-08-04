#ifndef _DEVICE_BCM2835_MINIUART_H
#define _DEVICE_BCM2835_MINIUART_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void uartInit(void);
extern void uartOutput(UnsignedByte ch);

#endif