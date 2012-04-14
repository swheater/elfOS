/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/MemoryDomains.h>
#include <ELF/ELF32.h>

unsigned int elf_numberOfMemoryDomainInfos(ELF32SectionHeader elf32SectionHeaders[], unsigned int numberOfELF32SectionHeaders)
{
    unsigned int numberOfMemoryDomainInfos = 0;

    unsigned int elf32SectionHeaderIndex;
    for (elf32SectionHeaderIndex = 0; elf32SectionHeaderIndex < numberOfELF32SectionHeaders; elf32SectionHeaderIndex++)
        if (elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_PROGBITS)
            numberOfMemoryDomainInfos++;

    return numberOfMemoryDomainInfos;
}

void elf_extractMemoryDomainInfos(ELF32SectionHeader elf32SectionHeaders[], unsigned int numberOfELF32SectionHeaders, MemoryDomainInfo memoryDomainInfos[], unsigned int *numberOfMemoryDomainInfos)
{
    *numberOfMemoryDomainInfos = 0;

    unsigned int elf32SectionHeaderIndex;
    for (elf32SectionHeaderIndex = 0; elf32SectionHeaderIndex < numberOfELF32SectionHeaders; elf32SectionHeaderIndex++)
        if (((elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_PROGBITS) || (elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_NOBITS)) && (elf32SectionHeaders[elf32SectionHeaderIndex].flags & ELF32_SECTIONHEADERFLAG_ALLOCATE) && (elf32SectionHeaders[elf32SectionHeaderIndex].size > 0))
        {
            memoryDomainInfos[*numberOfMemoryDomainInfos].size       = elf32SectionHeaders[elf32SectionHeaderIndex].size;
            memoryDomainInfos[*numberOfMemoryDomainInfos].writable   = (elf32SectionHeaders[elf32SectionHeaderIndex].flags & ELF32_SECTIONHEADERFLAG_WRITABLE) ? TRUE: FALSE;
            memoryDomainInfos[*numberOfMemoryDomainInfos].executable = (elf32SectionHeaders[elf32SectionHeaderIndex].flags & ELF32_SECTIONHEADERFLAG_EXECUTABLE) ? TRUE: FALSE;
            (*numberOfMemoryDomainInfos)++;
        }
}

void elf_sectionsInitialize(const char *elf32, unsigned int elf32Size, const ELF32SectionHeader *elf32SectionHeaders, unsigned int numberOfELF32SectionHeaders, UnsignedByte *sections[], unsigned int numberOfSections)
{
    unsigned int sectionIndex = 0;
    unsigned int sectionMapping[numberOfELF32SectionHeaders];

    unsigned int elf32SectionHeaderIndex;
    for (elf32SectionHeaderIndex = 0; elf32SectionHeaderIndex < numberOfELF32SectionHeaders; elf32SectionHeaderIndex++)
        if (((elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_PROGBITS) || (elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_NOBITS)) && (elf32SectionHeaders[elf32SectionHeaderIndex].flags & ELF32_SECTIONHEADERFLAG_ALLOCATE) && (elf32SectionHeaders[elf32SectionHeaderIndex].size > 0))
        {
            if (elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_PROGBITS)
            {
                unsigned int index;
                for (index = 0; index < elf32SectionHeaders[elf32SectionHeaderIndex].size; index++)
                    sections[sectionIndex][index] = elf32[elf32SectionHeaders[elf32SectionHeaderIndex].offset + index];
            }
            else if (elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_NOBITS)
            {
                unsigned int index;
                for (index = 0; index < elf32SectionHeaders[elf32SectionHeaderIndex].size; index++)
                    sections[sectionIndex][index] = 0;
            }
            sectionMapping[elf32SectionHeaderIndex] = sectionIndex;
            sectionIndex++;
        }
        else
            sectionMapping[elf32SectionHeaderIndex] = 0;

    for (elf32SectionHeaderIndex = 0; elf32SectionHeaderIndex < numberOfELF32SectionHeaders; elf32SectionHeaderIndex++)
        if (elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_REL)
        {
            ELF32SectionHeader sectionHeader = elf32SectionHeaders[elf32SectionHeaderIndex];

            ELF32Rel         *rels           = (ELF32Rel*) &elf32[sectionHeader.offset];
            unsigned int     numberOfRels    = sectionHeader.size / sectionHeader.entrySize;
            unsigned int     sectionIndex    = sectionHeader.info;
            ELF32SymbolEntry *symbols        = (ELF32SymbolEntry*) &elf32[elf32SectionHeaders[sectionHeader.link].offset];
            unsigned int     numberOfSymbols = elf32SectionHeaders[sectionHeader.link].size / elf32SectionHeaders[sectionHeader.link].entrySize;

            elf_sectionRelocation(sections[sectionMapping[sectionIndex]], rels, numberOfRels, symbols, numberOfSymbols);
        }
        else if (elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_RELA)
        {
            ELF32SectionHeader sectionHeader = elf32SectionHeaders[elf32SectionHeaderIndex];

            ELF32RelA        *relAs          = (ELF32RelA*) &elf32[sectionHeader.offset];
            unsigned int     numberOfRelAs   = sectionHeader.size / sectionHeader.entrySize;
            unsigned int     sectionIndex    = sectionHeader.info;
            ELF32SymbolEntry *symbols        = (ELF32SymbolEntry*) &elf32[elf32SectionHeaders[sectionHeader.link].offset];
            unsigned int     numberOfSymbols = elf32SectionHeaders[sectionHeader.link].size / elf32SectionHeaders[sectionHeader.link].entrySize;

            elf_sectionRelocationA(sections[sectionMapping[sectionIndex]], relAs, numberOfRelAs, symbols, numberOfSymbols);
        }
}
