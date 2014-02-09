/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Boot/ARM/KernelHandlerVectors.h>

void boot_kernelHandlerSetup(void)
{
    // Set Vector Base Address
    asm("mcr\tp15, 0, %0, c12, c0, 0": : "r" (&kernel_handlerVectors));

    // Enable interrupts
    asm("mrs\tr0, cpsr\n\t"
        "bic\tr0, r0, #0x000000C0\n\t"
        "msr\tcpsr_csfx, r0": : : "r0");
}
