#ifndef _DEVICE_BCM2835_SPI_H
#define _DEVICE_BCM2835_SPI_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void spiInit(void);
extern void spiRead(UnsignedByte chip, UnsignedWord32 data[], UnsignedWord16 dataLength);
extern void spiWrite(UnsignedByte chip, UnsignedWord32 data[], UnsignedWord16 dataLength);

extern void spiDebug(void);

#endif
