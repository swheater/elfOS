#
# Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

OBJS = BCM2835_miniUART.o BCM2835_GPIO.o BCM2835_BSC.o BCM2835_SPI.o BCM2835_SystemTimer.o BCM2835_Timer.o \
       BCM2835_PWM.o BCM2835_EMMC.o \
       RaspPi_Status.o RaspPi_PiGlow.o RaspPi_PiLITEr.o RaspPi_BerryClip.o RaspPi_Ladder.o RaspPi_DisplayTFT18.o \
       RaspPi_ILI9320.o RaspPi_SSD1351.o RaspPi_XPT2046.o RaspPi_MotorPiTX.o RaspPi_elfOSDebug.o RaspPi_ILSoftOLED.o \
       SPI_SecureDigital.o SPI_MCP23S17.o SPI_PN512.o

all: $(OBJS)

.c.o:
	$(CC) $(CCFLAGS) -c $<

clean:
	$(RM) -f *~ *.o
