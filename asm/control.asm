;
; control.asm
;
;  Created on: Aug 28, 2011
;      Author: anizzomc
;

GLOBAL halt

SECTION .text

halt:
	cli
	hlt
