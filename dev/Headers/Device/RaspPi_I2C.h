#ifndef _DEVICE_RASPPI_I2C_H
#define _DEVICE_RASPPI_I2C_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void i2cInit(void);
extern void i2c0Output(UnsignedByte address, UnsignedByte data[], UnsignedWord16 dataLength);
extern void i2c1Output(UnsignedByte address, UnsignedByte data[], UnsignedWord16 dataLength);

#endif
