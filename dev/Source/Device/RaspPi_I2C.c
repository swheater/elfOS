/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi, I2C0 & I2C1 (BSC0 & BSC1)

#include <Kernel/StdTypes.h>
#include <Device/RaspPi_I2C.h>

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
#define BSC_CONTROL_STARTTRANSFER_MASK  (0x00000008)
#define BSC_CONTROL_STARTTRANSFER_BIT   (0x00000008)
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
        *(base + BSC_CONTROL_OFFSET) = BSC_CONTROL_ENABLE_BIT | BSC_CONTROL_CLEARFIFO_BITS;
}

void i2cRead(UnsignedByte bus, UnsignedByte device, UnsignedByte address, UnsignedByte data[], UnsignedWord16 dataLength)
{
    volatile UnsignedWord32* base = getBusBase(bus);

    if (base != 0)
    {
        // Wait for no Active Transfer
        while ((*(base + BSC_STATUS_OFFSET) & BSC_STATUS_TRANSFERACTIVE_MASK) == BSC_STATUS_TRANSFERACTIVE_BIT);

        // Clear Clock Stretch Timeout, Ack Error & Done
        *(base + BSC_STATUS_OFFSET) = BSC_CONTROL_CLEARFIFO_BITS | BSC_STATUS_DONE_BIT;

	*(base + BSC_SLAVEADDRESS_OFFSET) = address;
        *(base + BSC_DATALENGTH_OFFSET)   = dataLength;

        // Start transfer
        *(base + BSC_CONTROL_OFFSET) = *(base + BSC_CONTROL_OFFSET) | BSC_CONTROL_STARTTRANSFER_BIT;

        int dataIndex;
        for (dataIndex = 0; dataIndex < dataLength; dataIndex++)
	{
            while ((*(base + BSC_STATUS_OFFSET) & BSC_STATUS_CONTAINSDATA_MASK) == BSC_STATUS_CONTAINSDATA_BIT);

            data[dataIndex] = *(base + BSC_DATAFIFO_OFFSET);
	}

        // Wait for Done
        while ((*(base + BSC_STATUS_OFFSET) & BSC_STATUS_DONE_MASK) == BSC_STATUS_DONE_BIT);
    }
}

void i2cWrite(UnsignedByte bus, UnsignedByte device, UnsignedByte address, UnsignedByte data[], UnsignedWord16 dataLength)
{
    volatile UnsignedWord32* base = getBusBase(bus);

    if (base != 0)
    {
        // Wait for no Active Transfer
        while ((*(base + BSC_STATUS_OFFSET) & BSC_STATUS_TRANSFERACTIVE_MASK) == BSC_STATUS_TRANSFERACTIVE_BIT);

        // Clear Clock Stretch Timeout, Ack Error & Done
        *(base + BSC_STATUS_OFFSET) = BSC_CONTROL_CLEARFIFO_BITS | BSC_STATUS_DONE_BIT;
        
	*(base + BSC_SLAVEADDRESS_OFFSET) = address;
        *(base + BSC_DATALENGTH_OFFSET)   = dataLength;

        // Start transfer
        *(base + BSC_CONTROL_OFFSET) = *(base + BSC_CONTROL_OFFSET) | BSC_CONTROL_STARTTRANSFER_BIT;

        int dataIndex;
        for (dataIndex = 0; dataIndex < dataLength; dataIndex++)
	{
            while ((*(base + BSC_STATUS_OFFSET) & BSC_STATUS_CONTAINSSPACE_MASK) == BSC_STATUS_CONTAINSSPACE_BIT);

            *(base + BSC_DATAFIFO_OFFSET) = data[dataIndex];
	}

        // Wait for Done
        while ((*(base + BSC_STATUS_OFFSET) & BSC_STATUS_DONE_MASK) == BSC_STATUS_DONE_BIT);
    }
}
