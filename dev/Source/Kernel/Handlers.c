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
    UnsignedWord32 dataFaultStatus;
    UnsignedWord32 instructionFaultStatus;
    UnsignedWord32 dataFaultAddress;
    UnsignedWord32 instructionFaultAddress;
    UnsignedWord32 watchpointFaultAddress;
    asm("mrc\tp15, 0, %0, c5, c0, 0": "=r" (dataFaultStatus));
    asm("mrc\tp15, 0, %0, c5, c0, 1": "=r" (instructionFaultStatus)); 
    asm("mrc\tp15, 0, %0, c6, c0, 0": "=r" (dataFaultAddress));
    asm("mrc\tp15, 0, %0, c6, c0, 2": "=r" (instructionFaultAddress));
    asm("mrc\tp14, 0, %0, c0, c6, 0": "=r" (watchpointFaultAddress));
    logMessage("Problem: Default Data Abort Handler\r\n");
    logMessage("    Data Fault Status:         ");
    logUnsignedWord32Bin(dataFaultStatus);
    logMessage("\r\n    Instruction Fault Status:  ");
    logUnsignedWord32Bin(instructionFaultStatus);
    logMessage("\r\n    Data Fault Address:        ");
    logUnsignedWord32Hex(dataFaultAddress);
    logMessage("\r\n    Instruction Fault Address: ");
    logUnsignedWord32Hex(instructionFaultAddress);
    logMessage("\r\n    Watchpoint Fault Address:  ");
    logUnsignedWord32Hex(watchpointFaultAddress);
    logMessage("\r\n");

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
