/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/Kernel.h>
#include <Kernel/VirtualMemory.h>
#include <Kernel/Symbol.h>
#include <Kernel/Process.h>
#include <Kernel/Handlers.h>
#include <Kernel/Logging.h>
#include <Device/RaspPi_GPIO.h>
#include <Device/RaspPi_UART.h>
#include <ELF/ELF32.h>
#include <elfOS/Process.h>

extern char start;
extern char zeroPageStart;
extern char zeroPageEnd;
extern char bssStart;
extern char bssEnd;
extern char elfAppl;

static void uiHandler(UnsignedWord32* undefinedInstructionAddress)
{
    logMessage("UIHandler: uiAddr:");
    logUnsignedWord32Hex((UnsignedWord32) undefinedInstructionAddress);
    logMessage(" (ui: ");
    logUnsignedWord32Hex(*undefinedInstructionAddress);
    logMessage(")\r\n");

    logMessage("    SCR: ");
    UnsignedWord32 scr;
    asm("mrc\tp15, 0, %0, c1, c1, 0": "=r" (scr));
    logUnsignedWord32Hex(scr);
    logMessage("\r\n");

    logMessage("    SP: ");
    UnsignedWord32 sp;
    asm("mov\t%0, sp": "=r" (sp));
    logUnsignedWord32Hex(sp);
    logMessage(", CPSR: ");
    UnsignedWord32 cpsr;
    asm("mrs\t%0, cpsr": "=r" (cpsr));
    logUnsignedWord32Hex(cpsr);
    logMessage("\r\n");

    gpioSetOutput(22);
}

static void swHandler(UnsignedWord32 opcode, UnsignedWord32 param)
{
    logMessage("SWHandler: opcode=");
    logUnsignedWord32Hex(opcode);
    logMessage(", param=");
    logUnsignedWord32Hex(param);
    logMessage("\r\n");

    logMessage("    SCR: ");
    UnsignedWord32 scr;
    asm("mrc\tp15, 0, %0, c1, c1, 0": "=r" (scr));
    logUnsignedWord32Hex(scr);

    logMessage("\r\n    SP: ");
    UnsignedWord32 sp;
    asm("mov\t%0, sp": "=r" (sp));
    logUnsignedWord32Hex(sp);

    logMessage(", CPSR: ");
    UnsignedWord32 cpsr;
    asm("mrs\t%0, cpsr": "=r" (cpsr));
    logUnsignedWord32Hex(cpsr);
    logMessage("\r\n");

    gpioSetOutput(21);
}

void kernel_init()
{
    char *zeroPageSource      = &zeroPageStart;
    char *zeroPageDestination = 0x0;
    while (zeroPageSource < &zeroPageEnd)
        *zeroPageDestination++ = *zeroPageSource++;

    char *bssAddress = &bssStart;
    while (bssAddress < &bssEnd)
        *bssAddress++ = 0;

    gpioInit();
    uartInit();

    undefinedInstructionHandler = &uiHandler;
    softwareInterruptHandler    = &swHandler;

    gpioSetOutput(17);
    gpioSetOutput(18);
    gpioSetOutput(21);
    gpioSetOutput(22);
    volatile int v;
    for (v = 0; v < 2000000; v++);
    gpioClearOutput(17);
    gpioClearOutput(18);
    gpioClearOutput(21);
    gpioClearOutput(22);
    gpioSetOutput(17);

    UnsignedWord32 cpuInfo;
    UnsignedWord32 scr;
    UnsignedWord32 sp;
    UnsignedWord32 cpsr;
    asm("mrc\tp15, 0, %0, c0, c0, 0": "=r" (cpuInfo));
    asm("mrc\tp15, 0, %0, c1, c1, 0": "=r" (scr));
    asm("mov\t%0, sp": "=r" (sp));
    asm("mrs\t%0, cpsr": "=r" (cpsr));

    logMessage("Init:\r\n");
    logMessage("    CPU Info: ");
    logUnsignedWord32Hex(cpuInfo);
    logMessage(", SCR: ");
    logUnsignedWord32Hex(scr);
    logMessage("\r\n    SP: ");
    logUnsignedWord32Hex(sp);
    logMessage(", CPSR: ");
    logUnsignedWord32Hex(cpsr);
    logMessage("\r\n\r\n");

    gpioSetOutput(18);

    const char         *elf32                            = (char*) &elfAppl;
    ELF32Header        *header                           = (ELF32Header*) elf32;
    ELF32SectionHeader *sectionHeaders                   = (ELF32SectionHeader*) &(elf32[header->sectionHeaderOffset]);
    unsigned int       numberOfSectionHeaders            = header->sectionHeaderEntryNumber;
    unsigned int       numberOfVirtualMemorySegmentInfos = elf32_numberOfVirtualMemorySegmentInfos(sectionHeaders, numberOfSectionHeaders);

    logMessage("elfAppl:\r\n    SectionHeader:   ");
    logUnsignedWord32Hex(numberOfSectionHeaders);
    logMessage("\r\n");

    logMessage("    VirtMemSegmInfo: ");
    logUnsignedWord32Hex(numberOfVirtualMemorySegmentInfos);
    logMessage("\r\n");

    VirtualMemorySegmentInfo virtualMemorySegmentInfos[numberOfVirtualMemorySegmentInfos];

    elf32_extractVirtualMemorySegmentInfos(sectionHeaders, numberOfSectionHeaders, virtualMemorySegmentInfos, &numberOfVirtualMemorySegmentInfos);

    unsigned int numberOfGlobalSymbols = 4;
    Symbol       globalSymbols[numberOfGlobalSymbols];
    globalSymbols[0].name  = "elfOS_processYield";
    globalSymbols[0].value = (UnsignedWord32) elfOS_processYield;
    globalSymbols[1].name  = "elfOS_processStop";
    globalSymbols[1].value = (UnsignedWord32) elfOS_processStop;
    globalSymbols[2].name  = "elfOS_processLogging";
    globalSymbols[2].value = (UnsignedWord32) elfOS_processLogging;

    unsigned int         numberOfSegments = numberOfVirtualMemorySegmentInfos;
    VirtualMemorySegment segments[numberOfSegments];

    int segmentIndex;
    for (segmentIndex = 0; segmentIndex < numberOfSegments; segmentIndex++)
    {
        segments[segmentIndex].physicalAddress = (UnsignedByte*) (segmentIndex * 0x10000) + 0x80000;
        segments[segmentIndex].virtualAddress  = (UnsignedByte*) (segmentIndex * 0x10000) + 0x80000;
    }

    if (elf32_segmentsInitialize(elf32, sectionHeaders, numberOfSectionHeaders, globalSymbols, numberOfGlobalSymbols, segments, numberOfSegments))
    {
        void (*runFunction)(void) = elf32_findFunction("run", elf32, sectionHeaders, numberOfSectionHeaders, segments, numberOfSegments);

        initProcesses();

        if (runFunction != 0)
        {
            logMessage("    runFunction: ");
            logUnsignedWord32Hex((UnsignedWord32) runFunction);
            logMessage("\r\n\r\n");

            currentProcessControlBlock = createProcess(runFunction, (UnsignedByte*) 0x100000);
            continueProcess(currentProcessControlBlock);

            gpioSetOutput(22);
	}
        else
            logMessage("**** no runFunction ****\r\n");
    }
    else
        logMessage("**** no init ****\r\n");


    logMessage("==== done ====\r\n");
    hereAndNow:
    goto hereAndNow;
}
