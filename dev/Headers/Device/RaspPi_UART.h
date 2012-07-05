#ifndef _DEVICE_RASPPI_UART_H
#define _DEVICE_RASPPI_UART_H 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void uartInit(void);
extern void uartOutput(UnsignedByte ch);

#endif
