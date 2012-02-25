#ifndef _ELFOS_KERNEL_ELF32_H
#define _ELFOS_KERNEL_ELF32_H 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#define ELF_HEADER_MAGIC_LENGTH 4
#define ELF_HEADER_PADDING_LENGTH 9

typedef struct
{
    char           magic[ELF_HEADER_MAGIC_LENGTH];
    unsigned char  class;
    unsigned char  byteorder;
    unsigned char  headerversion;
    char           padding[ELF_HEADER_PADDING_LENGTH];
    unsigned short type;
    unsigned short machine;
    unsigned long  version;
    unsigned int   entry;
    unsigned int   programheaderoffset;
    unsigned int   sectionheaderoffset;
    unsigned long  flags;
    unsigned short headersize;
    unsigned short programheaderentrysize;
    unsigned short programheadernumber;
    unsigned short sectionheaderentrysize;
    unsigned short sectionheaderentrynumber;
    unsigned short sectionheadertableindex;
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
    unsigned long addressalign;
    unsigned long entrysize;
} ELF32SectionHeader;

typedef struct
{
    unsigned long  name;
    unsigned int   value;
    unsigned long  size;
    unsigned char  info;
    unsigned char  other;
    unsigned short sectionheadertableindex;
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
    unsigned long filesize;
    unsigned long memsize;
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
