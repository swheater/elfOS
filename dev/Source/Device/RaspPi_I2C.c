/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi, I2C0 & I2C1 (BSC0 & BSC1)

#include <Kernel/StdTypes.h>
#include <Device/RaspPi_I2C.h>

#define BSC0_BASE                ((volatile UnsignedWord32*) 0x20205000)
#define BSC0_CONTROL             (BSC0_BASE + 0x00)
#define BSC0_STATUS              (BSC0_BASE + 0x01)
#define BSC0_DATALENGTH          (BSC0_BASE + 0x02)
#define BSC0_SLAVEADDRESS        (BSC0_BASE + 0x03)
#define BSC0_DATAFIFO            (BSC0_BASE + 0x04)
#define BSC0_CLOCKDIVIDER        (BSC0_BASE + 0x05)
#define BSC0_DATADELAY           (BSC0_BASE + 0x06)
#define BSC0_CLOCKSTRETCHTIMEOUT (BSC0_BASE + 0x07)
#define BSC1_BASE                ((volatile UnsignedWord32*) 0x20804000)
#define BSC1_CONTROL             (BSC1_BASE + 0x00)
#define BSC1_STATUS              (BSC1_BASE + 0x01)
#define BSC1_DATALENGTH          (BSC1_BASE + 0x02)
#define BSC1_SLAVEADDRESS        (BSC1_BASE + 0x03)
#define BSC1_DATAFIFO            (BSC1_BASE + 0x04)
#define BSC1_CLOCKDIVIDER        (BSC1_BASE + 0x05)
#define BSC1_DATADELAY           (BSC1_BASE + 0x06)
#define BSC1_CLOCKSTRETCHTIMEOUT (BSC1_BASE + 0x07)

void i2cInit(void)
{
}

void i2c0Output(UnsignedByte address, UnsignedByte data[], UnsignedWord16 dataLength)
{
}

void i2c1Output(UnsignedByte address, UnsignedByte data[], UnsignedWord16 dataLength)
{
}
