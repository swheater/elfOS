/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/Kernel.h>
#include <Kernel/VirtualMemory.h>
#include <Kernel/Symbol.h>
#include <Kernel/Process.h>
#include <Kernel/Handlers.h>
#include <Kernel/Logging.h>
#include <Kernel/KDebug.h>
#include <Device/RaspPi_GPIO.h>
#include <Device/RaspPi_UART.h>
#include <Device/RaspPi_Timer.h>
#include <ELF/ELF32.h>
#include <ELF/ELF32_ARM_EABI.h>
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
    logMessage("), SCR: ");
    UnsignedWord32 scr;
    asm("mrc\tp15, 0, %0, c1, c1, 0": "=r" (scr));
    logUnsignedWord32Hex(scr);
    logMessage("\r\n");

    kDebugCurrentProcess();

    gpioSetOutput(22);

    hereAndNow0:
    goto hereAndNow0;
}

static void swHandler(UnsignedWord32 opcode, ProcessControlBlock *processControlBlock)
{
    if (opcode == 1)
        yieldProcess();
    else if (opcode == 2)
        destroyProcess(processControlBlock);

    if (currentProcessControlBlock == 0)
    {
        gpioSetOutput(21);
        hereAndNow1:
        goto hereAndNow1;
    }
}

static void irqHandler(void)
{
    uartOutput('.');

    if (currentProcessControlBlock != 0)
        yieldProcess();

    timerClearInterruptRequest();
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

    resetHandler                = &defaultResetHandler;
    undefinedInstructionHandler = &defaultUndefinedInstructionHandler;
    softwareInterruptHandler    = &defaultSoftwareInterruptHandler;
    prefetchAbortHandler        = &defaultPrefetchAbortHandler;
    dataAbortHandler            = &defaultDataAbortHandler;
    reservedHandler             = &defaultReservedHandler;
    interruptRequestHandler     = &defaultInterruptRequestHandler;
    fastInterruptRequestHandler = &defaultFastInterruptRequestHandler;

    undefinedInstructionHandler = &uiHandler;
    softwareInterruptHandler    = &swHandler;
    interruptRequestHandler     = &irqHandler;

    gpioInit();
    uartInit();
    timerInit(127, 100000, TRUE);

//    timerDebug();

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

//    timerDebug();

//    kDebugCPUState();

    initProcesses();

    unsigned int numberOfGlobalSymbols = 5;
    Symbol       globalSymbols[numberOfGlobalSymbols];
    globalSymbols[0].name  = "elfOS_processYield";
    globalSymbols[0].value = (UnsignedWord32) elfOS_processYield;
    globalSymbols[1].name  = "elfOS_processStop";
    globalSymbols[1].value = (UnsignedWord32) elfOS_processStop;
    globalSymbols[2].name  = "elfOS_logUnsignedWord32Hex";
    globalSymbols[2].value = (UnsignedWord32) logUnsignedWord32Hex;
    globalSymbols[3].name  = "elfOS_logMessage";
    globalSymbols[3].value = (UnsignedWord32) logMessage;
    globalSymbols[4].name  = "elfOS_logNewLine";
    globalSymbols[4].value = (UnsignedWord32) logNewLine;

    UnsignedByte *nextSegment = (UnsignedByte*) 0x80000;

    const char *elf32 = (char*) &elfAppl;

    int valid = elf32_validate(elf32, 1032);
    while (valid)
    {
        ELF32Header        *header                           = (ELF32Header*) elf32;
        ELF32SectionHeader *sectionHeaders                   = (ELF32SectionHeader*) &(elf32[header->sectionHeaderOffset]);
        unsigned int       numberOfSectionHeaders            = header->sectionHeaderEntryNumber;
        unsigned int       numberOfVirtualMemorySegmentInfos = elf32_numberOfVirtualMemorySegmentInfos(sectionHeaders, numberOfSectionHeaders);

        VirtualMemorySegmentInfo virtualMemorySegmentInfos[numberOfVirtualMemorySegmentInfos];

        elf32_extractVirtualMemorySegmentInfos(sectionHeaders, numberOfSectionHeaders, virtualMemorySegmentInfos, &numberOfVirtualMemorySegmentInfos);

        unsigned int         numberOfSegments = numberOfVirtualMemorySegmentInfos;
        VirtualMemorySegment segments[numberOfSegments];

        int segmentIndex;
        for (segmentIndex = 0; segmentIndex < numberOfSegments; segmentIndex++)
        {
            segments[segmentIndex].physicalAddress = nextSegment;
            segments[segmentIndex].virtualAddress  = nextSegment;
            segments[segmentIndex].size            = 0;
            nextSegment += 0x10000;
        }

        if (elf32_segmentsInitialize(elf32, sectionHeaders, numberOfSectionHeaders, globalSymbols, numberOfGlobalSymbols, segments, numberOfSegments))
        {
            void (*runFunction)(void) = elf32_findFunction("run", elf32, sectionHeaders, numberOfSectionHeaders, segments, numberOfSegments);

            logMessage("runFunction: ");
            logUnsignedWord32Hex((UnsignedWord32) runFunction);
            logMessage("\r\n");

            if (runFunction != 0)
	    {
                createProcess(runFunction, nextSegment);
                nextSegment += 0x10000;
	    }
            else
                logMessage("**** no runFunction ****\r\n");
        }
        else
            logMessage("**** init failed ****\r\n");

        elf32 += 1032;
        valid = elf32_validate(elf32, 1032);
    }

    gpioSetOutput(18);

    startProcesses();

    gpioSetOutput(22);

    logMessage("**** stopped ****\r\n");
    hereAndNow2:
    goto hereAndNow2;
}
