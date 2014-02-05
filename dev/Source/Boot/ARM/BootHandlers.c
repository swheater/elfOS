/*                                                                                                                                                  * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.                                                      */

#include <Kernel/StdTypes.h>
#include <Boot/BDebug.h>
#include <Boot/ARM/BootHandlers.h>

void boot_undefinedInstructionHandler(void)
{
    bDebugInit();

    bDebugMessage("Undefined Instruction");
    bDebugNewLine();

    while (TRUE) ;
}

void boot_softwareInterruptHandler(void)
{
    bDebugInit();

    bDebugMessage("Software Interrupt");
    bDebugNewLine();

    while (TRUE) ;
}

void boot_prefetchAbortHandler(void)
{
    bDebugInit();

    bDebugMessage("Prefetch Abort");
    bDebugNewLine();

    while (TRUE) ;
}

void boot_dataAbortHandler(void)
{
    bDebugInit();

    bDebugMessage("Data Abort - DFS: ");

    UnsignedWord32 dataFaultStatusRegister;
    asm("mrc\tp15, 0, %0, c5, c0, 0": "=r" (dataFaultStatusRegister));
    bDebugUnsignedWord32Hex(dataFaultStatusRegister);
    bDebugMessage(", IFS: ");

    UnsignedWord32 instructionFaultStatusRegister;
    asm("mrc\tp15, 0, %0, c5, c0, 1": "=r" (instructionFaultStatusRegister));
    bDebugUnsignedWord32Hex(instructionFaultStatusRegister);
    bDebugMessage(", FA: ");

    UnsignedWord32 faultAddressRegister;
    asm("mrc\tp15, 0, %0, c6, c0, 0": "=r" (faultAddressRegister));
    bDebugUnsignedWord32Hex(faultAddressRegister);
    bDebugNewLine();

    while (TRUE) ;
}

void boot_reservedHandler(void)
{
    bDebugInit();

    bDebugMessage("Reserved");
    bDebugNewLine();

    while (TRUE) ;
}

void boot_interruptRequestHandler(void)
{
    bDebugInit();

    bDebugMessage("Interrupt Request");
    bDebugNewLine();

    while (TRUE) ;
}

void boot_fastInterruptRequestHandler(void)
{
    bDebugInit();

    bDebugMessage("Fast Interrupt Request");
    bDebugNewLine();

    while (TRUE) ;
}
