/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Segment.h>

void elfOS_segmentYield(void)
{
    asm("mov\tr0,#0": : : "r0");
    asm("swi\t#0x000021");
}

void elfOS_segmentStop(void)
{
    asm("mov\tr0,#0": : : "r0");
    asm("swi\t#0x000022");
}
