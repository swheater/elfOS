/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

EXTERN(resetStack kernelTranslationTable containerTranslationTable)
EXTERN(kernelBSSSectionStart kernelSectionStart kernelBSSSectionEnd kernelSectionEnd)
EXTERN(elfAppl)

MEMORY
{
	reset :		org = 0x00000000, len = 2048M
	kernel :	org = 0x80006000, len = 2048M
}

SECTIONS
{
	. = 0x00000000;

	.text.reset :
	{
		resetSectionStart = .;
                Source/Reset/ARM/ZeroPage.o (.text);
		Source/Reset/ARMv6/Init.o (.text);
	} > reset
	.bss.reset :
	{
		. = ALIGN(0x2000);
		PROVIDE(resetStack = .);
		PROVIDE(kernelTranslationTable = .);
		. = . + 0x2000;
		PROVIDE(containerTranslationTable = .);
		. = . + 0x2000;
		resetSectionEnd = .;
	} > reset
	.text : AT (resetSectionEnd - resetSectionStart)
	{
		kernelSectionStart = .;
                * (.text);
	} > kernel
	.rodata :
	{
		* (.rodata);
	} > kernel
	.data :
	{
		* (.data);
	} > kernel
	.bss :
	{
		elfAppl = .;
		. = . + 0x8000;
		kernelBSSSectionStart = .;
		* (.bss);
		kernelBSSSectionEnd = .;
		kernelSectionEnd = .;
	} > kernel
}
