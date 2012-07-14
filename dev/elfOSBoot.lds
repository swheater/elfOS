/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

EXTERN(kernelTranslationTable clientTranslationTable)

SECTIONS
{
	. = 0x00000000;
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
	elfAppl = .;
	. = ALIGN(0x10000);
	. += 0x00010000;
	bssStart = .;
	.bss :
	{
		* (.bss);
		. = ALIGN(0x4000);
		PROVIDE(kernelTranslationTable = .);
		. = . + 0x4000;
		. = ALIGN(0x4000);
		PROVIDE(clientTranslationTable = .);
		. = . + 0x4000;
	}
	bssEnd = .;
}
