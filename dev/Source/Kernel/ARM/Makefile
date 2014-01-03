#
# Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

OBJS = Boot.o Start.o ZeroPage.o HandlerVectors.o Thread.o StartThreads.o

all: $(OBJS)

.s.o:
	$(AS) $(ASFLAGS) -o $@ $<

.c.o:
	$(CC) $(CCFLAGS) -c $<

clean:
	$(RM) -f *~ *.o
