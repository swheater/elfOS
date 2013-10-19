/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/VirtualMemory.h>
#include <ELF/ELF32.h>
#include <ELF/ELF32_ARM_EABI.h>

int elf32_validate(const char *elf32, const unsigned int elf32Size)
{
    int valid;

    ELF32Header *elf32Header = (ELF32Header*) elf32;
    valid =  elf32_validateHeader(elf32Header);

    ELF32SectionHeader *elf32SectionHeader = (ELF32SectionHeader*) (elf32 + elf32Header->sectionHeaderOffset);
    int elf32SectionHeaderIndex;
    for (elf32SectionHeaderIndex = 0; elf32SectionHeaderIndex < elf32Header->sectionHeaderEntryNumber; elf32SectionHeaderIndex++)
        valid &= elf32_validateSectionHeader(&elf32SectionHeader[elf32SectionHeaderIndex]);

    return valid;
}

int elf32_validateHeader(const ELF32Header *elf32Header)
{
    int valid;

    valid =  (elf32Header->magic[0] == 0x7f) && (elf32Header->magic[1] == 'E') && (elf32Header->magic[2] == 'L') && (elf32Header->magic[3] == 'F');
    valid &= (elf32Header->fileClass == 0x01);
    valid &= (elf32Header->byteOrder == 0x01);
    valid &= (elf32Header->headerVersion == 0x01);
    int paddingIndex;
    for (paddingIndex = 0; paddingIndex < ELF32_HEADER_PADDING_LENGTH; paddingIndex++)
        valid &= (elf32Header->padding[paddingIndex] == 0x00);
    valid &= (elf32Header->type == 0x0001);
    valid &= (elf32Header->machine == 0x0028);
    valid &= (elf32Header->version == 0x00000001);
    valid &= (elf32Header->entry == 0x00000000);
    //    valid &= (elf32Header->programHeaderOffset == ????);
    //    valid &= (elf32Header->sectionHeaderOffset == ????);
    //    valid &= (elf32Header->flags == 0x00000000);
    valid &= (elf32Header->headerSize == sizeof(ELF32Header));
    valid &= (elf32Header->programHeaderEntrySize == 0) || (elf32Header->programHeaderEntrySize == sizeof(ELF32ProgramHeader));
    //    valid &= (elf32Header->programHeaderNumber == ????);
    valid &= (elf32Header->sectionHeaderEntrySize == 0) || (elf32Header->sectionHeaderEntrySize == sizeof(ELF32SectionHeader));
    //    valid &= (elf32Header->sectionHeaderEntryNumber == ????);
    //    valid &= (elf32Header->sectionHeaderStringTableIndex == ????);

    return valid;
}

int elf32_validateSectionHeader(const ELF32SectionHeader *elf32SectionHeader)
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
        case ELF32_SECTIONHEADERTYPE_RELA:
            valid = 0;
            break;
        case ELF32_SECTIONHEADERTYPE_ARM_EABI_ATTRIBUTES:
            valid = 1;
            break;
        default:
            valid = 0; 
            break;
    }

    return valid;
}

Boolean elf32_sectionRelocation(VirtualMemorySegment virtualMemorySegment, ELF32Rel rels[], unsigned int numberOfRels, UnsignedWord32 symbolValues[], unsigned int numberOfSymbolValues)
{
    Boolean done = FALSE;

    int relIndex;
    for (relIndex = 0; relIndex < numberOfRels; relIndex++)
    {
        switch (ELF32_REL_TYPE(rels[relIndex].info))
        {
            case ELF32_RELOCATIONTYPE_ARM_EABI_NONE:
                break;
            case ELF32_RELOCATIONTYPE_ARM_EABI_ABS32:
            {
                UnsignedWord32 *relAddr = (UnsignedWord32*) &(virtualMemorySegment.physicalAddress[rels[relIndex].offset]);
                *relAddr += symbolValues[ELF32_REL_SYMBOL(rels[relIndex].info)];
                done = TRUE;
                break;
            }
            case ELF32_RELOCATIONTYPE_ARM_EABI_REL32:
            {
                UnsignedWord32 *relAddr = (UnsignedWord32*) &(virtualMemorySegment.physicalAddress[rels[relIndex].offset]);
                *relAddr += (symbolValues[ELF32_REL_SYMBOL(rels[relIndex].info)] - (UnsignedWord32) relAddr) / 4;
                done = TRUE;
                break;
            }
            case ELF32_RELOCATIONTYPE_ARM_EABI_CALL:
            {
                UnsignedWord32 *relAddr = (UnsignedWord32*) &(virtualMemorySegment.physicalAddress[rels[relIndex].offset]);
                *relAddr = (*relAddr & 0xFF000000) | ((*relAddr + (symbolValues[ELF32_REL_SYMBOL(rels[relIndex].info)] - (UnsignedWord32) relAddr) / 4) & 0x00FFFFFF);
                done = TRUE;
                break;
            }
            case ELF32_RELOCATIONTYPE_ARM_EABI_V4BX:
                break;
            default:
                break;
        }
    }

    return done;
}

Boolean elf32_sectionRelocationA(VirtualMemorySegment virtualMemorySegment, ELF32RelA relAs[], unsigned int numberOfRelAs, UnsignedWord32 symbolValues[], unsigned int numberOfSymbolValues)
{
    return FALSE;
}
