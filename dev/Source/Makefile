#
# Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

MAKE   = make
RM     = rm

all:
	$(MAKE) -C Boot all
	$(MAKE) -C Kernel all
	$(MAKE) -C ELF all
	$(MAKE) -C String all
	$(MAKE) -C StdLibrary all
	$(MAKE) -C elfOS all
	$(MAKE) -C Device all

clean:
	$(MAKE) -C Boot clean
	$(MAKE) -C Kernel clean
	$(MAKE) -C ELF clean
	$(MAKE) -C String clean
	$(MAKE) -C StdLibrary clean
	$(MAKE) -C elfOS clean
	$(MAKE) -C Device clean
	$(RM) -f *~
