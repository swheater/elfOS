@
@ Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

	.global	_start

_start:
	LDR	SP,=stack
	BL	kernel_init
stop:
	B	stop

	.bss

	.space	32768
stack:
