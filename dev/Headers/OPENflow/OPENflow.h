#ifndef _OPENFLOW_OPENFLOW
#define _OPENFLOW_OPENFLOW 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

typedef void (*taskMain)(unsigned long opcode, void *arguments[], unsigned long numberOfArguments, unsigned long *outcome, void *(*results)[], unsigned long *numberOfResults);

#endif
