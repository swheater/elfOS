/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Process.h>
#include <elfOS/Log.h>

void run(void)
{
    elfOS_logMessage("z");
    elfOS_processYield();
    elfOS_logMessage("z");
    elfOS_processYield();
    elfOS_logMessage("z");
    elfOS_processYield();
    elfOS_logMessage("z");
    elfOS_processStop();
    elfOS_logMessage("Z");
    hereAndNow:
    goto hereAndNow;
}
