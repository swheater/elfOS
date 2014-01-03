@
@ Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

	.equ	NONSECURE_BIT, 0x01

	.global	startThreads
	.type	startThreads,%function

startThreads:
	@ TODO: Disable Interupts
	LDR	R0,=currentThreadControlBlock
	LDR	R0,[R0]
	CMP	R0,#0x00000000
	BEQ	startThreadsEnd
	MOV	SP,R0
	LDR	R1,[SP,#0x40]
	MSR	SPSR_csfx,R1
@	MRC	P15,0,R1,C1,C1,0
@	ORR	R1,R1,#NONSECURE_BIT
@	MCR	P15,0,R1,C1,C1,0
	LDMIA	SP!,{R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,SP,LR}^
	NOP
	LDMIA	SP,{PC}^
startThreadsEnd:
	BX	LR

	.end
