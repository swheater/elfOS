/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for SPI - Secure Digital

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_SPI.h>
#include <Device/SPI_SecureDigital.h>

static void logData(const char *message, UnsignedWord32 data[], UnsignedWord32 dataLength)
{
    logMessage(message);
    logMessage(":");
    UnsignedWord32 dataIndex;
    for (dataIndex = 0; dataIndex < dataLength; dataIndex++)
    {
        if ((dataIndex % 16) == 0)
            logMessage("\r\n");

        logMessage(" ");
        logUnsignedByteHex(data[dataIndex]);
    }
    logMessage("\r\n");
}

void securedigitalInit(void)
{
    spiSetClockRate(400000);

    UnsignedWord32 outputData[10];
    UnsignedWord32 inputData[10];

    UnsignedWord32 dataIndex;
    for (dataIndex = 0; dataIndex < 10; dataIndex++)
        outputData[dataIndex] = 0xFF;

    spiTransfer(2, outputData, inputData, 10);
}

void securedigitalSendCommand(UnsignedByte command, UnsignedByte args[4], UnsignedByte crc)
{
    UnsignedWord32 outputData[6];
    UnsignedWord32 inputData[1];

    outputData[0] = (0x0000003F & command) | 0x00000040;
    UnsignedWord32 argsIndex;
    for (argsIndex = 0; argsIndex < 4; argsIndex++)
        outputData[argsIndex + 1] = args[argsIndex];
    outputData[5] = (crc << 1) | 0x00000001;

    logData("Request", outputData, 6);
    spiAsyncTransfer(0, outputData, inputData, 6, 1);
    logData("Response", inputData, 1);
}

void securedigitalTest(void)
{
    UnsignedByte args[4];

    UnsignedWord32 argsIndex;
    for (argsIndex = 0; argsIndex < 4; argsIndex++)
        args[argsIndex] = 0x00;

    securedigitalSendCommand(0, args, 0x4A);

    securedigitalSendCommand(0, args, 0x4A);

    UnsignedWord32 count = 0;
    while (count < 8)
    {
        securedigitalSendCommand(55, args, 0x00);

        securedigitalSendCommand(41, args, 0x00);

        logUnsignedWord32Hex(count++);
        logMessage("\r\n");
    }
}
