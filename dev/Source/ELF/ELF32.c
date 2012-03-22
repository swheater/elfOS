/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/MemoryDomains.h>
#include <ELF/ELF32.h>

int elf_validateELF32File(const char *elf32File, const unsigned int elf32FileSize)
{
    int valid;

    ELF32Header *elf32Header = (ELF32Header*) elf32File;
    valid =  elf_validateELF32Header(elf32Header);

    ELF32SectionHeader *elf32SectionHeader = (ELF32SectionHeader*) (elf32File + elf32Header->sectionHeaderOffset);
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
        case SECTIONHEADERTYPE_NULL:
            valid = 1; 
	    break;
        case SECTIONHEADERTYPE_PROGBITS:
            valid = 1; 
	    break;
        case SECTIONHEADERTYPE_SYMTAB:
            valid = 1; 
	    break;
        case SECTIONHEADERTYPE_STRTAB:
            valid = 1; 
	    break;
        case SECTIONHEADERTYPE_NOBITS:
            valid = 1; 
	    break;
        case SECTIONHEADERTYPE_REL:
            valid = 1; 
	    break;
        default:
            valid = 0; 
    }

    return valid;
}

void elf_extractMemoryDomainInfos(const MemoryDomainInfo (*memoryDomainInfos)[], unsigned int *numberOfMemoryDomainInfos)
{
    *numberOfMemoryDomainInfos = 0;
}
