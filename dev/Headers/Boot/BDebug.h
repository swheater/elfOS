#ifndef _BOOT_BDEBUG
#define _BOOT_BDEBUG 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void bDebugInit(void);
extern void bDebugUnsignedWord32Hex(UnsignedWord32 unsignedWord32);
extern void bDebugMessage(const char *message);
extern void bDebugNewLine(void);
extern void bDebugShutdown(void);

#endif
