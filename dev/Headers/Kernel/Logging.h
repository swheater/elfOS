#ifndef _KERNEL_LOGGING
#define _KERNEL_LOGGING 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void logUnsignedWord32Hex(UnsignedWord32 unsignedWord32);
extern void logMessage(const char *message);

#endif
