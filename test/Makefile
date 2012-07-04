#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

CC      = arm-none-eabi-gcc
CCFLAGS = -Wall -I ../dev/Headers
RM      = rm

OBJS = Test1Appl.o Test2Appl.o Test3Appl.o Test4Appl.o Test5Appl.o Test6Appl.o \
       Test7wAppl.o Test7xAppl.o Test7yAppl.o Test7zAppl.o

all: $(OBJS)

.c.o:
	$(CC) $(CCFLAGS) -c $<

clean:
	$(RM) -f *~ *.o
