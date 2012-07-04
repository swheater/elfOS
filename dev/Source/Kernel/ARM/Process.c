/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/Process.h>

#define USERMODE_PROCESSSTATUS (0x10)
#define PROCESSCONTROLBLOCKS_LENGTH (16)

static int          currentProcessControlBlockIndex;
ProcessControlBlock *currentProcessControlBlock;

static ProcessControlBlock processControlBlocks[PROCESSCONTROLBLOCKS_LENGTH];

static void clearProcess(ProcessControlBlock *processControlBlock)
{
    processControlBlock->r0          = 0x0;
    processControlBlock->r1          = 0x0;
    processControlBlock->r2          = 0x0;
    processControlBlock->r3          = 0x0;
    processControlBlock->r4          = 0x0;
    processControlBlock->r5          = 0x0;
    processControlBlock->r6          = 0x0;
    processControlBlock->r7          = 0x0;
    processControlBlock->r8          = 0x0;
    processControlBlock->r9          = 0x0;
    processControlBlock->r10         = 0x0;
    processControlBlock->r11         = 0x0;
    processControlBlock->r12         = 0x0;
    processControlBlock->sp          = 0x0;
    processControlBlock->lr          = 0x0;
    processControlBlock->pc          = 0x0;
    processControlBlock->cpsr        = 0x0;
    processControlBlock->blockStatus = FREE;
}

void initProcesses(void)
{
    unsigned int processControlBlockIndex;
    for (processControlBlockIndex = 0; processControlBlockIndex < PROCESSCONTROLBLOCKS_LENGTH; processControlBlockIndex++)
        clearProcess(&processControlBlocks[processControlBlockIndex]);
}

void createProcess(void (*runFunction)(void), UnsignedByte *stack)
{
    ProcessControlBlock *choosenProcessControlBlock = 0;

    int processControlBlockIndex = 0;
    while ((choosenProcessControlBlock == 0) && (processControlBlockIndex < PROCESSCONTROLBLOCKS_LENGTH))
    {
        if (processControlBlocks[processControlBlockIndex].blockStatus == FREE)
            choosenProcessControlBlock = &processControlBlocks[processControlBlockIndex];
        else
            processControlBlockIndex++;
    }

    if (choosenProcessControlBlock != 0)
    {
        choosenProcessControlBlock->cpsr        = USERMODE_PROCESSSTATUS;
        choosenProcessControlBlock->sp          = (UnsignedWord32) stack;
        choosenProcessControlBlock->pc          = (UnsignedWord32) runFunction;
        choosenProcessControlBlock->blockStatus = USED;
    }

    if (currentProcessControlBlock == 0)
    {
        currentProcessControlBlockIndex = processControlBlockIndex;
        currentProcessControlBlock      = choosenProcessControlBlock;
    }
}

ProcessControlBlock *getCurrentProcessControlBlock(void)
{
    return currentProcessControlBlock;
}

void yieldProcess(void)
{
    currentProcessControlBlock = 0;

    int index = 0;
    while ((currentProcessControlBlock == 0) && (index < PROCESSCONTROLBLOCKS_LENGTH))
    {
        currentProcessControlBlockIndex = (currentProcessControlBlockIndex + 1) & 0x0000000F;
        if (processControlBlocks[currentProcessControlBlockIndex].blockStatus == USED)
            currentProcessControlBlock = &processControlBlocks[currentProcessControlBlockIndex];
        else
            index++;
    }
}

void destroyProcess(ProcessControlBlock *processControlBlock)
{
    if (processControlBlock != 0)
    {
        clearProcess(processControlBlock);

        if (processControlBlock == currentProcessControlBlock)
            yieldProcess();
    }
}
