#ifndef _STDLIBRARY_AEABI_H
#define _STDLIBRARY_AEABI_H 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

typedef struct
{
    int quot;
    int rem;
} idivmodReturn;

typedef struct
{
    unsigned quot;
    unsigned rem;
} uidivmodReturn;

extern int __aeabi_idiv(int numerator, int denominator);
// __value_in_regs?
extern idivmodReturn __aeabi_idivmod(int numerator, int denominator);
extern unsigned int __aeabi_uidiv(unsigned int numerator, unsigned int denominator);
// __value_in_regs?
extern uidivmodReturn __aeabi_uidivmod(unsigned int numerator, unsigned int denominator);

extern int __aeabi_idiv0(int returnValue);
extern long long __aeabi_ldiv0(long long returnValue);

#endif
