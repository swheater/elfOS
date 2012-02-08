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

reset:	MOV	SP,#1024
	BL	loadBaseELF
stop:
	B	stop

error:
	B	error

	.bss

	.space	1024
stack:
