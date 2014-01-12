#ifndef _KERNEL_PAGEMEMORY
#define _KERNEL_PAGEMEMORY 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

#define PAGEMAPSIZE (16384)
#define PAGESIZE    (4096)

extern void           kernel_pageMemorySetup(void);
extern UnsignedWord32 kernel_pageMemoryAcquire(void);
extern void           kernel_pageMemoryRelease(UnsignedWord32 pageAddress);

#endif
