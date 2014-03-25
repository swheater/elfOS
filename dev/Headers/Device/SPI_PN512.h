#ifndef _DEVICE_SPI_PN512_H
#define _DEVICE_SPI_PN512_H 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#define PN512_PAGE0_PAGE_REG    (0x00)
#define PN512_PAGE3_VERSION_REG (0x07)

extern void pn512Init(void);
extern void pn512ReadRegister(UnsignedByte chipSelect, UnsignedByte registAddr, UnsignedByte *value);
extern void pn512WriteRegister(UnsignedByte chipSelect, UnsignedByte registAddr, UnsignedByte value);
extern void pn512Test(void);
extern void pn512Shutdown(void);

#endif
