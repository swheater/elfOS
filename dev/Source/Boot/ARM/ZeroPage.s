@
@ Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

	.global	_start

_start:
	B	resetHandler
	B	undefinedInstructionHandler
	B	softwareInterruptHandler
	B	prefetchAbortHandler
	B	dataAbortHandler
	B	reservedHandler
	B	interruptRequestHandler
	B	fastInterruptRequestHandler

resetHandler:
	LDR	SP,=stack
	BL	kernel_init
stop:
	B	stop
undefinedInstructionHandler:
	B	undefinedInstructionHandler
softwareInterruptHandler:
	B	softwareInterruptHandler
prefetchAbortHandler:
	B	prefetchAbortHandler
dataAbortHandler:
	B	dataAbortHandler
reservedHandler:
	B	reservedHandler
interruptRequestHandler:
	B	interruptRequestHandler
fastInterruptRequestHandler:
	B	fastInterruptRequestHandler

	.bss

	.space	1024
stack:
