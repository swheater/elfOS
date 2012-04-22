#ifndef _ELF_ELF32_H
#define _ELF_ELF32_H 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/VirtualMemory.h>

#define ELF32_HEADER_MAGIC_LENGTH (4)
#define ELF32_HEADER_PADDING_LENGTH (9)

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

#define ELF32_SECTIONHEADERINDEX_UNDEF (0x0000)
#define ELF32_SECTIONHEADERINDEX_LOWRESERVE (0xFF00)
#define ELF32_SECTIONHEADERINDEX_LOwPROC (0xFF00)
#define ELF32_SECTIONHEADERINDEX_HIGHPROC (0xFF1F)
#define ELF32_SECTIONHEADERINDEX_ABSOLUTE (0xFFF1)
#define ELF32_SECTIONHEADERINDEX_COMMON (0xFFF2)
#define ELF32_SECTIONHEADERINDEX_HIGHRESERVE (0xFFFF)

#define ELF32_SECTIONHEADERTYPE_NULL (0)
#define ELF32_SECTIONHEADERTYPE_PROGBITS (1)
#define ELF32_SECTIONHEADERTYPE_SYMTAB (2)
#define ELF32_SECTIONHEADERTYPE_STRTAB (3)
#define ELF32_SECTIONHEADERTYPE_RELA (4)
#define ELF32_SECTIONHEADERTYPE_HASH (5)
#define ELF32_SECTIONHEADERTYPE_DYNAMIC (6)
#define ELF32_SECTIONHEADERTYPE_NOTE (7)
#define ELF32_SECTIONHEADERTYPE_NOBITS (8)
#define ELF32_SECTIONHEADERTYPE_REL (9)
#define ELF32_SECTIONHEADERTYPE_SHLIB (10)
#define ELF32_SECTIONHEADERTYPE_DYNSYM (11)

#define ELF32_SECTIONHEADERFLAG_WRITABLE (0x1)
#define ELF32_SECTIONHEADERFLAG_ALLOCATE (0x2)
#define ELF32_SECTIONHEADERFLAG_EXECUTABLE (0x4)

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

#define ELF32_SYMBOLTYPE_NOTYPE (0)
#define ELF32_SYMBOLTYPE_OBJECT (1)
#define ELF32_SYMBOLTYPE_FUNCTION (2)
#define ELF32_SYMBOLTYPE_SECTION (3)
#define ELF32_SYMBOLTYPE_FILE (4)

typedef struct
{
    UnsignedWord32 name;
    UnsignedWord32 value;
    UnsignedWord32 size;
    UnsignedByte   info;
    UnsignedByte   other;
    UnsignedWord16 sectionHeaderTableIndex;
} ELF32SymbolEntry;

#define ELF32_SYMBOL_BINDING(i) ((i) >> 4)
#define ELF32_SYMBOL_TYPE(i) ((i) & 0x0F)
#define ELF32_SYMBOL_INFO(b,t) (((b) << 4) + ((t) & 0x0F))

typedef struct
{
    UnsignedWord32 offset;
    UnsignedWord32 info;
} ELF32Rel;

#define ELF32_REL_SYMBOL(i) ((UnsignedByte) ((i) >> 8))
#define ELF32_REL_TYPE(i) ((UnsignedByte) ((i) & 0xFF))
#define ELF32_REL_INFO(s,t) (((s) << 8) + ((t) & 0xFF))

typedef struct
{
    UnsignedWord32 offset;
    UnsignedWord32 info;
    SignedWord32   addend;
} ELF32RelA;

#define ELF32_RELA_SYM(i) ((i) >> 8)
#define ELF32_RELA_TYPE(i) ((unsigned char) (i))
#define ELF32_RELA_INFO(s,t) (((s) << 8) + (unsigned char) (t))

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

extern unsigned int elf32_numberOfVirtualMemorySegmentInfos(ELF32SectionHeader sectionHeaders[], unsigned int numberOfSectionHeaders);
extern void elf32_extractVirtualMemorySegmentInfos(ELF32SectionHeader sectionHeaders[], unsigned int numberOfSectionHeaders, VirtualMemorySegmentInfo virtualMemorySegmentInfos[], unsigned int *numberOfVirtualMemorySegmentInfos);
extern void elf32_segmentsInitialize(const char *elf32, unsigned int elf32Size, const ELF32SectionHeader *elf32SectionHeaders, unsigned int numberOfELF32SectionHeaders, VirtualMemorySegment virtualMemorySegments[], unsigned int numberOfVirtualMemorySegments);

#endif
