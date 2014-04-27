#ifndef _DEVICE_SPI_SECUREDIGITAL_H
#define _DEVICE_SPI_SECUREDIGITAL_H 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

extern UnsignedByte securedigitalInit(void);
extern UnsignedByte securedigitalReadBlock(UnsignedWord32 blockNumber, UnsignedByte block[512]);
extern UnsignedByte securedigitalShutdown(void);

#endif
