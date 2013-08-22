/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - Serial 1.8in TFT Display

#include <Kernel/StdTypes.h>
#include <Device/BCM2835_miniUART.h>
#include <Device/RaspPi_DisplayTFT18.h>

#define COMMAND_START     (0x1B)
#define COMMAND_TERMINATE (0xFF)

void displayTFT18Init(void)
{
    // Delay to wait for ATmega328 chip startup
    volatile int c;
    for (c = 0; c < 1000000; c++);

    displayTFT18ClearScreen();
    displayTFT18SetForegroundColour(DISPLAYTFT18_COLOUR_WHITE);
    displayTFT18SetBackgroundColour(DISPLAYTFT18_COLOUR_BLACK);
    displayTFT18SetScreenRotation(DISPLAYTFT18_ROTATION_90D);
    displayTFT18SetFontSize(DISPLAYTFT18_FONTSIZE_SMALL);
}

void displayTFT18ClearScreen(void)
{
    uartOutput(COMMAND_START);
    uartOutput(0x00);
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18SetForegroundColour(UnsignedByte colour)
{
    uartOutput(COMMAND_START);
    uartOutput(0x01);
    uartOutput(colour);
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18SetBackgroundColour(UnsignedByte colour)
{
    uartOutput(COMMAND_START);
    uartOutput(0x02);
    uartOutput(colour);
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18SetScreenRotation(UnsignedByte screenRotation)
{
    uartOutput(COMMAND_START);
    uartOutput(0x03);
    uartOutput(screenRotation);
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18SetFontSize(UnsignedByte fontSize)
{
    uartOutput(COMMAND_START);
    uartOutput(0x04);
    uartOutput(fontSize);
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18SetTextPositionBeginningOfLine(void)
{
    uartOutput(COMMAND_START);
    uartOutput(0x05);
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18GotoTextPosition(UnsignedByte x, UnsignedByte y)
{
    uartOutput(COMMAND_START);
    uartOutput(0x06);
    uartOutput(x);
    uartOutput(y);
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18GotoPixelPosition(UnsignedByte x, UnsignedByte y)
{
    uartOutput(COMMAND_START);
    uartOutput(0x07);
    uartOutput(x);
    uartOutput(y);
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18DrawLine(UnsignedByte x1, UnsignedByte y1, UnsignedByte x2, UnsignedByte y2)
{
    uartOutput(COMMAND_START);
    uartOutput(0x08);
    uartOutput(x1);
    uartOutput(y1);
    uartOutput(x2);
    uartOutput(y2);
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18DrawBox(UnsignedByte x1, UnsignedByte y1, UnsignedByte x2, UnsignedByte y2)
{
    uartOutput(COMMAND_START);
    uartOutput(0x09);
    uartOutput(x1);
    uartOutput(y1);
    uartOutput(x2);
    uartOutput(y2);
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18DrawFilled(UnsignedByte x1, UnsignedByte y1, UnsignedByte x2, UnsignedByte y2)
{
    uartOutput(COMMAND_START);
    uartOutput(0x0A);
    uartOutput(x1);
    uartOutput(y1);
    uartOutput(x2);
    uartOutput(y2);
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18DrawCircle(UnsignedByte x, UnsignedByte y, UnsignedByte radius)
{
    uartOutput(COMMAND_START);
    uartOutput(0x0B);
    uartOutput(x);
    uartOutput(y);
    uartOutput(radius);
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18DrawFilledCircle(UnsignedByte x, UnsignedByte y, UnsignedByte radius)
{
    uartOutput(COMMAND_START);
    uartOutput(0x0C);
    uartOutput(x);
    uartOutput(y);
    uartOutput(radius);
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18DisplayBitmap(UnsignedByte x, UnsignedByte y, UnsignedByte *filename)
{
    uartOutput(COMMAND_START);
    uartOutput(0x0D);
    uartOutput(x);
    uartOutput(y);
    int index = 0;
    while (filename[index] != 0)
    {
        uartOutput(filename[index]);
        index++;
    }
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18BacklightBrightness(UnsignedByte backlightBrightness)
{
    uartOutput(COMMAND_START);
    uartOutput(0x0E);
    uartOutput(backlightBrightness);
    uartOutput(COMMAND_TERMINATE);
}

void displayTFT18OutputCharacter(UnsignedByte character)
{
    if (character != COMMAND_START)
        uartOutput(character);
}
