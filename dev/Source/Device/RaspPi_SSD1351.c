/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - SSD1351

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_GPIO.h>
#include <Device/BCM2835_SPI.h>
#include <Device/BCM2835_SystemTimer.h>
#include <Device/RaspPi_SSD1351.h>

#define SSD1351_GPIO_RESET     (24)
#define SSD1351_GPIO_IOCONTROL (25)

static void ssd1351SendOperation(UnsignedByte command, UnsignedByte params[], UnsignedWord32 paramsLength)
{
    UnsignedByte outputData[1];
    UnsignedByte inputData[32];

    spiStartCompoundTransfer();

    outputData[0] = command;
    gpioClearOutput(SSD1351_GPIO_IOCONTROL);
    spiTransfer(0, outputData, inputData, 1);
    if (paramsLength > 0)
    {
        gpioSetOutput(SSD1351_GPIO_IOCONTROL);
        spiTransfer(0, params, inputData, paramsLength);
    }

    spiEndCompoundTransfer();
}

static void ssd1351Reset(void)
{
    gpioFuncSelect(SSD1351_GPIO_RESET,     GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(SSD1351_GPIO_IOCONTROL, GPIO_FUNCSELECT_OUTPUT);

    systemtimerWaitUntil(1000);
    gpioClearOutput(SSD1351_GPIO_RESET);
    systemtimerWait(10);
    gpioSetOutput(SSD1351_GPIO_RESET);
    systemtimerWait(10);
    ssd1351SendOperation(0xAF, 0, 0);
    systemtimerWait(200000);
}

void ssd1351Init(void)
{
    spiSetClockRate(500000);

    ssd1351Reset();
}

void ssd1351Sleep(void)
{
}

void ssd1351Wake(void)
{
}

void ssd1351Shutdown(void)
{
}

void ssd1351Test(void)
{
  /*
    UnsignedByte params[30];

    params[0] = 0x1F;
    params[1] = 0x1F;
    params[2] = 0x1F;

    ssd1351SendOperation(0x5C, params, 30);
  */

    ssd1351SendOperation(0xA5, 0, 0);
}
