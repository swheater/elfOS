/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Threading.h>

void elfOS_yield(void)
{
    asm("swi\t#0x190019");
}
