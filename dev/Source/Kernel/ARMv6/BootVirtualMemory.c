/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/Kernel.h>
#include <Kernel/VirtualMemory.h>
#include <Device/RaspPi_UART.h>
#include <Kernel/KDebug.h>
#include <Kernel/Logging.h>

extern char kernel_zeroPagePhyStart;
extern char kernel_zeroPagePhyEnd;
extern char kernel_bssSectionStart;
extern char kernel_bssSectionEnd;

static UnsignedWord32 kernel_phyContainerTranslationTable[CONTAINER_TRANSLATIONTABLESIZE] __attribute__((aligned(0x1000)));
static UnsignedWord32 kernel_phyKernelTranslationTable[CONTAINER_TRANSLATIONTABLESIZE] __attribute__((aligned(0x1000)));

static UnsignedWord32 kernel_phyContainerPageTable[PAGETABLESIZE] __attribute__((aligned(0x1000)));
static UnsignedWord32 kernel_phyDevicePageTable[PAGETABLESIZE] __attribute__((aligned(0x1000)));
static UnsignedWord32 kernel_phyKernelPageTable[PAGETABLESIZE] __attribute__((aligned(0x1000)));

void kernel_boot_virtualMemorySetup(void)
{
    uartInit();

    // Copy Zero Page code to Zero Page
    char *zeroPageDestinationAddress = 0;
    char *zeroPageSourceAddress      = &kernel_zeroPagePhyStart;
    while (zeroPageSourceAddress < &kernel_zeroPagePhyEnd)
        *zeroPageDestinationAddress++ = *zeroPageSourceAddress++;

    // Set-up Domain Access Control Register, all client (Accesses are checked against access permissions)
    UnsignedWord32 domainAccessControl = 0x55555555;
    asm("mcr\tp15, 0, %0, c3, c0, 0": : "r" (domainAccessControl));

    // Set-up Translation Table Base Control Register
    UnsignedWord32 translationTableBaseControl = TRANSLATIONTABLE_BOUNDARYSIZE;
    asm("mcr\tp15, 0, %0, c2, c0, 2": : "r" (translationTableBaseControl));

    // Set-up container virtual memory
    int index;
    for (index = 0; index < CONTAINER_TRANSLATIONTABLESIZE; index++)
        kernel_phyContainerTranslationTable[index] = INVALID_L1DESCTYPE;

    for (index = 0; index < PAGETABLESIZE; index++)
        kernel_phyContainerPageTable[index] = (0x00000000 & 0xFFFFF000) | (index << 12) | 0x032;

    for (index = 0; index < PAGETABLESIZE; index++)
        kernel_phyDevicePageTable[index] = (0x20200000 & 0xFFFFF000) | (index << 12) | 0x032;

    kernel_phyContainerTranslationTable[0x000] = (((unsigned int) kernel_phyContainerPageTable) & 0xFFFFFFC0) | D00_L1DESCDOMAIN | NONSECURE_L1DESCPERM | PAGE_L1DESCTYPE;
    kernel_phyContainerTranslationTable[0x202] = (((unsigned int) kernel_phyDevicePageTable) & 0xFFFFFFC0) | D00_L1DESCDOMAIN | NONSECURE_L1DESCPERM | PAGE_L1DESCTYPE;

    asm("mcr\tp15, 0, %0, c2, c0, 0": : "r" (kernel_phyContainerTranslationTable));

    // Set-up kernel virtual memory
    for (index = 0; index < KERNEL_TRANSLATIONTABLESIZE; index++)
        kernel_phyKernelTranslationTable[index] = INVALID_L1DESCTYPE;

    for (index = 0; index < PAGETABLESIZE; index++)
        kernel_phyKernelPageTable[index] = (0x80000000 & 0xFFFFF000) | (index << 12) | 0x032;

    kernel_phyKernelTranslationTable[0x000] = (((unsigned int) kernel_phyKernelPageTable) & 0xFFFFFFC0) | D00_L1DESCDOMAIN | SECURE_L1DESCPERM | PAGE_L1DESCTYPE;

    asm("mcr\tp15, 0, %0, c2, c0, 1": : "r" (kernel_phyKernelTranslationTable));

    // Disable Instruction and Data Caching
    asm("mrc\tp15, 0, r0, c1, c0, 0\n\t"
        "bic\tr0, r0, #0x00000004\n\t"
        "bic\tr0, r0, #0x00001000\n\t"
        "mcr\tp15, 0, r0, c1, c0, 0": : : "r0");

    // Invalidate Instruction and Data Cache
    asm("mcr\tp15, 0, %0, c7, c7, 0": : "r" (0));

    // Invalidate Translation Look-aside Buffer
    asm("mcr\tp15, 0, %0, c8, c7, 0": : "r" (0));

    // Enable Memory Management Unit
    asm("mrc\tp15, 0, r0, c1, c0, 0\n\t"
        "orr\tr0, r0, #0x00000001\n\t"
        "orr\tr0, r0, #0x00800000\n\t"
        "mcr\tp15, 0, r0, c1, c0, 0": : : "r0");

    // Enable Instruction and Data Caching
    asm("mrc\tp15, 0, r0, c1, c0, 0\n\t"
        "orr\tr0, r0, #0x00000004\n\t"
        "orr\tr0, r0, #0x00001000\n\t"
        "mcr\tp15, 0, r0, c1, c0, 0": : : "r0");

    char *bssSectionAddress = &kernel_bssSectionStart;
    while (bssSectionAddress < &kernel_bssSectionEnd)
        *bssSectionAddress++ = 0;

    kDebugCPUState();
    logMessage("\r\n");

    kDebugMemoryManagement();
    logMessage("\r\n");

    while (1);
}
