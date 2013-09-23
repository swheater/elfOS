/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - ILI9320 (2.8in TFT)

#include <Kernel/StdTypes.h>
#include <Device/RaspPi_ILI9320.h>

#define GPIO_BASE                ((volatile UnsignedWord32*) 0x20200000)
#define GPIO_FUNCSELECT_BASE     (GPIO_BASE + 0x00)
#define GPIO_FUNCSELECT_1_OFFSET (0x01)
#define GPIO_FUNCSELECT_2_OFFSET (0x02)
#define GPIO_SET_BASE            (GPIO_BASE + 0x07)
#define GPIO_SET_0_OFFSET        (0x00)
#define GPIO_CLEAR_BASE          (GPIO_BASE + 0x0A)
#define GPIO_CLEAR_0_OFFSET      (0x00)

void ili9320Init(void)
{
    unsigned int gpioFuncSelect;

    // Select function output for GPIO18 & GPIO25
    gpioFuncSelect = *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_1_OFFSET);
    gpioFuncSelect &= 0xF8FFFFFF;
    gpioFuncSelect |= 0x01000000;
    *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_1_OFFSET) = gpioFuncSelect;

    // Select function output for GPIO25
    gpioFuncSelect = *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_2_OFFSET);
    gpioFuncSelect &= 0xFFFC7FFF;
    gpioFuncSelect |= 0x00008000;
    *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_2_OFFSET) = gpioFuncSelect;
}
