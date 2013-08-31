/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for BCM2835 - SPI0

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_SPI.h>

#define GPIO_BASE                ((volatile UnsignedWord32*) 0x20200000)
#define GPIO_FUNCSELECT_BASE     (GPIO_BASE + 0x00)
#define GPIO_FUNCSELECT_0_OFFSET (0x00)
#define GPIO_FUNCSELECT_1_OFFSET (0x01)

#define SPI_BASE                 ((volatile UnsignedWord32*) 0x20204000)
#define SPI_CONTROLSTATUS_OFFSET (0x00)
#define SPI_DATAFIFO_OFFSET      (0x01)
#define SPI_CLOCKDIVIDER_OFFSET  (0x02)

#define SPI_CONTROLSTATUS_CHIPSELECT_MASK       (0x00000003)
#define SPI_CONTROLSTATUS_CHIPSELECT_0_BITS     (0x00000000)
#define SPI_CONTROLSTATUS_CHIPSELECT_1_BITS     (0x00000001)
#define SPI_CONTROLSTATUS_CHIPSELECT_2_BITS     (0x00000002)
#define SPI_CONTROLSTATUS_CLEARFIFO_MASK        (0x00000030)
#define SPI_CONTROLSTATUS_CLEARFIFO_TX_BIT      (0x00000010)
#define SPI_CONTROLSTATUS_CLEARFIFO_RX_BIT      (0x00000020)
#define SPI_CONTROLSTATUS_TRANSFERACTIVITY_MASK (0x00000080)
#define SPI_CONTROLSTATUS_NOTRANSFERACTIVE_BIT  (0x00000000)
#define SPI_CONTROLSTATUS_TRANSFERACTIVE_BIT    (0x00000080)
#define SPI_CONTROLSTATUS_DONETRANSFER_MASK     (0x00010000)
#define SPI_CONTROLSTATUS_DONETRANSFER_BIT      (0x00010000)
#define SPI_CONTROLSTATUS_CONTAINSDATA_MASK     (0x00020000)
#define SPI_CONTROLSTATUS_CONTAINSDATA_BIT      (0x00020000)
#define SPI_CONTROLSTATUS_CANACCEPTDATA_MASK    (0x00040000)
#define SPI_CONTROLSTATUS_CANACCEPTDATA_BIT     (0x00040000)

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

    // Set Clock Divider to 250 for 1MHz clock
    *(SPI_BASE + SPI_CLOCKDIVIDER_OFFSET) = 250;
}

void spiTransfer(UnsignedByte chip, UnsignedWord32 outputData[], UnsignedWord32 inputData[], UnsignedWord32 dataLength)
{
    spiDebug("Entry");
    // Start transfer, Read
    UnsignedWord32 spiStart = *(SPI_BASE + SPI_CONTROLSTATUS_OFFSET);
    spiStart &= ~ (SPI_CONTROLSTATUS_CHIPSELECT_MASK | SPI_CONTROLSTATUS_TRANSFERACTIVITY_MASK | SPI_CONTROLSTATUS_CLEARFIFO_MASK);
    spiStart |= (SPI_CONTROLSTATUS_CHIPSELECT_MASK & chip) | SPI_CONTROLSTATUS_TRANSFERACTIVE_BIT | SPI_CONTROLSTATUS_CLEARFIFO_TX_BIT | SPI_CONTROLSTATUS_CLEARFIFO_RX_BIT;
    *(SPI_BASE + SPI_CONTROLSTATUS_OFFSET) = spiStart;

    spiDebug("PostStart");

    int count = 0;

    UnsignedWord32 outputDataIndex = 0;
    UnsignedWord32 inputDataIndex  = 0;
    while ((outputDataIndex < dataLength) || (inputDataIndex < dataLength))
    {
        if (count > 10000000)
	{
            spiDebug("Loop");
            count = 0;
	}
        else
  	    count++;

        while ((outputDataIndex < dataLength) && (((*(SPI_BASE + SPI_CONTROLSTATUS_OFFSET)) & SPI_CONTROLSTATUS_CANACCEPTDATA_MASK) == SPI_CONTROLSTATUS_CANACCEPTDATA_BIT))
	{
 	    *(SPI_BASE + SPI_DATAFIFO_OFFSET) = outputData[outputDataIndex++];
            logMessage("w");
	}

        while ((inputDataIndex < dataLength) && (((*(SPI_BASE + SPI_CONTROLSTATUS_OFFSET)) & SPI_CONTROLSTATUS_CONTAINSDATA_MASK) == SPI_CONTROLSTATUS_CONTAINSDATA_BIT))
	{
            inputData[inputDataIndex++] = *(SPI_BASE + SPI_DATAFIFO_OFFSET);
            logMessage("r");
	}
    }

    spiDebug("PreDone");

    // Wait for Done transfer
    while (((*(SPI_BASE + SPI_CONTROLSTATUS_OFFSET)) & SPI_CONTROLSTATUS_DONETRANSFER_MASK) == 0);

    spiDebug("PostDone");

    // Terminate transfer
    UnsignedWord32 spiTerminate = *(SPI_BASE + SPI_CONTROLSTATUS_OFFSET);
    spiTerminate &= ~ SPI_CONTROLSTATUS_TRANSFERACTIVITY_MASK;
    spiTerminate |= SPI_CONTROLSTATUS_NOTRANSFERACTIVE_BIT;
    *(SPI_BASE + SPI_CONTROLSTATUS_OFFSET) = spiTerminate;
    spiDebug("Exit");
}

void spiDebug(const char *message)
{
    logMessage("\r\nSPI: ");
    logMessage(message);
    logMessage("\r\nCtrlStat: ");
    logUnsignedWord32Hex(*(SPI_BASE + SPI_CONTROLSTATUS_OFFSET));
    logMessage("\r\n");
}
