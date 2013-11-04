#ifndef _DEVICE_RASPPI_ILI9320_H
#define _DEVICE_RASPPI_ILI9320_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

extern void ili9320Init(void);
extern void ili9320Sleep(void);
extern void ili9320Wake(void);
extern void ili9320Shutdown(void);

extern void ili9320Test(void);

#endif
