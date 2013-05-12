@
@ Copyright (c) 2012-2013, Stuart Wheater, Newcastle upon Tyne, England. All rights reserved.
@

	.text

zeroPageVectors:
	LDR	PC,=phy_boot
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
