#ifndef _DEVICE_BCM2835_EMMC_H
#define _DEVICE_BCM2835_EMMC_H 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern UnsignedByte emmcInit(void);
extern UnsignedByte emmcReadBlock(UnsignedWord32 blockNumber, UnsignedByte block[512]);
extern UnsignedByte emmcShutdown(void);

#endif
