#ifndef _KERNEL_MEMORYDOMAINS
#define _KERNEL_MEMORYDOMAINS 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

typedef struct
{
    UnsignedWord32 size;
    SignedByte     writeable;
    SignedByte     executable;
} MemoryDomainInfo;

#endif
