/*
 * pagination.c
 *
 *  Created on: Feb 26, 2011
 *      Author: anizzomc
 */


#include "types.h"
#include "arch/pagination.h"
#include "klib.h"

qword *PML = (qword *) 0x2000;

#define P_BIT 	0x1 //Present bit
#define RW_BIT	(0x1<<1) //Read Write bit
#define US_BIT	(0x1<<2) //User-Sup bit
#define PWT_BIT (0x1<<3)
#define SEVENTH_BIT (0x1 << 7)//The PAT knows who bit
#define G_BIT (0x1 << 8) //Global page bit
#define NX_BIT ((qword)0x1<<63) //No-Executable bit


static int pGetSelector(void *ptr, int depth);

static int pDoIsDescribed(void *ptr, int depth,const qword *base);

static long pDoGetMemoryDefined(const qword *base, depht_t depth);

int pIsPresent(qword descriptor){
	return (0x1 & descriptor);
}

int pIsReadWrite(qword descriptor){
	return (0x2 & descriptor);
}

// 0xFFFFFFFFFFFFF000


void *pGetBaseAddr(qword descriptor){
	return (void *)((descriptor & 0xFFFFFFFFFFFFF000) & 0x000FFFFFFFFFFFFF);
}

int pIsPageDescr(qword descriptor){
	return (descriptor & 0x80) != 0; //Check n 7 bit
}

int pAddrIsDescribed(void *ptr){
	return pDoIsDescribed(ptr, 0,PML);
}


long pGetMemoryDefined(){
	return pDoGetMemoryDefined(PML, depth_pml);
}

static int pDoIsDescribed(void *ptr, int depth,const qword *base) {

	//printf("pDoIsdescribed(%x, %d, %x)\n", ptr, depth, base);
	int index = pGetSelector(ptr, depth);

	if(pIsPresent(base[index])){
		if(pIsPageDescr(base[index]))
			return depth;
		return pDoIsDescribed(ptr, depth+1, pGetBaseAddr(base[index]));
	}
	return 0;
}

static int pGetSelector(void *ptr, int depth){

	switch (depth){
	case 0:
		return pGetPML(ptr);
		break;
	case 1:
		return pGetPDP(ptr);
		break;
	case 2:
		return pGetPD(ptr);
		break;
	case 3:
		return pGetPT(ptr);
		break;
	}
	return -1;
}

qword pGetPML2Mb(void *ptr, qword options){

	qword ret = 0 | options;
	qword p = (qword) ptr;
	p &= 0x000FFFFFFFFFF000; //clear sign-extend and 4Kb boundary
	ret |= (qword) p;

	return ret;

}

qword pGetPD2Mb(void *ptr, qword options){

	qword ret = (G_BIT | SEVENTH_BIT | PWT_BIT )| options;
	qword p = (qword) ptr;
	p &= 0x000FFFFFFFFFF000; //clear sign-extend and 4Kb boundary
	ret |= (qword) p;

	return ret;
}

qword pGetPDP2Mb(void *ptr, qword options){

	qword ret = 0 | options;
	qword p = (qword) ptr;
	p &= 0x000FFFFFFFFFF000; //clear sign-extend and 4Kb boundary
	ret |= (qword) p;

	return ret;

}

void pSetPresent(qword *descriptor, int flag){

	if(flag){
		*descriptor |=  P_BIT;
	} else {
		*descriptor &= ~P_BIT;
	}

}

void pSetRW(qword *descriptor, int flag) {
	if (flag) {
		*descriptor |= RW_BIT;
	} else {
		*descriptor &= ~RW_BIT;
	}
}

void pSetUS(qword *descriptor, int flag){
	if(flag){
		*descriptor |= US_BIT;
	}else {
		*descriptor &= ~US_BIT;
	}
}

void pSetNX(qword *descriptor, int flag){
	if(flag){
		*descriptor |= NX_BIT;
	} else
		*descriptor &= ~NX_BIT;
}

int pGetPML(void *ptr){
	qword val = (qword) ptr;

	val>>=12; //Remove offset;
	val>>=9;  //Remove PT
	val>>=9;  //Remove PD
	val>>=9;  //Remove PDP
	return  val & 0x1FF; //Clear the other bits
}

int pGetPDP(void *ptr){

	qword val = (qword) ptr;

	val>>=12; //Remove offset;
	val>>=9;  //Remove PT
	val>>=9;  //Remove PD
	return  val & 0x1FF; //Clear the other bits
}

int pGetPD(void *ptr){
	qword val = (qword) ptr;

	val>>=12; //Remove offset;
	val>>=9;  //Remove PT
	return  val & 0x1FF; //Clear the other bits
}

int pGetPT(void *ptr){
	qword val = (qword) ptr;

	val>>=12; //Remove offset;
	return  val & 0x1FF; //Clear the other bits
}


static long pDoGetMemoryDefined(const qword *base, depht_t depth){

	int i;
	long memory = 0;


	for(i = 0; i < PML_SIZE ; i++){
		if(pIsPresent(base[i])){
			if(pIsPageDescr(base[i])){
				switch(depth){
				case depth_pml: //Not used
				case depth_pdp:
					memory+=1024*1024*1024; //1Gb
					break;
				case depth_pd:
					memory+=(1024*1024) * 2; // 2Mb
					break;
				case depth_pt:
					memory+=1024*4; //4Kb
					break;
				}

				}
			else{
				memory+= pDoGetMemoryDefined(pGetBaseAddr(base[i]), depth+1);
			}
		}
	}

	return memory;
}
