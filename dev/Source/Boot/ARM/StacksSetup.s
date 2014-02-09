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

	.global	boot_stacksSetup
	.global	boot_fiqStack
	.global	boot_irqStack
	.global	boot_abtStack
	.global	boot_undefStack
	.global	boot_svcStack

boot_stacksSetup:
	MRS	R1,CPSR
	MRS	R0,CPSR

	BIC	R0,R0,#MODE_MASK
	ORR	R0,R0,#FIQ_MODE
	MSR	CPSR_csfx,R0
	LDR	SP,=boot_fiqStack

	BIC	R0,R0,#MODE_MASK
	ORR	R0,R0,#IRQ_MODE
	MSR	CPSR_csfx,R0
	LDR	SP,=boot_irqStack

	BIC	R0,R0,#MODE_MASK
	ORR	R0,R0,#ABT_MODE
	MSR	CPSR_csfx,R0
	LDR	SP,=boot_abtStack

	BIC	R0,R0,#MODE_MASK
	ORR	R0,R0,#UNDEF_MODE
	MSR	CPSR_csfx,R0
	LDR	SP,=boot_undefStack

	MSR	CPSR_csfx,R1

	BX	LR

	.ltorg

	.bss

	.align	4
	.space	256
boot_fiqStack:
	.space	256
boot_irqStack:
	.space	256
boot_abtStack:
	.space	256
boot_undefStack:
	.space	256
boot_svcStack:

	.end
