/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Container.h>

void elfOS_containerCreate(void)
{
    asm("mov\tr0,#0": : : "r0");
    asm("swi\t#0x000011");
}

void elfOS_containerDestroy(void)
{
    asm("mov\tr0,#0": : : "r0");
    asm("swi\t#0x000012");
}
