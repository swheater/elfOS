/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/VirtualMemory.h>
#include <ELF/ELF32.h>
#include <ELF/ELF32_ARM_EABI.h>

unsigned int elf32_numberOfVirtualMemorySegmentInfos(ELF32SectionHeader sectionHeaders[], unsigned int numberOfSectionHeaders)
{
    unsigned int numberOfMemoryDomainInfos = 0;

    unsigned int sectionHeaderIndex;
    for (sectionHeaderIndex = 0; sectionHeaderIndex < numberOfSectionHeaders; sectionHeaderIndex++)
        if (((sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_PROGBITS) || (sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_NOBITS)) && (sectionHeaders[sectionHeaderIndex].flags & ELF32_SECTIONHEADERFLAG_ALLOCATE) && (sectionHeaders[sectionHeaderIndex].size > 0))
            numberOfMemoryDomainInfos++;

    return numberOfMemoryDomainInfos;
}

void elf32_extractVirtualMemorySegmentInfos(ELF32SectionHeader sectionHeaders[], unsigned int numberOfSectionHeaders, VirtualMemorySegmentInfo virtualMemorySegmentInfos[], unsigned int *numberOfVirtualMemorySegmentInfos)
{
    *numberOfVirtualMemorySegmentInfos = 0;

    unsigned int sectionHeaderIndex;
    for (sectionHeaderIndex = 0; sectionHeaderIndex < numberOfSectionHeaders; sectionHeaderIndex++)
        if (((sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_PROGBITS) || (sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_NOBITS)) && (sectionHeaders[sectionHeaderIndex].flags & ELF32_SECTIONHEADERFLAG_ALLOCATE) && (sectionHeaders[sectionHeaderIndex].size > 0))
        {
            virtualMemorySegmentInfos[*numberOfVirtualMemorySegmentInfos].size       = sectionHeaders[sectionHeaderIndex].size;
            virtualMemorySegmentInfos[*numberOfVirtualMemorySegmentInfos].writable   = (sectionHeaders[sectionHeaderIndex].flags & ELF32_SECTIONHEADERFLAG_WRITABLE) ? TRUE: FALSE;
            virtualMemorySegmentInfos[*numberOfVirtualMemorySegmentInfos].executable = (sectionHeaders[sectionHeaderIndex].flags & ELF32_SECTIONHEADERFLAG_EXECUTABLE) ? TRUE: FALSE;
            (*numberOfVirtualMemorySegmentInfos)++;
        }
}

Boolean elf32_segmentsInitialize(const char *elf32, unsigned int elf32Size, const ELF32SectionHeader *sectionHeaders, unsigned int numberOfSectionHeaders, VirtualMemorySegment virtualMemorySegments[], unsigned int numberOfVirtualMemorySegments)
{
    unsigned int sectionIndex = 0;
    unsigned int sectionMapping[numberOfSectionHeaders];

    unsigned int sectionHeaderIndex;
    for (sectionHeaderIndex = 0; sectionHeaderIndex < numberOfSectionHeaders; sectionHeaderIndex++)
        if (((sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_PROGBITS) || (sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_NOBITS)) && (sectionHeaders[sectionHeaderIndex].flags & ELF32_SECTIONHEADERFLAG_ALLOCATE) && (sectionHeaders[sectionHeaderIndex].size > 0))
        {
            if (sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_PROGBITS)
            {
                unsigned int index;
                for (index = 0; index < sectionHeaders[sectionHeaderIndex].size; index++)
                    virtualMemorySegments[sectionIndex].physicalAddress[index] = elf32[sectionHeaders[sectionHeaderIndex].offset + index];
            }
            else if (sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_NOBITS)
            {
                unsigned int index;
                for (index = 0; index < sectionHeaders[sectionHeaderIndex].size; index++)
                    virtualMemorySegments[sectionIndex].physicalAddress[index] = 0;
            }
            sectionMapping[sectionHeaderIndex] = sectionIndex;
            sectionIndex++;
        }
        else
            sectionMapping[sectionHeaderIndex] = 0;

    Boolean valid = TRUE; 
    for (sectionHeaderIndex = 0; sectionHeaderIndex < numberOfSectionHeaders; sectionHeaderIndex++)
        if (sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_REL)
        {
            ELF32SectionHeader sectionHeader = sectionHeaders[sectionHeaderIndex];

            ELF32Rel         *rels           = (ELF32Rel*) &elf32[sectionHeader.offset];
            unsigned int     numberOfRels    = sectionHeader.size / sectionHeader.entrySize;
            unsigned int     segmentIndex    = sectionHeader.info;
            unsigned int     numberOfSymbolValues = sectionHeaders[sectionHeader.link].size / sectionHeaders[sectionHeader.link].entrySize;
            UnsignedWord32   symbolValues[numberOfSymbolValues];
            ELF32SymbolEntry *symbols        = (ELF32SymbolEntry*) &elf32[sectionHeaders[sectionHeader.link].offset];

            unsigned int symbolIndex;
            for (symbolIndex = 0; symbolIndex < numberOfSymbolValues; symbolIndex++)
                if (symbols[symbolIndex].sectionHeaderTableIndex < ELF32_SECTIONHEADERINDEX_LOWRESERVE)
                    symbolValues[symbolIndex] = &(virtualMemorySegments[sectionMapping[symbols[symbolIndex].sectionHeaderTableIndex]].virtualAddress[symbols[symbolIndex].value]);
                else
                    symbolValues[symbolIndex] = 0;

            valid &= elf32_sectionRelocation(virtualMemorySegments[sectionMapping[segmentIndex]], rels, numberOfRels, symbolValues, numberOfSymbolValues);
        }
        else if (sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_RELA)
        {
            ELF32SectionHeader sectionHeader = sectionHeaders[sectionHeaderIndex];

            ELF32RelA        *relAs          = (ELF32RelA*) &elf32[sectionHeader.offset];
            unsigned int     numberOfRelAs   = sectionHeader.size / sectionHeader.entrySize;
            unsigned int     segmentIndex    = sectionHeader.info;
            unsigned int     numberOfSymbolValues = sectionHeaders[sectionHeader.link].size / sectionHeaders[sectionHeader.link].entrySize;
            UnsignedWord32   symbolValues[numberOfSymbolValues];
            ELF32SymbolEntry *symbols        = (ELF32SymbolEntry*) &elf32[sectionHeaders[sectionHeader.link].offset];

            unsigned int symbolIndex;
            for (symbolIndex = 0; symbolIndex < numberOfSymbolValues; symbolIndex++)
                if (symbols[symbolIndex].sectionHeaderTableIndex < ELF32_SECTIONHEADERINDEX_LOWRESERVE)
                    symbolValues[symbolIndex] = &(virtualMemorySegments[sectionMapping[symbols[symbolIndex].sectionHeaderTableIndex]].virtualAddress[symbols[symbolIndex].value]);
                else
                    symbolValues[symbolIndex] = 0;

            valid &= elf32_sectionRelocationA(virtualMemorySegments[sectionMapping[segmentIndex]], relAs, numberOfRelAs, symbolValues, numberOfSymbolValues);
        }

    return valid;
}
