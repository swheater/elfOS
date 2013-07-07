#ifndef _DEVICE_RASPPI_I2C_H
#define _DEVICE_RASPPI_I2C_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void i2cInit(UnsignedByte bus);
extern void i2cRead(UnsignedByte bus, UnsignedByte device, UnsignedByte address, UnsignedByte data[], UnsignedWord16 dataLength);
extern void i2cWrite(UnsignedByte bus, UnsignedByte device, UnsignedByte address, UnsignedByte data[], UnsignedWord16 dataLength);

#endif
