/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

// Device driver for BCM2835 - mini UART

#include <Kernel/StdTypes.h>
#include <Device/BCM2835_GPIO.h>
#include <Device/BCM2835_miniUART.h>

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

#define UART_TRANSMIT_GPIO (14)
#define UART_RECEIVE_GPIO  (15)

#define BASEBAUD_RATE (31250000)

void uartInit(void)
{
    *(AUX_BASE + AUX_ENABLES_OFFSET) |= AUX_ENABLES_UART_BIT; // Enable UART

    *(UART_BASE + UART_INTERRUPTENABLE_OFFSET)   = 0x00;      // Disable receive and transmit interrupts
    *(UART_BASE + UART_EXTRACONTROL_OFFSET)      = 0x00;      // Disable receive and transmit
    *(UART_BASE + UART_LINECONTROL_OFFSET)       = 0x03;      // Select 8 bit 
    *(UART_BASE + UART_INTERRUPTIDENTIFY_OFFSET) = 0xC6;      // Clear receive and transmit FIFO queue
    *(UART_BASE + UART_MODEMCONTROL_OFFSET)      = 0x00;      // RTS to high

    uartSetBaudRate(115200);

    gpioFuncSelect(UART_TRANSMIT_GPIO,     GPIO_FUNCSELECT_ALTFUNC5);
    gpioSetPullControl(UART_TRANSMIT_GPIO, GPIO_PULL_OFF);
    gpioFuncSelect(UART_RECEIVE_GPIO,      GPIO_FUNCSELECT_ALTFUNC5);
    gpioSetPullControl(UART_RECEIVE_GPIO,  GPIO_PULL_OFF);

    *(UART_BASE + UART_EXTRACONTROL_OFFSET) = 0x02; // Enable transmit only
}

UnsignedWord32 uartSetBaudRate(UnsignedWord32 baudRate)
{
    UnsignedWord32 baudRateReg = (BASEBAUD_RATE / baudRate) - 1;
    *(UART_BASE + UART_BAUDRATE_OFFSET) = baudRateReg;

    return BASEBAUD_RATE / (baudRateReg + 1);
}

void uartOutput(UnsignedByte ch)
{
    // Wait for line status to indicate transmit queue not full
    while (((*(UART_BASE + UART_LINESTATUS_OFFSET)) & UART_LINESTATUS_TXQNOTFULL_BIT) == 0);

    // Write byte to data register
    *(UART_BASE + UART_IODATA_OFFSET) = ch;
}

void uartShutdown(void)
{
}
