#ifndef _DEVICE_BCM2835_BSC_H
#define _DEVICE_BCM2835_BSC_H 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void i2cInit(UnsignedByte bus);
extern void i2cRead(UnsignedByte bus, UnsignedByte deviceAddress, UnsignedByte data[], UnsignedWord16 dataLength);
extern void i2cRegRead(UnsignedByte bus, UnsignedByte deviceAddress, UnsignedByte registerAddress, UnsignedByte data[], UnsignedWord16 dataLength);
extern void i2cWrite(UnsignedByte bus, UnsignedByte deviceAddress, UnsignedByte data[], UnsignedWord16 dataLength);
extern void i2cRegWrite(UnsignedByte bus, UnsignedByte deviceAddress, UnsignedByte registerAddress, UnsignedByte data[], UnsignedWord16 dataLength);

extern void i2cDebug(volatile UnsignedWord32 *base);

#endif
