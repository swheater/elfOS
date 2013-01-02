/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/Kernel.h>
#include <Kernel/VirtualMemory.h>

void kernel_boot_virtualMemorySetup(void)
{
    // Set-up Domain Access Control Register
    UnsignedWord32 domainAccessControl = 0xFFFFFFFF;
    asm("mcr\tp15, 0, %0, c3, c0, 0": : "r" (domainAccessControl));

    // Set-up Translation Table Base Control Register
    UnsignedWord32 translationTableBaseControl = TRANSLATIONTABLE_BOUNDARYSIZE;
    asm("mcr\tp15, 0, %0, c2, c0, 2": : "r" (translationTableBaseControl));

    int index;

    // Set-up container virtual memory
    for (index = 0; index < CONTAINER_TRANSLATIONTABLESIZE; index++)
        kernel_containerTranslationTable[index] = (index << 20) | READWRITE_ACCESSCONTROL | SECTION_L1DESCTYPE;

    asm("mcr\tp15, 0, %0, c2, c0, 0": : "r" (kernel_containerTranslationTable));

    // Set-up kernel virtual memory
    for (index = 0; index < KERNEL_TRANSLATIONTABLESIZE; index++)
        kernel_kernelTranslationTable[index] = (index << 20) | READWRITE_ACCESSCONTROL | SECTION_L1DESCTYPE;

    asm("mcr\tp15, 0, %0, c2, c0, 1": : "r" (kernel_kernelTranslationTable));

    // Disable Instruction and Data Caching
    asm("mrc\tp15, 0, r0, c1, c0, 0\n\t"
        "bic\tr0, r0, #0x00000004\n\t"
        "bic\tr0, r0, #0x00001000\n\t"
        "mcr\tp15, 0, r0, c1, c0, 0": : : "r0");

    // Invalidate Instruction and Data Cache
    asm("mcr\tp15, 0, %0, c7, c7, 0": : "r" (0));

    // Invalidate Translation Look-aside Buffer
    asm("mcr\tp15, 0, %0, c5, c0, 0": : "r" (0));

    // Enable Memory Management Unit
    asm("mrc\tp15, 0, r0, c1, c0, 0\n\t"
        "orr\tr0, r0, #0x00000001\n\t"
        "mcr\tp15, 0, r0, c1, c0, 0": : : "r0");

    // Enable Instruction and Data Caching
    asm("mrc\tp15, 0, r0, c1, c0, 0\n\t"
        "orr\tr0, r0, #0x00000004\n\t"
        "orr\tr0, r0, #0x00001000\n\t"
        "mcr\tp15, 0, r0, c1, c0, 0": : : "r0");
}
