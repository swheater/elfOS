/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Thread.h>
#include <elfOS/Log.h>

void run(void)
{
    elfOS_logMessage("Before Yield\r\n");
    elfOS_threadYield();
    elfOS_logMessage("Between Yield and Stop\r\n");
    elfOS_threadStop();
    elfOS_logMessage("After Stop\r\n");
    hereAndNow:
    goto hereAndNow;
}
