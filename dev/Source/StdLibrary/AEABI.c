/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <StdLibrary/AEABI.h>

int __aeabi_idiv(int numerator, int denominator)
{
    return 0;
}

// __value_in_regs?
idivmodReturn __aeabi_idivmod(int numerator, int denominator)
{
    register idivmodReturn idivmodReturn;

    return idivmodReturn;
}

unsigned int __aeabi_uidiv(unsigned int numerator, unsigned int denominator)
{
    return 0;
}

// __value_in_regs?
uidivmodReturn __aeabi_uidivmod(unsigned int numerator, unsigned int denominator)
{
    register uidivmodReturn uidivmodReturn;

    return uidivmodReturn;
}
