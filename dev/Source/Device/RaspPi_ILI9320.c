/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - ILI9320

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_GPIO.h>
#include <Device/BCM2835_SPI.h>
#include <Device/BCM2835_SystemTimer.h>
#include <Device/RaspPi_ILI9320.h>

#define ILI9320_GPIO_RESET     (18)
#define ILI9320_GPIO_BACKLIGHT (25)

#define ILI9320_GPIO_DRIVERCODEREAD_INST                 (0x0000)
#define ILI9320_GPIO_STARTOSCILLATION_INST               (0x0000)
#define ILI9320_GPIO_DRIVEROUTPUTCONTROL1_INST           (0x0001)
#define ILI9320_GPIO_ENTRYMODE_INST                      (0x0002)
#define ILI9320_GPIO_LCDDRIVINGCONTROL_INST              (0x0003)
#define ILI9320_GPIO_RESIZECONTROL_INST                  (0x0004)
#define ILI9320_GPIO_DISPLAYCONTROL1_INST                (0x0007)
#define ILI9320_GPIO_DISPLAYCONTROL2_INST                (0x0008)
#define ILI9320_GPIO_DISPLAYCONTROL3_INST                (0x0009)
#define ILI9320_GPIO_DISPLAYCONTROL4_INST                (0x000A)
#define ILI9320_GPIO_RGBDISPLAYINTERFACECONTROL1_INST    (0x000C)
#define ILI9320_GPIO_FRAMEMAKERPOSITION_INST             (0x000D)
#define ILI9320_GPIO_RGBDISPLAYINTERFACECONTROL2_INST    (0x000F)
#define ILI9320_GPIO_POWERCONTROL1_INST                  (0x0010)
#define ILI9320_GPIO_POWERCONTROL2_INST                  (0x0011)
#define ILI9320_GPIO_POWERCONTROL3_INST                  (0x0012)
#define ILI9320_GPIO_POWERCONTROL4_INST                  (0x0013)
#define ILI9320_GPIO_HORIZONTALGRAMADDRESSSET_INST       (0x0020)
#define ILI9320_GPIO_VERTICALGRAMADDRESSSET_INST         (0x0021)
#define ILI9320_GPIO_WRITEDATATOGRAM_INST                (0x0022)
#define ILI9320_GPIO_POWERCONTROL7_INST                  (0x0029)
#define ILI9320_GPIO_FRAMERATEANDCOLORCONTROL_INST       (0x002B)
#define ILI9320_GPIO_GAMMACONTROL01_INST                 (0x0030)
#define ILI9320_GPIO_GAMMACONTROL02_INST                 (0x0031)
#define ILI9320_GPIO_GAMMACONTROL03_INST                 (0x0032)
#define ILI9320_GPIO_GAMMACONTROL04_INST                 (0x0035)
#define ILI9320_GPIO_GAMMACONTROL05_INST                 (0x0036)
#define ILI9320_GPIO_GAMMACONTROL06_INST                 (0x0037)
#define ILI9320_GPIO_GAMMACONTROL07_INST                 (0x0038)
#define ILI9320_GPIO_GAMMACONTROL08_INST                 (0x0039)
#define ILI9320_GPIO_GAMMACONTROL09_INST                 (0x003C)
#define ILI9320_GPIO_GAMMACONTROL10_INST                 (0x003D)
#define ILI9320_GPIO_HORIZONTALADDRESSSTARTPOSITION_INST (0x0050)
#define ILI9320_GPIO_HORIZONTALADDRESSENDPOSITION_INST   (0x0051)
#define ILI9320_GPIO_VERTICALADDRESSSTARTPOSITION_INST   (0x0052)
#define ILI9320_GPIO_VERTICALADDRESSENDPOSITION_INST     (0x0053)
#define ILI9320_GPIO_DRIVEROUTPUTCONTROL2_INST           (0x0060)
#define ILI9320_GPIO_BASEIMAGEDISPLAYCONTROL_INST        (0x0061)
#define ILI9320_GPIO_VERTICALSCROLLCONTROL_INST          (0x006A)
#define ILI9320_GPIO_PARTIALIMAGE1DISPLAYPOSITION_INST   (0x0080)
#define ILI9320_GPIO_PARTIALIMAGE1AREASTARTLINE_INST     (0x0081)
#define ILI9320_GPIO_PARTIALIMAGE1AREAENDLINE_INST       (0x0082)
#define ILI9320_GPIO_PARTIALIMAGE2DISPLAYPOSITION_INST   (0x0083)
#define ILI9320_GPIO_PARTIALIMAGE2AREASTARTLINE_INST     (0x0084)
#define ILI9320_GPIO_PARTIALIMAGE2AREAENDLINE_INST       (0x0085)
#define ILI9320_GPIO_PANELINTERFACECONTROL1_INST         (0x0090)
#define ILI9320_GPIO_PANELINTERFACECONTROL2_INST         (0x0092)
#define ILI9320_GPIO_PANELINTERFACECONTROL3_INST         (0x0093)
#define ILI9320_GPIO_PANELINTERFACECONTROL4_INST         (0x0095)
#define ILI9320_GPIO_PANELINTERFACECONTROL5_INST         (0x0097)
#define ILI9320_GPIO_PANELINTERFACECONTROL6_INST         (0x0098)

static void logData(const char *message, UnsignedWord32 data[], UnsignedWord32 dataLength)
{
    logMessage(message);
    logMessage(":");
    UnsignedWord32 dataIndex;
    for (dataIndex = 0; dataIndex < dataLength; dataIndex++)
    {
        if ((dataIndex % 48) == 0)
            logMessage("\r\n");

        logMessage(" ");
        logUnsignedByteHex(data[dataIndex]);
    }
    logMessage("\r\n");
}

static void ili9320SetIndexRegistar(UnsignedWord16 registar)
{
    UnsignedWord32 outputData[3];
    UnsignedWord32 inputData[3];

    outputData[0] =  0x70;
    outputData[1] = (registar >> 8) & 0xFF;
    outputData[2] = registar & 0xFF;
 
    logData("sir output", outputData, 3);
    spiTransfer(0, outputData, inputData, 3);
    logData("sir input", inputData, 3);
}

static UnsignedWord16 ili9320GetStatusRegistar(void)
{
    UnsignedWord32 outputData[4];
    UnsignedWord32 inputData[4];

    outputData[0] = 0x71;
    outputData[1] = 0xFF;
    outputData[2] = 0xFF;
    outputData[3] = 0xFF;
 
    logData("gsr output", outputData, 4);
    spiTransfer(0, outputData, inputData, 4);
    logData("gsr input", inputData, 4);

    return (inputData[3] << 8) | inputData[2];
}

static UnsignedWord16 ili9320GetRegistar(void)
{
    UnsignedWord32 outputData[4];
    UnsignedWord32 inputData[4];

    outputData[0] = 0x73;
    outputData[1] = 0xFF;
    outputData[2] = 0xFF;
    outputData[3] = 0xFF;
 
    logData("gr output", outputData, 4);
    spiTransfer(0, outputData, inputData, 4);
    logData("gr input", inputData, 4);

    return (inputData[3] << 8) | inputData[2];
}

static void ili9320Reset(void)
{
    // Reset
    gpioSetOutput(ILI9320_GPIO_RESET);
    systemtimerWait(20000);
    gpioClearOutput(ILI9320_GPIO_RESET);
    systemtimerWait(20000);
    gpioSetOutput(ILI9320_GPIO_RESET);
    systemtimerWait(200000);
}

static void ili9320EnableBacklight(Boolean enabled)
{
    if (enabled)
        gpioSetOutput(ILI9320_GPIO_BACKLIGHT);
    else
        gpioClearOutput(ILI9320_GPIO_BACKLIGHT);
}

void ili9320Init(void)
{
    ili9320Reset();
    ili9320EnableBacklight(TRUE);

    UnsignedWord16 status = ili9320GetStatusRegistar();
    logMessage("Status: ");
    logUnsignedWord16Hex(status);
    logMessage("\r\n");

    ili9320SetIndexRegistar(ILI9320_GPIO_DRIVERCODEREAD_INST);

    UnsignedWord16 reg = ili9320GetRegistar();
    logMessage("Reg: ");
    logUnsignedWord16Hex(reg);
    logMessage("\r\n");
}

void ili9320Sleep(void)
{
}

void ili9320Wake(void)
{
}

void ili9320Shutdown(void)
{
}
