/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <StdLibrary/AEABI.h>

// int __aeabi_idiv(int numerator, int denominator)
// {
//     return 0;
// }

// __value_in_regs?
// idivmodReturn __aeabi_idivmod(int numerator, int denominator)
// {
//     register idivmodReturn idivmodReturn;
// 
//     return idivmodReturn;
// }

unsigned int __aeabi_uidiv(unsigned int numerator, unsigned int denominator)
{
    if (numerator == 0)
       return 0; 
    else if (denominator == 1)
       return numerator;

    register unsigned int result  = 0;
    register unsigned int bit     = 0x00000001;
    register unsigned int shifted = denominator;

    while ((shifted < numerator) && (shifted <= 0x80000000))
    {
        bit     <<= 1;
        shifted <<= 1;
    }    

    while (bit != 0)
    {
        if (shifted <= numerator)
        {
            result    |= bit;
            numerator -= shifted;
        }

        shifted >>= 1;
        bit     >>= 1;
    }

    return result;
}

// __value_in_regs?
// uidivmodReturn __aeabi_uidivmod(unsigned int numerator, unsigned int denominator)
// {
//     register uidivmodReturn uidivmodReturn;
//
//    return uidivmodReturn;
// }
