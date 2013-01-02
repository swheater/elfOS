/*
 * Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

const int c0 = 17;
const int c1 = 18;

static int v0 = 1;
static int v1 = 2;
static int v2 = 3;
static int v3 = 4;

extern void set(void) __attribute__ ((section (".text.elfos")));

void set(void)
{
    v0 = c0;
    v1 = c1;
    v2 = 19;
    v3 = 20;
}

void run(void)
{
    set();
}
