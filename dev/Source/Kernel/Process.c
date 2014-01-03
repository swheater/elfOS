/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
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
#include <ELF/ELF32.h>
#include <ELF/ELF32_ARM_EABI.h>

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
}
