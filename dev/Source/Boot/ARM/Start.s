@
@ Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

	.equ	MODE_MASK,  0x1F
	.equ	USER_MODE,  0x10	
	.equ	FIQ_MODE,   0x11
	.equ	IRQ_MODE,   0x12
	.equ	SUP_MODE,   0x13
	.equ	ABT_MODE,   0x17
	.equ	UNDEF_MODE, 0x1B

	.global	start

start:
	MRS     R1,CPSR
	MRS     R0,CPSR

	BIC     R0,R0,#MODE_MASK
	ORR     R0,R0,#FIQ_MODE
	MSR     CPSR_csfx,R0
	LDR     SP,=fiqStack

	BIC     R0,R0,#MODE_MASK
	ORR     R0,R0,#IRQ_MODE
	MSR     CPSR_csfx,R0
	LDR     SP,=irqStack

	BIC     R0,R0,#MODE_MASK
	ORR     R0,R0,#ABT_MODE
	MSR     CPSR_csfx,R0
	LDR     SP,=abtStack

	BIC     R0,R0,#MODE_MASK
	ORR     R0,R0,#SUP_MODE
	MSR     CPSR_csfx,R0
	LDR     SP,=supStack

	BIC     R0,R0,#MODE_MASK
	ORR     R0,R0,#UNDEF_MODE
	MSR     CPSR_csfx,R0
	LDR     SP,=undefStack

	MSR     CPSR_csfx,R1

	BL	kernel_init
stop:
	B	stop

	.bss

	.space	32768
fiqStack:
	.space	32768
irqStack:
	.space	32768
supStack:
	.space	32768
abtStack:
	.space	32768
undefStack:
