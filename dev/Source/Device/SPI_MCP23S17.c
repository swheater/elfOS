/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for SPI - MCP23S17

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_SPI.h>
#include <Device/SPI_MCP23S17.h>

void mcp23s17Init(void)
{
    spiSetClockRate(10000000);
}

void mcp23s17ReadRegister(UnsignedByte chipSelect, UnsignedByte chipAddr, UnsignedByte regist, UnsignedByte *value)
{
    UnsignedByte outputData[3];
    UnsignedByte inputData[3];

    outputData[0] = 0x41 | ((chipAddr & 0x07) << 1);
    outputData[1] = regist;
    outputData[2] = 0x00;

    spiTransfer(chipSelect, outputData, inputData, 3);
    
    *value = inputData[2];
}

void mcp23s17WriteRegister(UnsignedByte chipSelect, UnsignedByte chipAddr, UnsignedByte regist, UnsignedByte value)
{
    UnsignedByte outputData[3];
    UnsignedByte inputData[3];

    outputData[0] = 0x40 | ((chipAddr & 0x07) << 1);
    outputData[1] = regist;
    outputData[2] = value;

    spiTransfer(chipSelect, outputData, inputData, 3);
}

void mcp23s17Shutdown(void)
{
}
