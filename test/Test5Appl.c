/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Process.h>

void run(void)
{
    elfOS_processYield();

    elfOS_processStop();
}
