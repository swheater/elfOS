/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - XPT2046

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_GPIO.h>
#include <Device/BCM2835_SPI.h>
#include <Device/BCM2835_SystemTimer.h>
#include <Device/RaspPi_XPT2046.h>

#define GPIO_BASE                ((volatile UnsignedWord32*) 0x20200000)
#define GPIO_FUNCSELECT_BASE     (GPIO_BASE + 0x00)
#define GPIO_FUNCSELECT_1_OFFSET (0x01)
#define GPIO_LEVEL_BASE          (GPIO_BASE + 0x0D)
#define GPIO_LEVEL_0_OFFSET      (0x00)
#define GPIO_LEVEL_1_OFFSET      (0x01)

#define XPT2046_GPIO_PENIRQN (17)

#define XPI2046_POWERDOWNMODE0_BIT        (0x00)
#define XPI2046_POWERDOWNMODE1_BIT        (0x01)
#define XPI2046_POWERDOWNMODE2_BIT        (0x02)
#define XPI2046_POWERDOWNMODE3_BIT        (0x03)
#define XPI2046_DIFFERENTIALREFERENCE_BIT (0x00)
#define XPI2046_SINGLEENDEDREFERENCE_BIT  (0x04)
#define XPI2046_MODE_8BIT_BIT             (0x08)
#define XPI2046_MODE_12BIT_BIT            (0x00)
#define XPI2046_CHANNELSELECT0_BITS       (0x00)
#define XPI2046_CHANNELSELECT1_BITS       (0x10)
#define XPI2046_CHANNELSELECT2_BITS       (0x20)
#define XPI2046_CHANNELSELECT3_BITS       (0x30)
#define XPI2046_CHANNELSELECT4_BITS       (0x40)
#define XPI2046_CHANNELSELECT5_BITS       (0x50)
#define XPI2046_CHANNELSELECT6_BITS       (0x60)
#define XPI2046_CHANNELSELECT7_BITS       (0x70)
#define XPI2046_START_BIT                 (0x80)

static void logData(const char *message, UnsignedWord32 data[], UnsignedWord32 dataLength)
{
    logMessage(message);
    logMessage(":");
    UnsignedWord32 dataIndex;
    for (dataIndex = 0; dataIndex < dataLength; dataIndex++)
    {
        logMessage(" ");
        logUnsignedByteHex(data[dataIndex]);
    }
    logMessage("\r\n");
}

void xpt2046Init(void)
{
    spiSetClockRate(500000);

    UnsignedWord32 gpioFuncSelect;

    // Select function input for GPIO17
    gpioFuncSelect = *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_1_OFFSET);
    gpioFuncSelect &= 0xFF1FFFFF;
    gpioFuncSelect |= 0x00000000;
    *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_1_OFFSET) = gpioFuncSelect;
}

void xpt2046Test(void)
{
    UnsignedWord16 count;
    for (count = 0; count < 255; count++)
    {
        UnsignedWord32 outputData[8];
        UnsignedWord32 inputData[8];

        outputData[0] = XPI2046_START_BIT | XPI2046_CHANNELSELECT5_BITS | XPI2046_MODE_12BIT_BIT | XPI2046_DIFFERENTIALREFERENCE_BIT | XPI2046_POWERDOWNMODE0_BIT;
        outputData[1] = 0xFF;
        outputData[2] = 0xFF;
        outputData[3] = 0xFF;
        outputData[4] = 0xFF;
        outputData[5] = 0xFF;
        outputData[6] = 0xFF;
        outputData[7] = 0xFF;

        logData("Output", outputData, 3);
        spiTransfer(1, outputData, inputData, 3);
        logData("Input", inputData, 3);

	systemtimerWait(1000000);
    }
}

void xpt2046Shutdown(void)
{
}
