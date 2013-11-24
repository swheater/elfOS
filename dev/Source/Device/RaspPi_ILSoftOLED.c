/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi - ILSoftOLED

#include <Kernel/StdTypes.h>
#include <Device/BCM2835_GPIO.h>
#include <Device/RaspPi_SSD1351.h>
#include <Device/RaspPi_ILSoftOLED.h>

#define SWITCH_UP_GPIO     (23)
#define SWITCH_RIGHT_GPIO  (21)
#define SWITCH_DOWN_GPIO   (17)
#define SWITCH_LEFT_GPIO   (18)
#define SWITCH_SELECT_GPIO (22)

#define FB_WIDTH  (128)
#define FB_HEIGHT (128)
#define FB_DEPTH  (3)
#define FB_LENGTH (FB_WIDTH * FB_HEIGHT * FB_DEPTH)

static UnsignedByte framebuffer[FB_LENGTH];

static void ilsoftoledReloadPoint(UnsignedByte x, UnsignedByte y)
{
    UnsignedByte params[2];

    params[0] = x;
    params[1] = x;
    ssd1351SendOperation(0x15, params, 2);

    params[0] = y;
    params[1] = y;
    ssd1351SendOperation(0x75, params, 2);

    ssd1351SendOperation(0x5C, &framebuffer[3 * (x + (FB_HEIGHT * y))], 3);
}

static void ilsoftoledReloadArea(UnsignedByte x, UnsignedByte y, UnsignedByte width, UnsignedByte height)
{
    UnsignedByte params[2];

    params[0] = x;
    params[1] = x + width - 1;
    ssd1351SendOperation(0x15, params, 2);

    params[0] = y;
    params[1] = y + height - 1;
    ssd1351SendOperation(0x75, params, 2);

    int bufferLength    = 3 * width;
    int bufferStart     = 3 * (x + (FB_HEIGHT * y));
    int bufferIncrement = 3 * FB_WIDTH;
    int rowNumber;
    for (rowNumber = 0; rowNumber < height; rowNumber++)
    {
        ssd1351SendOperation(0x5C, &framebuffer[bufferStart], bufferLength);
        bufferStart += bufferIncrement;
    }
}

void ilsoftoledInit(void)
{
    UnsignedByte params[1];

    params[0] = 0xA0;
    ssd1351SendOperation(0xA0, params, 1);

    params[0] = 0xB1;
    ssd1351SendOperation(0xFD, params, 1);

    params[0] = 0x00;
    ssd1351SendOperation(0xA2, params, 1);

    params[0] = 0xB0;
    ssd1351SendOperation(0xFD, params, 1);

    int index;
    for (index = 0; index < FB_LENGTH; index++)
        framebuffer[index] = 0;
    ilsoftoledReloadArea(0, 0, FB_WIDTH, FB_HEIGHT);

    ssd1351Wake();

    gpioFuncSelect(SWITCH_UP_GPIO,         GPIO_FUNCSELECT_INPUT);
    gpioSetPullControl(SWITCH_UP_GPIO,     GPIO_PULL_UP);
    gpioFuncSelect(SWITCH_RIGHT_GPIO,      GPIO_FUNCSELECT_INPUT);
    gpioSetPullControl(SWITCH_RIGHT_GPIO,  GPIO_PULL_UP);
    gpioFuncSelect(SWITCH_DOWN_GPIO,       GPIO_FUNCSELECT_INPUT);
    gpioSetPullControl(SWITCH_DOWN_GPIO,   GPIO_PULL_UP);
    gpioFuncSelect(SWITCH_LEFT_GPIO,       GPIO_FUNCSELECT_INPUT);
    gpioSetPullControl(SWITCH_LEFT_GPIO,   GPIO_PULL_UP);
    gpioFuncSelect(SWITCH_SELECT_GPIO,     GPIO_FUNCSELECT_INPUT);
    gpioSetPullControl(SWITCH_SELECT_GPIO, GPIO_PULL_UP);
}

Boolean ilsoftoledGetSwitchState(UnsignedByte switches)
{
    Boolean result = FALSE;

    if ((switches & SWITCH_UP) == SWITCH_UP)
        result = result || (! gpioGetInput(SWITCH_UP_GPIO));

    if ((switches & SWITCH_RIGHT) == SWITCH_RIGHT)
        result = result || (! gpioGetInput(SWITCH_RIGHT_GPIO));

    if ((switches & SWITCH_DOWN) == SWITCH_DOWN)
        result = result || (! gpioGetInput(SWITCH_DOWN_GPIO));

    if ((switches & SWITCH_LEFT) == SWITCH_LEFT)
        result = result || (! gpioGetInput(SWITCH_LEFT_GPIO));

    if ((switches & SWITCH_SELECT) == SWITCH_SELECT)
        result = result || (! gpioGetInput(SWITCH_SELECT_GPIO));

    return result;
}

UnsignedByte ilsoftoledGetSwitchStates(void)
{
    UnsignedByte result = 0x00;

    if (! gpioGetInput(SWITCH_UP_GPIO))
	result |= SWITCH_UP;

    if (! gpioGetInput(SWITCH_RIGHT_GPIO))
	result |= SWITCH_RIGHT;

    if (! gpioGetInput(SWITCH_DOWN_GPIO))
	result |= SWITCH_DOWN;

    if (! gpioGetInput(SWITCH_LEFT_GPIO))
	result |= SWITCH_LEFT;

    if (! gpioGetInput(SWITCH_SELECT_GPIO))
	result |= SWITCH_SELECT;


    return result;
}

void ilsoftoledRedraw(void)
{
    ilsoftoledReloadArea(0, 0, FB_WIDTH, FB_HEIGHT);
}

void ilsoftoledDrawPixel(UnsignedByte x, UnsignedByte y, UnsignedByte red, UnsignedByte green, UnsignedByte blue)
{
    int pixelStart = 3 * (x + (FB_HEIGHT * y));

    framebuffer[pixelStart]     = blue  >> 2;
    framebuffer[pixelStart + 1] = red   >> 2;
    framebuffer[pixelStart + 2] = green >> 2;

    ilsoftoledReloadPoint(x, y);
}

void ilsoftoledSetPixel(UnsignedByte x, UnsignedByte y, UnsignedByte red, UnsignedByte green, UnsignedByte blue)
{
    int pixelStart = 3 * (x + (FB_HEIGHT * y));

    framebuffer[pixelStart]     = blue  >> 2;
    framebuffer[pixelStart + 1] = red   >> 2;
    framebuffer[pixelStart + 2] = green >> 2;
}

void ilsoftoledShutdown(void)
{
}

static int range(int bottom, int v, int top)
{
    if (bottom > v)
        return bottom;
    else if (v > top)
        return top;
    else
        return v;
}

void ilsoftoledTest(void)
{
    int x, y;
    for (x = 0; x < 128; x++)
        for (y = 0; y < 128; y++)
        {
            int red   = max(0, x - y, 255);
            int green = max(0, y - x, 255);
            int blue  = max(0, (x + y) / 2, 255);

            ilsoftoledSetPixel(x, y, red, green, blue);
        }
    ilsoftoledRedraw();

    x = 0;
    y = 0;
    while (TRUE)
    {
        if (ilsoftoledGetSwitchState(SWITCH_UP))
            ilsoftoledDrawPixel(FB_WIDTH / 2, (3 * FB_HEIGHT) / 4, 255, 255, 255);
            
        if (ilsoftoledGetSwitchState(SWITCH_RIGHT))
            ilsoftoledDrawPixel((3 * FB_WIDTH) / 4, FB_HEIGHT / 2, 255, 255, 255);

        if (ilsoftoledGetSwitchState(SWITCH_DOWN))
            ilsoftoledDrawPixel(FB_WIDTH / 2, FB_HEIGHT / 4, 255, 255, 255);
            
        if (ilsoftoledGetSwitchState(SWITCH_LEFT))
            ilsoftoledDrawPixel(FB_WIDTH / 4, FB_HEIGHT / 2, 255, 255, 255);

        if (ilsoftoledGetSwitchState(SWITCH_SELECT))
            ilsoftoledDrawPixel(FB_WIDTH / 2, FB_HEIGHT / 2, 255, 255, 255);
    }
}
