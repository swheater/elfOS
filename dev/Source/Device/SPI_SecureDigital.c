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
        if ((dataIndex % 7) == 0)
            logMessage("\r\n");

        logMessage(" ");
        logUnsignedByteHex(data[dataIndex]);
    }
    logMessage("\r\n");
}

void securedigitalInit(void)
{
    spiSetClockRate(400000);

    UnsignedWord32 outputData[14];
    UnsignedWord32 inputData[14];

    UnsignedWord32 dataIndex;
    for (dataIndex = 0; dataIndex < 14; dataIndex++)
       outputData[dataIndex] = 0xFF;

    logData("State-up, Output", outputData, 14);
    spiTransfer(2, outputData, inputData, 14);
    logData("Start-up, Input", inputData, 14);
}

void securedigitalSendCommand(UnsignedByte command, UnsignedByte args[6], UnsignedByte crc)
{
    UnsignedWord32 outputData[42];
    UnsignedWord32 inputData[42];

    UnsignedWord32 dataIndex;
    for (dataIndex = 0; dataIndex < 42; dataIndex++)
        outputData[dataIndex] = 0xFF;

    outputData[0] = (0x000000C0 & command) | 0x00000040;
    UnsignedWord32 argsIndex;
    for (argsIndex = 0; argsIndex < 6; argsIndex++)
        outputData[argsIndex + 1] = args[argsIndex];
    outputData[7] = (crc << 1) | 0x00000001;

    logData("Command", outputData, 8);
    spiTransfer(0, outputData, inputData, 42);
    logData("Command", inputData, 42);
}

void securedigitalTest(void)
{
    UnsignedByte args[6];

    UnsignedWord32 argsIndex;
    for (argsIndex = 0; argsIndex < 6; argsIndex++)
        args[argsIndex] = 0x00;

    securedigitalSendCommand(0, args, 0x00);
}
