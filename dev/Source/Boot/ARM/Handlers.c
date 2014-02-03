/*                                                                                                                                                  * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.                                                      */

#include <Boot/BDebug.h>
#include <Boot/ARM/Handlers.h>

void boot_undefinedInstructionHandler(void)
{
    bDebugMessage("Undefined Instruction");
    bDebugNewLine();
}

void boot_softwareInterruptHandler(void)
{
    bDebugMessage("Software Interrupt");
    bDebugNewLine();
}

void boot_prefetchAbortHandler(void)
{
    bDebugMessage("Prefetch Abort");
    bDebugNewLine();
}

void boot_dataAbortHandler(void)
{
    bDebugMessage("Data Abort: ");

    UnsignedWord32 dataFaultStatusRegister;
    asm("mcr\tp15, 0, %0, c5, c0, 0": "=r" (dataFaultStatusRegister));
    bDebugUnsignedWord32Hex(dataFaultStatusRegister);
    bDebugMessage(", ");

    UnsignedWord32 instructionFaultStatusRegister;
    asm("mcr\tp15, 0, %0, c5, c0, 1": "=r" (instructionFaultStatusRegister));
    bDebugUnsignedWord32Hex(instructionFaultStatusRegister);
    bDebugMessage(", ");

    UnsignedWord32 faultAddressRegister;
    asm("mcr\tp15, 0, %0, c6, c0, 0": "=r" (faultAddressRegister));
    bDebugUnsignedWord32Hex(faultAddressRegister);
    bDebugNewLine();
}

void boot_reservedHandler(void)
{
    bDebugMessage("Reserved");
    bDebugNewLine();
}

void boot_interruptRequestHandler(void)
{
    bDebugMessage("Interrupt Request");
    bDebugNewLine();
}

void boot_fastInterruptRequestHandler(void)
{
    bDebugMessage("Fast Interrupt Request");
    bDebugNewLine();
}
