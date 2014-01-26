#ifndef _KERNEL_PAGEMEMORY
#define _KERNEL_PAGEMEMORY 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

#define PAGEMAPSIZE (16384)
#define PAGESIZE    (4096)

extern void           kernel_pageMemoryInit(void);
extern UnsignedWord32 kernel_pageMemorySingleAcquirePage(void);
extern UnsignedWord32 kernel_pageMemoryAcquireDualPage(void);
extern UnsignedWord32 kernel_pageMemoryAcquireQuadPage(void);
extern UnsignedWord32 kernel_pageMemoryAcquireOctPage(void);
extern void           kernel_pageMemorySinglePageRelease(UnsignedWord32 pageAddress);
extern void           kernel_pageMemoryDualPageRelease(UnsignedWord32 pageAddress);
extern void           kernel_pageMemoryQuadPageRelease(UnsignedWord32 pageAddress);
extern void           kernel_pageMemoryOctPageRelease(UnsignedWord32 pageAddress);
extern void           kernel_pageMemoryShutdown(void);

#endif
