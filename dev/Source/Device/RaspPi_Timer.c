/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi, Timer

#include <Kernel/StdTypes.h>
#include <Kernel/Logging.h>
#include <Device/RaspPi_Timer.h>

#define IRQCTRL_BASE                    ((volatile UnsignedWord32*) 0xF000B000)
#define IRQCTRL_BASICENABLE_OFFSET      (0x86)

#define IRQCTRL_TIMERIRQ_BIT            (0x00000001)

#define TIMER_BASE                      ((volatile UnsignedWord32*) 0xF000B000)
#define TIMER_LOAD_OFFSET               (0x100)
#define TIMER_VALUE_OFFSET              (0x101)
#define TIMER_CONTROL_OFFSET            (0x102)
#define TIMER_IRQCLEAR_OFFSET           (0x103)
#define TIMER_RAWIRQ_OFFSET             (0x104)
#define TIMER_MASKEDIRQ_OFFSET          (0x105)
#define TIMER_RELOAD_OFFSET             (0x106)
#define TIMER_PREDIVIDER_OFFSET         (0x107)
#define TIMER_FREERUNNINGCOUNTER_OFFSET (0x108)

#define TIMER_16BITCOUNTER_BIT          (0x00000000)
#define TIMER_32BITCOUNTER_BIT          (0x00000002)
#define TIMER_PRESCALE1_BITS            (0x00000000)
#define TIMER_PRESCALE16_BITS           (0x00000004)
#define TIMER_PRESCALE265_BITS          (0x00000008)
#define TIMER_IRQDISABLED_BIT           (0x00000000)
#define TIMER_IRQENABLED_BIT            (0x00000020)
#define TIMER_IRQENABLE_MASK            (0xFFFFFFDF)
#define TIMER_DISABLED_BIT              (0x00000000)
#define TIMER_ENABLED_BIT               (0x00000080)
#define TIMER_ENABLE_MASK               (0xFFFFFF7F)
#define TIMER_PREDIVIDE_INVMASK         (0x000003FF)

void timerInit(UnsignedWord16 predivide, UnsignedWord32 load, Boolean enabled)
{
    *(TIMER_BASE + TIMER_PREDIVIDER_OFFSET) = predivide & TIMER_PREDIVIDE_INVMASK;
    *(TIMER_BASE + TIMER_LOAD_OFFSET)       = load;
    if (enabled)
        *(TIMER_BASE + TIMER_CONTROL_OFFSET) = TIMER_32BITCOUNTER_BIT | TIMER_PRESCALE1_BITS | TIMER_IRQENABLED_BIT | TIMER_ENABLED_BIT;
    else
        *(TIMER_BASE + TIMER_CONTROL_OFFSET) = TIMER_32BITCOUNTER_BIT | TIMER_PRESCALE1_BITS | TIMER_IRQDISABLED_BIT | TIMER_DISABLED_BIT;
    
    *(IRQCTRL_BASE + IRQCTRL_BASICENABLE_OFFSET) |= IRQCTRL_TIMERIRQ_BIT;
}

void timerEnable(void)
{
    UnsignedWord32 control = *(TIMER_BASE + TIMER_CONTROL_OFFSET);
    control &= TIMER_IRQENABLE_MASK & TIMER_ENABLE_MASK;
    control |= TIMER_IRQENABLED_BIT | TIMER_ENABLED_BIT;
    *(TIMER_BASE + TIMER_CONTROL_OFFSET) = control;
}

void timerDisable(void)
{
    UnsignedWord32 control = *(TIMER_BASE + TIMER_CONTROL_OFFSET);
    control &= TIMER_IRQENABLE_MASK & TIMER_ENABLE_MASK;
    control |= TIMER_IRQDISABLED_BIT | TIMER_DISABLED_BIT;
    *(TIMER_BASE + TIMER_CONTROL_OFFSET) = control;
}

void timerClearInterruptRequest(void)
{
    *(TIMER_BASE + TIMER_IRQCLEAR_OFFSET) = 0;
}

void timerDebug(void)
{
    UnsignedWord32 load               = *(TIMER_BASE + TIMER_LOAD_OFFSET);
    UnsignedWord32 value              = *(TIMER_BASE + TIMER_VALUE_OFFSET);
    UnsignedWord32 control            = *(TIMER_BASE + TIMER_CONTROL_OFFSET);
    UnsignedWord32 rawIRQ             = *(TIMER_BASE + TIMER_RAWIRQ_OFFSET);
    UnsignedWord32 maskedIRQ          = *(TIMER_BASE + TIMER_MASKEDIRQ_OFFSET);
    UnsignedWord32 reload             = *(TIMER_BASE + TIMER_RELOAD_OFFSET);
    UnsignedWord32 predivide          = *(TIMER_BASE + TIMER_PREDIVIDER_OFFSET);
    UnsignedWord32 freeRunningCounter = *(TIMER_BASE + TIMER_FREERUNNINGCOUNTER_OFFSET);

    logMessage("Timer:\r\n    Load=");
    logUnsignedWord32Hex(load);
    logMessage(" Value=");
    logUnsignedWord32Hex(value);
    logMessage(" Control=");
    logUnsignedWord32Hex(control);
    logMessage(" RawIRQ=");
    logUnsignedWord32Hex(rawIRQ);
    logMessage("\r\n    MaskedIRQ=");
    logUnsignedWord32Hex(maskedIRQ);
    logMessage(" Reload=");
    logUnsignedWord32Hex(reload);
    logMessage(" Predivide=");
    logUnsignedWord32Hex(predivide);
    logMessage(" FreeRunningCounter=");
    logUnsignedWord32Hex(freeRunningCounter);
}
