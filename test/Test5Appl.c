/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Thread.h>

void run(void)
{
    elfOS_threadYield();

    elfOS_threadStop();
}
