/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for SPI - Secure Digital

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_SPI.h>
#include <Device/SPI_SecureDigital.h>

static Boolean startFirstResponseInput(UnsignedByte inputData, void *context)
{
    return (inputData != 0x3F) && ((inputData & 0x80) == 0x00);
}

static Boolean startResponseInput(UnsignedByte inputData, void *context)
{
    return (inputData & 0x80) == 0x00;
}

static Boolean stopResponseInput(UnsignedByte inputData, void *context)
{
    return FALSE;
}

static Boolean startDataInput(UnsignedByte inputData, void *context)
{
    if (inputData == 0xFE)
    {
        *((Boolean*) context) = FALSE;
        return TRUE;
    }
    else if ((inputData & 0xE0) == 0x00)
    {
        *((Boolean*) context) = TRUE;
        return TRUE;
    }
    else
        return FALSE;
}

static Boolean stopDataInput(UnsignedByte inputData, void *context)
{
    if (*((Boolean*) context))
        return TRUE;
    else
        return FALSE;
}

static UnsignedByte securedigitalSendFirstCommandR1(UnsignedByte command, UnsignedByte args[4], UnsignedByte crc)
{
    UnsignedByte outputData[6];
    UnsignedByte inputData[1];

    outputData[0] = (0x3F & command) | 0x40;
    UnsignedWord32 argsIndex;
    for (argsIndex = 0; argsIndex < 4; argsIndex++)
        outputData[argsIndex + 1] = args[argsIndex];
    outputData[5] = (crc << 1) | 0x01;
 
    Boolean context = FALSE;
    spiAsyncTransfer(1, outputData, inputData, 6, 1, startFirstResponseInput, stopResponseInput, &context);

    return inputData[0];
}

static UnsignedByte securedigitalSendCommandR1(UnsignedByte command, UnsignedByte args[4], UnsignedByte crc)
{
    UnsignedByte outputData[6];
    UnsignedByte inputData[1];

    outputData[0] = (0x3F & command) | 0x40;
    UnsignedWord32 argsIndex;
    for (argsIndex = 0; argsIndex < 4; argsIndex++)
        outputData[argsIndex + 1] = args[argsIndex];
    outputData[5] = (crc << 1) | 0x01;
 
    Boolean context = FALSE;
    //    logData("OutputData R1", outputData, 6);
    spiAsyncTransfer(1, outputData, inputData, 6, 1, startResponseInput, stopResponseInput, &context);
    //    logData("InputData  R1", inputData, 1);

    return inputData[0];
}

static UnsignedByte securedigitalSendCommandR3(UnsignedByte command, UnsignedByte args[4], UnsignedByte crc)
{
    UnsignedByte outputData[6];
    UnsignedByte inputData[5];

    outputData[0] = (0x3F & command) | 0x40;
    UnsignedWord32 argsIndex;
    for (argsIndex = 0; argsIndex < 4; argsIndex++)
        outputData[argsIndex + 1] = args[argsIndex];
    outputData[5] = (crc << 1) | 0x01;
 
    Boolean context = FALSE;
    //    logData("OutputData R3", outputData, 6);
    spiAsyncTransfer(1, outputData, inputData, 6, 5, startResponseInput, stopResponseInput, &context);
    //    logData("InputData  R3", inputData, 5);

    return inputData[0];
}

static UnsignedByte securedigitalSendCommandR7(UnsignedByte command, UnsignedByte args[4], UnsignedByte crc)
{
    UnsignedByte outputData[6];
    UnsignedByte inputData[5];

    outputData[0] = (0x3F & command) | 0x40;
    UnsignedWord32 argsIndex;
    for (argsIndex = 0; argsIndex < 4; argsIndex++)
        outputData[argsIndex + 1] = args[argsIndex];
    outputData[5] = (crc << 1) | 0x01;

    Boolean context = FALSE;
    //    logData("OutputData R7", outputData, 6);
    spiAsyncTransfer(1, outputData, inputData, 6, 5, startResponseInput, stopResponseInput, &context);
    //    logData("InputData  R7", inputData, 5);

    return inputData[0];
}

static UnsignedByte securedigitalReceiveData(UnsignedByte *inputData)
{
    UnsignedByte outputData[0];

    Boolean context = FALSE;
    spiAsyncTransfer(1, outputData, inputData, 0, 515, startDataInput, stopDataInput, &context);

    return inputData[0];
}

UnsignedByte securedigitalInit(void)
{
    spiSetClockRate(400000);

    UnsignedByte outputData[10];
    UnsignedByte inputData[10];

    UnsignedWord32 dataIndex;
    for (dataIndex = 0; dataIndex < 10; dataIndex++)
        outputData[dataIndex] = 0xFF;

    spiTransfer(2, outputData, inputData, 10);

    UnsignedByte args[4];

    UnsignedWord32 argsIndex;
    for (argsIndex = 0; argsIndex < 4; argsIndex++)
        args[argsIndex] = 0x00;

    securedigitalSendFirstCommandR1(0, args, 0x4A);

    securedigitalSendCommandR1(0, args, 0x4A);

    UnsignedByte res;
    args[2] = 0x01;
    args[3] = 0xAA;
    res = securedigitalSendCommandR7(8, args, 0x43);

    args[2] = 0x00;
    args[3] = 0x00;
    UnsignedWord32 count = 0;
    while ((res == 0x01) && (count < 1024))
    {
        securedigitalSendCommandR1(55, args, 0x00);

        args[0] = 0x40;
        res = securedigitalSendCommandR1(41, args, 0x00);
        args[0] = 0x00;
        count++;
    }

    if (res == 0x00)
        res = securedigitalSendCommandR3(58, args, 0x00);
 
    return res;
}

UnsignedByte securedigitalReadBlock(UnsignedWord32 blockNumber, UnsignedByte block[512])
{
    UnsignedByte res;
    UnsignedByte args[4];
    args[0] = (blockNumber >> 24) & 0xFF;
    args[1] = (blockNumber >> 16) & 0xFF;
    args[2] = (blockNumber >> 8) & 0xFF;
    args[3] = blockNumber & 0xFF;

    res = securedigitalSendCommandR1(17, args, 0x00);
    if (res == 0x00)
    {
        UnsignedWord32 index;
        UnsignedByte   inputData[515];

        res = securedigitalReceiveData(inputData);

        if (res == 0xFE)
            for (index = 0; index < 512; index++)
                block[index] = inputData[index + 1];

        return res;
    }
    else
        return res;
}
