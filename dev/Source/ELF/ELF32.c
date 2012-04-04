/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/MemoryDomains.h>
#include <ELF/ELF32.h>

#include <stdio.h>

int elf_validateELF32(const char *elf32, const unsigned int elf32Size)
{
    int valid;

    ELF32Header *elf32Header = (ELF32Header*) elf32;
    valid =  elf_validateELF32Header(elf32Header);

    ELF32SectionHeader *elf32SectionHeader = (ELF32SectionHeader*) (elf32 + elf32Header->sectionHeaderOffset);
    int elf32SectionHeaderIndex;
    for (elf32SectionHeaderIndex = 0; elf32SectionHeaderIndex < elf32Header->sectionHeaderEntryNumber; elf32SectionHeaderIndex++)
        valid &= elf_validateELF32SectionHeader(&elf32SectionHeader[elf32SectionHeaderIndex]);

    return valid;
}

int elf_validateELF32Header(const ELF32Header *elf32Header)
{
    int valid;

    valid =  (elf32Header->magic[0] == 0x7f) && (elf32Header->magic[1] == 'E') && (elf32Header->magic[2] == 'L') && (elf32Header->magic[3] == 'F');
    valid &= (elf32Header->fileClass == 0x01);
    valid &= (elf32Header->byteOrder == 0x01);
    valid &= (elf32Header->headerVersion == 0x01);
    valid &= (elf32Header->padding[0] == 'a');
    int paddingIndex;
    for (paddingIndex = 1; paddingIndex < ELF32_HEADER_PADDING_LENGTH; paddingIndex++)
        valid &= (elf32Header->padding[paddingIndex] == 0x00);
    valid &= (elf32Header->type == 0x0001);
    valid &= (elf32Header->machine == 0x0028);
    valid &= (elf32Header->version == 0x00000001);
    valid &= (elf32Header->entry == 0x00000000);
    //    valid &= (elf32Header->programHeaderOffset == ????);
    //    valid &= (elf32Header->sectionHeaderOffset == ????);
    valid &= (elf32Header->flags == 0x00000000);
    valid &= (elf32Header->headerSize == sizeof(ELF32Header));
    valid &= (elf32Header->programHeaderEntrySize == 0) || (elf32Header->programHeaderEntrySize == sizeof(ELF32ProgramHeader));
    //    valid &= (elf32Header->programHeaderNumber == ????);
    valid &= (elf32Header->sectionHeaderEntrySize == 0) || (elf32Header->sectionHeaderEntrySize == sizeof(ELF32SectionHeader));
    //    valid &= (elf32Header->sectionHeaderEntryNumber == ????);
    //    valid &= (elf32Header->sectionHeaderStringTableIndex == ????);

    return valid;
}

int elf_validateELF32SectionHeader(const ELF32SectionHeader *elf32SectionHeader)
{
    int valid;

    switch (elf32SectionHeader->type)
    {
        case ELF32_SECTIONHEADERTYPE_NULL:
            valid = 1; 
            break;
        case ELF32_SECTIONHEADERTYPE_PROGBITS:
            valid = 1; 
            break;
        case ELF32_SECTIONHEADERTYPE_SYMTAB:
            valid = 1; 
            break;
        case ELF32_SECTIONHEADERTYPE_STRTAB:
            valid = 1; 
            break;
        case ELF32_SECTIONHEADERTYPE_NOBITS:
            valid = 1; 
            break;
        case ELF32_SECTIONHEADERTYPE_REL:
            valid = 1; 
            break;
        default:
            valid = 0; 
    }

    return valid;
}

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
    unsigned int sectionHeaderMapping[numberOfELF32SectionHeaders];

    unsigned int elf32SectionHeaderIndex;
    for (elf32SectionHeaderIndex = 0; elf32SectionHeaderIndex < numberOfELF32SectionHeaders; elf32SectionHeaderIndex++)
        if (((elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_PROGBITS) || (elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_NOBITS)) && (elf32SectionHeaders[elf32SectionHeaderIndex].flags & ELF32_SECTIONHEADERFLAG_ALLOCATE) && (elf32SectionHeaders[elf32SectionHeaderIndex].size > 0))
        {
            if (elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_PROGBITS)
            {
                printf("PROGBITS %d\n", sectionIndex);
                printf("         %d\n", elf32SectionHeaders[elf32SectionHeaderIndex].size);
                unsigned int index;
                for (index = 0; index < elf32SectionHeaders[elf32SectionHeaderIndex].size; index++)
                    sections[sectionIndex][index] = elf32[elf32SectionHeaders[elf32SectionHeaderIndex].offset + index];
            }
            else if (elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_NOBITS)
            {
                printf("NOBITS %d\n", sectionIndex);
                printf("       %d\n", elf32SectionHeaders[elf32SectionHeaderIndex].size);
                unsigned int index;
                for (index = 0; index < elf32SectionHeaders[elf32SectionHeaderIndex].size; index++)
                    sections[sectionIndex][index] = 0;
            }

            sectionHeaderMapping[elf32SectionHeaderIndex] = sectionIndex; 
            sectionIndex++;
        }

    for (elf32SectionHeaderIndex = 0; elf32SectionHeaderIndex < numberOfELF32SectionHeaders; elf32SectionHeaderIndex++)
        if (elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_REL)
        {
            ELF32Rel *elf32Rel = (ELF32Rel*) &elf32[elf32SectionHeaders[elf32SectionHeaderIndex].offset];

            unsigned int elf32RelIndex;
            unsigned int numberOfELF32Rel = elf32SectionHeaders[elf32SectionHeaderIndex].size / elf32SectionHeaders[elf32SectionHeaderIndex].entrySize;
            for (elf32RelIndex = 0; elf32RelIndex < numberOfELF32Rel; elf32RelIndex++)
            {
                printf("REL %d\n", elf32RelIndex);
                printf("  offset %d\n", elf32Rel[elf32RelIndex].offset);
                printf("  info   %d\n", elf32Rel[elf32RelIndex].info);
                printf("    sym  %d\n", elf32Rel[elf32RelIndex].info >> 8);
                printf("    type %d\n", elf32Rel[elf32RelIndex].info & 0xFF);
            }    
        }
        else if (elf32SectionHeaders[elf32SectionHeaderIndex].type == ELF32_SECTIONHEADERTYPE_RELA)
            printf("RELA %d\n", elf32SectionHeaderIndex);
}
