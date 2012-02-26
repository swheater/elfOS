#ifndef _ELFOS_KERNEL_ELF32_H
#define _ELFOS_KERNEL_ELF32_H 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <StdTypes.h>

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
    UnsignedWord16 stringTableSectionHeaderIndex;
} ELF32Header;

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

#endif
