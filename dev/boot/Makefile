#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

CC     = arm-gp2x-linux-gcc
CFLAGS = -Wall -O2
MAKE   = make
RM     = rm

all: BaseELFLoader.o
	$(MAKE) -C arm all

BaseELFLoader.o: BaseELFLoader.c BaseELFLoader.h
	$(CC) $(CCFLAGS) -c BaseELFLoader.c

clean:
	$(MAKE) -C arm clean
	$(RM) -f *~ *.o
