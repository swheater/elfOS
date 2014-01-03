/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

const int c0 = 17;
const int c1 = 18;

static int v0 = 1;
static int v1 = 2;
static int v2 = 3;
static int v3 = 4;

extern void set1(void);
extern void set2(void);

void set1(void)
{
    v2 = 19;
    v3 = 20;
}

void run(void)
{
    set1();
    set2();
}

void set2(void)
{
    v0 = c0;
    v1 = c1;
}

