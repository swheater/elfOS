/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - ILI9320

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_GPIO.h>
#include <Device/BCM2835_SPI.h>
#include <Device/BCM2835_SystemTimer.h>
#include <Device/RaspPi_ILI9320.h>

#define ILI9320_GPIO_RESET     (25)
#define ILI9320_GPIO_BACKLIGHT (18)

#define ILI9320_DRIVERCODEREAD_INST                 (0x0000)
#define ILI9320_STARTOSCILLATION_INST               (0x0000)
#define ILI9320_DRIVEROUTPUTCONTROL1_INST           (0x0001)
#define ILI9320_LCDDRIVINGCONTROL_INST              (0x0002)
#define ILI9320_ENTRYMODE_INST                      (0x0003)
#define ILI9320_RESIZECONTROL_INST                  (0x0004)
#define ILI9320_DISPLAYCONTROL1_INST                (0x0007)
#define ILI9320_DISPLAYCONTROL2_INST                (0x0008)
#define ILI9320_DISPLAYCONTROL3_INST                (0x0009)
#define ILI9320_DISPLAYCONTROL4_INST                (0x000A)
#define ILI9320_RGBDISPLAYINTERFACECONTROL1_INST    (0x000C)
#define ILI9320_FRAMEMAKERPOSITION_INST             (0x000D)
#define ILI9320_RGBDISPLAYINTERFACECONTROL2_INST    (0x000F)
#define ILI9320_POWERCONTROL1_INST                  (0x0010)
#define ILI9320_POWERCONTROL2_INST                  (0x0011)
#define ILI9320_POWERCONTROL3_INST                  (0x0012)
#define ILI9320_POWERCONTROL4_INST                  (0x0013)
#define ILI9320_HORIZONTALGRAMADDRESSSET_INST       (0x0020)
#define ILI9320_VERTICALGRAMADDRESSSET_INST         (0x0021)
#define ILI9320_WRITEDATATOGRAM_INST                (0x0022)
#define ILI9320_POWERCONTROL7_INST                  (0x0029)
#define ILI9320_FRAMERATEANDCOLORCONTROL_INST       (0x002B)
#define ILI9320_GAMMACONTROL01_INST                 (0x0030)
#define ILI9320_GAMMACONTROL02_INST                 (0x0031)
#define ILI9320_GAMMACONTROL03_INST                 (0x0032)
#define ILI9320_GAMMACONTROL04_INST                 (0x0035)
#define ILI9320_GAMMACONTROL05_INST                 (0x0036)
#define ILI9320_GAMMACONTROL06_INST                 (0x0037)
#define ILI9320_GAMMACONTROL07_INST                 (0x0038)
#define ILI9320_GAMMACONTROL08_INST                 (0x0039)
#define ILI9320_GAMMACONTROL09_INST                 (0x003C)
#define ILI9320_GAMMACONTROL10_INST                 (0x003D)
#define ILI9320_HORIZONTALADDRESSSTARTPOSITION_INST (0x0050)
#define ILI9320_HORIZONTALADDRESSENDPOSITION_INST   (0x0051)
#define ILI9320_VERTICALADDRESSSTARTPOSITION_INST   (0x0052)
#define ILI9320_VERTICALADDRESSENDPOSITION_INST     (0x0053)
#define ILI9320_DRIVEROUTPUTCONTROL2_INST           (0x0060)
#define ILI9320_BASEIMAGEDISPLAYCONTROL_INST        (0x0061)
#define ILI9320_VERTICALSCROLLCONTROL_INST          (0x006A)
#define ILI9320_PARTIALIMAGE1DISPLAYPOSITION_INST   (0x0080)
#define ILI9320_PARTIALIMAGE1AREASTARTLINE_INST     (0x0081)
#define ILI9320_PARTIALIMAGE1AREAENDLINE_INST       (0x0082)
#define ILI9320_PARTIALIMAGE2DISPLAYPOSITION_INST   (0x0083)
#define ILI9320_PARTIALIMAGE2AREASTARTLINE_INST     (0x0084)
#define ILI9320_PARTIALIMAGE2AREAENDLINE_INST       (0x0085)
#define ILI9320_PANELINTERFACECONTROL1_INST         (0x0090)
#define ILI9320_PANELINTERFACECONTROL2_INST         (0x0092)
#define ILI9320_PANELINTERFACECONTROL3_INST         (0x0093)
#define ILI9320_PANELINTERFACECONTROL4_INST         (0x0095)
#define ILI9320_PANELINTERFACECONTROL5_INST         (0x0097)
#define ILI9320_PANELINTERFACECONTROL6_INST         (0x0098)

static void logOutputInputData(const char *message, UnsignedByte outputData[], UnsignedWord32 outputDataLength, UnsignedByte inputData[], UnsignedWord32 inputDataLength)
{
    logMessage(message);
    logMessage(": output = ");
    logDataHex(outputData, outputDataLength);
    logMessage(", input = ");
    logDataHex(inputData, inputDataLength);
    logMessage("\r\n");
}

static void ili9320SetIndexRegister(UnsignedWord16 reg)
{
    UnsignedByte outputData[3];
    UnsignedByte inputData[3];

    outputData[0] =  0x70;
    outputData[1] = (reg >> 8) & 0xFF;
    outputData[2] = reg & 0xFF;
 
    spiTransfer(0, outputData, inputData, 3);
    //    logOutputInputData("sir", outputData, 3, inputData, 3);
}

static UnsignedWord16 ili9320GetStatusRegister(void)
{
    UnsignedByte outputData[4];
    UnsignedByte inputData[4];

    outputData[0] = 0x71;
    outputData[1] = 0xFF;
    outputData[2] = 0xFF;
    outputData[3] = 0xFF;
 
    spiTransfer(0, outputData, inputData, 4);
    //    logOutputInputData("gsr", outputData, 4, inputData, 4);

    return (inputData[2] << 8) | inputData[3];
}

static UnsignedWord16 ili9320GetCurrentRegister(void)
{
    UnsignedByte outputData[4];
    UnsignedByte inputData[4];

    outputData[0] = 0x73;
    outputData[1] = 0xFF;
    outputData[2] = 0xFF;
    outputData[3] = 0xFF;
 
    spiTransfer(0, outputData, inputData, 4);
    //    logOutputInputData("gcr", outputData, 4, inputData, 4);

    return (inputData[3] << 8) | inputData[2];
}

static void ili9320SetCurrentRegister(UnsignedWord16 value)
{
    UnsignedByte outputData[3];
    UnsignedByte inputData[3];

    outputData[0] =  0x72;
    outputData[1] = (value >> 8) & 0xFF;
    outputData[2] = value & 0xFF;
 
    spiTransfer(0, outputData, inputData, 3);
    //    logOutputInputData("scr", outputData, 3, inputData, 3);
}

static UnsignedWord16 ili9320GetRegister(UnsignedWord16 reg)
{
    spiStartCompoundTransfer();

    ili9320SetIndexRegister(reg);

    UnsignedWord16 value = ili9320GetCurrentRegister();

    spiEndCompoundTransfer();

    return value;
}

static void ili9320SetRegister(UnsignedWord16 reg, UnsignedWord16 value)
{
    logMessage("Reg = ");
    logUnsignedWord16Hex(reg);
    logMessage(", Value = ");
    logUnsignedWord16Hex(value);
    logMessage("\r\n");

    spiStartCompoundTransfer();

    ili9320SetIndexRegister(reg);

    ili9320SetCurrentRegister(value);

    spiEndCompoundTransfer();
}

static void ili9320Reset(void)
{
    gpioSetOutput(ILI9320_GPIO_RESET);
    systemtimerWait(1000);
    gpioClearOutput(ILI9320_GPIO_RESET);
    systemtimerWait(10000);
    gpioSetOutput(ILI9320_GPIO_RESET);
    systemtimerWait(50000);
}

static void ili9320EnableBacklight(Boolean enabled)
{
    pwmSetRange(0, 2000000);
    pwmSetMark(0, 1800000);
  //    if (enabled)
  //      gpioSetOutput(ILI9320_GPIO_BACKLIGHT);
  //  else
  //      gpioClearOutput(ILI9320_GPIO_BACKLIGHT);
}

static void ili9320StartInitialSequence(void)
{
    ili9320SetRegister(0x00E5, 0x8000); // What is this?
    ili9320SetRegister(ILI9320_STARTOSCILLATION_INST,     0x0001);
    ili9320SetRegister(ILI9320_DRIVEROUTPUTCONTROL1_INST, 0x0100);
    ili9320SetRegister(ILI9320_LCDDRIVINGCONTROL_INST,    0x0700);
    //    ili9320SetRegister(ILI9320_ENTRYMODE_INST,                   0x1030);
    ili9320SetRegister(ILI9320_RESIZECONTROL_INST,        0x0000);

    //    ili9320SetRegister(ILI9320_DISPLAYCONTROL1_INST,             0x0202);
    //    ili9320SetRegister(ILI9320_DISPLAYCONTROL2_INST,             0x0000);
    ili9320SetRegister(ILI9320_DISPLAYCONTROL2_INST,             0x0202);
    ili9320SetRegister(ILI9320_DISPLAYCONTROL3_INST,             0x0000);
    ili9320SetRegister(ILI9320_DISPLAYCONTROL4_INST,             0x0000);
    ili9320SetRegister(ILI9320_RGBDISPLAYINTERFACECONTROL1_INST, 0x0000);
    ili9320SetRegister(ILI9320_FRAMEMAKERPOSITION_INST,          0x0000);
    ili9320SetRegister(ILI9320_RGBDISPLAYINTERFACECONTROL2_INST, 0x0000);
}

static void ili9320PowerOnSequence(void)
{
    ili9320SetRegister(ILI9320_POWERCONTROL1_INST, 0x0000);
    //    ili9320SetRegister(ILI9320_POWERCONTROL2_INST, 0x0000);
    ili9320SetRegister(ILI9320_POWERCONTROL2_INST, 0x0007);
    ili9320SetRegister(ILI9320_POWERCONTROL3_INST, 0x0000);
    ili9320SetRegister(ILI9320_POWERCONTROL4_INST, 0x0000);
    systemtimerWait(200000);

    ili9320SetRegister(ILI9320_POWERCONTROL1_INST, 0x17B0);
    ili9320SetRegister(ILI9320_POWERCONTROL2_INST, 0x0031);
    systemtimerWait(50000);
    ili9320SetRegister(ILI9320_POWERCONTROL3_INST, 0x0138);
    systemtimerWait(50000);
    ili9320SetRegister(ILI9320_POWERCONTROL4_INST, 0x1800);

    ili9320SetRegister(ILI9320_POWERCONTROL7_INST, 0x0008);
    systemtimerWait(50000);

    ili9320SetRegister(ILI9320_HORIZONTALGRAMADDRESSSET_INST, 0x0000);
    ili9320SetRegister(ILI9320_VERTICALGRAMADDRESSSET_INST, 0x0000);
}

static void ili9320DefaultGammaCurve(void)
{
    ili9320SetRegister(ILI9320_GAMMACONTROL01_INST, 0x0000);
    ili9320SetRegister(ILI9320_GAMMACONTROL02_INST, 0x0505);
    ili9320SetRegister(ILI9320_GAMMACONTROL03_INST, 0x0004);
    ili9320SetRegister(ILI9320_GAMMACONTROL04_INST, 0x0006);
    ili9320SetRegister(ILI9320_GAMMACONTROL05_INST, 0x0707);
    ili9320SetRegister(ILI9320_GAMMACONTROL06_INST, 0x0105);
    ili9320SetRegister(ILI9320_GAMMACONTROL07_INST, 0x0002);
    ili9320SetRegister(ILI9320_GAMMACONTROL08_INST, 0x0707);
    ili9320SetRegister(ILI9320_GAMMACONTROL09_INST, 0x0704);
    ili9320SetRegister(ILI9320_GAMMACONTROL10_INST, 0x0807);
}

static void ili9320SetGRAMArea(void)
{
    ili9320SetRegister(ILI9320_HORIZONTALADDRESSSTARTPOSITION_INST, 0x0000);
    ili9320SetRegister(ILI9320_HORIZONTALADDRESSENDPOSITION_INST, 0x00EF);
    ili9320SetRegister(ILI9320_VERTICALADDRESSSTARTPOSITION_INST, 0x0000);
    ili9320SetRegister(ILI9320_VERTICALADDRESSENDPOSITION_INST, 0x013F);

    ili9320SetRegister(ILI9320_DRIVEROUTPUTCONTROL2_INST, 0x2700);
    //    ili9320SetRegister(ILI9320_BASEIMAGEDISPLAYCONTROL_INST, 0x0010);
    ili9320SetRegister(ILI9320_BASEIMAGEDISPLAYCONTROL_INST, 0x0001);
    ili9320SetRegister(ILI9320_VERTICALSCROLLCONTROL_INST, 0x0000);
}

static void ili9320PartialDisplayControl(void)
{
    ili9320SetRegister(ILI9320_PARTIALIMAGE1DISPLAYPOSITION_INST , 0x0000);
    ili9320SetRegister(ILI9320_PARTIALIMAGE1AREASTARTLINE_INST, 0x0000);
    ili9320SetRegister(ILI9320_PARTIALIMAGE1AREAENDLINE_INST, 0x0000);
    ili9320SetRegister(ILI9320_PARTIALIMAGE2DISPLAYPOSITION_INST , 0x0000);
    ili9320SetRegister(ILI9320_PARTIALIMAGE2AREASTARTLINE_INST, 0x0000);
    ili9320SetRegister(ILI9320_PARTIALIMAGE2AREAENDLINE_INST, 0x0000);
}

static void ili9320PanelControl(void)
{
    ili9320SetRegister(ILI9320_PANELINTERFACECONTROL1_INST, 0x0010);
    ili9320SetRegister(ILI9320_PANELINTERFACECONTROL2_INST, 0x0000);
    ili9320SetRegister(ILI9320_PANELINTERFACECONTROL3_INST, 0x0003);
    ili9320SetRegister(ILI9320_PANELINTERFACECONTROL4_INST, 0x0110);
    ili9320SetRegister(ILI9320_PANELINTERFACECONTROL5_INST, 0x0000);
    ili9320SetRegister(ILI9320_PANELINTERFACECONTROL6_INST, 0x0000);

    ili9320SetRegister(ILI9320_DISPLAYCONTROL1_INST, 0x0173);
}

void ili9320Init(void)
{
    gpioFuncSelect(ILI9320_GPIO_RESET, GPIO_FUNCSELECT_OUTPUT);
    gpioSetPullControl(ILI9320_GPIO_RESET, GPIO_PULL_OFF);
    //    gpioFuncSelect(ILI9320_GPIO_BACKLIGHT, GPIO_FUNCSELECT_OUTPUT);
    //    gpioSetPullControl(ILI9320_GPIO_BACKLIGHT, GPIO_PULL_OFF);

    spiSetClockRate(5000000);

    ili9320Reset();

    ili9320StartInitialSequence();
    ili9320PowerOnSequence();
    ili9320DefaultGammaCurve();
    ili9320SetGRAMArea();
    ili9320PartialDisplayControl();
    ili9320PanelControl();

    ili9320EnableBacklight(TRUE);
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

void ili9320Test(void)
{
    UnsignedWord16 status = ili9320GetStatusRegister();
    logMessage("\r\nStatus: ");
    logUnsignedWord16Hex(status);
    logMessage("\r\n");

    int            count = 0;
    UnsignedWord16 reg   = 0;
    while ((reg == 0x0000) && (count < 8))
    {
        reg = ili9320GetRegister(ILI9320_DRIVERCODEREAD_INST);

        logMessage("Driver Code: ");
        logUnsignedWord16Hex(reg);
        logMessage("\r\n");

        systemtimerWait(6000000);
        count++;
    }

    spiStartCompoundTransfer();

    ili9320SetIndexRegister(ILI9320_WRITEDATATOGRAM_INST);
    for (count = 0; count < 4096; count++)
    {
        ili9320SetCurrentRegister(0x0FF0);
    }

    spiEndCompoundTransfer();
}
