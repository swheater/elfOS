/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/Kernel.h>
#include <Kernel/VirtualMemory.h>
#include <Kernel/Symbol.h>
#include <Kernel/Thread.h>
#include <Kernel/Handlers.h>
#include <Kernel/Logging.h>
#include <Kernel/KDebug.h>
#include <Device/BCM2835_GPIO.h>
#include <Device/BCM2835_miniUART.h>
#include <Device/BCM2835_BSC.h>
#include <Device/BCM2835_Timer.h>
#include <Device/BCM2835_SystemTimer.h>
#include <Device/RaspPi_DisplayTFT18.h>
#include <Device/BCM2835_SPI.h>
#include <Device/RaspPi_ILI9320.h>
#include <Device/RaspPi_XPT2046.h>
#include <Device/RaspPi_Status.h>
#include <Device/RaspPi_PiLITEr.h>
#include <Device/RaspPi_Ladder.h>
#include <Device/RaspPi_BerryClip.h>
#include <Device/RaspPi_MotorPiTX.h>
#include <Device/SPI_SecureDigital.h>
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
    systemtimerInit();
    gpioInit();
    //    spiInit();
    //    uartInit();
    //    displayTFT18Init();
    //    i2cInit(0);
    //    ladderInit();
    threadsInit();
    timerInit(127, 1000000, TRUE);

    motorpitxInit();

    int count;
    for (count = 0; count < 30; count++)
    {
        motorpitxSetReadyLED(motorpitxGetInput(MOTORPITX_INPUT2));
        systemtimerWait(1000000);
    }

    UnsignedWord32 reg = 0;
    while (TRUE)
    {
        statusSetActiveLED();
        asm("mcr\tp15, 0, %0, c7, c0, 4": : "r" (reg));
        statusClearActiveLED();
        asm("mcr\tp15, 0, %0, c7, c0, 4": : "r" (reg));
    }
}
