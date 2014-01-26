/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/PageMemory.h>

static int          pageBitmapIndex;
static UnsignedByte pageBitmap[PAGEMAPSIZE];

void kernel_pageMemoryInit(void)
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
    pageBitmap[6] = 0xFF;
    pageBitmap[7] = 0xFF;

    for (index = PAGEMAPSIZE - ((16 * 1024 * 1024) / (4 * 1024 * 8)); index < PAGEMAPSIZE; index++)
        pageBitmap[index] = 0xFF;

    pageBitmapIndex = 0;
}

static UnsignedWord32 kernel_pageMemoryAcquirePage(UnsignedByte bitmask, UnsignedByte bitsPerGroup)
{
    UnsignedWord32 page = 0;

    int pageIndex;
    for (pageIndex = 0; (pageIndex < PAGEMAPSIZE) && (page == 0); pageIndex++)
    {
        if (pageBitmap[(pageIndex + pageBitmapIndex) % PAGEMAPSIZE] != 0xFF)
        {
            UnsignedByte bitmap = pageBitmap[(pageIndex + pageBitmapIndex) % PAGEMAPSIZE];
 
            int bitIndex;
            for (bitIndex = 0; (bitIndex < 8) && (page == 0); bitIndex += bitsPerGroup)
            {
                if ((bitmap & bitmask) == 0x00)
                {
                    page = 4096 * ((8 * (pageIndex + pageBitmapIndex)) + bitIndex);
                    pageBitmap[(pageIndex + pageBitmapIndex) % PAGEMAPSIZE] |= (bitmask << bitIndex);
                }

                bitmap =  bitmap >> bitsPerGroup;
            }
        }
    }

    return page;
}

UnsignedWord32 kernel_pageMemorySinglePageAcquire(void)
{
    return kernel_pageMemoryAcquirePage(0x01, 1);
}

UnsignedWord32 kernel_pageMemoryDuelPageAcquire(void)
{
    return kernel_pageMemoryAcquirePage(0x03, 2);
}

UnsignedWord32 kernel_pageMemoryQuadPageAcquire(void)
{
    return kernel_pageMemoryAcquirePage(0x0F, 4);
}

UnsignedWord32 kernel_pageMemoryOctPageAcquire(void)
{
    return kernel_pageMemoryAcquirePage(0xFF, 8);
}

void kernel_pageMemoryPageReleases(UnsignedWord32 pageAddress, UnsignedByte bitmask)
{
    int pageIndex = pageAddress / (4096 * 8);
    int bitIndex  = (pageAddress / 4096) % 8;

    pageBitmap[pageIndex] &= ~ (bitmask << bitIndex);
}

void kernel_pageMemorySinglePageRelease(UnsignedWord32 pageAddress)
{
    kernel_pageMemoryPageReleases(pageAddress, 0x01);
}

void kernel_pageMemoryDuelPageRelease(UnsignedWord32 pageAddress)
{
    kernel_pageMemoryPageReleases(pageAddress, 0x03);
}

void kernel_pageMemoryQuadPageRelease(UnsignedWord32 pageAddress)
{
    kernel_pageMemoryPageReleases(pageAddress, 0x0F);
}

void kernel_pageMemoryOctPageRelease(UnsignedWord32 pageAddress)
{
    kernel_pageMemoryPageReleases(pageAddress, 0xFF);
}

void kernel_pageMemoryShutdown(void)
{
}
