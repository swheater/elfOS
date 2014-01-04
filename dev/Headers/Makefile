#
# Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
#

all:
	$(MAKE) -e -C Kernel all
	$(MAKE) -e -C String all
	$(MAKE) -e -C ELF all
	$(MAKE) -e -C StdLibrary all
	$(MAKE) -e -C elfOS all
	$(MAKE) -e -C Device all
	$(MAKE) -e -C OPENflow all

clean:
	$(MAKE) -e -C Kernel clean
	$(MAKE) -e -C String clean
	$(MAKE) -e -C ELF clean
	$(MAKE) -e -C StdLibrary clean
	$(MAKE) -e -C elfOS clean
	$(MAKE) -e -C Device clean
	$(MAKE) -e -C OPENflow clean
	$(RM) -f *~
