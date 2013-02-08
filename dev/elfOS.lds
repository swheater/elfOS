/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

EXTERN(kernel_boot kernel)
EXTERN(kernel_zeroPagePhyStart kernel_zeroPagePhyEnd);
EXTERN(kernel_bssSectionStart kernel_bssSectionEnd)
EXTERN(kernel_containerTranslationTable kernel_phyContainerTranslationTable kernel_kernelTranslationTable kernel_phyKernelTranslationTable);

SECTIONS
{
	kernel_boot = 0x00008000;
	kernel      = 0x80000000;

	dev_phyStart = 0x20000000;
	dev_phyEnd   = 0x20FFFFFF;
	dev_virStart = 0xF0000000;

	.text.boot kernel_boot :
	{
                Source/Kernel/ARM/Boot.o (.text);
		Source/Kernel/ARMv6/BootVirtualMemory.o (.text);
		. = ALIGN(0x1000);
	}
	.text kernel : AT (ADDR(.text.boot) + SIZEOF(.text.boot))
	{
		kernel_zeroPagePhyStart = (. - ADDR(.text)) + (ADDR(.text.boot) + SIZEOF(.text.boot));
                Source/Kernel/ARM/ZeroPage.o (.text);
		kernel_zeroPagePhyEnd = (. - ADDR(.text)) + (ADDR(.text.boot) + SIZEOF(.text.boot));
                * (.text);
	}
	.rodata :
	{
		* (.rodata);
	}
	.data :
	{
		* (.data);
		. = ALIGN(0x2000);
		kernel_containerTranslationTable    = .;
		kernel_phyContainerTranslationTable = (. - ADDR(.text)) + (ADDR(.text.boot) + SIZEOF(.text.boot));
		. = . + 0x2000;
		kernel_kernelTranslationTable    = .;
		kernel_phyKernelTranslationTable = (. - ADDR(.text)) + (ADDR(.text.boot) + SIZEOF(.text.boot));
		. = . + 0x2000;
	}
	.bss :
	{
		kernel_bssSectionStart = .;
		* (.bss);
		kernel_bssSectionEnd = .;
	}
}
