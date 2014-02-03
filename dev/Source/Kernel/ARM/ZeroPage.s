@
@ Copyright (c) 2012-2014, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

zeroPageVectors:
	LDR	PC,=boot_phyStart
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
