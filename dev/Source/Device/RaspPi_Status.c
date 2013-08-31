/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - Status (LED)

#include <Kernel/StdTypes.h>
#include <Device/RaspPi_Status.h>

#define GPIO_BASE                ((volatile UnsignedWord32*) 0x20200000)
#define GPIO_FUNCSELECT_BASE     (GPIO_BASE + 0x00)
#define GPIO_FUNCSELECT_1_OFFSET (0x01)
#define GPIO_SET_BASE            (GPIO_BASE + 0x07)
#define GPIO_SET_0_OFFSET        (0x07)
#define GPIO_CLEAR_BASE          (GPIO_BASE + 0x0A)
#define GPIO_CLEAR_0_OFFSET      (0x0A)

void statusInit(void)
{
    unsigned int gpioFuncSelect;

    // Select function output for GPIO16
    gpioFuncSelect = *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_1_OFFSET);
    gpioFuncSelect &= 0xFFE3FFFF;
    gpioFuncSelect |= 0x01040000;
    *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_1_OFFSET) = gpioFuncSelect;
}

void statusSetActiveLED(void)
{
    *(GPIO_SET_BASE + GPIO_SET_0_OFFSET) = 0x0001000;
}

void statusClearActiveLED(void)
{
    *(GPIO_CLEAR_BASE + GPIO_CLEAR_0_OFFSET) = 0x0001000;
}
