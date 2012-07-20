/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for Raspberry Pi, mini UART

#include <Kernel/StdTypes.h>
#include <Reset/UART.h>

#define GPIO_BASE                              ((volatile UnsignedWord32*) 0x20200000)
#define GPIO_FUNCSELECT_BASE                   (GPIO_BASE + 0x00)
#define GPIO_FUNCSELECT_1_OFFSET               (0x01)
#define GPIO_PINPULLUPDOWNENABLE_OFFSET        (0x25)
#define GPIO_PINPULLUPDOWNENABLECLOCK_0_OFFSET (0x26)

#define GPIO_FUNCSELECT_1_GPIO14_MASK              (0xFFFF8FFF)
#define GPIO_FUNCSELECT_1_GPIO14_ALT5FUNC          (0x00002000)
#define GPIO_PINPULLUPDOWNENABLE_OFF               (0x00000000)
#define GPIO_PINPULLUPDOWNENABLECLOCK_0_GPIO14_BIT (0x00004000)
#define GPIO_PINPULLUPDOWNENABLECLOCK_0_NONE_BITS  (0x00000000)
#define GPIO_PINPULLUPDOWN_SETUPDELAY              (150)

#define AUX_BASE                      ((volatile UnsignedWord32*) 0x20215000)
#define AUX_INTERRUPTSTATUS_OFFSET    (0x00)
#define AUX_ENABLES_OFFSET            (0x01)
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

void resetUARTInit()
{
    *(AUX_BASE + AUX_ENABLES_OFFSET) |= AUX_ENABLES_UART_BIT; // Enable UART

    *(UART_BASE + UART_INTERRUPTENABLE_OFFSET)   = 0x00;      // Disable receive and transmit interrupts
    *(UART_BASE + UART_EXTRACONTROL_OFFSET)      = 0x00;      // Disable receive and transmit
    *(UART_BASE + UART_LINECONTROL_OFFSET)       = 0x03;      // Select 8 bit 
    *(UART_BASE + UART_INTERRUPTIDENTIFY_OFFSET) = 0xC6;      // Clear receive and transmit FIFO queue
    *(UART_BASE + UART_MODEMCONTROL_OFFSET)      = 0x00;      // RTS to high
    *(UART_BASE + UART_BAUDRATE_OFFSET)          = 0x010E;    // Set baud rate of 115200 pulses per second

    UnsignedWord32 funcSelect1 = *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_1_OFFSET);
    funcSelect1 &= GPIO_FUNCSELECT_1_GPIO14_MASK;
    funcSelect1 |= GPIO_FUNCSELECT_1_GPIO14_ALT5FUNC;
    *(GPIO_FUNCSELECT_BASE + GPIO_FUNCSELECT_1_OFFSET) = funcSelect1;

    volatile unsigned int delayCount;
    *(GPIO_BASE + GPIO_PINPULLUPDOWNENABLE_OFFSET)        = GPIO_PINPULLUPDOWNENABLE_OFF;
    for (delayCount = 0; delayCount < GPIO_PINPULLUPDOWN_SETUPDELAY; delayCount++);
    *(GPIO_BASE + GPIO_PINPULLUPDOWNENABLECLOCK_0_OFFSET) = GPIO_PINPULLUPDOWNENABLECLOCK_0_GPIO14_BIT;
    for (delayCount = 0; delayCount < GPIO_PINPULLUPDOWN_SETUPDELAY; delayCount++);
    *(GPIO_BASE + GPIO_PINPULLUPDOWNENABLE_OFFSET)        = GPIO_PINPULLUPDOWNENABLE_OFF;
    *(GPIO_BASE + GPIO_PINPULLUPDOWNENABLECLOCK_0_OFFSET) = GPIO_PINPULLUPDOWNENABLECLOCK_0_NONE_BITS;

    *(UART_BASE + UART_EXTRACONTROL_OFFSET)      = 0x02;      // Enable transmit only
}

void resetUARTOutput(UnsignedByte ch)
{
    // Wait for line status to indicate transmit queue not full
    while (((*(UART_BASE + UART_LINESTATUS_OFFSET)) & UART_LINESTATUS_TXQNOTFULL_BIT) == 0);

    // Write byte to data register
    *(UART_BASE + UART_IODATA_OFFSET) = ch;
}
