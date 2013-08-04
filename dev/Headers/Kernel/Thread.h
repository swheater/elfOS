#ifndef _KERNEL_THREAD
#define _KERNEL_THREAD 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/ARM/ThreadControlBlock.h>

extern ThreadControlBlock *currentThreadControlBlock;

extern void               threadsInit(void);
extern void               threadcreate(void (*runFunction)(void), UnsignedByte *stack);
extern void               threadsStart(void);
extern ThreadControlBlock *getCurrentThreadControlBlock(void);
extern void               threadYield(void);
extern void               threadDestroy(ThreadControlBlock *threadControlBlock);

#endif
