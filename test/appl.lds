/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

SECTIONS
{
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
	.bss :
	{
		* (.bss);
	}
}
