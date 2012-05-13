/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <elfOS/Threading.h>

static int value = 0;

void run(void)
{
    value += 1;
    elfOS_yield();
}
