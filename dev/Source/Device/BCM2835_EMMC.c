/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for BCM2835 - EMMC (External Mass Media Controller)

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_EMMC.h>

#define EMMC_BASE    ((volatile UnsignedWord32*) 0x20300000)
#define EMMC__OFFSET (0x00)

void emmcInit(void)
{
}

void emmcShutdown(void)
{
}
