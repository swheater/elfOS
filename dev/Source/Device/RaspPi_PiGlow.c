/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - PiGlow

#include <Kernel/StdTypes.h>
#include <Device/BCM2835_BSC.h>
#include <Device/RaspPi_PiGlow.h>

#define I2C_BUS            (0x00)
#define I2C_SN3218_ADDRESS (0x54)

#define SN3218_ENABLE_REG       (0x00)
#define SN3218_PWM_REG_BASE     (0x01)
#define SN3218_CONTROL_REG_BASE (0x13)
#define SN3218_UPDATE_REG       (0x16)
#define SN3218_RESET_REG        (0x17)

#define SN3218_ENABLE_MASK      (0x01)
#define SN3218_ENABLE_SET_BIT   (0x01)
#define SN3218_ENABLE_CLEAR_BIT (0x00)

#define SN3218_PINS_PERCONTROL (6)

#define SN3218_UNSPECIFIED_VALUE (0xFF)

void piglowInit(void)
{
    piglowReset();
    int arm, ledColour;
    for (arm = PIGLOW_ARM_MIN; arm < PIGLOW_ARM_MAX; arm++)
        for (ledColour = PIGLOW_LEDCOLOUR_MIN; ledColour < PIGLOW_LEDCOLOUR_MAX; ledColour++)
        {
            piglowSetLEDBrightness(arm, ledColour, PIGLOW_BRIGHTNESS_MIN);
            piglowSetLEDEnabled(arm, ledColour, TRUE);
        }
    piglowSetEnabled(TRUE);
}

void piglowReset(void)
{
    UnsignedByte data[2];
    data[0] = SN3218_RESET_REG;
    data[1] = SN3218_UNSPECIFIED_VALUE;
    i2cWrite(I2C_BUS, I2C_SN3218_ADDRESS, data, 2);
}

void piglowGetEnabled(Boolean *enabled)
{
    UnsignedByte data[2];
    data[0] = SN3218_ENABLE_REG;
    i2cRegRead(I2C_BUS, I2C_SN3218_ADDRESS, SN3218_ENABLE_REG, data, 1);
    *enabled = (data[1] & SN3218_ENABLE_MASK) == SN3218_ENABLE_SET_BIT;
}

void piglowSetEnabled(Boolean enabled)
{
    UnsignedByte data[2];
    data[0] = SN3218_ENABLE_REG;
    if (enabled)
        data[1]= SN3218_ENABLE_SET_BIT;
    else
        data[1]= SN3218_ENABLE_CLEAR_BIT;
    i2cWrite(I2C_BUS, I2C_SN3218_ADDRESS, data, 2);
}

void piglowGetLEDEnabled(UnsignedByte arm, UnsignedByte ledColour, Boolean *enabled)
{
    if ((PIGLOW_ARM_MIN <= arm) && (arm <= PIGLOW_ARM_MAX) && (PIGLOW_LEDCOLOUR_MIN <= ledColour) && (ledColour <= PIGLOW_LEDCOLOUR_MAX))
    {
        UnsignedByte data[2];
        i2cRegRead(I2C_BUS, I2C_SN3218_ADDRESS, SN3218_CONTROL_REG_BASE + arm, data, 1);
        *enabled = (data[1] & (0x01 << ledColour)) != 0;
    }
}

void piglowSetLEDEnabled(UnsignedByte arm, UnsignedByte ledColour, Boolean enabled)
{
    if ((PIGLOW_ARM_MIN <= arm) && (arm <= PIGLOW_ARM_MAX) && (PIGLOW_LEDCOLOUR_MIN <= ledColour) && (ledColour <= PIGLOW_LEDCOLOUR_MAX))
    {
        UnsignedByte data[2];
        data[0] = SN3218_PWM_REG_BASE + ((PIGLOW_ARM_MAX - PIGLOW_ARM_MIN) * arm) + ledColour;
        i2cRegRead(I2C_BUS, I2C_SN3218_ADDRESS, SN3218_CONTROL_REG_BASE + arm, data, 1);
        if (enabled)
            data[1] = data[0] | (0x01 << ledColour);
        else
            data[1] = data[0] & (~ (0x01 << ledColour));
        data[0] = SN3218_CONTROL_REG_BASE + arm;
        i2cWrite(I2C_BUS, I2C_SN3218_ADDRESS, data, 2);
    }
}

void piglowGetLEDBrightness(UnsignedByte arm, UnsignedByte ledColour, UnsignedByte *brightness)
{
    if ((PIGLOW_ARM_MIN <= arm) && (arm <= PIGLOW_ARM_MAX) && (PIGLOW_LEDCOLOUR_MIN <= ledColour) && (ledColour <= PIGLOW_LEDCOLOUR_MAX))
    {
        UnsignedByte data[1];
        i2cRegRead(I2C_BUS, I2C_SN3218_ADDRESS, SN3218_PWM_REG_BASE + ((PIGLOW_ARM_MAX - PIGLOW_ARM_MIN) * arm) + ledColour, data, 1);
        *brightness = data[0];
    }
}

void piglowSetLEDBrightness(UnsignedByte arm, UnsignedByte ledColour, UnsignedByte brightness)
{
    if ((PIGLOW_ARM_MIN <= arm) && (arm <= PIGLOW_ARM_MAX) && (PIGLOW_LEDCOLOUR_MIN <= ledColour) && (ledColour <= PIGLOW_LEDCOLOUR_MAX))
    {
        UnsignedByte data[2];
        data[0] = SN3218_PWM_REG_BASE + ((PIGLOW_ARM_MAX - PIGLOW_ARM_MIN) * arm) + ledColour;
        data[1] = brightness;
        i2cWrite(I2C_BUS, I2C_SN3218_ADDRESS, data, 2);
    }
}
