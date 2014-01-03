/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
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

void ssd1351Init(Boolean andWake)
{
    spiSetClockRate(20000000);

    gpioFuncSelect(SSD1351_GPIO_RESET,     GPIO_FUNCSELECT_OUTPUT);
    gpioFuncSelect(SSD1351_GPIO_IOCONTROL, GPIO_FUNCSELECT_OUTPUT);

    systemtimerWaitUntil(1000);
    gpioClearOutput(SSD1351_GPIO_RESET);
    systemtimerWait(10);
    gpioSetOutput(SSD1351_GPIO_RESET);
    systemtimerWait(10);

    if (andWake)
        ssd1351Wake();
}

void ssd1351SendOperation(UnsignedByte command, UnsignedByte params[], UnsignedWord32 paramsLength)
{
    UnsignedByte outputData[1];

    spiStartCompoundTransfer();

    outputData[0] = command;
    gpioClearOutput(SSD1351_GPIO_IOCONTROL);
    spiOutputTransfer(0, outputData, 1);
    if (paramsLength > 0)
    {
        gpioSetOutput(SSD1351_GPIO_IOCONTROL);
        spiOutputTransfer(0, params, paramsLength);
    }

    spiEndCompoundTransfer();
}

void ssd1351Sleep(void)
{
    ssd1351SendOperation(0xAE, 0, 0);
}

void ssd1351Wake(void)
{
    ssd1351SendOperation(0xAF, 0, 0);
    systemtimerWait(200000);
}

void ssd1351Shutdown(void)
{
    ssd1351SendOperation(0xAE, 0, 0);
}
