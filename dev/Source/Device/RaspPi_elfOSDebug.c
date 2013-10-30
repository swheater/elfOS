/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - elfOSDebug

#include <Kernel/StdTypes.h>
#include <Device/BCM2835_GPIO.h>
#include <Device/RaspPi_elfOSDebug.h>

void elfosdebugInit(void)
{
    gpioFuncSelect(ELFOSDEBUG_YELLOW_LED_1, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(ELFOSDEBUG_YELLOW_LED_2, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(ELFOSDEBUG_YELLOW_LED_3, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(ELFOSDEBUG_YELLOW_LED_4, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(ELFOSDEBUG_YELLOW_LED_5, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(ELFOSDEBUG_YELLOW_LED_6, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(ELFOSDEBUG_GREEN_LED,    GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(ELFOSDEBUG_RED_LED,      GPIO_FUNCSELECT_OUTPUT);
}

void elfosdebugSetLED(UnsignedByte ledNumber, Boolean on)
{
    if (on)
        gpioSetOutput(ledNumber);
    else
        gpioClearOutput(ledNumber);
}

void elfosdebugShutdown(void)
{
}
