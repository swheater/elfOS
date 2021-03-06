/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Process.h>
#include <elfOS/Log.h>

void run(void)
{
    elfOS_logMessage("Before Yield\r\n");
    elfOS_processYield();
    elfOS_logMessage("Between Yield and Stop\r\n");
    elfOS_processStop();
    elfOS_logMessage("After Stop\r\n");
    hereAndNow:
    goto hereAndNow;
}
