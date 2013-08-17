/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for BCM2835 - SPI0

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_SPI.h>
#include <Device/BCM2835_miniUART.h>

#define GPIO_BASE                ((volatile UnsignedWord32*) 0x20200000)
#define GPIO_FUNCSELECT_BASE     (GPIO_BASE + 0x00)
#define GPIO_FUNCSELECT_0_OFFSET (0x00)
#define GPIO_FUNCSELECT_1_OFFSET (0x01)

#define SPI_BASE                 ((volatile UnsignedWord32*) 0x20204000)
#define SPI_CONTROLSTATUS_OFFSET (0x00)
#define SPI_DATAFIFO_OFFSET      (0x01)

#define SPI_CONTROLSTATUS_CHIPSELECT_MASK       (0x00000003)
#define SPI_CONTROLSTATUS_CHIPSELECT_0_BITS     (0x00000000)
#define SPI_CONTROLSTATUS_CHIPSELECT_1_BITS     (0x00000001)
#define SPI_CONTROLSTATUS_CHIPSELECT_2_BITS     (0x00000002)
#define SPI_CONTROLSTATUS_TRANSFERACTIVITY_MASK (0x00000080)
#define SPI_CONTROLSTATUS_NOTRANSFERACTIVE_BIT  (0x00000000)
#define SPI_CONTROLSTATUS_TRANSFERACTIVE_BIT    (0x00000080)
#define SPI_CONTROLSTATUS_DONETRANSFER_MASK     (0x00000100)
#define SPI_CONTROLSTATUS_DONETRANSFER_BIT      (0x00000100)
#define SPI_CONTROLSTATUS_CONTAINSDATA_MASK     (0x00000200)
#define SPI_CONTROLSTATUS_CONTAINSDATA_BIT      (0x00000200)
#define SPI_CONTROLSTATUS_CANACCEPTDATA_MASK    (0x00000400)
#define SPI_CONTROLSTATUS_CANACCEPTDATA_BIT     (0x00000400)

void spiInit(void)
{
    // Select function for GPIO7, GPI08 & GPIO9
    UnsignedWord32 gpioFuncSelect;
    gpioFuncSelect = *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_0_OFFSET);
    gpioFuncSelect &= 0xC01FFFFF;
    gpioFuncSelect |= 0x24800000;
    *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_0_OFFSET) = gpioFuncSelect;

    // Select function for GPIO10 & GPIO11
    gpioFuncSelect = *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_1_OFFSET);
    gpioFuncSelect &= 0xFFFFFFC0;
    gpioFuncSelect |= 0x00000024;
    *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_1_OFFSET) = gpioFuncSelect;
}

void spiRead(UnsignedByte chip, UnsignedWord32 data[], UnsignedWord16 dataLength)
{
    // Start transfer, Read
    UnsignedWord32 spiStart = *(SPI_BASE + SPI_CONTROLSTATUS_OFFSET);
    spiStart &= ~ (SPI_CONTROLSTATUS_CHIPSELECT_MASK | SPI_CONTROLSTATUS_TRANSFERACTIVITY_MASK);
    spiStart |= (SPI_CONTROLSTATUS_CHIPSELECT_MASK & chip) | SPI_CONTROLSTATUS_TRANSFERACTIVE_BIT;
    *(SPI_BASE + SPI_CONTROLSTATUS_OFFSET) = spiStart;

    int dataIndex;
    for (dataIndex = 0; dataIndex < dataLength; dataIndex++)
    {
        while (((*(SPI_BASE + SPI_CONTROLSTATUS_OFFSET)) & SPI_CONTROLSTATUS_CONTAINSDATA_MASK) == 0);

        data[dataIndex] = *(SPI_BASE + SPI_DATAFIFO_OFFSET);
    }

    // Wait for Done transfer
    while (((*(SPI_BASE + SPI_CONTROLSTATUS_OFFSET)) & SPI_CONTROLSTATUS_DONETRANSFER_MASK) == 0);

    // Terminate transfer
    UnsignedWord32 spiTerminate = *(SPI_BASE + SPI_CONTROLSTATUS_OFFSET);
    spiTerminate &= ~ SPI_CONTROLSTATUS_TRANSFERACTIVITY_MASK;
    spiTerminate |= SPI_CONTROLSTATUS_NOTRANSFERACTIVE_BIT;
    *(SPI_BASE + SPI_CONTROLSTATUS_OFFSET) = spiTerminate;
}

void spiWrite(UnsignedByte chip, UnsignedWord32 data[], UnsignedWord16 dataLength)
{
    // Start transfer, Write
    UnsignedWord32 spiStart = *(SPI_BASE + SPI_CONTROLSTATUS_OFFSET);
    spiStart &= ~ (SPI_CONTROLSTATUS_CHIPSELECT_MASK | SPI_CONTROLSTATUS_TRANSFERACTIVITY_MASK);
    spiStart |= (SPI_CONTROLSTATUS_CHIPSELECT_MASK & chip) | SPI_CONTROLSTATUS_TRANSFERACTIVE_BIT;
    *(SPI_BASE + SPI_CONTROLSTATUS_OFFSET) = spiStart;

    int dataIndex;
    for (dataIndex = 0; dataIndex < dataLength; dataIndex++)
    {
        while (((*(SPI_BASE + SPI_CONTROLSTATUS_OFFSET)) & SPI_CONTROLSTATUS_CONTAINSDATA_MASK) == 0);

        data[dataIndex] = *(SPI_BASE + SPI_DATAFIFO_OFFSET);
    }

    // Wait for Done transfer
    while (((*(SPI_BASE + SPI_CONTROLSTATUS_OFFSET)) & SPI_CONTROLSTATUS_DONETRANSFER_MASK) == 0);

    // Terminate transfer
    UnsignedWord32 spiTerminate = *(SPI_BASE + SPI_CONTROLSTATUS_OFFSET);
    spiTerminate &= ~ SPI_CONTROLSTATUS_TRANSFERACTIVITY_MASK;
    spiTerminate |= SPI_CONTROLSTATUS_NOTRANSFERACTIVE_BIT;
    *(SPI_BASE + SPI_CONTROLSTATUS_OFFSET) = spiTerminate;
}

void spiDebug(void)
{
    logMessage("\r\nSPI:");
    logMessage("\r\nCtrlStat: ");
    logUnsignedWord32Hex(*(SPI_BASE + SPI_CONTROLSTATUS_OFFSET));
    logMessage("\r\n");
}
