/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/Kernel.h>
#include <Kernel/VirtualMemory.h>
#include <ELF/ELF32.h>

extern char _elf32Appl;

static int res = -1;

void kernel_init()
{
    const char* elf32 = &_elf32Appl;

    ELF32Header        *header                           = (ELF32Header*) elf32;
    ELF32SectionHeader *sectionHeaders                   = (ELF32SectionHeader*) &(elf32[header->sectionHeaderOffset]);
    unsigned int       numberOfSectionHeaders            = header->sectionHeaderEntryNumber;
    unsigned int       numberOfVirtualMemorySegmentInfos = elf32_numberOfVirtualMemorySegmentInfos(sectionHeaders, numberOfSectionHeaders);

    VirtualMemorySegmentInfo virtualMemorySegmentInfos[numberOfVirtualMemorySegmentInfos];

    elf32_extractVirtualMemorySegmentInfos(sectionHeaders, numberOfSectionHeaders, virtualMemorySegmentInfos, &numberOfVirtualMemorySegmentInfos);

    unsigned int         numberOfSegments = numberOfVirtualMemorySegmentInfos;
    VirtualMemorySegment segments[numberOfSegments];

    int segmentIndex;
    for (segmentIndex = 0; segmentIndex < numberOfSegments; segmentIndex++)
    {
        segments[segmentIndex].physicalAddress = (UnsignedByte*) (segmentIndex * 0x10000) + 0x40000;
        segments[segmentIndex].virtualAddress  = (UnsignedByte*) (segmentIndex * 0x10000) + 0x40000;
    }

    if (elf32_segmentsInitialize(elf32, sectionHeaders, numberOfSectionHeaders, segments, numberOfSegments))
    {
        res = 0x09;

        void (*runFunction)(void) = elf32_findFunction("run", elf32, sectionHeaders, numberOfSectionHeaders, segments, numberOfSegments);

        if (runFunction != 0)
	{
            res = 0x19;
            (*runFunction)();
            res = 0x29;
	}
        else
            res = 0x39;
    }
    else
        res = 0x49;
}
