#ifndef _DEVICE_RASPPI_XPT2046_H
#define _DEVICE_RASPPI_XPT2046_H 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

extern void xpt2046Init(void);
extern Boolean xpt2046GetTouch(void);
extern UnsignedWord16 xpt2046GetXPosition(void);
extern UnsignedWord16 xpt2046GetYPosition(void);
extern UnsignedWord16 xpt2046GetTouchPressure(void);
extern void xpt2046Shutdown(void);

#endif
