/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - Ladder

#include <Kernel/StdTypes.h>
#include <Device/BCM2835_GPIO.h>
#include <Device/RaspPi_Ladder.h>

void ladderInit(void)
{
    gpioFuncSelect(LADDER_SMALLRED_LED,   GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(LADDER_SMALLGREEN_LED, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(LADDER_RED_LED_1,      GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(LADDER_RED_LED_2,      GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(LADDER_YELLOW_LED_1,   GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(LADDER_YELLOW_LED_2,   GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(LADDER_GREEN_LED_1,    GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(LADDER_GREEN_LED_2,    GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(LADDER_BLUE_LED_1,     GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(LADDER_BLUE_LED_2,     GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(LADDER_SWITCH_1,       GPIO_FUNCSELECT_INPUT);
    gpioFuncSelect(LADDER_SWITCH_2,       GPIO_FUNCSELECT_INPUT);
    gpioFuncSelect(LADDER_SWITCH_3,       GPIO_FUNCSELECT_INPUT);
    gpioFuncSelect(LADDER_SWITCH_4,       GPIO_FUNCSELECT_INPUT);
}

void ladderSetLED(UnsignedByte ledNumber, Boolean on)
{
    if (on)
        gpioSetOutput(ledNumber);
    else
        gpioClearOutput(ledNumber);
}

Boolean ladderGetSwitch(UnsignedByte switchNumber)
{
    return ! gpioGetInput(switchNumber);
}

void ladderShutdown(void)
{
}
