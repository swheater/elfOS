#ifndef _KERNEL_PROCESSCONTROLBLOCK
#define _KERNEL_PROCESSCONTROLBLOCK 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

typedef enum { USED, FREE } BlockStatus;

typedef struct
{
    UnsignedWord32 r1;
    UnsignedWord32 r2;
    UnsignedWord32 r3;
    UnsignedWord32 r4;
    UnsignedWord32 r5;
    UnsignedWord32 r6;
    UnsignedWord32 r7;
    UnsignedWord32 r8;
    UnsignedWord32 r9;
    UnsignedWord32 r10;
    UnsignedWord32 r11;
    UnsignedWord32 r12;
    UnsignedWord32 sp;
    UnsignedWord32 lr;
    UnsignedWord32 r0;
    UnsignedWord32 pc;
    UnsignedWord32 cpsr;

    BlockStatus blockStatus;
} ProcessControlBlock;

#endif
