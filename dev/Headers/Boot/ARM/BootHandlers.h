#ifndef _BOOT_BOOTHANDLERS
#define _BOOT_BOOTHANDLERS 1

/*                                                                                                                                                  * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.                                                      */

extern void boot_undefinedInstructionHandler(void);
extern void boot_softwareInterruptHandler(void);
extern void boot_prefetchAbortHandler(void);
extern void boot_dataAbortHandler(void);
extern void boot_reservedHandler(void);
extern void boot_interruptRequestHandler(void);
extern void boot_fastInterruptRequestHandler(void);

#endif
