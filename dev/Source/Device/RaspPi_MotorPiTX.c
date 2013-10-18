/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for RaspPi - MotorPiTX

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
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
}

void motorpitxShutdown(void)
{
}
