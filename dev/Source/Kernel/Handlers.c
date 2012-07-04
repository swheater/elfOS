/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/RaspPi_GPIO.h>
#include <Kernel/Handlers.h>

void (*resetHandler)(void);
void (*undefinedInstructionHandler)(UnsignedWord32* undefinedInstructionAddress);
void (*softwareInterruptHandler)(UnsignedWord32 opcode, ProcessControlBlock *processControlBlock);
void (*prefetchAbortHandler)(void);
void (*dataAbortHandler)(void);
void (*reservedHandler)(void);
void (*interruptRequestHandler)(void);
void (*fastInterruptRequestHandler)(void);

static void signalError(void)
{
    volatile int count;
    while (1)
    {
        gpioSetOutput(22);
        for (count = 0; count < 2000000; count++);
        gpioClearOutput(22);
        for (count = 0; count < 2000000; count++);
    }
}

void defaultResetHandler(void)
{
    logMessage("Problem: Default Reset Handler\r\n");
    signalError();
}

void defaultUndefinedInstructionHandler(UnsignedWord32* undefinedInstructionAddress)
{
    logMessage("Problem: Default Undefined Instruction Handler\r\n");
    signalError();
}

void defaultSoftwareInterruptHandler(UnsignedWord32 opcode, ProcessControlBlock *processControlBlock)
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
