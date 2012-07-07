/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <elfOS/Process.h>
#include <elfOS/Log.h>

void run(void)
{
    volatile int v;
    while (TRUE)
    {
        elfOS_logMessage("x");
        elfOS_processYield();
        for (v = 0; v < 200000; v++);
    }
}
