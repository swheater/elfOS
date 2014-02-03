@
@ Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

	.global	boot_handlerVectors

boot_handlerVectors:
	B	boot_resetHandler
	B	boot_undefinedInstructionHandler
	B	boot_softwareInterruptHandler
	B	boot_prefetchAbortHandler
	B	boot_dataAbortRedirector
	B	boot_reservedHandler
	B	boot_interruptRequestHandler
	B	boot_fastInterruptRequestHandler

boot_resetHandler:
	LDR	PC,=boot_phyStart

boot_dataAbortRedirector:
	PUSH	{R0,LR}
	BL	boot_dataAbortHandler
	POP	{R0,LR}
	SUBS	PC,LR,#0x08

	.end
