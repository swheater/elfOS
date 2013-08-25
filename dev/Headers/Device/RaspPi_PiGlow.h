#ifndef _DEVICE_RASPPI_PIGLOW_H
#define _DEVICE_RASPPI_PIGLOW_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

#define PIGLOW_ARMS    (6)
#define PIGLOW_ARM_0   (0x00)
#define PIGLOW_ARM_1   (0x01)
#define PIGLOW_ARM_2   (0x02)
#define PIGLOW_ARM_MIN (PIGLOW_ARM_0)
#define PIGLOW_ARM_MAX (PIGLOW_ARM_2)

#define PIGLOW_LEDS_PER_ARM     (6)
#define PIGLOW_LEDCOLOUR_WHITE  (0x00)
#define PIGLOW_LEDCOLOUR_BLUE   (0x01)
#define PIGLOW_LEDCOLOUR_GREEN  (0x02)
#define PIGLOW_LEDCOLOUR_YELLOW (0x03)
#define PIGLOW_LEDCOLOUR_ORANGE (0x04)
#define PIGLOW_LEDCOLOUR_RED    (0x05)
#define PIGLOW_LEDCOLOUR_MIN    (PIGLOW_LEDCOLOUR_WHITE)
#define PIGLOW_LEDCOLOUR_MAX    (PIGLOW_LEDCOLOUR_RED)

#define PIGLOW_BRIGHTNESS_MIN (0)
#define PIGLOW_BRIGHTNESS_MAX (255)

extern void piglowInit(void);
extern void piglowReset(void);
extern void piglowGetEnabled(Boolean *enabled);
extern void piglowSetEnabled(Boolean enabled);
extern void piglowGetLEDEnabled(UnsignedByte arm, UnsignedByte ledColour, Boolean *enabled);
extern void piglowSetLEDEnabled(UnsignedByte arm, UnsignedByte ledColour, UnsignedByte enabled);
extern void piglowGetLEDBrightness(UnsignedByte arm, UnsignedByte ledColour, UnsignedByte *brightness);
extern void piglowSetLEDBrightness(UnsignedByte arm, UnsignedByte ledColour, UnsignedByte brightness);

#endif
