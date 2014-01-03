/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/VirtualMemory.h>
#include <Kernel/Symbol.h>
#include <String/String.h>
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

Boolean findGlobalSymbolValue(const char *symbolName, UnsignedWord32 *symbolValue, Symbol globalSymbols[], unsigned int numberOfGlobalSymbols)
{
    Boolean valid = FALSE;

    unsigned int globalSymbolIndex;
    for (globalSymbolIndex = 0; globalSymbolIndex < numberOfGlobalSymbols; globalSymbolIndex++)
        if (string_equal(symbolName, (char*) globalSymbols[globalSymbolIndex].name))
        {
            *symbolValue = globalSymbols[globalSymbolIndex].value;
            valid = TRUE;
        }

    return valid;
}

Boolean populateSymbolValues(UnsignedWord32 symbolValues[], unsigned int numberOfSymbolValues, ELF32SymbolEntry *symbols, const char* stringTable, unsigned int sectionMapping[], Symbol globalSymbols[], unsigned int numberOfGlobalSymbols, VirtualMemorySegment virtualMemorySegments[])
{
    Boolean valid = TRUE;

    unsigned int symbolIndex;
    for (symbolIndex = 0; symbolIndex < numberOfSymbolValues; symbolIndex++)
        if ((ELF32_SYMBOL_BINDING(symbols[symbolIndex].info) == ELF32_SYMBOLBINDING_GLOBAL) && (symbols[symbolIndex].sectionHeaderTableIndex == ELF32_SECTIONHEADERINDEX_UNDEFINED))
        {
            const char *name = &stringTable[symbols[symbolIndex].name];
            valid &= findGlobalSymbolValue(name, &symbolValues[symbolIndex], globalSymbols, numberOfGlobalSymbols);
        }
        else if ((symbols[symbolIndex].sectionHeaderTableIndex != ELF32_SECTIONHEADERINDEX_UNDEFINED) && (symbols[symbolIndex].sectionHeaderTableIndex < ELF32_SECTIONHEADERINDEX_LOWRESERVE))
            symbolValues[symbolIndex] = (UnsignedWord32) &(virtualMemorySegments[sectionMapping[symbols[symbolIndex].sectionHeaderTableIndex]].virtualAddress[symbols[symbolIndex].value]);
        else
            symbolValues[symbolIndex] = 0;

    return valid;
}

Boolean elf32_segmentsInitialize(const char *elf32, const ELF32SectionHeader sectionHeaders[], unsigned int numberOfSectionHeaders, Symbol globalSymbols[], unsigned int numberOfGlobalSymbols, VirtualMemorySegment virtualMemorySegments[], unsigned int numberOfVirtualMemorySegments)
{
    unsigned int sectionIndex = 0;
    unsigned int sectionMapping[numberOfSectionHeaders];

    unsigned int sectionHeaderIndex;
    for (sectionHeaderIndex = 0; sectionHeaderIndex < numberOfSectionHeaders; sectionHeaderIndex++)
        if (((sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_PROGBITS) || (sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_NOBITS)) && (sectionHeaders[sectionHeaderIndex].flags & ELF32_SECTIONHEADERFLAG_ALLOCATE) && (sectionHeaders[sectionHeaderIndex].size > 0))
        {
            if (sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_PROGBITS)
            {
                virtualMemorySegments[sectionIndex].size = sectionHeaders[sectionHeaderIndex].size;

                unsigned int index;
                for (index = 0; index < virtualMemorySegments[sectionIndex].size; index++)
                    virtualMemorySegments[sectionIndex].physicalAddress[index] = elf32[sectionHeaders[sectionHeaderIndex].offset + index];
            }
            else if (sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_NOBITS)
            {
                virtualMemorySegments[sectionIndex].size = sectionHeaders[sectionHeaderIndex].size;

                unsigned int index;
                for (index = 0; index < virtualMemorySegments[sectionIndex].size; index++)
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
            const char       *stringTable    = &elf32[sectionHeaders[sectionHeaders[sectionHeader.link].link].offset];
            ELF32SymbolEntry *symbols        = (ELF32SymbolEntry*) &elf32[sectionHeaders[sectionHeader.link].offset];

            valid &= populateSymbolValues(symbolValues, numberOfSymbolValues, symbols, stringTable, sectionMapping, globalSymbols, numberOfGlobalSymbols, virtualMemorySegments);

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
            const char       *stringTable    = &elf32[sectionHeaders[sectionHeaders[sectionHeader.link].link].offset];
            ELF32SymbolEntry *symbols        = (ELF32SymbolEntry*) &elf32[sectionHeaders[sectionHeader.link].offset];

            valid &= populateSymbolValues(symbolValues, numberOfSymbolValues, symbols, stringTable, sectionMapping, globalSymbols, numberOfGlobalSymbols, virtualMemorySegments);

            valid &= elf32_sectionRelocationA(virtualMemorySegments[sectionMapping[segmentIndex]], relAs, numberOfRelAs, symbolValues, numberOfSymbolValues);
        }

    return valid;
}

void (*elf32_findFunction(const char *functionName, const char *elf32, const ELF32SectionHeader sectionHeaders[], unsigned int numberOfSectionHeaders, VirtualMemorySegment virtualMemorySegments[], unsigned int numberOfVirtualMemorySegments))(void)
{
    void (*func)(void) = 0;

    unsigned int sectionIndex = 0;
    unsigned int sectionMapping[numberOfSectionHeaders];

    unsigned int sectionHeaderIndex;
    for (sectionHeaderIndex = 0; sectionHeaderIndex < numberOfSectionHeaders; sectionHeaderIndex++)
        if (((sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_PROGBITS) || (sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_NOBITS)) && (sectionHeaders[sectionHeaderIndex].flags & ELF32_SECTIONHEADERFLAG_ALLOCATE) && (sectionHeaders[sectionHeaderIndex].size > 0))
        {
            sectionMapping[sectionHeaderIndex] = sectionIndex;
            sectionIndex++;
        }
        else
            sectionMapping[sectionHeaderIndex] = 0;

    for (sectionHeaderIndex = 0; sectionHeaderIndex < numberOfSectionHeaders; sectionHeaderIndex++)
        if (sectionHeaders[sectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_SYMTAB)
        {
            ELF32SectionHeader sectionHeader = sectionHeaders[sectionHeaderIndex];

            ELF32SymbolEntry *symbolEntries      = (ELF32SymbolEntry*) &elf32[sectionHeader.offset];
            unsigned int     numberOfSymbolEntry = sectionHeader.size / sectionHeader.entrySize;
            const char       *stringTable        = &elf32[sectionHeaders[sectionHeader.link].offset];
   
            int symbolEntryIndex;
            for (symbolEntryIndex = 0; symbolEntryIndex < numberOfSymbolEntry; symbolEntryIndex++)
            {
                ELF32SymbolEntry *symbolEntry = &symbolEntries[symbolEntryIndex];

                if (ELF32_SYMBOL_TYPE(symbolEntry->info) == ELF32_SYMBOLTYPE_FUNCTION)
                {
                    const char *name = &stringTable[symbolEntry->name];
                    if (string_equal(functionName, name))
                        func = (void (*)(void)) &(virtualMemorySegments[sectionMapping[symbolEntry->sectionHeaderTableIndex]].virtualAddress[symbolEntry->value]);
                }
            }
        }

    return func;
}
