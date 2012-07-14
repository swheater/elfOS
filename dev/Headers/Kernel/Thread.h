#ifndef _KERNEL_THREAD
#define _KERNEL_THREAD 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/ARM/ThreadControlBlock.h>

extern ThreadControlBlock *currentThreadControlBlock;

extern void               initThreads(void);
extern void               createThread(void (*runFunction)(void), UnsignedByte *stack);
extern void               startThreads(void);
extern ThreadControlBlock *getCurrentThreadControlBlock(void);
extern void               yieldThread(void);
extern void               destroyThread(ThreadControlBlock *threadControlBlock);

#endif
