/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/Kernel.h>
#include <Kernel/Logging.h>
#include <Kernel/ARMv6/MemoryManagement.h>

#define INVALID_L1DESCTYPE (0x0)
#define PAGE_L1DESCTYPE    (0x1)
#define SECTION_L1DESCTYPE (0x2)

#define NOACCESS_ACCESSCONTROL  (0x1 << 10)
#define READONLY_ACCESSCONTROL  (0x2 << 10)
#define READWRITE_ACCESSCONTROL (0x3 << 10)

#define TRANSLATIONTABLE_BOUNDARYSIZE  (0x1)
#define KERNEL_TRANSLATIONTABLESIZE    (32)
#define CONTAINER_TRANSLATIONTABLESIZE (2048)

extern UnsignedWord32 kernelTranslationTable[KERNEL_TRANSLATIONTABLESIZE];
extern UnsignedWord32 containerTranslationTable[CONTAINER_TRANSLATIONTABLESIZE];

void kernelARMv6_initKernelTranslationTable(UnsignedWord32 *kernelTranslationTable)
{
    logMessage("initKernelTranslationTable: kernelTranslationTable=");
    logUnsignedWord32Hex((UnsignedWord32) kernelTranslationTable);
    logMessage("\r\n");
    // Set-up virtual memory to match physical memory (if 256MB)
    int index;
    for (index = 0; index < KERNEL_TRANSLATIONTABLESIZE; index++)
        kernelTranslationTable[index] = (index << 20) | READWRITE_ACCESSCONTROL | SECTION_L1DESCTYPE;
}

void kernelARMv6_initContainerTranslationTable(UnsignedWord32 *containerTranslationTable)
{
    logMessage("containerKernelTranslationTable: containerTranslationTable=");
    logUnsignedWord32Hex((UnsignedWord32) containerTranslationTable);
    logMessage("\r\n");
    int index;
    for (index = 0; index < CONTAINER_TRANSLATIONTABLESIZE; index++)
        containerTranslationTable[index] = (index << 20) | READWRITE_ACCESSCONTROL | SECTION_L1DESCTYPE;
}

void kernelARMv6_setKernelTranslationTable(UnsignedWord32 *kernelTranslationTable)
{
    logMessage("Set Translation Table Base Register 1, Kernel\r\n");
    // Set Translation Table Base Register 1, Kernel
    asm("mcr\tp15, 0, %0, c2, c0, 1": : "r" (kernelTranslationTable));
}

void kernelARMv6_setContainerTranslationTable(UnsignedWord32 *containerTranslationTable)
{
    logMessage("Set Translation Table Base Register 0, Container\r\n");
    // Set Translation Table Base Register 0, Container
    asm("mcr\tp15, 0, %0, c2, c0, 0": : "r" (containerTranslationTable));
}

void kernelARMv6_enableMemoryManagement(void)
{
    logMessage("Disable Instruction and Data Caching\r\n");
    // Disable Instruction and Data Caching
    asm("mrc\tp15, 0, r0, c1, c0, 0\n\t"
        "bic\tr0, r0, #0x00000004\n\t"
        "bic\tr0, r0, #0x00001000\n\t"
        "mcr\tp15, 0, r0, c1, c0, 0": : : "r0");

    logMessage("Invalidate Instruction and Data Cache\r\n");
    // Invalidate Instruction and Data Cache
    asm("mcr\tp15, 0, %0, c7, c7, 0": : "r" (0));

    logMessage("Invalidate Translation Look-aside Buffer\r\n");
    // Invalidate Translation Look-aside Buffer
    asm("mcr\tp15, 0, %0, c5, c0, 0": : "r" (0));

    logMessage("Enable Memory Management Unit\r\n");
    // Enable Memory Management Unit
    asm("mrc\tp15, 0, r0, c1, c0, 0\n\t"
        "orr\tr0, r0, #0x00000001\n\t"
        "mcr\tp15, 0, r0, c1, c0, 0": : : "r0");

    logMessage("Enable Instruction and Data Caching\r\n");
    // Enable Instruction and Data Caching
    asm("mrc\tp15, 0, r0, c1, c0, 0\n\t"
        "orr\tr0, r0, #0x00000004\n\t"
        "orr\tr0, r0, #0x00001000\n\t"
        "mcr\tp15, 0, r0, c1, c0, 0": : : "r0");
}

void kernelARMv6_disableMemoryManagement(void)
{
    logMessage("Disable Instruction and Data Caching\r\n");
    // Disable Instruction and Data Caching
    asm("mrc\tp15, 0, r0, c1, c0, 0\n\t"
        "bic\tr0, r0, #0x00000004\n\t"
        "bic\tr0, r0, #0x00001000\n\t"
        "mcr\tp15, 0, r0, c1, c0, 0": : : "r0");

    logMessage("Invalidate Instruction and Data Cache\r\n");
    // Invalidate Instruction and Data Cache
    asm("mcr\tp15, 0, %0, c7, c7, 0": : "r" (0));

    logMessage("Disable Memory Management Unit\r\n");
    // Disable Memory Management Unit
    asm("mrc\tp15, 0, r0, c1, c0, 0\n\t"
        "bic\tr0, r0, #0x00000001\n\t"
        "mcr\tp15, 0, r0, c1, c0, 0": : : "r0");

    logMessage("Invalidate Translation Look-aside Buffer\r\n");
    // Invalidate Translation Look-aside Buffer
    asm("mcr\tp15, 0, %0, c5, c0, 0": : "r" (0));

    logMessage("Enable Instruction and Data Caching\r\n");
    // Enable Instruction and Data Caching
    asm("mrc\tp15, 0, r0, c1, c0, 0\n\t"
        "orr\tr0, r0, #0x00000004\n\t"
        "orr\tr0, r0, #0x00001000\n\t"
        "mcr\tp15, 0, r0, c1, c0, 0": : : "r0");
}

void kernelARMv6_init(void)
{
    logMessage("Set-up Domain Access Control Register\r\n");
    // Set-up Domain Access Control Register
    UnsignedWord32 domainAccessControl = 0xFFFFFFFF;
    asm("mcr\tp15, 0, %0, c3, c0, 0": : "r" (domainAccessControl));

    logMessage("Set-up Translation Table Base Control Register\r\n");
    // Set-up Translation Table Base Control Register
    UnsignedWord32 translationTableBaseControl = TRANSLATIONTABLE_BOUNDARYSIZE;
    asm("mcr\tp15, 0, %0, c2, c0, 2": : "r" (translationTableBaseControl));

    kernelARMv6_initKernelTranslationTable(kernelTranslationTable);
    kernelARMv6_initContainerTranslationTable(containerTranslationTable);
    kernelARMv6_setKernelTranslationTable(kernelTranslationTable);
    kernelARMv6_setContainerTranslationTable(containerTranslationTable);
    kernelARMv6_enableMemoryManagement();
}
