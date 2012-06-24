/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Process.h>

void elfOS_processYield(void)
{
    asm("mov\tr0,#1": : : "r0");
    asm("swi\t#0x000001");
}

void elfOS_processStop(void)
{
    asm("mov\tr0,#2": : : "r0");
    asm("swi\t#0x000002");
}

void elfOS_processLogging(int param)
{
    asm("mov\tr0,%0": : "r" (param): "r0");
    asm("swi\t#0x000003");
}
