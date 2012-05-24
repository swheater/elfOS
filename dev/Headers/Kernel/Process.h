#ifndef _KERNEL_PROCESS
#define _KERNEL_PROCESS 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/ARM/ProcessControlBlock.h>

extern ProcessControlBlock *currentProcessControlBlock;

extern void                initProcesses(void);
extern ProcessControlBlock *createProcess(void (*runFunction)(void), UnsignedByte *stack);
extern void                continueProcess(ProcessControlBlock *processControlBlock);
extern void                destroyProcess(ProcessControlBlock *processControlBlock);

#endif
