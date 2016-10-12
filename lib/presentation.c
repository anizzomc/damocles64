/*
 * presentation.c
 *
 *  Created on: Aug 28, 2011
 *      Author: anizzomc
 */

#include "presentation.h"
#include "klib.h"

void printIDTD(IDTD_t idtd, int index){
	printf("IDT[%d]:\n");
	printf("\tIgnore: %x\n", idtd.ignore);
	printf("\tTarget Offset Extended: %x\n", idtd.offset_ext);
	printf("\tTarget Offset High: %x\n", idtd.offset_h);
	printf("\tTarget Offset Low: %x\n", idtd.offset_l);
	printf("\tSelector: %d\n", idtd.selector);
	printf("\tFlags: %b\n", idtd.flags);


}
