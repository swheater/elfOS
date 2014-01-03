/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for BCM2835 - GPIO output (GPIO17, GPIO18, GPIO21 and GPIO22)

#include <Kernel/StdTypes.h>
#include <Device/BCM2835_GPIO.h>

#define GPIO_BASE            ((volatile UnsignedWord32*) 0x20200000)
#define GPIO_FUNCSELECT_BASE (GPIO_BASE + 0x00)
#define GPIO_SET_BASE        (GPIO_BASE + 0x07)
#define GPIO_CLEAR_BASE      (GPIO_BASE + 0x0A)
#define GPIO_LEVEL_BASE      (GPIO_BASE + 0x0D)

#define GPIO_PINPULLUPDOWNENABLE_OFFSET       (0x25)
#define GPIO_PINPULLUPDOWNENABLECLOCK_BASE    (GPIO_BASE + 0x26)
#define GPIO_PINPULLUPDOWNENABLECLOCK0_OFFSET (0x00)
#define GPIO_PINPULLUPDOWNENABLECLOCK1_OFFSET (0x01)

#define GPIO_PINPULLUPDOWN_SETUPDELAY           (150)
#define GPIO_FUNCSELECT_MASK                    (0x7)
#define GPIO_PULLCONTROL_MASK                   (0x3)
#define GPIO_PINPULLUPDOWNENABLE_OFF_BITS       (0x00000000)
#define GPIO_PINPULLUPDOWNENABLECLOCK_NONE_BITS (0x00000000)

void gpioInit(void)
{
    *(GPIO_PINPULLUPDOWNENABLECLOCK_BASE + GPIO_PINPULLUPDOWNENABLECLOCK0_OFFSET) = GPIO_PINPULLUPDOWNENABLECLOCK_NONE_BITS;
    *(GPIO_PINPULLUPDOWNENABLECLOCK_BASE + GPIO_PINPULLUPDOWNENABLECLOCK1_OFFSET) = GPIO_PINPULLUPDOWNENABLECLOCK_NONE_BITS;
}

void gpioFuncSelect(UnsignedByte gpioIndex, UnsignedByte funcSelect)
{
    UnsignedWord32 gpioFuncSelect = *(GPIO_FUNCSELECT_BASE + (gpioIndex / 10));
    gpioFuncSelect &= ~ (GPIO_FUNCSELECT_MASK << (3 * (gpioIndex % 10)));
    gpioFuncSelect |= funcSelect << (3 * (gpioIndex % 10));
    *(GPIO_FUNCSELECT_BASE + (gpioIndex / 10)) = gpioFuncSelect;
}

void gpioSetPullControl(UnsignedByte gpioIndex, UnsignedByte pullControl)
{
    volatile unsigned int delayCount;
    *(GPIO_BASE + GPIO_PINPULLUPDOWNENABLE_OFFSET)           = (pullControl & GPIO_PULLCONTROL_MASK);
    for (delayCount = 0; delayCount < GPIO_PINPULLUPDOWN_SETUPDELAY; delayCount++);
    *(GPIO_PINPULLUPDOWNENABLECLOCK_BASE + (gpioIndex >> 5)) = (1 << (gpioIndex & 0x1F));
    for (delayCount = 0; delayCount < GPIO_PINPULLUPDOWN_SETUPDELAY; delayCount++);
    *(GPIO_BASE + GPIO_PINPULLUPDOWNENABLE_OFFSET)           = GPIO_PINPULLUPDOWNENABLE_OFF_BITS;
    *(GPIO_PINPULLUPDOWNENABLECLOCK_BASE + (gpioIndex >> 5)) = GPIO_PINPULLUPDOWNENABLECLOCK_NONE_BITS;
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
