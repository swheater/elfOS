#ifndef _KERNEL_HANDLERS
#define _KERNEL_HANDLERS 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/Handlers.h>

void (*resetHandler)(void);
void (*undefinedInstructionHandler)(void);
void (*softwareInterruptHandler)(UnsignedWord32 operand);
void (*prefetchAbortHandler)(void);
void (*dataAbortHandler)(void);
void (*reservedHandler)(void);
void (*interruptRequestHandler)(void);
void (*fastInterruptRequestHandler)(void);

#endif
