/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Device/BCM2835_miniUART.h>
#include <Kernel/Logging.h>

void logUnsignedByteHex(UnsignedByte unsignedByte)
{
    int index;
    for (index = 0; index < 2; index++)
    {
        UnsignedByte digit = unsignedByte >> 4;
        if (digit < 10)
            uartOutput(digit + '0');
        else
            uartOutput(digit + 'A' - 10);
        unsignedByte <<= 4;
    }
}

void logUnsignedByteASCII(UnsignedByte unsignedByte)
{
    if ((unsignedByte >= 32) && (unsignedByte <= 127))
        uartOutput(unsignedByte);
    else
        uartOutput(191);
}

void logUnsignedWord16Hex(UnsignedWord16 unsignedWord16)
{
    int index;
    for (index = 0; index < 4; index++)
    {
        UnsignedWord16 digit = unsignedWord16 >> 12;
        if (digit < 10)
            uartOutput(digit + '0');
        else
            uartOutput(digit + 'A' - 10);
        unsignedWord16 <<= 4;
    }
}

void logUnsignedWord32Hex(UnsignedWord32 unsignedWord32)
{
    int index;
    for (index = 0; index < 8; index++)
    {
        UnsignedWord32 digit = unsignedWord32 >> 28;
        if (digit < 10)
            uartOutput(digit + '0');
        else
            uartOutput(digit + 'A' - 10);
        unsignedWord32 <<= 4;
    }
}

void logUnsignedWord32Bin(UnsignedWord32 unsignedWord32)
{
    int index;
    for (index = 0; index < 32; index++)
    {
        UnsignedWord32 digit = unsignedWord32 >> 31;
        if (digit != 0)
            uartOutput('1');
        else
            uartOutput('0');
        unsignedWord32 <<= 1;
    }
}

void logUnsignedWord64Hex(UnsignedWord64 unsignedWord64)
{
    int index;
    for (index = 0; index < 16; index++)
    {
        UnsignedWord64 digit = unsignedWord64 >> 60;
        if (digit < 10)
            uartOutput(digit + '0');
        else
            uartOutput(digit + 'A' - 10);
        unsignedWord64 <<= 4;
    }
}

void logDataHex(UnsignedByte data[], UnsignedWord32 dataLength)
{
    UnsignedWord32 dataIndex;
    for (dataIndex = 0; dataIndex < dataLength; dataIndex++)
    {
        if (dataIndex != 0)
            logMessage(" ");
        logUnsignedByteHex(data[dataIndex]);
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

void logData(const char *message, UnsignedByte data[], UnsignedWord32 dataLength)
{
    logMessage(message);
    logMessage(":");
    UnsignedWord32 dataIndex;
    for (dataIndex = 0; dataIndex < dataLength; dataIndex++)
    {
        if ((dataIndex % 40) == 0)
            logMessage("\r\n");

        logMessage(" ");
        logUnsignedByteHex(data[dataIndex]);
    }
    logMessage("\r\n");
}

void logNewLine(void)
{
    uartOutput('\r');
    uartOutput('\n');
}
