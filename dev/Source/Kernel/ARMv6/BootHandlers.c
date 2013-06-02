/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/ARM/HandlerVectors.h>

extern int kernel_boot_handlerStacksSetup;
extern int kernel_fiqStack;
extern int kernel_irqStack;
extern int kernel_abtStack;
extern int kernel_svcStack;
extern int kernel_undefStack;

void kernel_boot_handlersSetup(void)
{
    kDebugCPUState();
    logMessage("\r\n");

    logMessage("kernel_boot_handlerStacksSetup: ");
    logUnsignedWord32Hex((UnsignedWord32) &kernel_boot_handlerStacksSetup);
    logMessage("\r\nkernel_fiqStack:                ");
    logUnsignedWord32Hex((UnsignedWord32) &kernel_fiqStack);
    logMessage("\r\nkernel_irqStack:                ");
    logUnsignedWord32Hex((UnsignedWord32) &kernel_irqStack);
    logMessage("\r\nkernel_abtStack:                ");
    logUnsignedWord32Hex((UnsignedWord32) &kernel_abtStack);
    logMessage("\r\nkernel_svcStack:                ");
    logUnsignedWord32Hex((UnsignedWord32) &kernel_svcStack);
    logMessage("\r\nkernel_undefStack:              ");
    logUnsignedWord32Hex((UnsignedWord32) &kernel_undefStack);
    logMessage("\r\n");

    volatile int c = 0;
    for (c = 0; c < 1000000; c++) ;

    // Setup Handlers Stacks
    // kernel_boot_handlerStacksSetup();

    // Set Vector Base Address
    asm("mcr\tp15, 0, %0, c12, c0, 0": : "r" (&kernel_handlerVectors));

    // Enable interrupts
    asm("mrs\tr0, cpsr\n\t"
        "bic\tr0, r0, #0x000000C0\n\t"
        "msr\tcpsr_csfx, r0": : : "r0");
}
