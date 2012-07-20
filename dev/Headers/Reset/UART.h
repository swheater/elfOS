#ifndef _RESET_UART_H
#define _RESET_UART_H 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void resetUARTInit(void);
extern void resetUARTOutput(UnsignedByte ch);

#endif
