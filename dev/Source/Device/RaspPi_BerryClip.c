/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - BerryClip

#include <Kernel/StdTypes.h>
#include <Device/BCM2835_GPIO.h>
#include <Device/RaspPi_BerryClip.h>

#define BERRYCLIP_BUZZER (8)
#define BERRYCLIP_SWITCH (7)

void berryclipInit(void)
{
    gpioFuncSelect(BERRYCLIP_LED_1, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(BERRYCLIP_LED_2, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(BERRYCLIP_LED_3, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(BERRYCLIP_LED_4, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(BERRYCLIP_LED_5, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(BERRYCLIP_LED_6, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(BERRYCLIP_BUZZER, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(BERRYCLIP_SWITCH, GPIO_FUNCSELECT_INPUT);
}

void berryclipSetLED(UnsignedByte ledNumber, Boolean on)
{
    if (on)
        gpioSetOutput(ledNumber);
    else
        gpioClearOutput(ledNumber);
}

void berryclipSetBuzzer(Boolean on)
{
    if (on)
        gpioSetOutput(BERRYCLIP_BUZZER);
    else
        gpioClearOutput(BERRYCLIP_BUZZER);
}

Boolean berryclipGetSwitch(void)
{
    return ! gpioGetInput(BERRYCLIP_SWITCH);
}

void berryclipShutdown(void)
{
}
