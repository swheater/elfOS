/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - PiGlow

#include <Kernel/StdTypes.h>
#include <Device/BCM2835_BSC.h>
#include <Device/RaspPi_PiGlow.h>

#define I2C_BUS            (0x00)
#define I2C_SN3218_ADDRESS (0x54)

#define SN3218_ENABLE_REG        (0x00)
#define SN3218_PWM_REGS_BASE     (0x01)
#define SN3218_CONTROL_REGS_BASE (0x13)
#define SN3218_UPDATE_REG        (0x16)
#define SN3218_RESET_REG         (0x17)

#define SN3218_ENABLE_MASK      (0x01)
#define SN3218_ENABLE_SET_BIT   (0x01)
#define SN3218_ENABLE_CLEAR_BIT (0x00)

#define SN3218_ENABLEDREG_RESETVALUE (0x00)
#define SN3218_PWMREG_RESETVALUE     (0x00)
#define SN3218_CONTROLREG_RESETVALUE (0x00)

#define SN3218_PWM_REGS         (18)
#define SN3218_CONTROL_REGS     (3)
#define SN3218_OUTS_PRE_CONTROL (6)

#define SN3218_UNSPECIFIED_VALUE (0xFF)

static UnsignedByte enabledReg;
static UnsignedByte pwmRegs[SN3218_PWM_REGS];
static UnsignedByte controlRegs[SN3218_CONTROL_REGS];

UnsignedByte pinMapping[PIGLOW_ARMS][PIGLOW_LEDS_PER_ARM] =  { { 12, 14,  3,  2,  1,  0 }, {  9,  4,  5,  8,  7,  6 }, { 10, 11, 13, 15, 16, 17 } };

void piglowInit(void)
{
    piglowReset();
    int arm, ledColour;
    for (arm = PIGLOW_ARM_MIN; arm <= PIGLOW_ARM_MAX; arm++)
        for (ledColour = PIGLOW_LEDCOLOUR_MIN; ledColour <= PIGLOW_LEDCOLOUR_MAX; ledColour++)
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

    enabledReg = SN3218_ENABLEDREG_RESETVALUE;
    int index;
    for (index = 0; index < SN3218_PWM_REGS; index++)
        pwmRegs[index] = SN3218_PWMREG_RESETVALUE;
    for (index = 0; index < SN3218_CONTROL_REGS; index++)
        controlRegs[index] = SN3218_CONTROLREG_RESETVALUE;
}

void piglowGetEnabled(Boolean *enabled)
{
    *enabled = enabledReg;
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

    enabledReg = data[1];
}

void piglowGetLEDEnabled(UnsignedByte arm, UnsignedByte ledColour, Boolean *enabled)
{
    if ((PIGLOW_ARM_MIN <= arm) && (arm <= PIGLOW_ARM_MAX) && (PIGLOW_LEDCOLOUR_MIN <= ledColour) && (ledColour <= PIGLOW_LEDCOLOUR_MAX))
    {
        UnsignedByte controlRegIndex = pinMapping[arm][ledColour] / SN3218_OUTS_PRE_CONTROL;
        UnsignedByte outBitIndex     = pinMapping[arm][ledColour] % SN3218_OUTS_PRE_CONTROL;

        *enabled = (controlRegs[controlRegIndex] & (0x01 << outBitIndex)) != 0;
    }
}

void piglowSetLEDEnabled(UnsignedByte arm, UnsignedByte ledColour, Boolean enabled)
{
    if ((PIGLOW_ARM_MIN <= arm) && (arm <= PIGLOW_ARM_MAX) && (PIGLOW_LEDCOLOUR_MIN <= ledColour) && (ledColour <= PIGLOW_LEDCOLOUR_MAX))
    {
        UnsignedByte controlRegIndex = pinMapping[arm][ledColour] / SN3218_OUTS_PRE_CONTROL;
        UnsignedByte outBitIndex     = pinMapping[arm][ledColour] % SN3218_OUTS_PRE_CONTROL;

        UnsignedByte data[2];
        data[0] = SN3218_CONTROL_REGS_BASE + controlRegIndex;
        if (enabled)
            data[1] = controlRegs[controlRegIndex] | (0x01 << outBitIndex);
        else
            data[1] = controlRegs[controlRegIndex] & (~ (0x01 << outBitIndex));
        i2cWrite(I2C_BUS, I2C_SN3218_ADDRESS, data, 2);

        controlRegs[controlRegIndex] = data[1];
    }
}

void piglowGetLEDBrightness(UnsignedByte arm, UnsignedByte ledColour, UnsignedByte *brightness)
{
    if ((PIGLOW_ARM_MIN <= arm) && (arm <= PIGLOW_ARM_MAX) && (PIGLOW_LEDCOLOUR_MIN <= ledColour) && (ledColour <= PIGLOW_LEDCOLOUR_MAX))
        *brightness = pwmRegs[pinMapping[arm][ledColour]];
}

void piglowSetLEDBrightness(UnsignedByte arm, UnsignedByte ledColour, UnsignedByte brightness)
{
    if ((PIGLOW_ARM_MIN <= arm) && (arm <= PIGLOW_ARM_MAX) && (PIGLOW_LEDCOLOUR_MIN <= ledColour) && (ledColour <= PIGLOW_LEDCOLOUR_MAX))
    {
        UnsignedByte data[2];
        data[0] = SN3218_PWM_REGS_BASE + pinMapping[arm][ledColour];
        data[1] = brightness;
        i2cWrite(I2C_BUS, I2C_SN3218_ADDRESS, data, 2);
        data[0] = SN3218_UPDATE_REG;
        data[1] = SN3218_UNSPECIFIED_VALUE;
        i2cWrite(I2C_BUS, I2C_SN3218_ADDRESS, data, 2);

        pwmRegs[pinMapping[arm][ledColour]] = brightness;
    }
}
