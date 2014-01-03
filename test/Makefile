#
# Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

CC      = arm-none-eabi-gcc
CCFLAGS = -Wall -I ../dev/Headers
LD      = arm-none-eabi-ld
LDFLAGS = 
RM      = rm

ELFOS_OBJS = ../dev/Source/elfOS/Container.o ../dev/Source/elfOS/Segment.o ../dev/Source/elfOS/Thread.o ../dev/Source/elfOS/Log.o

OBJS = Test1Appl.o Test2Appl.o Test3Appl.o Test4Appl.o Test5Appl.o Test6Appl.o \
       Test7wAppl.o Test7xAppl.o Test7yAppl.o Test7zAppl.o

all: $(OBJS)

.c.o:
	$(CC) $(CCFLAGS) -c $<

Test7xAppl.elf: Test7xAppl.o
	$(LD) $(LDFLAGS) -nostdlib -T appl.lds -o Test7xAppl.elf Test7xAppl.o $(ELFOS_OBJS)

clean:
	$(RM) -f *~ *.o *.elf
