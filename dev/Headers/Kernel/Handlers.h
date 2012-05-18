#ifndef _KERNEL_HANDLERS
#define _KERNEL_HANDLERS 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void (*resetHandler)(void);
extern void (*undefinedInstructionHandler)(void);
extern void (*softwareInterruptHandler)(UnsignedWord32 operand);
extern void (*prefetchAbortHandler)(void);
extern void (*dataAbortHandler)(void);
extern void (*reservedHandler)(void);
extern void (*interruptRequestHandler)(void);
extern void (*fastInterruptRequestHandler)(void);

#endif
