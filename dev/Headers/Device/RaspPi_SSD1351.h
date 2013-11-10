#ifndef _DEVICE_RASPPI_SSD1351_H
#define _DEVICE_RASPPI_SSD1351_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

extern void ssd1351Init(Boolean andWake);
extern void ssd1351SendOperation(UnsignedByte command, UnsignedByte params[], UnsignedWord32 paramsLength);
extern void ssd1351Sleep(void);
extern void ssd1351Wake(void);
extern void ssd1351Shutdown(void);

#endif
