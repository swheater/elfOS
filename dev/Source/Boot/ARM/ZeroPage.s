@
@ Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

	.global	zeroPageStart
	.global	zeroPageEnd

zeroPageStart:
	B	resetHandler
	B	undefinedInstructionHandler
	B	softwareInterruptHandler
	B	prefetchAbortHandler
	B	dataAbortHandler
	B	reservedHandler
	B	interruptRequestHandler
	B	fastInterruptRequestHandler

resetHandler:
	B	resetHandler
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
zeroPageEnd:
