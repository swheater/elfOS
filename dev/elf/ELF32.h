#ifndef _ELFOS_ELF32_H
#define _ELFOS_ELF32_H 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#define ELF_HEADER_IDENTIFICATION 16

typedef struct
{
    unsigned char  identification[ELF_HEADER_IDENTIFICATION];
    unsigned short type;
    unsigned short machine;
    unsigned long  version;
    unsigned void  *entry;
    unsigned void  *programHeaderOffset;
    unsigned void  *sectionHeaderOffset;
    unsigned long  flags;
    unsigned short headerSize;
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
    unsigned void *addr;
    unsigned void *offset;
    unsigned long size;
    unsigned long link;
    unsigned long info;
    unsigned long addressAlign;
    unsigned long entrySize;
} ELF32SectionHeader;

typedef struct
{
    unsigned long  name;
    void           *value;
    unsigned long  size;
    unsigned char  info;
    unsigned char  other;
    unsigned short sectionHeaderTableIndex;
} ELF32SymbolEntry;

typedef struct
{
    void          *offset;
    unsigned long info;
} ELF32_Rel;

typedef struct
{
    void          *offset;
    unsigned long info;
    long          addend;
} ELF32_Rela;

typedef struct
{
    unsigned long type;
    void          *offset;
    void          *vaddr;
    void          *paddr;
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
        void          *pointer;
    } DynamicUnion;
} ELF32Dynamic;

#endif
