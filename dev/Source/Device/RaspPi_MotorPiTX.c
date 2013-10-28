/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for RaspPi - MotorPiTX

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_GPIO.h>
#include <Device/RaspPi_MotorPiTX.h>

#define MOTORPITX_GPIO_READYLED      (7)
#define MOTORPITX_GPIO_SHUTDOWN      (8)
#define MOTORPITX_GPIO_INPUT1        (21)
#define MOTORPITX_GPIO_INPUT2        (4)
#define MOTORPITX_GPIO_OUTPUT1       (22)
#define MOTORPITX_GPIO_OUTPUT2       (17)
#define MOTORPITX_GPIO_MOTOR1_ENABLE (11)
#define MOTORPITX_GPIO_MOTOR1_A      (9)
#define MOTORPITX_GPIO_MOTOR1_B      (10)
#define MOTORPITX_GPIO_MOTOR2_ENABLE (25)
#define MOTORPITX_GPIO_MOTOR2_A      (24)
#define MOTORPITX_GPIO_MOTOR2_B      (23)
#define MOTORPITX_GPIO_SERVO1        (18)
#define MOTORPITX_GPIO_SERVO2        (15)

void motorpitxInit(void)
{
    gpioFuncSelect(MOTORPITX_GPIO_READYLED, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(MOTORPITX_GPIO_SHUTDOWN, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(MOTORPITX_GPIO_INPUT1, GPIO_FUNCSELECT_INPUT);
    gpioFuncSelect(MOTORPITX_GPIO_INPUT2, GPIO_FUNCSELECT_INPUT);
    gpioFuncSelect(MOTORPITX_GPIO_OUTPUT1, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(MOTORPITX_GPIO_OUTPUT2, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(MOTORPITX_GPIO_MOTOR1_ENABLE, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(MOTORPITX_GPIO_MOTOR1_A, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(MOTORPITX_GPIO_MOTOR1_B, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(MOTORPITX_GPIO_MOTOR2_ENABLE, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(MOTORPITX_GPIO_MOTOR2_A, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(MOTORPITX_GPIO_MOTOR2_B, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(MOTORPITX_GPIO_SERVO1, GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(MOTORPITX_GPIO_SERVO2, GPIO_FUNCSELECT_OUTPUT);

    gpioClearOutput(MOTORPITX_GPIO_SHUTDOWN);
}

void motorpitxSetReadyLED(Boolean on)
{
    if (on)
        gpioSetOutput(MOTORPITX_GPIO_READYLED);
    else
        gpioClearOutput(MOTORPITX_GPIO_READYLED);
}

void motorpitxSetOutput(UnsignedByte outputNumber, Boolean on)
{
    if (outputNumber == MOTORPITX_OUTPUT1)
    {
        if (on)
            gpioSetOutput(MOTORPITX_GPIO_OUTPUT1);
        else
            gpioClearOutput(MOTORPITX_GPIO_OUTPUT1);
    }
    else if (outputNumber == MOTORPITX_OUTPUT2)
    {
        if (on)
            gpioSetOutput(MOTORPITX_GPIO_OUTPUT2);
        else
            gpioClearOutput(MOTORPITX_GPIO_OUTPUT2);
    }
}

Boolean motorpitxGetInput(UnsignedByte inputNumber)
{
    if (inputNumber == MOTORPITX_INPUT1)
        return ! gpioGetInput(MOTORPITX_GPIO_INPUT1);
    else if (inputNumber == MOTORPITX_INPUT2)
        return ! gpioGetInput(MOTORPITX_GPIO_INPUT2);
    else
        return FALSE;
}

void motorpitxShutdown(void)
{
}
