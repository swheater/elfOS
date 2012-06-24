/*
 * Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
 */

#include <Kernel/StdTypes.h>
#include <Kernel/Handlers.h>

void (*resetHandler)(void);
void (*undefinedInstructionHandler)(UnsignedWord32* undefinedInstructionAddress);
void (*softwareInterruptHandler)(UnsignedWord32 opcode, UnsignedWord32 param);
void (*prefetchAbortHandler)(void);
void (*dataAbortHandler)(void);
void (*reservedHandler)(void);
void (*interruptRequestHandler)(void);
void (*fastInterruptRequestHandler)(void);
