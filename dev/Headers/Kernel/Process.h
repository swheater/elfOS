#ifndef _KERNEL_PROCESS
#define _KERNEL_PROCESS 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/ARM/ProcessControlBlock.h>

extern ProcessControlBlock *currentProcessControlBlock;

extern void                initProcesses(void);
extern void                createProcess(void (*runFunction)(void), UnsignedByte *stack);
extern void                startProcesses(void);
extern ProcessControlBlock *getCurrentProcessControlBlock(void);
extern void                yieldProcess(void);
extern void                destroyProcess(ProcessControlBlock *processControlBlock);

#endif
