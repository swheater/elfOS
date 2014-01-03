/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <elfOS/Thread.h>
#include <elfOS/Log.h>

void run(void)
{
    volatile int v;
    while (TRUE)
    {
        elfOS_threadYield();
        elfOS_logMessage("x");
        elfOS_threadYield();
        for (v = 0; v < 200000; v++);
    }
}
