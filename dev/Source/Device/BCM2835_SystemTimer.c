/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for BCM2835 - System Timer

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/BCM2835_SystemTimer.h>

#define SYSTEMTIMER_BASE                 ((volatile UnsignedWord32*) 0x20003000)
#define SYSTEMTIMER_CONTROLSTATUS_OFFSET (0x00)
#define SYSTEMTIMER_COUNTER_OFFSET       (0x01)
#define SYSTEMTIMER_COMPARE0_OFFSET      (0x03)
#define SYSTEMTIMER_COMPARE1_OFFSET      (0x04)
#define SYSTEMTIMER_COMPARE2_OFFSET      (0x05)
#define SYSTEMTIMER_COMPARE3_OFFSET      (0x06)

void systemtimerInit()
{
    *(SYSTEMTIMER_BASE + SYSTEMTIMER_CONTROLSTATUS_OFFSET) = 0x00000000;
    *(SYSTEMTIMER_BASE + SYSTEMTIMER_COMPARE0_OFFSET)      = 0x00000000;
    *(SYSTEMTIMER_BASE + SYSTEMTIMER_COMPARE1_OFFSET)      = 0x00000000;
    *(SYSTEMTIMER_BASE + SYSTEMTIMER_COMPARE2_OFFSET)      = 0x00000000;
    *(SYSTEMTIMER_BASE + SYSTEMTIMER_COMPARE3_OFFSET)      = 0x00000000;
}

UnsignedWord64 systemtimerGetCounterValue(void)
{
    return *((volatile UnsignedWord64*) (SYSTEMTIMER_BASE + SYSTEMTIMER_COUNTER_OFFSET));
}

void systemtimerWait(UnsignedWord64 microSecondDelay)
{
    UnsignedWord64 counterValue = *((volatile UnsignedWord64*) (SYSTEMTIMER_BASE + SYSTEMTIMER_COUNTER_OFFSET));

    UnsignedWord64 counterTargetValue = counterValue + microSecondDelay;
    while (counterValue < counterTargetValue)
        counterValue = *((volatile UnsignedWord64*) (SYSTEMTIMER_BASE + SYSTEMTIMER_COUNTER_OFFSET));
}

void systemtimerWaitUntil(UnsignedWord64 microSecondCounterValue)
{
    while (*((volatile UnsignedWord64*) (SYSTEMTIMER_BASE + SYSTEMTIMER_COUNTER_OFFSET)) < microSecondCounterValue);
}

void systemtimerDebug(void)
{
    UnsignedWord32 controlstatus = *(SYSTEMTIMER_BASE + SYSTEMTIMER_CONTROLSTATUS_OFFSET);
    UnsignedWord64 counterValue  = *((volatile UnsignedWord64*) (SYSTEMTIMER_BASE + SYSTEMTIMER_COUNTER_OFFSET));
    UnsignedWord32 compare0      = *(SYSTEMTIMER_BASE + SYSTEMTIMER_COMPARE0_OFFSET);
    UnsignedWord32 compare1      = *(SYSTEMTIMER_BASE + SYSTEMTIMER_COMPARE1_OFFSET);
    UnsignedWord32 compare2      = *(SYSTEMTIMER_BASE + SYSTEMTIMER_COMPARE2_OFFSET);
    UnsignedWord32 compare3      = *(SYSTEMTIMER_BASE + SYSTEMTIMER_COMPARE3_OFFSET);

    logMessage("System Timer:\r\n  ControlStatus=");
    logUnsignedWord32Hex(controlstatus);
    logMessage(" CounterValue=");
    logUnsignedWord64Hex(counterValue);
    logMessage("\r\n  Compare0=");
    logUnsignedWord32Hex(compare0);
    logMessage(" Compare1=");
    logUnsignedWord32Hex(compare1);
    logMessage("\r\n  Compare2=");
    logUnsignedWord32Hex(compare2);
    logMessage(" Compare3=");
    logUnsignedWord32Hex(compare3);
    logMessage("\r\n");
}
