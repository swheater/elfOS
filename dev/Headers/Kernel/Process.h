#ifndef _KERNEL_PROCESS
#define _KERNEL_PROCESS 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/ARM/ProcessControlBlock.h>

extern void processInit(void);
extern void processCreate(void);
extern void processShutdown(void);

#endif
