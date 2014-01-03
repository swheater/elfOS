#
# Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

OBJS = Container.o Thread.o Segment.o Log.o

all: $(OBJS)

.c.o:
	$(CC) $(CCFLAGS) -c $<

clean:
	$(RM) -f *~ *.o
