@
@ Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

kernel_boot:
	LDR	SP,=boot_stack
	BL	kernel_boot_virtualMemorySetup
	BL	kernel_boot_handlersSetup
	LDR	SP,=kernel_svcStack
	LDR	PC,=kernel_start

	.ltorg

	.align	4
	.space	2048
boot_stack:

	.end
