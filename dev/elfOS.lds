/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

EXTERN(boot_phyStart boot_virStart)
EXTERN(kernel_phyStart kernel_virStart)
EXTERN(dev_phyStart dev_phyEnd)

EXTERN(boot_textSectionStart boot_textSectionEnd);
EXTERN(boot_dataSectionStart boot_dataSectionEnd);
EXTERN(boot_bssSectionStart boot_bssSectionEnd);
EXTERN(boot_rodataSectionStart boot_rodataSectionEnd);
EXTERN(kernel_textSectionStart kernel_textSectionEnd);
EXTERN(kernel_dataSectionStart kernel_dataSectionEnd);
EXTERN(kernel_bssSectionStart kernel_bssSectionEnd);
EXTERN(kernel_rodataSectionStart kernel_rodataSectionEnd);

EXTERN(kernel_zeroPagePhyStart kernel_zeroPagePhyEnd);

SECTIONS
{
	boot_phyStart   = 0x00008000;
	boot_virStart   = 0x00008000;
	kernel_phyStart = 0x00020000;
	kernel_virStart = 0x80000000;
	dev_phyStart    = 0x20000000;
	dev_phyEnd      = 0x20FFFFFF;

	.text.boot boot_virStart : AT (boot_phyStart)
	{
		boot_textSectionStart = .;
		Source/Boot/ARM/Init.o (.text);
		. = ALIGN(0x20);
		Source/Boot/ARM/HandlerVectors.o (.text);
		Source/Boot/*.o (.text);
		Source/Boot/ARM/*.o (.text);
		Source/Boot/ARMv6/*.o (.text);
		boot_textSectionEnd = .;
	}
	.data.boot :
	{
		boot_dataSectionStart = .;
		Source/Boot/*.o (.data);
		Source/Boot/ARM/*.o (.data);
		Source/Boot/ARMv6/*.o (.data);
		boot_dataSectionEnd = .;
	}
	.rodata.boot :
	{
		boot_rodataSectionStart = .;
		Source/Boot/*.o (.rodata);
		Source/Boot/*.o (.rodata.str1.4);
		Source/Boot/ARM/*.o (.rodata);
		Source/Boot/ARM/*.o (.rodata.str1.4);
		Source/Boot/ARMv6/*.o (.rodata);
		Source/Boot/ARMv6/*.o (.rodata.str1.4);
		boot_rodataSectionEnd = .;
	}
	.bss.boot :
	{
		boot_bssSectionStart = .;
		Source/Boot/*.o (.bss);
		Source/Boot/ARM/*.o (.bss);
		Source/Boot/ARMv6/*.o (.bss);
		boot_bssSectionEnd = .;
		. = ALIGN(0x1000);
	}
	.text kernel_virStart : AT (kernel_phyStart)
	{
		kernel_textSectionStart = .;
		kernel_zeroPagePhyStart = .;
		Source/Kernel/ARM/ZeroPage.o (.text);
		kernel_zeroPagePhyEnd = .;
		. = ALIGN(0x20);
		Source/Kernel/ARM/HandlerVectors.o (.text);
		* (.text);
		kernel_textSectionEnd = .;
	}
	.data :
	{
		kernel_dataSectionStart = .;
		* (.data);	
		kernel_dataSectionEnd = .;
	}
	.rodata :
	{
		kernel_rodataSectionStart = .;
		* (.rodata);
		kernel_rodataSectionEnd = .;
	}
	.bss :
	{
		kernel_bssSectionStart = .;
		* (.bss);
		kernel_bssSectionEnd = .;
	}
}
