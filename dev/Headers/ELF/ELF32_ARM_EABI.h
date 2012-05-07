#ifndef _ELF_ELF32_ARM_EABI_H
#define _ELF_ELF32_ARM_EABI_H 1

/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#define ELF32_SECTIONHEADERTYPE_ARM_EABI_EXCEPTIONINDEXTABLE (0x70000001)
#define ELF32_SECTIONHEADERTYPE_ARM_EABI_PREEMPTIONMAP (0x70000002)
#define ELF32_SECTIONHEADERTYPE_ARM_EABI_ATTRIBUTES (0x70000003)
#define ELF32_SECTIONHEADERTYPE_ARM_EABI_DEBUGOVERLAY (0x70000004)
#define ELF32_SECTIONHEADERTYPE_ARM_EABI_OVERLAYSECTION (0x70000005)

#define ELF32_RELOCATIONTYPE_ARM_EABI_NONE (0)
#define ELF32_RELOCATIONTYPE_ARM_EABI_PC24 (1)
#define ELF32_RELOCATIONTYPE_ARM_EABI_ABS32 (2)
#define ELF32_RELOCATIONTYPE_ARM_EABI_REL32 (3)
#define ELF32_RELOCATIONTYPE_ARM_EABI_CALL (28)
#define ELF32_RELOCATIONTYPE_ARM_EABI_V4BX (40)

extern int elf32_validate(const char *elf32, unsigned int elf32Size);
extern int elf32_validateHeader(const ELF32Header *elf32Header);
extern int elf32_validateSectionHeader(const ELF32SectionHeader *elf32SectionHeader);

extern Boolean elf32_sectionRelocation(VirtualMemorySegment virtualMemorySegment, ELF32Rel rels[], unsigned int numberOfRels, UnsignedWord32 symbolValues[], unsigned int numberOfSymbolValues);
extern Boolean elf32_sectionRelocationA(VirtualMemorySegment virtualMemorySegment, ELF32RelA relAs[], unsigned int numberOfRelAs, UnsignedWord32 symbolValues[], unsigned int numberOfSymbolValues);

#endif
