#ifndef _DEVICE_BCM2835_SPI_H
#define _DEVICE_BCM2835_SPI_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void spiInit(void);
extern UnsignedWord32 spiSetClockRate(UnsignedWord32 clockRate);
extern void spiStartCompoundTransfer(void);
extern void spiEndCompoundTransfer(void);
extern void spiTransfer(UnsignedByte chip, UnsignedByte outputData[], UnsignedByte inputData[], UnsignedWord32 dataLength);
extern void spiAsyncTransfer(UnsignedByte chip, UnsignedByte outputData[], UnsignedByte inputData[], UnsignedWord32 outputDataLength, UnsignedWord32 inputDataLength, Boolean (*startInput)(UnsignedByte, void*), Boolean (*stopInput)(UnsignedByte, void*), void *context);

#endif
