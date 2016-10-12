/*
 * interrupt.c
 *
 *  Created on: Aug 28, 2011
 *      Author: anizzomc
 */

#include "arch/interrupt.h"

IDTD_t *IDT = (IDTD_t*) 0x0;

IDTD_t iGetDescriptor(int index){
	return IDT[index];
}



void iDebug(qword fnc){

	IDT[0].offset_l = fnc & 0xFFFF;
	IDT[0].offset_h = (fnc >> 16) & 0xFFFF;
	IDT[0].offset_ext = (fnc >> 32) & 0xFFFFFFFF;

	char val = 0;
	char vel = 10/val;
	vel++;

}

void iSetIDTD(qword fnc, int index){
	IDT[index].flags = 0x8E00;
	IDT[index].offset_l = fnc & 0xFFFF;
	IDT[index].offset_h = (fnc >> 16) & 0xFFFF;
	IDT[index].offset_ext = (fnc >> 32) & 0xFFFFFFFF;
	IDT[index].selector = 0x08;
}







