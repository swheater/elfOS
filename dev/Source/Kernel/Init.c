/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/Kernel.h>
#include <Kernel/VirtualMemory.h>
#include <Kernel/Symbol.h>
#include <Kernel/Process.h>
#include <Kernel/Handlers.h>
#include <ELF/ELF32.h>
#include <elfOS/Process.h>

extern char zeroPageStart;
extern char zeroPageEnd;
extern char elf32Appl;

static int res = -1;

static void swHandler(UnsignedWord32 operand)
{
    res = 0xff00ff00 + operand;
}

void kernel_init()
{
    char *zeroPageSource = &zeroPageStart;
    char *zeroPageDestination = 0x0;
    while (zeroPageSource < &zeroPageEnd)
        *zeroPageDestination++ = *zeroPageSource++;

    softwareInterruptHandler = &swHandler;

    initProcesses();

    const char* elf32 = &elf32Appl;

    ELF32Header        *header                           = (ELF32Header*) elf32;
    ELF32SectionHeader *sectionHeaders                   = (ELF32SectionHeader*) &(elf32[header->sectionHeaderOffset]);
    unsigned int       numberOfSectionHeaders            = header->sectionHeaderEntryNumber;
    unsigned int       numberOfVirtualMemorySegmentInfos = elf32_numberOfVirtualMemorySegmentInfos(sectionHeaders, numberOfSectionHeaders);

    VirtualMemorySegmentInfo virtualMemorySegmentInfos[numberOfVirtualMemorySegmentInfos];

    elf32_extractVirtualMemorySegmentInfos(sectionHeaders, numberOfSectionHeaders, virtualMemorySegmentInfos, &numberOfVirtualMemorySegmentInfos);

    unsigned int numberOfGlobalSymbols = 2;
    Symbol       globalSymbols[numberOfGlobalSymbols];
    globalSymbols[0].name  = "elfOS_processYield";
    globalSymbols[0].value = (UnsignedWord32) elfOS_processYield;
    globalSymbols[1].name  = "elfOS_processStop";
    globalSymbols[1].value = (UnsignedWord32) elfOS_processStop;

    unsigned int         numberOfSegments = numberOfVirtualMemorySegmentInfos;
    VirtualMemorySegment segments[numberOfSegments];

    int segmentIndex;
    for (segmentIndex = 0; segmentIndex < numberOfSegments; segmentIndex++)
    {
        segments[segmentIndex].physicalAddress = (UnsignedByte*) (segmentIndex * 0x10000) + 0x80000;
        segments[segmentIndex].virtualAddress  = (UnsignedByte*) (segmentIndex * 0x10000) + 0x80000;
    }

    if (elf32_segmentsInitialize(elf32, sectionHeaders, numberOfSectionHeaders, globalSymbols, numberOfGlobalSymbols, segments, numberOfSegments))
    {
        res = 0x09;

        void (*runFunction)(void) = elf32_findFunction("run", elf32, sectionHeaders, numberOfSectionHeaders, segments, numberOfSegments);

        if (runFunction != 0)
	{
            res = 0x19;
            currentProcessControlBlock = createProcess(runFunction, (UnsignedByte*) 0x100000);
            continueProcess(currentProcessControlBlock);
            res = 0x29;
	}
        else
            res = 0x39;
    }
    else
        res = 0x49;
}
