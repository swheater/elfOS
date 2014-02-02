/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

EXTERN(phy_boot vir_boot)
EXTERN(phy_kernel vir_kernel)
EXTERN(phy_devStart phy_devEnd)
EXTERN(kernel_zeroPagePhyStart kernel_zeroPagePhyEnd);
EXTERN(boot_bssSectionStart boot_bssSectionEnd);
EXTERN(kernel_bssSectionStart kernel_bssSectionEnd);

SECTIONS
{
	phy_boot     = 0x00008000;
	vir_boot     = 0x00008000;
	phy_kernel   = 0x00020000;
	vir_kernel   = 0x80000000;

	phy_devStart = 0x20000000;
	phy_devEnd   = 0x20FFFFFF;

	.text.boot phy_boot :
	{
		Source/Kernel/ARM/Boot.o (.text);
		Source/Kernel/BDebug.o (.text);
		Source/Kernel/ARMv6/BootVirtualMemory.o (.text);
	}
	.data.boot :
	{
		Source/Kernel/ARM/Boot.o (.data);
		Source/Kernel/BDebug.o (.data);
		Source/Kernel/ARMv6/BootVirtualMemory.o (.data);
	}
	.bss.boot :
	{
                boot_bssSectionStart = .;
		Source/Kernel/ARM/Boot.o (.bss);
		Source/Kernel/BDebug.o (.bss);
		Source/Kernel/ARMv6/BootVirtualMemory.o (.bss);
		boot_bssSectionEnd = .;
	}
	.rodata.boot :
	{
		Source/Kernel/ARM/Boot.o (.rodata);
		Source/Kernel/BDebug.o (.rodata);
		Source/Kernel/ARMv6/BootVirtualMemory.o (.rodata);
		Source/Kernel/ARM/Boot.o (.rodata.str1.4);
		Source/Kernel/BDebug.o (.rodata.str1.4);
		Source/Kernel/ARMv6/BootVirtualMemory.o (.rodata.str1.4);
		. = ALIGN(0x1000);
	}
	.text vir_kernel : AT (phy_kernel)
	{
		kernel_zeroPagePhyStart = .;
		Source/Kernel/ARM/ZeroPage.o (.text);
		kernel_zeroPagePhyEnd = .;
		. = ALIGN(0x20);
		Source/Kernel/ARM/HandlerVectors.o (.text);
		* (.text);
	}
	.rodata :
	{
		* (.rodata);
	}
	.data :
	{
		* (.data);
	}
	.bss :
	{
		kernel_bssSectionStart = .;
		* (.bss);
		kernel_bssSectionEnd = .;
	}
}
