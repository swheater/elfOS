/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for SPI - PN512

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_SPI.h>
#include <Device/SPI_PN512.h>

void pn512Init(void)
{
    spiSetClockRate(10000000);
}

void pn512ReadRegister(UnsignedByte chipSelect, UnsignedByte registAddr, UnsignedByte *value)
{
    UnsignedByte outputData[2];
    UnsignedByte inputData[2];

    outputData[0] = (registAddr << 1) | 0x80;
    outputData[1] = 0x00;

    spiTransfer(chipSelect, outputData, inputData, 2);

    *value = inputData[1];
}

void pn512WriteRegister(UnsignedByte chipSelect, UnsignedByte registAddr, UnsignedByte value)
{
    UnsignedByte outputData[2];
    UnsignedByte inputData[2];

    outputData[0] = (registAddr << 1) & 0x7F;
    outputData[1] = value;

    spiTransfer(chipSelect, outputData, inputData, 2);
}

void pn512Test(void)
{
    UnsignedByte value[64];
    UnsignedByte index;

    for (index = 0; index < 64; index++)
    {
        pn512ReadRegister(0, index, &value[index]);

        logMessage("Reg: ");
        logUnsignedByteHex(index);
        logMessage(" = ");
        logUnsignedByteHex(value[index]);
        logNewLine();
    }

    logNewLine();

    UnsignedByte currentValue;
    while (TRUE)
    {
        for (index = 0; index < 64; index++)
        {
            pn512ReadRegister(0, index, &currentValue);

            if (currentValue != value[index])
	    {
                logMessage("Reg: ");
                logUnsignedByteHex(index);
                logMessage(" = ");
                logUnsignedByteHex(currentValue);
                logNewLine();
	    }
        }
    }
}

void pn512Shutdown(void)
{
}
