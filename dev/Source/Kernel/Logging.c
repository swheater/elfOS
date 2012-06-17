/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.

 */

#include <Kernel/StdTypes.h>
#include <Device/RaspPi_UART.h>
#include <Kernel/Logging.h>

void logUnsignedWord32Hex(UnsignedWord32 unsignedWord32)
{
    int index;
    for (index = 0; index < 8; index++)
    {
        unsigned int digit = unsignedWord32 >> 28;
        if (digit < 10)
            uartOutput(digit + '0');
        else
            uartOutput(digit + 'A' - 10);
        unsignedWord32 <<= 4;
    }
}


void logMessage(const char *message)
{
    while (*message != 0) 
    {
        uartOutput(*message);
        message++;
    }
}
