@
@ Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text
	
zeroPageVectors:
	LDR	PC,=kernel_boot
	B	resetError
	B	resetError
	B	resetError
	B	resetError
	B	resetError
	B	resetError
	B	resetError

resetError:
	B	resetError

	.ltorg

	.end
