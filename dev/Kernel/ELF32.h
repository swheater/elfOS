#ifndef _ELFOS_KERNEL_ELF32_H
#define _ELFOS_KERNEL_ELF32_H 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#define ELF32_HEADER_MAGIC_LENGTH 4
#define ELF32_HEADER_PADDING_LENGTH 9

typedef struct
{
    char           magic[ELF32_HEADER_MAGIC_LENGTH];
    unsigned char  fileClass;
    unsigned char  byteOrder;
    unsigned char  headerVersion;
    char           padding[ELF32_HEADER_PADDING_LENGTH];
    unsigned short type;
    unsigned short machine;
    unsigned long  version;
    unsigned int   entry;
    unsigned int   programHeaderOffset;
    unsigned int   sectionHeaderOffset;
    unsigned long  flags;
    unsigned short headersize;
    unsigned short programHeaderEntrySize;
    unsigned short programHeaderNumber;
    unsigned short sectionHeaderEntrySize;
    unsigned short sectionHeaderEntryNumber;
    unsigned short sectionHeaderTableIndex;
} ELF32Header;

typedef struct
{
    unsigned long name;
    unsigned long type;
    unsigned long flags;
    unsigned int  addr;
    unsigned int  offset;
    unsigned long size;
    unsigned long link;
    unsigned long info;
    unsigned long addressAlign;
    unsigned long entrySize;
} ELF32SectionHeader;

typedef struct
{
    unsigned long  name;
    unsigned int   value;
    unsigned long  size;
    unsigned char  info;
    unsigned char  other;
    unsigned short sectionHeaderTableIndex;
} ELF32SymbolEntry;

typedef struct
{
    unsigned int  offset;
    unsigned long info;
} ELF32_Rel;

typedef struct
{
    unsigned int  offset;
    unsigned long info;
    long          addend;
} ELF32_Rela;

typedef struct
{
    unsigned long type;
    unsigned int  offset;
    unsigned int  vaddr;
    unsigned int  paddr;
    unsigned long fileSize;
    unsigned long memSize;
    unsigned long flags;
    unsigned long align;
} ELF32ProgramHeader;

typedef struct
{
    long tag;
    union
    {
        unsigned long value;
        unsigned int  pointer;
    } DynamicUnion;
} ELF32Dynamic;

#endif
