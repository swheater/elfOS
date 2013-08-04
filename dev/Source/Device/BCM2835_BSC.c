/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for BCM2835 - BSC0 & BSC1 (I2C0 & I2C1)

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_BSC.h>
#include <Device/BCM2835_miniUART.h>

#define GPIO_BASE                ((volatile UnsignedWord32*) 0x20200000)
#define GPIO_FUNCSELECT_BASE     (GPIO_BASE + 0x00)
#define GPIO_FUNCSELECT_0_OFFSET (0x00)

#define BSC0_BASE                      ((volatile UnsignedWord32*) 0x20205000)
#define BSC1_BASE                      ((volatile UnsignedWord32*) 0x20804000)
#define BSC_CONTROL_OFFSET             (0x00)
#define BSC_STATUS_OFFSET              (0x01)
#define BSC_DATALENGTH_OFFSET          (0x02)
#define BSC_SLAVEADDRESS_OFFSET        (0x03)
#define BSC_DATAFIFO_OFFSET            (0x04)
#define BSC_CLOCKDIVIDER_OFFSET        (0x05)
#define BSC_DATADELAY_OFFSET           (0x06)
#define BSC_CLOCKSTRETCHTIMEOUT_OFFSET (0x07)

#define BSC_CONTROL_OPERATION_MASK      (0x00000001)
#define BSC_CONTROL_READ_OPERATION_BIT  (0x00000001)
#define BSC_CONTROL_WRITE_OPERATION_BIT (0x00000000)
#define BSC_CONTROL_STARTTRANSFER_MASK  (0x00000080)
#define BSC_CONTROL_STARTTRANSFER_BIT   (0x00000080)
#define BSC_CONTROL_CLEARFIFO_MASK      (0x00000030)
#define BSC_CONTROL_CLEARFIFO_BITS      (0x00000010)
#define BSC_CONTROL_ENABLE_MASK         (0x00008000)
#define BSC_CONTROL_ENABLE_BIT          (0x00008000)
#define BSC_CONTROL_DISABLE_BIT         (0x00000000)

#define BSC_STATUS_TRANSFERACTIVE_MASK (0x00000001)
#define BSC_STATUS_TRANSFERACTIVE_BIT  (0x00000001)
#define BSC_STATUS_DONE_MASK           (0x00000002)
#define BSC_STATUS_DONE_BIT            (0x00000002)
#define BSC_STATUS_CONTAINSSPACE_MASK  (0x00000010)
#define BSC_STATUS_CONTAINSSPACE_BIT   (0x00000010)
#define BSC_STATUS_CONTAINSDATA_MASK   (0x00000020)
#define BSC_STATUS_CONTAINSDATA_BIT    (0x00000020)

volatile UnsignedWord32* getBusBase(UnsignedByte bus)
{
    if (bus == 0)
        return BSC0_BASE;
    else if (bus == 1)
        return BSC1_BASE;
    else
        return 0;
}

void i2cInit(UnsignedByte bus)
{
    volatile UnsignedWord32* base = getBusBase(bus);

    // Enable & Clear FIFO
    if (base != 0)
    {
        // Select function  for GPIO01 & GPI02
        UnsignedWord32 gpioFuncSelect = *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_0_OFFSET);
        gpioFuncSelect &= 0xFFFFFFC0;
        gpioFuncSelect |= 0x00000024;
        *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_0_OFFSET) = gpioFuncSelect;

        *(base + BSC_CONTROL_OFFSET) = BSC_CONTROL_ENABLE_BIT | BSC_CONTROL_CLEARFIFO_BITS;
    }
}

void i2cRead(UnsignedByte bus, UnsignedByte address, UnsignedByte data[], UnsignedWord16 dataLength)
{
    volatile UnsignedWord32* base = getBusBase(bus);

    if (base != 0)
    {
        // Wait for no Active Transfer
        while (((*(base + BSC_STATUS_OFFSET)) & BSC_STATUS_TRANSFERACTIVE_MASK) != 0);

        // Clear Clock Stretch Timeout, Ack Error & Done
        *(base + BSC_STATUS_OFFSET) = BSC_CONTROL_CLEARFIFO_BITS | BSC_STATUS_DONE_BIT;

        *(base + BSC_SLAVEADDRESS_OFFSET) = address;
        *(base + BSC_DATALENGTH_OFFSET)   = dataLength;

        // Start transfer, Read
        UnsignedWord32 bscControl = *(base + BSC_CONTROL_OFFSET);
        bscControl &= ~ (BSC_CONTROL_STARTTRANSFER_MASK | BSC_CONTROL_OPERATION_MASK);
        bscControl |= BSC_CONTROL_STARTTRANSFER_BIT | BSC_CONTROL_READ_OPERATION_BIT;
        *(base + BSC_CONTROL_OFFSET) = bscControl;

        int dataIndex;
        for (dataIndex = 0; dataIndex < dataLength; dataIndex++)
        {
            while (((*(base + BSC_STATUS_OFFSET)) & BSC_STATUS_CONTAINSDATA_MASK) == 0);

            data[dataIndex] = *(base + BSC_DATAFIFO_OFFSET);
        }

        // Wait for Done
        while (((*(base + BSC_STATUS_OFFSET)) & BSC_STATUS_DONE_MASK) != 0);
    }
}

void i2cWrite(UnsignedByte bus, UnsignedByte address, UnsignedByte data[], UnsignedWord16 dataLength)
{
    volatile UnsignedWord32* base = getBusBase(bus);

    if (base != 0)
    {
        // Wait for no Active Transfer
        while (((*(base + BSC_STATUS_OFFSET)) & BSC_STATUS_TRANSFERACTIVE_MASK) != 0);

        // Clear Clock Stretch Timeout, Ack Error & Done
        *(base + BSC_STATUS_OFFSET) = BSC_CONTROL_CLEARFIFO_BITS | BSC_STATUS_DONE_BIT;

        *(base + BSC_SLAVEADDRESS_OFFSET) = address;
        *(base + BSC_DATALENGTH_OFFSET)   = dataLength;

        // Load Data
        int dataIndex = 0;
        while ((dataIndex < dataLength) && (((*(base + BSC_STATUS_OFFSET)) & BSC_STATUS_CONTAINSSPACE_MASK) != 0))
        {
            *(base + BSC_DATAFIFO_OFFSET) = data[dataIndex];
            dataIndex++;
        }

        // Start transfer
        UnsignedWord32 bscControl = *(base + BSC_CONTROL_OFFSET);
        bscControl &= ~ (BSC_CONTROL_STARTTRANSFER_MASK | BSC_CONTROL_OPERATION_MASK);
        bscControl |= BSC_CONTROL_STARTTRANSFER_BIT | BSC_CONTROL_WRITE_OPERATION_BIT;
        *(base + BSC_CONTROL_OFFSET) = bscControl;

        while (dataIndex < dataLength)
        {
            while (((*(base + BSC_STATUS_OFFSET)) & BSC_STATUS_CONTAINSSPACE_MASK) == 0);

            *(base + BSC_DATAFIFO_OFFSET) = data[dataIndex];
            dataIndex++;
        }

        // Wait for Done
        while (((*(base + BSC_STATUS_OFFSET)) & BSC_STATUS_DONE_MASK) != 0);
    }
}

void i2cDebug(volatile UnsignedWord32 *base)
{
    logMessage("\r\nI2C:");
    logMessage("\r\nCtrl:   ");
    logUnsignedWord32Hex(*(base + BSC_CONTROL_OFFSET));
    logMessage("\r\nStat:   ");
    logUnsignedWord32Hex(*(base + BSC_STATUS_OFFSET));
    logMessage("\r\nD Len:  ");
    logUnsignedWord32Hex(*(base + BSC_DATALENGTH_OFFSET));
    logMessage("\r\nS Addr: ");
    logUnsignedWord32Hex(*(base + BSC_SLAVEADDRESS_OFFSET));
    logMessage("\r\nD FIFO: ");
    logUnsignedWord32Hex(*(base + BSC_DATAFIFO_OFFSET));
    logMessage("\r\n");
}
