#ifndef _KERNEL_LOGGING
#define _KERNEL_LOGGING 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern void logUnsignedByteHex(UnsignedByte unsignedByte);
extern void logUnsignedByteASCII(UnsignedByte unsignedByte);
extern void logUnsignedWord16Hex(UnsignedWord16 unsignedWord16);
extern void logUnsignedWord32Hex(UnsignedWord32 unsignedWord32);
extern void logUnsignedWord32Bin(UnsignedWord32 unsignedWord32);
extern void logUnsignedWord64Hex(UnsignedWord64 unsignedWord64);
extern void logMessage(const char *message);
extern void logNewLine(void);

#endif
