/*
 * interrupt.h
 *
 *  Created on: Aug 28, 2011
 *      Author: anizzomc
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "types.h"

extern IDTD_t *IDT;

IDTD_t iGetDescriptor(int index);

void iDebug(qword fnc);

void iSetIDTD(qword fnc, int index);


/* Hardcoded handlers */

void keyboardHandler();

void timerTickHandler();


/* Maskarable Interrupts */

void setPic1Mask(byte mask);

#endif /* INTERRUPT_H_ */
