@
@ Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

	.global	continueProcess
	.type	continueProcess, %function

continueProcess:
	@ TODO: Disable Interupts
	@ TODO: Reset SP?
	MSR	SPSR,R1
	LDMIA	R0,{R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,SP,LR,PC}^

	.end
