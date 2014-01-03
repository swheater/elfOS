/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Thread.h>

void elfOS_threadYield(void)
{
    asm("mov\tr0,#0": : : "r0");
    asm("swi\t#0x000001");
}

void elfOS_threadStop(void)
{
    asm("mov\tr0,#0": : : "r0");
    asm("swi\t#0x000002");
}
