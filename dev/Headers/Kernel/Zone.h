#ifndef _KERNEL_ZONE
#define _KERNEL_ZONE 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/ARM/ZoneControlBlock.h>

extern ZoneControlBlock *currentZoneControlBlock;

extern void             zone_init(void);
extern ZoneControlBlock *zone_create();
extern void             zone_destroy(ZoneControlBlock *zoneControlBlock);
extern void             zone_shutdown(void);

#endif
