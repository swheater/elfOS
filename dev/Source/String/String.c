/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
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

Boolean string_equal(const char *string1, const char *string2)
{
    if (string1 == string2)
        return TRUE;
    else if ((string1 == 0) || (string2 == 0))
        return FALSE;
    else
    {
        unsigned int index = 0;
        while ((string1[index] != 0) && (string2[index] != 0))
            index++;

        return (string1[index] == 0) && (string2[index] == 0);
    }
}
