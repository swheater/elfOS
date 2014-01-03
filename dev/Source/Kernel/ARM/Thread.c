/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/Thread.h>

#define USERMODE_THREADSTATUS (0x10)
#define THREADCONTROLBLOCKS_LENGTH (16)

static int          currentThreadControlBlockIndex;
ThreadControlBlock *currentThreadControlBlock = 0;

static ThreadControlBlock threadControlBlocks[THREADCONTROLBLOCKS_LENGTH];

static void threadClear(ThreadControlBlock *threadControlBlock)
{
    threadControlBlock->r0          = 0x0;
    threadControlBlock->r1          = 0x0;
    threadControlBlock->r2          = 0x0;
    threadControlBlock->r3          = 0x0;
    threadControlBlock->r4          = 0x0;
    threadControlBlock->r5          = 0x0;
    threadControlBlock->r6          = 0x0;
    threadControlBlock->r7          = 0x0;
    threadControlBlock->r8          = 0x0;
    threadControlBlock->r9          = 0x0;
    threadControlBlock->r10         = 0x0;
    threadControlBlock->r11         = 0x0;
    threadControlBlock->r12         = 0x0;
    threadControlBlock->sp          = 0x0;
    threadControlBlock->lr          = 0x0;
    threadControlBlock->pc          = 0x0;
    threadControlBlock->cpsr        = 0x0;
    threadControlBlock->blockStatus = FREE;
}

void threadsInit(void)
{
    unsigned int threadControlBlockIndex;
    for (threadControlBlockIndex = 0; threadControlBlockIndex < THREADCONTROLBLOCKS_LENGTH; threadControlBlockIndex++)
        threadClear(&threadControlBlocks[threadControlBlockIndex]);
}

void threadCreate(void (*runFunction)(void), UnsignedByte *stack)
{
    ThreadControlBlock *choosenThreadControlBlock = 0;

    int threadControlBlockIndex = 0;
    while ((choosenThreadControlBlock == 0) && (threadControlBlockIndex < THREADCONTROLBLOCKS_LENGTH))
    {
        if (threadControlBlocks[threadControlBlockIndex].blockStatus == FREE)
            choosenThreadControlBlock = &threadControlBlocks[threadControlBlockIndex];
        else
            threadControlBlockIndex++;
    }

    if (choosenThreadControlBlock != 0)
    {
        choosenThreadControlBlock->cpsr        = USERMODE_THREADSTATUS;
        choosenThreadControlBlock->sp          = (UnsignedWord32) stack;
        choosenThreadControlBlock->pc          = (UnsignedWord32) runFunction;
        choosenThreadControlBlock->blockStatus = USED;
    }

    if (currentThreadControlBlock == 0)
    {
        currentThreadControlBlockIndex = threadControlBlockIndex;
        currentThreadControlBlock      = choosenThreadControlBlock;
    }
}

ThreadControlBlock *getCurrentThreadControlBlock(void)
{
    return currentThreadControlBlock;
}

void threadYield(void)
{
    currentThreadControlBlock = 0;

    int index = 0;
    while ((currentThreadControlBlock == 0) && (index < THREADCONTROLBLOCKS_LENGTH))
    {
        currentThreadControlBlockIndex = (currentThreadControlBlockIndex + 1) & 0x0000000F;
        if (threadControlBlocks[currentThreadControlBlockIndex].blockStatus == USED)
            currentThreadControlBlock = &threadControlBlocks[currentThreadControlBlockIndex];
        else
            index++;
    }
}

void threadDestroy(ThreadControlBlock *threadControlBlock)
{
    if (threadControlBlock != 0)
    {
        threadClear(threadControlBlock);

        if (threadControlBlock == currentThreadControlBlock)
            threadYield();
    }
}
