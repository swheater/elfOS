/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Process.h>
#include <elfOS/Log.h>

void run(void)
{
    elfOS_logMessage("w");
    elfOS_processYield();
    elfOS_logMessage("w");
    elfOS_processYield();
    elfOS_logMessage("w");
    elfOS_processYield();
    elfOS_logMessage("w");
    elfOS_processStop();
    elfOS_logMessage("W");
    hereAndNow:
    goto hereAndNow;
}
