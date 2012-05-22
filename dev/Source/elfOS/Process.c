/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Process.h>

void elfOS_processYield(void)
{
    asm("swi\t#0x000001");
}

void elfOS_processStop(void)
{
    asm("swi\t#0x000000");
}
