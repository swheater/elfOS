@
@ Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

	.global	zeroPageStart
	.global	zeroPageEnd

zeroPageStart:
	B	resetRedirector
	B	undefinedInstructionRedirector
	B	softwareInterruptRedirector
	B	prefetchAbortRedirector
	B	dataAbortRedirector
	B	reservedRedirector
	B	interruptRequestRedirector
	B	fastInterruptRequestRedirector

resetRedirector:
	B	resetRedirector

undefinedInstructionRedirector:
	B	undefinedInstructionRedirector

softwareInterruptRedirector:
	PUSH	{R0,R1,LR}
	LDR	R0,=softwareInterruptHandler
	LDR	R1,[R0]
	CMP	R1,#0x00000000
	BEQ	softwareInterruptRedirectSkip
	LDR	R0,[LR,#-0x04]
	BIC	R0,R0,#0xFF000000
	MOV	LR,PC
	BX	R1
softwareInterruptRedirectSkip:	
	POP	{R0,R1,LR}
	MOVS	PC,LR
	
prefetchAbortRedirector:
	SUBS	PC,LR,#0x04

dataAbortRedirector:
	SUBS	PC,LR,#0x08

reservedRedirector:
	B	reservedRedirector

interruptRequestRedirector:
	SUBS	PC,LR,#0x04

fastInterruptRequestRedirector:
	SUBS	PC,LR,#0x04

	.ltorg

zeroPageEnd:

	.end
