/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Process.h>

void run(void)
{
    int i;
    elfOS_processYield();
    elfOS_processLogging((int) &i);
    elfOS_processStop();
    elfOS_processLogging(0x1212);
    hereAndNow:
    goto hereAndNow;
}
