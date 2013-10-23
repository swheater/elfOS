/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - PiLITEr

#include <Kernel/StdTypes.h>
#include <Device/BCM2835_GPIO.h>
#include <Device/RaspPi_PiLITEr.h>

void piliterInit(void)
{
    gpioFuncSelect(PILITER_LED_0, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(PILITER_LED_1, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(PILITER_LED_2, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(PILITER_LED_3, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(PILITER_LED_4, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(PILITER_LED_5, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(PILITER_LED_6, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(PILITER_LED_7, GPIO_FUNCSELECT_OUTPUT);
}

void piliterSetLED(UnsignedByte ledNumber, Boolean on)
{
    if (on)
        gpioSetOutput(ledNumber);
    else
        gpioClearOutput(ledNumber);
}

void piliterShutdown(void)
{
}
