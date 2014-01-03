#ifndef _STRING_STRING_H
#define _STRING_STRING_H 1

/*
 * Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>

extern unsigned int string_length(const char *string);
extern Boolean string_equal(const char *string1, const char *string2);

#endif
