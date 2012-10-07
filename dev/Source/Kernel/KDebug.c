/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/ARM/ThreadControlBlock.h>
#include <Kernel/Thread.h>
#include <Kernel/Handlers.h>
#include <Device/RaspPi_UART.h>
#include <Kernel/Logging.h>
#include <Kernel/KDebug.h>

void kDebugCPUState(void)
{
    UnsignedWord32 cpuInfo;
    UnsignedWord32 scr;
    UnsignedWord32 sp;
    UnsignedWord32 lr;
    UnsignedWord32 pc;
    UnsignedWord32 cpsr;
    UnsignedWord32 spsr;
    asm("mrc\tp15, 0, %0, c0, c0, 0": "=r" (cpuInfo));
    asm("mrc\tp15, 0, %0, c1, c1, 0": "=r" (scr));
    asm("mov\t%0, sp": "=r" (sp));
    asm("mov\t%0, lr": "=r" (lr));
    asm("mov\t%0, pc": "=r" (pc));
    asm("mrs\t%0, cpsr": "=r" (cpsr));
    asm("mrs\t%0, spsr": "=r" (spsr));

    logMessage("CPU Status:\r\n");
    logMessage("    CPU Info: ");
    logUnsignedWord32Hex(cpuInfo);
    logMessage(", SCR: ");
    logUnsignedWord32Hex(scr);
    logMessage("\r\n    SP:   ");
    logUnsignedWord32Hex(sp);
    logMessage(",   LR: ");
    logUnsignedWord32Hex(lr);
    logMessage(",   PC: ");
    logUnsignedWord32Hex(pc);
    logMessage("\r\n    CPSR: ");
    logUnsignedWord32Hex(cpsr);
    logMessage(", SPSR: ");
    logUnsignedWord32Hex(spsr);
    logMessage("\r\n");
}

void kDebugCurrentThread(void)
{
    if (currentThreadControlBlock != 0)
    {
        logMessage("\r\nRegisters:\r\n      r0=");
        logUnsignedWord32Hex(currentThreadControlBlock->r0);
        logMessage(",   r1=");
        logUnsignedWord32Hex(currentThreadControlBlock->r1);
        logMessage(",   r2=");
        logUnsignedWord32Hex(currentThreadControlBlock->r2);
        logMessage(",   r3=");
        logUnsignedWord32Hex(currentThreadControlBlock->r3);
        logMessage("\r\n      r4=");
        logUnsignedWord32Hex(currentThreadControlBlock->r4);
        logMessage(",   r5=");
        logUnsignedWord32Hex(currentThreadControlBlock->r5);
        logMessage(",   r6=");
        logUnsignedWord32Hex(currentThreadControlBlock->r6);
        logMessage(",   r7=");
        logUnsignedWord32Hex(currentThreadControlBlock->r7);
        logMessage("\r\n      r8=");
        logUnsignedWord32Hex(currentThreadControlBlock->r8);
        logMessage(",   r9=");
        logUnsignedWord32Hex(currentThreadControlBlock->r9);
        logMessage(",  r10=");
        logUnsignedWord32Hex(currentThreadControlBlock->r10);
        logMessage(",  r11=");
        logUnsignedWord32Hex(currentThreadControlBlock->r11);
        logMessage("\r\n     r12=");
        logUnsignedWord32Hex(currentThreadControlBlock->r12);
        logMessage(",   sp=");
        logUnsignedWord32Hex(currentThreadControlBlock->sp);
        logMessage(",   lr=");
        logUnsignedWord32Hex(currentThreadControlBlock->lr);
        logMessage(",   pc=");
        logUnsignedWord32Hex(currentThreadControlBlock->pc);
        logMessage("\r\n    cpsr=");
        logUnsignedWord32Hex(currentThreadControlBlock->cpsr);
        logMessage("\r\n");
    }
    else
        logMessage("No Current Thread\r\n");
}

void kDebugVirtualMemorySegments(VirtualMemorySegment virtualMemorySegments[], unsigned int numberOfVirtualMemorySegments)
{
    int virtualMemorySegmentIndex;
    for (virtualMemorySegmentIndex = 0; virtualMemorySegmentIndex < numberOfVirtualMemorySegments; virtualMemorySegmentIndex++)
    {
        logMessage("Virtual Memory ");
        logUnsignedWord32Hex((UnsignedWord32) virtualMemorySegmentIndex);
        logMessage(":\r\n    Phy memory base ");
        logUnsignedWord32Hex((UnsignedWord32) virtualMemorySegments[virtualMemorySegmentIndex].physicalAddress);
        logMessage("\r\n    Vir memory base ");
        logUnsignedWord32Hex((UnsignedWord32) virtualMemorySegments[virtualMemorySegmentIndex].virtualAddress);
        logMessage("\r\n");
    }
}

void kDebugVirtualMemorySegment(VirtualMemorySegment* virtualMemorySegment)
{
    int index;
    for (index = 0; index < virtualMemorySegment->size; index++)
    {
        if ((index & 0x7) == 0)
        {
	    if (index != 0)
                logMessage("\r\n");
            logUnsignedWord32Hex((UnsignedWord32) (virtualMemorySegment->physicalAddress) + index);
            logMessage(":");
        }

        logMessage(" ");
        logUnsignedByteHex((UnsignedByte) virtualMemorySegment->physicalAddress[index]);
        logMessage(" ");
        logUnsignedByteASCII((UnsignedByte) virtualMemorySegment->physicalAddress[index]);
    }
    logMessage("\r\n");
}

void kDebugHandlers(void)
{
    logMessage("undefinedInstructionHandler = ");
    logUnsignedWord32Hex((UnsignedWord32) *undefinedInstructionHandler);
    logMessage("\r\nsoftwareInterruptHandler    = ");
    logUnsignedWord32Hex((UnsignedWord32) *softwareInterruptHandler);
    logMessage("\r\nprefetchAbortHandler        = ");
    logUnsignedWord32Hex((UnsignedWord32) *prefetchAbortHandler);
    logMessage("\r\ndataAbortHandler            = ");
    logUnsignedWord32Hex((UnsignedWord32) *dataAbortHandler);
    logMessage("\r\nreservedHandler             = ");
    logUnsignedWord32Hex((UnsignedWord32) *reservedHandler);
    logMessage("\r\ninterruptRequestHandler     = ");
    logUnsignedWord32Hex((UnsignedWord32) *interruptRequestHandler);
    logMessage("\r\nfastInterruptRequestHandler = ");
    logUnsignedWord32Hex((UnsignedWord32) *fastInterruptRequestHandler);
    logMessage("\r\n");
}
