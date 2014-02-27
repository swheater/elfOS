#ifndef _KERNEL_VIRTUALMEMORY
#define _KERNEL_VIRTUALMEMORY 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

#define INVALID_L1DESCTYPE (0x00000000)
#define PAGE_L1DESCTYPE    (0x00000001)
#define SECTION_L1DESCTYPE (0x00000002)

#define NONSECURE_L1DESCPERM (0x00000000)
#define SECURE_L1DESCPERM    (0x00000008)

#define D00_L1DESCDOMAIN    (0x00000000)

#define TRANSLATIONTABLE_BOUNDARYSIZE  (0x2)
#define CONTAINER_TRANSLATIONTABLESIZE (1024)
#define KERNEL_TRANSLATIONTABLESIZE    (4096)

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

extern void boot_virtualMemorySetup(void);

extern UnsignedWord32 phyDevice200PageTable[PAGETABLESIZE];
extern UnsignedWord32 phyDevice202PageTable[PAGETABLESIZE];
extern UnsignedWord32 phyDevice208PageTable[PAGETABLESIZE];

#endif
