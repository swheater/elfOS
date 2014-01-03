/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Log.h>

void elfOS_logUnsignedWord32Hex(UnsignedWord32 unsignedWord32)
{
    asm("swi\t#0x000041");
}

void elfOS_logMessage(const char *message)
{
    asm("swi\t#0x000042");
}
