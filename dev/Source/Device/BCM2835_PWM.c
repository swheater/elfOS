/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for BCM2835 - PWM

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_GPIO.h>
#include <Device/BCM2835_SystemTimer.h>
#include <Device/BCM2835_PWM.h>

#define PWN_BASE                  ((volatile UnsignedWord32*) 0x2020C000)
#define PWM_CONTROL_OFFSET        (0x00)
#define PWM_STATUS_OFFSET         (0x01)
#define PWM_DMA_CONFIG_OFFSET     (0x02)
#define PWM_CHANNEL1_RANGE_OFFSET (0x04)
#define PWM_CHANNEL1_DATA_OFFSET  (0x05)
#define PWM_FIFO_INPUT_OFFSET     (0x06)
#define PWM_CHANNEL2_RANGE_OFFSET (0x08)
#define PWM_CHANNEL2_DATA_OFFSET  (0x09)

#define PWM_CONTROL_CHANNEL1_ENABLE_MASK         (0x0001)
#define PWM_CONTROL_CHANNEL1_DISABLE_BIT         (0x0000)
#define PWM_CONTROL_CHANNEL1_ENABLE_BIT          (0x0001)
#define PWM_CONTROL_CHANNEL1_MODE_MASK           (0x0002)
#define PWM_CONTROL_CHANNEL1_MODE_PWM_BIT        (0x0000)
#define PWM_CONTROL_CHANNEL1_MODE_SERIALISER_BIT (0x0002)

#define PWM_CHANNEL0_GPIO       (40)
#define PWM_CHANNEL0_FUNCSELECT (GPIO_FUNCSELECT_ALTFUNC0)
#define PWM_CHANNEL1_GPIO       (45)
#define PWM_CHANNEL1_FUNCSELECT (GPIO_FUNCSELECT_ALTFUNC0)

void pwmInit(void)
{
    gpioFuncSelect(PWM_CHANNEL0_GPIO, PWM_CHANNEL0_FUNCSELECT);
    gpioSetPullControl(PWM_CHANNEL0_GPIO, GPIO_PULL_OFF);
    gpioFuncSelect(PWM_CHANNEL1_GPIO, PWM_CHANNEL1_FUNCSELECT);
    gpioSetPullControl(PWM_CHANNEL1_GPIO, GPIO_PULL_OFF);
    pwmSetRange(0, 2000000);
    pwmSetMark(0, 1000000);
    *(PWN_BASE + PWM_CONTROL_OFFSET) = 0x00A5;
}

void pwmSetRange(UnsignedByte servoNumber, UnsignedWord32 range)
{
    *(PWN_BASE + PWM_CHANNEL1_RANGE_OFFSET) = range;
}

void pwmSetMark(UnsignedByte servoNumber, UnsignedWord32 mark)
{
    *(PWN_BASE + PWM_FIFO_INPUT_OFFSET) = mark;
}

void pwmShutdown(void)
{
}
