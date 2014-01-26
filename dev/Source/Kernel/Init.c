/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/Kernel.h>
#include <Kernel/VirtualMemory.h>
#include <Kernel/PageMemory.h>
#include <Kernel/Symbol.h>
#include <Kernel/Thread.h>
#include <Kernel/Handlers.h>
#include <Kernel/Logging.h>
#include <Kernel/KDebug.h>
#include <Device/BCM2835_miniUART.h>
#include <Device/BCM2835_Timer.h>
#include <Device/RaspPi_Status.h>
#include <elfOS/Thread.h>

static void swHandler(UnsignedWord32 opcode, ThreadControlBlock *threadControlBlock)
{
    uartOutput('@');

    //    if (opcode == 1)
    //        threadYield();
    //    else if (opcode == 2)
    //        threadDestroy(threadControlBlock);
}

static void irqHandler(void)
{
    if (currentThreadControlBlock != 0)
        threadYield();

    timerClearInterruptRequest();
}

void kernel_start(void)
{
    undefinedInstructionHandler = &defaultUndefinedInstructionHandler;
    softwareInterruptHandler    = &defaultSoftwareInterruptHandler;
    prefetchAbortHandler        = &defaultPrefetchAbortHandler;
    dataAbortHandler            = &defaultDataAbortHandler;
    reservedHandler             = &defaultReservedHandler;
    interruptRequestHandler     = &defaultInterruptRequestHandler;
    fastInterruptRequestHandler = &defaultFastInterruptRequestHandler;

    softwareInterruptHandler    = &swHandler;
    interruptRequestHandler     = &irqHandler;

    statusInit();
    threadsInit();
    timerInit(127, 1000000, TRUE);

    uartInit();

    kernel_pageMemoryInit();

    UnsignedWord32 page;

    page = kernel_pageMemoryOctPageAcquire();
    while (page != 0)
    {
        logUnsignedWord32Hex(page);
        logNewLine();

        page = kernel_pageMemoryOctPageAcquire();
    }
    logNewLine();

    kernel_pageMemorySinglePageRelease(0x01000000);
    page = kernel_pageMemorySinglePageAcquire();
    logUnsignedWord32Hex(page);
    logNewLine();

    kernel_pageMemorySinglePageRelease(0x01001000);
    page = kernel_pageMemorySinglePageAcquire();
    logUnsignedWord32Hex(page);
    logNewLine();

    kernel_pageMemoryDuelPageRelease(0x01000000);
    page = kernel_pageMemoryDuelPageAcquire();
    logUnsignedWord32Hex(page);
    logNewLine();

    kernel_pageMemoryQuadPageRelease(0x01000000);
    page = kernel_pageMemoryQuadPageAcquire();
    logUnsignedWord32Hex(page);
    logNewLine();

    kernel_pageMemoryOctPageRelease(0x01000000);
    page = kernel_pageMemoryOctPageAcquire();
    logUnsignedWord32Hex(page);
    logNewLine();

    UnsignedWord32 reg = 0;
    while (TRUE)
    {
        statusSetActiveLED();
        asm("mcr\tp15, 0, %0, c7, c0, 4": : "r" (reg));
        statusClearActiveLED();
        asm("mcr\tp15, 0, %0, c7, c0, 4": : "r" (reg));
    }
}
