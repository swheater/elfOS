#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

MAKE = make
RM   = rm

all:
	$(MAKE) -C Kernel all
	$(MAKE) -C String all
	$(MAKE) -C ELF all

clean:
	$(MAKE) -C Kernel clean
	$(MAKE) -C String clean
	$(MAKE) -C ELF clean
	$(RM) -f *~
