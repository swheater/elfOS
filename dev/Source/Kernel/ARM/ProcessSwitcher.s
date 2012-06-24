@
@ Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

	.equ	MODE_MASK,     0x1F
	.equ	USER_MODE,     0x10
	.equ	SVC_MODE,      0x13
	.equ	NONSECURE_BIT, 0x01

	.global	continueProcess
	.type	continueProcess,%function

continueProcess:
	@ TODO: Disable Interupts
	LDR	R1,[R0,#0x40]
	MSR	SPSR_fsxc,R1
@	MRC	P15,0,R1,C1,C1,0
@	ORR	R1,R1,#NONSECURE_BIT
@	MCR	P15,0,R1,C1,C1,0
	LDMIA	R0!,{R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,SP,LR}^
	NOP
	LDR	SP,=svcStack
	LDMIA	R0,{R0,PC}^

	.end
