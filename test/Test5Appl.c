/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Threading.h>

static int value1 = -1;
static int value2 = -1;

void run(void)
{
    value1 = 1;
    elfOS_yield();
    value2 = 1;
}
