/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/Logging.h>
#include <Device/RaspPi_UART.h>

void logMessage(const char *message)
{
    while (*message != 0)
    {
        uartOutput(*message);
        message++;
    }
}
