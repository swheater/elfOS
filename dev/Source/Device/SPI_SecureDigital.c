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

UnsignedByte securedigitalSendCommandR1(UnsignedByte command, UnsignedByte args[4], UnsignedByte crc)
{
    UnsignedWord32 outputData[6];
    UnsignedWord32 inputData[1];

    outputData[0] = (0x0000003F & command) | 0x00000040;
    UnsignedWord32 argsIndex;
    for (argsIndex = 0; argsIndex < 4; argsIndex++)
        outputData[argsIndex + 1] = args[argsIndex];
    outputData[5] = (crc << 1) | 0x00000001;

    //    logData("Request", outputData, 6);
    spiAsyncTransfer(1, outputData, inputData, 6, 1);
    //    logData("Response", inputData, 1);

    return inputData[0];
}

UnsignedByte securedigitalSendCommandR7(UnsignedByte command, UnsignedByte args[4], UnsignedByte crc)
{
    UnsignedWord32 outputData[6];
    UnsignedWord32 inputData[5];

    outputData[0] = (0x0000003F & command) | 0x00000040;
    UnsignedWord32 argsIndex;
    for (argsIndex = 0; argsIndex < 4; argsIndex++)
        outputData[argsIndex + 1] = args[argsIndex];
    outputData[5] = (crc << 1) | 0x00000001;

    //    logData("Request", outputData, 6);
    spiAsyncTransfer(1, outputData, inputData, 6, 5);
    //    logData("Response", inputData, 5);

    return inputData[0];
}

void securedigitalTest(void)
{
    UnsignedByte args[4];

    UnsignedWord32 argsIndex;
    for (argsIndex = 0; argsIndex < 4; argsIndex++)
        args[argsIndex] = 0x00;

    securedigitalSendCommandR1(0, args, 0x4A);

    securedigitalSendCommandR1(0, args, 0x4A);

    UnsignedByte res;
    args[2] = 0x01;
    args[3] = 0xAA;
    res = securedigitalSendCommandR7(8, args, 0x43);
    args[2] = 0x00;
    args[3] = 0x00;

    UnsignedWord32 count = 0;
    while ((res == 0x01) && (count < 16))
    {
        securedigitalSendCommandR1(55, args, 0x00);

        args[0] = 0x40;
        res = securedigitalSendCommandR1(41, args, 0x00);
        args[0] = 0x00;
        count++;
    }

    logUnsignedByteHex(res);
    logMessage("\r\n");
    logUnsignedWord32Hex(count++);
    logMessage("\r\n");
}
