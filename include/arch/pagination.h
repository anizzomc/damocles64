/*
 * pagination.h
 *
 *  Created on: Feb 26, 2011
 *      Author: anizzomc
 */

#ifndef PAGINATION_H_
#define PAGINATION_H_

#include "types.h"

#define PML_SIZE 512

#define O_PRESENT 0x1
#define O_RW (0x1<<1)
#define O_NX ((qword)0x1<<63)
#define O_US (0x1<<2)

typedef enum {depth_pml, depth_pdp, depth_pd, depth_pt} depht_t;
//							1Gb			2Mb		4Kb
extern qword *PML;



int pIsPresent(qword descriptor);

void *pGetBaseAddr(qword descriptor);

int pIsPageDescr(qword descriptor);

int pAddrIsDescribed(void *ptr);

long pGetMemoryDefined();

void pSetPresent(qword *descriptor, int flag);

/**
 * When set to TRUE, Write and Read is enabled, when
 * set to FALSE, only Read is enabled.
 */
void pSetRW(qword *descriptor, int flag);


qword pGetPML2Mb(void *ptr, qword options);

qword pGetPDP2Mb(void *ptr, qword options);

qword pGetPD2Mb(void *ptr, qword options);


int pGetPML(void *ptr);
int pGetPDP(void *ptr);
int pGetPD(void *ptr);
int pGetPT(void *ptr);

#endif /* PAGINATION_H_ */
