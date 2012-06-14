#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

CC      = arm-none-eabi-gcc
CCFLAGS = -Wall -I../../Headers
RM      = rm

OBJS = Init.o Handlers.o Logging.o

all: $(OBJS)
	$(MAKE) -C ARM all

.c.o:
	$(CC) $(CCFLAGS) -c $<

clean:
	$(MAKE) -C ARM clean
	$(RM) -f *~ *.o
