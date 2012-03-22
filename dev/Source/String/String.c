/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <String/String.h>

unsigned int string_length(const char *string)
{
    if (string != 0)
    {
        unsigned int length = 0;
        while (string[length] != 0)
            length++;
        return length;
    }
    else
        return 0;
}
