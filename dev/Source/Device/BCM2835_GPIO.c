/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for BCM2835 - GPIO output (GPIO17, GPIO18, GPIO21 and GPIO22)

#include <Kernel/StdTypes.h>
#include <Device/BCM2835_GPIO.h>

#define GPIO_BASE                ((volatile UnsignedWord32*) 0x20200000)
#define GPIO_FUNCSELECT_BASE     (GPIO_BASE + 0x00)
#define GPIO_FUNCSELECT_0_OFFSET (0x00)
#define GPIO_FUNCSELECT_1_OFFSET (0x01)
#define GPIO_FUNCSELECT_2_OFFSET (0x02)
#define GPIO_FUNCSELECT_3_OFFSET (0x03)
#define GPIO_FUNCSELECT_4_OFFSET (0x04)
#define GPIO_FUNCSELECT_5_OFFSET (0x05)
#define GPIO_SET_BASE            (GPIO_BASE + 0x07)
#define GPIO_SET_0_OFFSET        (0x00)
#define GPIO_SET_1_OFFSET        (0x01)
#define GPIO_CLEAR_BASE          (GPIO_BASE + 0x0A)
#define GPIO_CLEAR_0_OFFSET      (0x00)
#define GPIO_CLEAR_1_OFFSET      (0x01)
#define GPIO_LEVEL_BASE          (GPIO_BASE + 0x0D)
#define GPIO_LEVEL_0_OFFSET      (0x00)
#define GPIO_LEVEL_1_OFFSET      (0x01)

#define GPIO_FUNC_MASK   (0x7)
#define GPIO_INPUT_FUNC  (0x0)
#define GPIO_OUTPUT_FUNC (0x1)

void gpioInit(void)
{
}

void gpioFuncSelect(UnsignedByte gpioIndex, UnsignedByte funcSelect)
{
    UnsignedWord32 gpioFuncSelect = *(GPIO_FUNCSELECT_BASE + (gpioIndex / 10));
    gpioFuncSelect &= ~ (0x07 << (3 * (gpioIndex % 10)));
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
