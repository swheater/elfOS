#ifndef _KERNEL_VIRTUALMEMORY
#define _KERNEL_VIRTUALMEMORY 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

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

#endif
