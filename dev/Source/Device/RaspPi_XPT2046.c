/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - XPT2046

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_GPIO.h>
#include <Device/BCM2835_SPI.h>
#include <Device/BCM2835_SystemTimer.h>
#include <Device/RaspPi_XPT2046.h>

#define GPIO_BASE                ((volatile UnsignedWord32*) 0x20200000)
#define GPIO_FUNCSELECT_BASE     (GPIO_BASE + 0x00)
#define GPIO_FUNCSELECT_1_OFFSET (0x01)
#define GPIO_LEVEL_BASE          (GPIO_BASE + 0x0D)
#define GPIO_LEVEL_0_OFFSET      (0x00)
#define GPIO_LEVEL_1_OFFSET      (0x01)

#define XPT2046_GPIO_PENIRQN (17)

void xpt2046Init(void)
{
    UnsignedWord32 gpioFuncSelect;

    // Select function input for GPIO17
    gpioFuncSelect = *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_1_OFFSET);
    gpioFuncSelect &= 0xFF1FFFFF;
    gpioFuncSelect |= 0x00000000;
    *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_1_OFFSET) = gpioFuncSelect;
}

void xpt2046Test(void)
{
    UnsignedWord16 count;
    for (count = 0; count < 255; count++)
    {
        UnsignedWord32 value = (*(GPIO_LEVEL_BASE + GPIO_LEVEL_0_OFFSET)) & 0x00020000;
        logUnsignedWord16Hex(count);
        logMessage(" ");
        logUnsignedWord32Hex(value);
        logMessage("\r\n");

	systemtimerWait(1000000);
    }
}

void xpt2046Shutdown(void)
{
}
