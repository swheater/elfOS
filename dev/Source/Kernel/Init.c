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
#include <Device/SPI_SecureDigital.h>
#include <ELF/ELF32.h>
#include <ELF/ELF32_ARM_EABI.h>
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
    threadsInit();
    timerInit(127, 1000000, TRUE);

    ladderInit();

    while (TRUE)
    {
        if (ladderGetSwitch(LADDER_SWITCH_1))
	{
            ladderSetLED(LADDER_RED_LED_1, TRUE);
            ladderSetLED(LADDER_RED_LED_2, FALSE);
	}
        else
	{
            ladderSetLED(LADDER_RED_LED_1, FALSE);
            ladderSetLED(LADDER_RED_LED_2, TRUE);
	}

        if (ladderGetSwitch(LADDER_SWITCH_2))
	{
            ladderSetLED(LADDER_YELLOW_LED_1, TRUE);
            ladderSetLED(LADDER_YELLOW_LED_2, FALSE);
	}
        else
	{
            ladderSetLED(LADDER_YELLOW_LED_1, FALSE);
            ladderSetLED(LADDER_YELLOW_LED_2, TRUE);
	}

        if (ladderGetSwitch(LADDER_SWITCH_3))
	{
            ladderSetLED(LADDER_GREEN_LED_1, TRUE);
            ladderSetLED(LADDER_GREEN_LED_2, FALSE);
	}
        else
	{
            ladderSetLED(LADDER_GREEN_LED_1, FALSE);
            ladderSetLED(LADDER_GREEN_LED_2, TRUE);
	}

        if (ladderGetSwitch(LADDER_SWITCH_4))
	{
            ladderSetLED(LADDER_BLUE_LED_1, TRUE);
            ladderSetLED(LADDER_BLUE_LED_2, FALSE);
	}
        else
	{
            ladderSetLED(LADDER_BLUE_LED_1, FALSE);
            ladderSetLED(LADDER_BLUE_LED_2, TRUE);
	}
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

void workInit(void)
{
    //    unsigned int numberOfGlobalSymbols = 0;
    //    unsigned int numberOfGlobalSymbols = 5;
    //    Symbol       globalSymbols[numberOfGlobalSymbols];
    //    globalSymbols[0].name  = "elfOS_threadYield";
    //    globalSymbols[0].value = (UnsignedWord32) elfOS_threadYield;
    //    globalSymbols[1].name  = "elfOS_threadStop";
    //    globalSymbols[1].value = (UnsignedWord32) elfOS_threadStop;
    //    globalSymbols[2].name  = "elfOS_logUnsignedWord32Hex";
    //    globalSymbols[2].value = (UnsignedWord32) logUnsignedWord32Hex;
    //    globalSymbols[3].name  = "elfOS_logMessage";
    //    globalSymbols[3].value = (UnsignedWord32) logMessage;
    //    globalSymbols[4].name  = "elfOS_logNewLine";
    //    globalSymbols[4].value = (UnsignedWord32) logNewLine;

    //    UnsignedByte *nextSegment = (UnsignedByte*) 0x80000;

    /*
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

        gpioSetOutput(18);

        if (elf32_segmentsInitialize(elf32, sectionHeaders, numberOfSectionHeaders, globalSymbols, numberOfGlobalSymbols, segments, numberOfSegments))
        {
            void (*runFunction)(void) = elf32_findFunction("run", elf32, sectionHeaders, numberOfSectionHeaders, segments, numberOfSegments);

            logMessage("runFunction: ");
            logUnsignedWord32Hex((UnsignedWord32) runFunction);
            logMessage("\r\n");

            if (runFunction != 0)
            {
                createThread(runFunction, nextSegment);
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
    */
    gpioSetOutput(22);

    kDebugCurrentThread();
    logMessage("\r\n");

    kDebugHandlers();
    logMessage("\r\n");

    kDebugCPUState();
    logMessage("\r\n");

    //    startThreads();

    gpioSetOutput(25);

    logMessage("**** stopped ****\r\n");
    hereAndNow2:
    goto hereAndNow2;
}
