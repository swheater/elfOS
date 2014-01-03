#ifndef _DEVICE_RASPPI_ILSOFTOLED_H
#define _DEVICE_RASPPI_ILSOFTOLED_H 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#define SWITCH_UP     (0x01)
#define SWITCH_RIGHT  (0x02)
#define SWITCH_DOWN   (0x04)
#define SWITCH_LEFT   (0x08)
#define SWITCH_SELECT (0x10)

extern void         ilsoftoledInit(void);
extern Boolean      ilsoftoledGetSwitchState(UnsignedByte switchs);
extern UnsignedByte ilsoftoledGetSwitchStates(void);
extern void         ilsoftoledRedraw(void);
extern void         ilsoftoledDrawPixel(UnsignedByte x, UnsignedByte y, UnsignedByte red, UnsignedByte green, UnsignedByte blue);
extern void         ilsoftoledSetPixel(UnsignedByte x, UnsignedByte y, UnsignedByte red, UnsignedByte green, UnsignedByte blue);
extern void         ilsoftoledShutdown(void);

#endif
