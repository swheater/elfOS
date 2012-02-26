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
	.data :
	{
		* (.data);
	}
	.bss :
	{
		* (.bss);
	}
}
