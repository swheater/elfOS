#
# Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

all:
	$(MAKE) -C Boot all
	$(MAKE) -C Kernel all
	$(MAKE) -C ELF all
	$(MAKE) -C String all
	$(MAKE) -C StdLibrary all
	$(MAKE) -C elfOS all
	$(MAKE) -C Device all
	$(MAKE) -C OPENflow all

clean:
	$(MAKE) -C Boot clean
	$(MAKE) -C Kernel clean
	$(MAKE) -C ELF clean
	$(MAKE) -C String clean
	$(MAKE) -C StdLibrary clean
	$(MAKE) -C elfOS clean
	$(MAKE) -C Device clean
	$(MAKE) -C OPENflow clean
	$(RM) -f *~
