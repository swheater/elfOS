/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Boot/ARM/BootHandlerVectors.h>

void boot_bootHandlerSetup(void)
{
    // Set Vector Base Address
    asm("mcr\tp15, 0, %0, c12, c0, 0": : "r" (&boot_handlerVectors));
}
