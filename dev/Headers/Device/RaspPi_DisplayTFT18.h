#ifndef _DEVICE_RASPPI_DISPLAYTFT18_H
#define _DEVICE_RASPPI_DISPLAYTFT18_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#define DISPLAYTFT18_COLOUR_BLACK   (0x00)
#define DISPLAYTFT18_COLOUR_BLUE    (0x01)
#define DISPLAYTFT18_COLOUR_RED     (0x02)
#define DISPLAYTFT18_COLOUR_GREEN   (0x03)
#define DISPLAYTFT18_COLOUR_AQUA    (0x04)
#define DISPLAYTFT18_COLOUR_FUCHSIA (0x05)
#define DISPLAYTFT18_COLOUR_YELLOW  (0x06)
#define DISPLAYTFT18_COLOUR_WHITE   (0x07)

// Clockwise Display Rotations
#define DISPLAYTFT18_ROTATION_0D    (0x03)
#define DISPLAYTFT18_ROTATION_90D   (0x02)
#define DISPLAYTFT18_ROTATION_180D  (0x01)
#define DISPLAYTFT18_ROTATION_270D  (0x00)

#define DISPLAYTFT18_FONTSIZE_SMALL  (1)
#define DISPLAYTFT18_FONTSIZE_MEDIUM (2)
#define DISPLAYTFT18_FONTSIZE_LARGE  (3)

#define DISPLAYTFT18_BACKLIGHTBRIGHTNESS_OFF (0)
#define DISPLAYTFT18_BACKLIGHTBRIGHTNESS_MAX (100)

extern void displayTFT18Init(void);
extern void displayTFT18ClearScreen(void);
extern void displayTFT18SetForegroundColour(UnsignedByte colour);
extern void displayTFT18SetBackgroundColour(UnsignedByte colour);
extern void displayTFT18SetScreenRotation(UnsignedByte screenRotation);
extern void displayTFT18SetFontSize(UnsignedByte fontSize);
extern void displayTFT18SetTextPositionBeginningOfLine(void);
extern void displayTFT18GotoTextPosition(UnsignedByte x, UnsignedByte y);
extern void displayTFT18GotoPixelPosition(UnsignedByte x, UnsignedByte y);
extern void displayTFT18DrawLine(UnsignedByte x1, UnsignedByte y1, UnsignedByte x2, UnsignedByte y2);
extern void displayTFT18DrawBox(UnsignedByte x1, UnsignedByte y1, UnsignedByte x2, UnsignedByte y2);
extern void displayTFT18DrawFilled(UnsignedByte x1, UnsignedByte y1, UnsignedByte x2, UnsignedByte y2);
extern void displayTFT18DrawCircle(UnsignedByte x, UnsignedByte y, UnsignedByte radius);
extern void displayTFT18DrawFilledCircle(UnsignedByte x, UnsignedByte y, UnsignedByte radius);
extern void displayTFT18DisplayBitmap(UnsignedByte x, UnsignedByte y, UnsignedByte *filename);
extern void displayTFT18BacklightBrightness(UnsignedByte backlightBrightness);
extern void displayTFT18OutputCharacter(UnsignedByte character);

#endif
