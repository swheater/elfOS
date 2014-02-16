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

#include <Device/BCM2835_GPIO.h>
#include <Device/BCM2835_SPI.h>
#include <Device/BCM2835_PWM.h>
#include <Device/RaspPi_XPT2046.h>
#include <Device/RaspPi_ILI9320.h>

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
    softwareInterruptHandler = &swHandler;
    interruptRequestHandler  = &irqHandler;

    gpioInit();
    uartInit();
    statusInit();
    threadsInit();
    timerInit(127, 1000000, TRUE);

    spiInit();
    pwmInit();
    xpt2046Init();
    ili9320Init();

    ili9320Test();
 
    UnsignedWord32 mark  = 0x1000;
    UnsignedWord32 range = 0x2000;

    pwmSetRange(0, range);
    pwmSetMark(0, mark);

    UnsignedWord32 reg = 0;
    while (TRUE)
    {
      /*
        if (xpt2046GetTouch())
        {
            logMessage("x = ");
            logUnsignedWord16Hex(xpt2046GetXPosition());
            logMessage(", y = ");
            logUnsignedWord16Hex(xpt2046GetYPosition());
            logMessage("\r\n");
        }
      */

        statusSetActiveLED();
        asm("mcr\tp15, 0, %0, c7, c0, 4": : "r" (reg));
        statusClearActiveLED();
        asm("mcr\tp15, 0, %0, c7, c0, 4": : "r" (reg));
    }
}
