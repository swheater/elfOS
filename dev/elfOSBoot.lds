/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

SECTIONS
{
	. = 0x00010000;
	.text :
	{
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
        _elf32Appl = .;
        . = ALIGN(0x10000);
        . += 0x00010000;
	.bss :
	{
		* (.bss);
	}
}
