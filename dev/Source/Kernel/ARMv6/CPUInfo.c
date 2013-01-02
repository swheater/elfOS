/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/ARMv6/CPUInfo.h>

UnsignedWord32 kernelARMv6_cpuInfo(void)
{
    UnsignedWord32 cpuInfo;

    // Put CPU ID into R1
    asm("mrc\tp15, 0, %0, c0, c0, 0": "=r" (cpuInfo));

    return cpuInfo;
}
