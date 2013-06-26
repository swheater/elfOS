/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/RaspPi_GPIO.h>
#include <Kernel/Handlers.h>

void (*undefinedInstructionHandler)(UnsignedWord32* undefinedInstructionAddress)                = 0;
void (*softwareInterruptHandler)(UnsignedWord32 opcode, ThreadControlBlock *threadControlBlock) = 0;
void (*prefetchAbortHandler)(void)                                                              = 0;
void (*dataAbortHandler)(void)                                                                  = 0;
void (*reservedHandler)(void)                                                                   = 0;
void (*interruptRequestHandler)(void)                                                           = 0;
void (*fastInterruptRequestHandler)(void)                                                       = 0;

static void signalError(void)
{
    volatile int count;
    while (1)
    {
        gpioSetOutput(4);
        for (count = 0; count < 500000; count++);
        gpioClearOutput(4);
        for (count = 0; count < 500000; count++);
    }
}

void defaultUndefinedInstructionHandler(UnsignedWord32* undefinedInstructionAddress)
{
    logMessage("Problem: Default Undefined Instruction Handler\r\n");
    signalError();
}

void defaultSoftwareInterruptHandler(UnsignedWord32 opcode, ThreadControlBlock *threadControlBlock)
{
    logMessage("Problem: Default Software Interrupt Handler\r\n");
    signalError();
}

void defaultPrefetchAbortHandler(void)
{
    logMessage("Problem: Default Prefetch Abort Handler\r\n");
    signalError();
}

void defaultDataAbortHandler(void)
{
    logMessage("Problem: Default Data Abort Handler\r\n");
    signalError();
}

void defaultReservedHandler(void)
{
    logMessage("Problem: Default Reserved Handler\r\n");
    signalError();
}

void defaultInterruptRequestHandler(void)
{
    logMessage("Problem: Default Interrupt Request Handler\r\n");
    signalError();
}

void defaultFastInterruptRequestHandler(void)
{
    logMessage("Problem: Default Fast Interrupt Request Handler\r\n");
    signalError();
}
