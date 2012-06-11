/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi, GPIO output (GPIO17, GPIO18, GPIO21 and GPIO22)

#include <Kernel/StdTypes.h>
#include <Device/RaspPi_GPIO.h>

#define GPIO_BASE                ((volatile UnsignedWord32*) 0x20200000)
#define GPIO_FUNCSELECT_BASE     (GPIO_BASE + 0x00)
#define GPIO_FUNCSELECT_0_OFFSET (0x00)
#define GPIO_FUNCSELECT_1_OFFSET (0x01)
#define GPIO_FUNCSELECT_2_OFFSET (0x02)
#define GPIO_FUNCSELECT_3_OFFSET (0x03)
#define GPIO_FUNCSELECT_4_OFFSET (0x04)
#define GPIO_FUNCSELECT_5_OFFSET (0x05)
#define GPIO_SET_BASE            (GPIO_BASE + 0x07)
#define GPIO_SET_0_OFFSET        (0x07)
#define GPIO_SET_1_OFFSET        (0x08)
#define GPIO_CLEAR_BASE          (GPIO_BASE + 0x0A)
#define GPIO_CLEAR_0_OFFSET      (0x0A)
#define GPIO_CLEAR_1_OFFSET      (0x0B)

#define GPIO_FUNC_MASK   (0x7)
#define GPIO_INPUT_FUNC  (0x0)
#define GPIO_OUTPUT_FUNC (0x1)

void gpioInit(void)
{
    unsigned int gpioFuncSelect;

    // Select function output for GPIO17 and GPIO18
    gpioFuncSelect = *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_1_OFFSET);
    gpioFuncSelect &= 0xF81FFFFF;
    gpioFuncSelect |= 0x01200000;
    *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_1_OFFSET) = gpioFuncSelect;

    // Select function output for GPIO21 and GPIO22
    gpioFuncSelect = *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_2_OFFSET);
    gpioFuncSelect &= 0xFFFFFE07;
    gpioFuncSelect |= 0x00000048;
    *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_2_OFFSET) = gpioFuncSelect;
}

void gpioSetOutput(int gpioIndex)
{
    *(GPIO_SET_BASE + (gpioIndex >> 5)) = 1 << (gpioIndex & 0x1F);
}

void gpioClearOutput(int gpioIndex)
{
    *(GPIO_CLEAR_BASE + (gpioIndex >> 5)) = 1 << (gpioIndex & 0x1F);
}
