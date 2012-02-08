@
@ Copyright (c) 2012, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

	.global	_start

_start:
	B	reset
	B	error
	B	error
	B	error
	B	error
	B	error
	B	error
	B	error

reset:	LDR	SP,=stack
	BL	init
stop:
	B	stop

error:
	B	error

	.bss

	.space	1024
stack:
