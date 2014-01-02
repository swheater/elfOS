#ifndef _DEVICE_SPI_MCP23S17_H
#define _DEVICE_SPI_MCP23S17_H 1

/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#define MCP23S17_BANK0_IODIRA_REG   (0x00)
#define MCP23S17_BANK0_IODIRB_REG   (0x01)
#define MCP23S17_BANK0_IPOLA_REG    (0x02)
#define MCP23S17_BANK0_IPOLB_REG    (0x03)
#define MCP23S17_BANK0_GPINTENA_REG (0x04)
#define MCP23S17_BANK0_GPINTENB_REG (0x05)
#define MCP23S17_BANK0_DEFVALA_REG  (0x06)
#define MCP23S17_BANK0_DEFVALB_REG  (0x07)
#define MCP23S17_BANK0_INTCONA_REG  (0x08)
#define MCP23S17_BANK0_INTCONB_REG  (0x09)
#define MCP23S17_BANK0_IOCONA_REG   (0x0A)
#define MCP23S17_BANK0_IOCONB_REG   (0x0B)
#define MCP23S17_BANK0_IOCON_REG    (MCP23S17_BANK0_IOCONA_REG)
#define MCP23S17_BANK0_GPPUA_REG    (0x0C)
#define MCP23S17_BANK0_GPPUB_REG    (0x0D)
#define MCP23S17_BANK0_INTFA_REG    (0x0E)
#define MCP23S17_BANK0_INTFB_REG    (0x0F)
#define MCP23S17_BANK0_INTCAPA_REG  (0x10)
#define MCP23S17_BANK0_INTCAPB_REG  (0x11)
#define MCP23S17_BANK0_GPIOA_REG    (0x12)
#define MCP23S17_BANK0_GPIOB_REG    (0x13)
#define MCP23S17_BANK0_OLATA_REG    (0x14)
#define MCP23S17_BANK0_OLATB_REG    (0x15)

#define MCP23X17_BANK1_IODIRA_REG   (0x00)
#define MCP23X17_BANK1_IODIRB_REG   (0x10)
#define MCP23X17_BANK1_IPOLA_REG    (0x01)
#define MCP23X17_BANK1_IPOLB_REG    (0x11)
#define MCP23X17_BANK1_GPINTENA_REG (0x02)
#define MCP23X17_BANK1_GPINTENB_REG (0x12)
#define MCP23X17_BANK1_DEFVALA_REG  (0x03)
#define MCP23X17_BANK1_DEFVALB_REG  (0x13)
#define MCP23X17_BANK1_INTCONA_REG  (0x04)
#define MCP23X17_BANK1_INTCONB_REG  (0x14)
#define MCP23X17_BANK1_IOCONA_REG   (0x05)
#define MCP23X17_BANK1_IOCONB_REG   (0x15)
#define MCP23X17_BANK1_IOCON_REG    (MCP23X17_BANK1_IOCONA_REG)
#define MCP23X17_BANK1_GPPUA_REG    (0x06)
#define MCP23X17_BANK1_GPPUB_REG    (0x16)
#define MCP23X17_BANK1_INTFA_REG    (0x07)
#define MCP23X17_BANK1_INTFB_REG    (0x17)
#define MCP23X17_BANK1_INTCAPA_REG  (0x08)
#define MCP23X17_BANK1_INTCAPB_REG  (0x18)
#define MCP23X17_BANK1_GPIOA_REG    (0x09)
#define MCP23X17_BANK1_GPIOB_REG    (0x19)
#define MCP23X17_BANK1_OLATA_REG    (0x0A)
#define MCP23X17_BANK1_OLATB_REG    (0x1A)

extern void mcp23s17Init(void);
extern void mcp23s17ReadRegister(UnsignedByte chipSelect, UnsignedByte chipAddr, UnsignedByte regist, UnsignedByte *value);
extern void mcp23s17WriteRegister(UnsignedByte chipSelect, UnsignedByte chipAddr, UnsignedByte regist, UnsignedByte value);
extern void mcp23s17Shutdown(void);

#endif