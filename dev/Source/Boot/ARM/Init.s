@
@ Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

boot_start:
	LDR	SP,=boot_stack
	BL	boot_stacksSetup
	BL	boot_bootHandlerSetup
	BL	boot_virtualMemorySetup
	BL	boot_kernelHandlerSetup
	LDR	SP,=kernel_svcStack
	LDR	PC,=kernel_start

	.ltorg

	.align	4
	.space	1024
boot_stack:

	.end
