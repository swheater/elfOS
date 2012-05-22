/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Process.h>

static int value1 = -1;
static int value2 = -1;

void run(void)
{
    value1 = 1;
    elfOS_processYield();
    value2 = 1;
    elfOS_processStop();
}
