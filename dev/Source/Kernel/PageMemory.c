/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/PageMemory.h>

static int          pageBitmapIndex;
static UnsignedByte pageBitmap[PAGEMAPSIZE];

void kernel_pageMemorySetup(void)
{
    int index;
    for (index = 0; index < PAGEMAPSIZE; index++)
        pageBitmap[index] = 0x00;

    pageBitmap[0] = 0xFF;
    pageBitmap[1] = 0xFF;
    pageBitmap[2] = 0xFF;
    pageBitmap[3] = 0xFF;
    pageBitmap[4] = 0xFF;
    pageBitmap[5] = 0xFF;

    for (index = PAGEMAPSIZE - ((16 * 1024 * 1024) / (4 * 1024 * 8)); index < PAGEMAPSIZE; index++)
        pageBitmap[index] = 0xFF;

    pageBitmapIndex = 0;
}

UnsignedWord32 kernel_pageMemoryAcquire(void)
{
    UnsignedWord32 page = 0;

    int pageIndex;
    for (pageIndex = 0; (pageIndex < PAGEMAPSIZE) && (page == 0); pageIndex++)
    {
        if (pageBitmap[(pageIndex + pageBitmapIndex) % PAGEMAPSIZE] != 0xFF)
        {
            UnsignedByte bitmap = pageBitmap[(pageIndex + pageBitmapIndex) % PAGEMAPSIZE];
 
            int bitIndex;
            for (bitIndex = 0; (bitIndex < 8) && (page == 0); bitIndex++)
	    {
                if ((bitmap & 0x01) == 0x00)
		{
                    page = 4096 * ((8 * (pageIndex + pageBitmapIndex)) + bitIndex);
                    pageBitmap[(pageIndex + pageBitmapIndex) % PAGEMAPSIZE] |= (1 << bitIndex);
		}

                bitmap = bitmap >> 1;
	    }
        }
    }

    return page;
}

void kernel_pageMemoryRelease(UnsignedWord32 pageAddress)
{
    int pageIndex = pageAddress / (4096 * 8);
    int bitIndex  = (pageAddress / 4096) % 8;

    pageBitmap[pageIndex] &= ~ (1 << bitIndex);
}
