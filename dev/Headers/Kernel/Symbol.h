#ifndef _KERNEL_SYMBOL
#define _KERNEL_SYMBOL 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

typedef struct
{
    SignedByte     *name;
    UnsignedWord32 value;
} Symbol;

#endif
