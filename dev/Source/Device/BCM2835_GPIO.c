/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for BCM2835 - GPIO output (GPIO17, GPIO18, GPIO21 and GPIO22)

#include <Kernel/StdTypes.h>
#include <Device/BCM2835_GPIO.h>

#define GPIO_BASE            ((volatile UnsignedWord32*) 0x20200000)
#define GPIO_FUNCSELECT_BASE (GPIO_BASE + 0x00)
#define GPIO_SET_BASE        (GPIO_BASE + 0x07)
#define GPIO_CLEAR_BASE      (GPIO_BASE + 0x0A)
#define GPIO_LEVEL_BASE      (GPIO_BASE + 0x0D)

#define GPIO_FUNCSELECT_MASK (0x7)

void gpioInit(void)
{
}

void gpioFuncSelect(UnsignedByte gpioIndex, UnsignedByte funcSelect)
{
    UnsignedWord32 gpioFuncSelect = *(GPIO_FUNCSELECT_BASE + (gpioIndex / 10));
    gpioFuncSelect &= ~ (GPIO_FUNCSELECT_MASK << (3 * (gpioIndex % 10)));
    gpioFuncSelect |= funcSelect << (3 * (gpioIndex % 10));
    *(GPIO_FUNCSELECT_BASE + (gpioIndex / 10)) = gpioFuncSelect;
}

Boolean gpioGetInput(UnsignedByte gpioIndex)
{
    return ((*(GPIO_LEVEL_BASE + (gpioIndex >> 5))) & (1 << (gpioIndex & 0x1F))) != 0;
}

void gpioSetOutput(UnsignedByte gpioIndex)
{
    *(GPIO_SET_BASE + (gpioIndex >> 5)) = 1 << (gpioIndex & 0x1F);
}

void gpioClearOutput(UnsignedByte gpioIndex)
{
    *(GPIO_CLEAR_BASE + (gpioIndex >> 5)) = 1 << (gpioIndex & 0x1F);
}

void gpioShutdown(void)
{
}
