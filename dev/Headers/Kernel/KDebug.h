#ifndef _KERNEL_KDEBUG
#define _KERNEL_KDEBUG 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/VirtualMemory.h>

extern void kDebugCPUState(void);
extern void kDebugCurrentThread(void);
extern void kDebugVirtualMemorySegments(VirtualMemorySegment virtualMemorySegments[], unsigned int numberOfVirtualMemorySegments);
extern void kDebugVirtualMemorySegment(VirtualMemorySegment* virtualMemorySegment);
extern void kDebugHandlers(void);

#endif
