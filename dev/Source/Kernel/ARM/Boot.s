@
@ Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

kernel_boot:
	LDR	SP,=kernel_boot_stack
	BL	kernel_boot_virtualMemorySetup
	BL	kernel_boot_handlersSetup
	LDR	PC,=kernel_start

	.ltorg

	.align	4
	.space	2048
kernel_boot_stack:

	.end
