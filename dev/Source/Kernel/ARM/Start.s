@
@ Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

	.equ	MODE_MASK,  0x1F
	.equ	USR_MODE,   0x10
	.equ	FIQ_MODE,   0x11
	.equ	IRQ_MODE,   0x12
	.equ	SVC_MODE,   0x13
	.equ	ABT_MODE,   0x17
	.equ	UNDEF_MODE, 0x1B
	.equ	SYS_MODE,   0x1F
	.equ	MON_MODE,   0x16

	.global	kernel_boot_handlerStacksSetup
	.global	kernel_fiqStack
	.global	kernel_irqStack
	.global	kernel_abtStack
	.global	kernel_undefStack
	.global	kernel_svcStack

kernel_boot_handlerStacksSetup:
	MRS	R1,CPSR
	MRS	R0,CPSR

	BIC	R0,R0,#MODE_MASK
	ORR	R0,R0,#FIQ_MODE
	MSR	CPSR_csfx,R0
	LDR	SP,=kernel_fiqStack

	BIC	R0,R0,#MODE_MASK
	ORR	R0,R0,#IRQ_MODE
	MSR	CPSR_csfx,R0
	LDR	SP,=kernel_irqStack

	BIC	R0,R0,#MODE_MASK
	ORR	R0,R0,#ABT_MODE
	MSR	CPSR_csfx,R0
	LDR	SP,=kernel_abtStack

	BIC	R0,R0,#MODE_MASK
	ORR	R0,R0,#UNDEF_MODE
	MSR	CPSR_csfx,R0
	LDR	SP,=kernel_undefStack

	MSR	CPSR_csfx,R1

	BX	LR

	.ltorg

	.bss

	.align	4
	.space	4096
kernel_fiqStack:
	.space	4096
kernel_irqStack:
	.space	4096
kernel_abtStack:
	.space	4096
kernel_undefStack:
	.space	16384
kernel_svcStack:

	.end
