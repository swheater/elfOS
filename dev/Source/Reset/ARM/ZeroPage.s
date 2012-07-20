@
@ Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

resetStart:
	B	resetHandler
	B	undefinedInstructionRedirector
	B	softwareInterruptRedirector
	B	prefetchAbortRedirector
	B	dataAbortRedirector
	B	reservedRedirector
	B	interruptRequestRedirector
	B	fastInterruptRequestRedirector

resetHandler:
	LDR	SP,=resetStack
	BL	reset_init
	B	kernelStart

undefinedInstructionRedirector:
	PUSH	{R0,R1,LR}
	LDR	R1,=undefinedInstructionHandler
	LDR	R1,[R1]
	CMP	R1,#0x00000000
	BEQ	undefinedInstructionRedirectSkip
	SUB	R0,LR,#0x04
	MOV	LR,PC
	BX	R1
undefinedInstructionRedirectSkip:
	POP	{R0,R1,LR}
	MOVS	PC,LR

softwareInterruptRedirector:
	LDR	SP,=currentThreadControlBlock
	LDR	SP,[SP]
	STMIA	SP!,{R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,SP,LR}^
	NOP
	STMIA	SP!,{LR}
	NOP
	MRS	R2,SPSR
	STMIA	SP!,{R2}

	LDR	SP,=svcStack
	LDR	R2,=softwareInterruptHandler
	LDR	R2,[R2]
	CMP	R2,#0x00000000
	BEQ	softwareInterruptRedirectSkip
	LDR	R0,[LR,#-0x04]
	BIC	R0,R0,#0xFF000000
	LDR	R1,=currentThreadControlBlock
	LDR	R1,[R1]
	MOV	LR,PC
	BX	R2

softwareInterruptRedirectSkip:
	LDR	SP,=currentThreadControlBlock
	LDR	SP,[SP]
	LDMIA	SP!,{R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,SP,LR}^
	NOP
	LDMIA	SP,{PC}^

prefetchAbortRedirector:
	PUSH	{R0,LR}
	LDR	R0,=prefetchAbortHandler
	LDR	R0,[R0]
	CMP	R0,#0x00000000
	BEQ	prefetchAbortRedirectSkip
	MOV	LR,PC
	BX	R0
prefetchAbortRedirectSkip:
	POP	{R0,LR}
	SUBS	PC,LR,#0x04

dataAbortRedirector:
	PUSH	{R0,LR}
	LDR	R0,=dataAbortHandler
	LDR	R0,[R0]
	CMP	R0,#0x00000000
	BEQ	dataAbortRedirectSkip
	MOV	LR,PC
	BX	R0
dataAbortRedirectSkip:
	POP	{R0,LR}
	SUBS	PC,LR,#0x08

reservedRedirector:
	PUSH	{R0,LR}
	LDR	R0,=reservedHandler
	LDR	R0,[R0]
	CMP	R0,#0x00000000
	BEQ	reservedRedirectSkip
	MOV	LR,PC
	BX	R0
reservedRedirectSkip:
	POP	{R0,LR}

interruptRequestRedirector:
	LDR	SP,=currentThreadControlBlock
	LDR	SP,[SP]
	STMIA	SP!,{R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,SP,LR}^
	NOP
	SUB	LR,LR,#0x04
	STMIA	SP!,{LR}
	NOP
	MRS	R2,SPSR
	STMIA	SP!,{R2}

	LDR	SP,=irqStack
	LDR	R0,=interruptRequestHandler
	LDR	R0,[R0]
	CMP	R0,#0x00000000
	BEQ	interruptRequestRedirectSkip
	MOV	LR,PC
	BX	R0

interruptRequestRedirectSkip:
	LDR	SP,=currentThreadControlBlock
	LDR	SP,[SP]
	LDMIA	SP!,{R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,SP,LR}^
	NOP
	LDMIA	SP,{PC}^

fastInterruptRequestRedirector:
	PUSH	{R0,LR}
	LDR	R0,=fastInterruptRequestHandler
	LDR	R0,[R0]
	CMP	R0,#0x00000000
	BEQ	fastInterruptRequestRedirectSkip
	MOV	LR,PC
	BX	R0
fastInterruptRequestRedirectSkip:
	POP	{R0,LR}
	SUBS	PC,LR,#0x04

	.ltorg

	.end
