#ifndef _KERNEL_HANDLERS
#define _KERNEL_HANDLERS 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/Thread.h>

extern void (*undefinedInstructionHandler)(UnsignedWord32* undefinedInstructionAddress);
extern void (*softwareInterruptHandler)(UnsignedWord32 opcode, ThreadControlBlock *threadControlBlock);
extern void (*prefetchAbortHandler)(void);
extern void (*dataAbortHandler)(void);
extern void (*reservedHandler)(void);
extern void (*interruptRequestHandler)(void);
extern void (*fastInterruptRequestHandler)(void);

extern void defaultUndefinedInstructionHandler(UnsignedWord32* undefinedInstructionAddress);
extern void defaultSoftwareInterruptHandler(UnsignedWord32 opcode, ThreadControlBlock *threadControlBlock);
extern void defaultPrefetchAbortHandler(void);
extern void defaultDataAbortHandler(void);
extern void defaultReservedHandler(void);
extern void defaultInterruptRequestHandler(void);
extern void defaultFastInterruptRequestHandler(void);

#endif
