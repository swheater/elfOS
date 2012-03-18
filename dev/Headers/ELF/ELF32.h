#ifndef _ELF_ELF32_H
#define _ELF_ELF32_H 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

#define ELF32_HEADER_MAGIC_LENGTH 4
#define ELF32_HEADER_PADDING_LENGTH 9

typedef struct
{
    SignedByte     magic[ELF32_HEADER_MAGIC_LENGTH];
    UnsignedByte   fileClass;
    UnsignedByte   byteOrder;
    UnsignedByte   headerVersion;
    SignedByte     padding[ELF32_HEADER_PADDING_LENGTH];
    UnsignedWord16 type;
    UnsignedWord16 machine;
    UnsignedWord32 version;
    UnsignedWord32 entry;
    UnsignedWord32 programHeaderOffset;
    UnsignedWord32 sectionHeaderOffset;
    UnsignedWord32 flags;
    UnsignedWord16 headerSize;
    UnsignedWord16 programHeaderEntrySize;
    UnsignedWord16 programHeaderNumber;
    UnsignedWord16 sectionHeaderEntrySize;
    UnsignedWord16 sectionHeaderEntryNumber;
    UnsignedWord16 sectionHeaderStringTableIndex;
} ELF32Header;

#define SECTIONHEADERTYPE_NULL 0
#define SECTIONHEADERTYPE_PROGBITS 1
#define SECTIONHEADERTYPE_SYMTAB 2
#define SECTIONHEADERTYPE_STRTAB 3
#define SECTIONHEADERTYPE_RELA 4
#define SECTIONHEADERTYPE_HASH 5
#define SECTIONHEADERTYPE_DYNAMIC 6
#define SECTIONHEADERTYPE_NOTE 7
#define SECTIONHEADERTYPE_NOBITS 8
#define SECTIONHEADERTYPE_REL 9
#define SECTIONHEADERTYPE_SHLIB 10
#define SECTIONHEADERTYPE_DYNSYM 11

typedef struct
{
    UnsignedWord32 name;
    UnsignedWord32 type;
    UnsignedWord32 flags;
    UnsignedWord32 addr;
    UnsignedWord32 offset;
    UnsignedWord32 size;
    UnsignedWord32 link;
    UnsignedWord32 info;
    UnsignedWord32 addressAlign;
    UnsignedWord32 entrySize;
} ELF32SectionHeader;

typedef struct
{
    UnsignedWord32 name;
    UnsignedWord32 value;
    UnsignedWord32 size;
    UnsignedByte   info;
    UnsignedByte   other;
    UnsignedWord16 sectionHeaderTableIndex;
} ELF32SymbolEntry;

typedef struct
{
    UnsignedWord32 offset;
    UnsignedWord32 info;
} ELF32Rel;

typedef struct
{
    UnsignedWord32 offset;
    UnsignedWord32 info;
    SignedWord32   addend;
} ELF32Rela;

typedef struct
{
    UnsignedWord32 type;
    UnsignedWord32 offset;
    UnsignedWord32 vaddr;
    UnsignedWord32 paddr;
    UnsignedWord32 fileSize;
    UnsignedWord32 memSize;
    UnsignedWord32 flags;
    UnsignedWord32 align;
} ELF32ProgramHeader;

typedef struct
{
    SignedWord32 tag;
    union
    {
        UnsignedWord32 value;
        UnsignedWord32 pointer;
    } dynamicUnion;
} ELF32Dynamic;

extern int elf_validateELF32File(const char *elf32File, const unsigned int elf32FileSize);
extern int elf_validateELF32Header(const ELF32Header *elf32Header);
extern int elf_validateELF32SectionHeader(const ELF32SectionHeader *elf32SectionHeader);

#endif
