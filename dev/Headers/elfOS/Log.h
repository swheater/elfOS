#ifndef _ELFOS_LOG
#define _ELFOS_LOG 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void elfOS_logUnsignedWord32Hex(UnsignedWord32 unsignedWord32);
extern void elfOS_logMessage(const char *message);

#endif
