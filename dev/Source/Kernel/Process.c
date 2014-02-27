/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/Kernel.h>
#include <Kernel/VirtualMemory.h>

void prcoessInit(void)
{
}

void processCreate(void)
{
    UnsignedWord32 *phyTaskTranslationTable = kernel_pageMemorySinglePageAcquire();
    UnsignedWord32 *phyTaskMemory           = kernel_pageMemorySinglePageAcquire();

    // Set-up container virtual memory
    int index;
    for (index = 0; index < CONTAINER_TRANSLATIONTABLESIZE; index++)
        phyTaskTranslationTable[index] = INVALID_L1DESCTYPE;

    phyTaskTranslationTable[0x000] = (((UnsignedWord32) phyTaskMemory) & 0xFFFFFFC0) | D00_L1DESCDOMAIN | NONSECURE_L1DESCPERM | PAGE_L1DESCTYPE;
    phyTaskTranslationTable[0x200] = (((UnsignedWord32) phyDevice200PageTable) & 0xFFFFFFC0) | D00_L1DESCDOMAIN | NONSECURE_L1DESCPERM | PAGE_L1DESCTYPE;
    phyTaskTranslationTable[0x202] = (((UnsignedWord32) phyDevice202PageTable) & 0xFFFFFFC0) | D00_L1DESCDOMAIN | NONSECURE_L1DESCPERM | PAGE_L1DESCTYPE;
    phyTaskTranslationTable[0x208] = (((UnsignedWord32) phyDevice208PageTable) & 0xFFFFFFC0) | D00_L1DESCDOMAIN | NONSECURE_L1DESCPERM | PAGE_L1DESCTYPE;
}

void prcoessShutdown(void)
{
}
