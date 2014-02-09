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
    if (opcode == 1)
       threadYield();
    else if (opcode == 2)
       threadDestroy(threadControlBlock);
}

static void irqHandler(void)
{
    if (currentThreadControlBlock != 0)
        threadYield();

    timerClearInterruptRequest();
}

void kernel_start(void)
{
    softwareInterruptHandler = &swHandler;
    interruptRequestHandler  = &irqHandler;

    statusInit();
    uartInit();
    threadsInit();
    timerInit(127, 1000000, TRUE);

    kDebugCPUState();
    logNewLine();
    kDebugMemoryManagement();
    logNewLine();
    kDebugCurrentThread();
    logNewLine();
    kDebugHandlers();

    UnsignedWord32 reg = 0;
    while (TRUE)
    {
        statusSetActiveLED();
        asm("mcr\tp15, 0, %0, c7, c0, 4": : "r" (reg));
        statusClearActiveLED();
        asm("mcr\tp15, 0, %0, c7, c0, 4": : "r" (reg));
    }
}
