/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Book Debug

#include <Kernel/StdTypes.h>
#include <Kernel/BDebug.h>

#define AUX_BASE                      ((volatile UnsignedWord32*) 0x20215000)
#define AUX_INTERRUPTSTATUS_OFFSET    (0x00)
#define AUX_ENABLES_OFFSET            (0x01)

#define GPIO_BASE            ((volatile UnsignedWord32*) 0x20200000)
#define GPIO_FUNCSELECT_BASE (GPIO_BASE + 0x00)
#define GPIO_SET_BASE        (GPIO_BASE + 0x07)
#define GPIO_CLEAR_BASE      (GPIO_BASE + 0x0A)
#define GPIO_LEVEL_BASE      (GPIO_BASE + 0x0D)

#define GPIO_PINPULLUPDOWNENABLE_OFFSET       (0x25)
#define GPIO_PINPULLUPDOWNENABLECLOCK_BASE    (GPIO_BASE + 0x26)
#define GPIO_PINPULLUPDOWNENABLECLOCK0_OFFSET (0x00)
#define GPIO_PINPULLUPDOWNENABLECLOCK1_OFFSET (0x01)

#define GPIO_PINPULLUPDOWN_SETUPDELAY           (150)
#define GPIO_FUNCSELECT_MASK                    (0x7)
#define GPIO_PULLCONTROL_MASK                   (0x3)
#define GPIO_PINPULLUPDOWNENABLE_OFF_BITS       (0x00000000)
#define GPIO_PINPULLUPDOWNENABLECLOCK_NONE_BITS (0x00000000)

#define GPIO_FUNCSELECT_ALTFUNC5 (0x02)
#define GPIO_PULL_OFF  (0x00)

#define UART_BASE                     (AUX_BASE + 0x10)
#define UART_IODATA_OFFSET            (0x00)
#define UART_INTERRUPTENABLE_OFFSET   (0x01)
#define UART_INTERRUPTIDENTIFY_OFFSET (0x02)
#define UART_LINECONTROL_OFFSET       (0x03)
#define UART_MODEMCONTROL_OFFSET      (0x04)
#define UART_LINESTATUS_OFFSET        (0x05)
#define UART_MODEMSTATUS_OFFSET       (0x06)
#define UART_SCRATCH_OFFSET           (0x07)
#define UART_EXTRACONTROL_OFFSET      (0x08)
#define UART_EXTRASTATUS_OFFSET       (0x09)
#define UART_BAUDRATE_OFFSET          (0x0A)

#define AUX_ENABLES_UART_BIT           (0x00000001)
#define UART_LINESTATUS_TXQNOTFULL_BIT (0x00000020)
#define UART_LINESTATUS_TXQEMPTY_BIT   (0x00000040)

#define UART_TRANSMIT_GPIO (14)
#define UART_RECEIVE_GPIO  (15)

#define BASEBAUD_RATE (31250000)

static void bDebugFuncSelect(UnsignedByte gpioIndex, UnsignedByte funcSelect)
{
    UnsignedWord32 gpioFuncSelect = *(GPIO_FUNCSELECT_BASE + (gpioIndex / 10));
    gpioFuncSelect &= ~ (GPIO_FUNCSELECT_MASK << (3 * (gpioIndex % 10)));
    gpioFuncSelect |= funcSelect << (3 * (gpioIndex % 10));
    *(GPIO_FUNCSELECT_BASE + (gpioIndex / 10)) = gpioFuncSelect;
}

static void bDebugSetPullControl(UnsignedByte gpioIndex, UnsignedByte pullControl)
{
    volatile unsigned int delayCount;
    *(GPIO_BASE + GPIO_PINPULLUPDOWNENABLE_OFFSET)           = (pullControl & GPIO_PULLCONTROL_MASK);
    for (delayCount = 0; delayCount < GPIO_PINPULLUPDOWN_SETUPDELAY; delayCount++);
    *(GPIO_PINPULLUPDOWNENABLECLOCK_BASE + (gpioIndex >> 5)) = (1 << (gpioIndex & 0x1F));
    for (delayCount = 0; delayCount < GPIO_PINPULLUPDOWN_SETUPDELAY; delayCount++);
    *(GPIO_BASE + GPIO_PINPULLUPDOWNENABLE_OFFSET)           = GPIO_PINPULLUPDOWNENABLE_OFF_BITS;
    *(GPIO_PINPULLUPDOWNENABLECLOCK_BASE + (gpioIndex >> 5)) = GPIO_PINPULLUPDOWNENABLECLOCK_NONE_BITS;
}

void bDebugInit(void)
{
    *(AUX_BASE + AUX_ENABLES_OFFSET) |= AUX_ENABLES_UART_BIT; // Enable UART

    *(UART_BASE + UART_INTERRUPTENABLE_OFFSET)   = 0x00;      // Disable receive and transmit interrupts
    *(UART_BASE + UART_EXTRACONTROL_OFFSET)      = 0x00;      // Disable receive and transmit
    *(UART_BASE + UART_LINECONTROL_OFFSET)       = 0x03;      // Select 8 bit 
    *(UART_BASE + UART_INTERRUPTIDENTIFY_OFFSET) = 0xC6;      // Clear receive and transmit FIFO queue
    *(UART_BASE + UART_MODEMCONTROL_OFFSET)      = 0x00;      // RTS to high

    *(UART_BASE + UART_BAUDRATE_OFFSET) = (BASEBAUD_RATE / 115200) - 1;

    bDebugFuncSelect(UART_TRANSMIT_GPIO,     GPIO_FUNCSELECT_ALTFUNC5);
    bDebugSetPullControl(UART_TRANSMIT_GPIO, GPIO_PULL_OFF);
    bDebugFuncSelect(UART_RECEIVE_GPIO,      GPIO_FUNCSELECT_ALTFUNC5);
    bDebugSetPullControl(UART_RECEIVE_GPIO,  GPIO_PULL_OFF);

    *(UART_BASE + UART_EXTRACONTROL_OFFSET) = 0x02; // Enable transmit only
}

static void bDebugOutput(UnsignedByte ch)
{
    // Wait for line status to indicate transmit queue not full
    while (((*(UART_BASE + UART_LINESTATUS_OFFSET)) & UART_LINESTATUS_TXQNOTFULL_BIT) == 0);

    // Write byte to data register
    *(UART_BASE + UART_IODATA_OFFSET) = ch;

    // Wait for line status to indicate transmit queue not full
    while (((*(UART_BASE + UART_LINESTATUS_OFFSET)) & UART_LINESTATUS_TXQEMPTY_BIT) == 0);
}

void bDebugUnsignedWord32Hex(UnsignedWord32 unsignedWord32)
{
    int index;
    for (index = 0; index < 8; index++)
    {
        UnsignedWord32 digit = unsignedWord32 >> 28;
        if (digit < 10)
	    bDebugOutput(digit + '0');
        else
	    bDebugOutput(digit + 'A' - 10);
        unsignedWord32 <<= 4;
    }
}

void bDebugMessage(const char *message)
{
    while (*message != 0)
    {
        bDebugOutput(*message);
        message++;
    }
}

void bDebugNewLine(void)
{
    bDebugOutput('\r');
    bDebugOutput('\n');
}

void bDebugShutdown(void)
{
}
