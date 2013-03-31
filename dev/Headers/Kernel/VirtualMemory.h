#ifndef _KERNEL_VIRTUALMEMORY
#define _KERNEL_VIRTUALMEMORY 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

#define INVALID_L1DESCTYPE (0x0)
#define PAGE_L1DESCTYPE    (0x1)
#define SECTION_L1DESCTYPE (0x2)

#define TRANSLATIONTABLE_BOUNDARYSIZE  (0x1)
#define CONTAINER_TRANSLATIONTABLESIZE (2048)
#define KERNEL_TRANSLATIONTABLESIZE    (2048)

#define PAGETABLESIZE (256)
#define PAGESIZE      (4096)

typedef struct
{
    UnsignedWord32 size;
    Boolean        writable;
    Boolean        executable;
} VirtualMemorySegmentInfo;

typedef struct
{
    UnsignedByte  *physicalAddress;
    UnsignedByte  *virtualAddress;
    UnsignedWord32 size;
} VirtualMemorySegment;

extern UnsignedWord32 kernel_containerTranslationTable[CONTAINER_TRANSLATIONTABLESIZE];
extern UnsignedWord32 kernel_kernelTranslationTable[KERNEL_TRANSLATIONTABLESIZE];
extern UnsignedWord32 kernel_containerPageTable[PAGETABLESIZE];
extern UnsignedWord32 kernel_kernelPageTable[PAGETABLESIZE];
extern UnsignedWord32 kernel_devicePageTable[PAGETABLESIZE];

extern UnsignedWord32 *kernel_phyContainerTranslationTable;
extern UnsignedWord32 *kernel_phyKernelTranslationTable;

extern UnsignedWord32 *kernel_phyContainerPageTable;
extern UnsignedWord32 *kernel_phyKernelPageTable;
extern UnsignedWord32 *kernel_phyDevicePageTable;

extern void kernel_boot_virtualMemorySetup(void);

#endif
