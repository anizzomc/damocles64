/*
 * demoPagination.c
 *
 *  Created on: Apr 6, 2011
 *      Author: anizzomc
 */

#include "prog/demoPagination.h"
#include "arch/pagination.h"
#include "arch/memory.h"
#include "types.h"
#include "klib.h"
#include "string.h"

qword * PML1 = (qword*) 0x200000; //The 2nd MB of Memory
qword * PDP0 = ((qword*) 0x200000) + 1 * 512; //4Kbs after PML1 (512*8)
qword * PDP1 = ((qword*) 0x200000) + 2 * 512; //
qword * PDP2 = ((qword*) 0x200000) + 3 * 512;
qword * PDP3 = ((qword*) 0x200000) + 4 * 512;
qword * PDP4 = ((qword*) 0x200000) + 5 * 512;
qword * PDP5 = ((qword*) 0x200000) + 6 * 512;
qword * PDP6 = ((qword*) 0x200000) + 7 * 512;
qword * PDP7 = ((qword*) 0x200000) + 8 * 512;

byte * Page2Mb = (byte*) 0x400000; //The page that we will describe a lot of times
byte * Page2MbHigh = (byte *) 0x8000000000; //The same page described very high


void doDemoPagination1() {

	int cicles = 0;

	PML[1] = pGetPML2Mb(PML1, O_PRESENT | O_RW | O_US);
	PML1[0] = pGetPDP2Mb(PDP0, O_PRESENT | O_RW | O_US);
	PML1[1] = pGetPDP2Mb(PDP1, O_PRESENT | O_RW | O_US);
	PML1[2] = pGetPDP2Mb(PDP2, O_PRESENT | O_RW | O_US);
	PML1[3] = pGetPDP2Mb(PDP3, O_PRESENT | O_RW | O_US);
	PML1[4] = pGetPDP2Mb(PDP4, O_PRESENT | O_RW | O_US);
	PML1[5] = pGetPDP2Mb(PDP5, O_PRESENT | O_RW | O_US);
	PML1[6] = pGetPDP2Mb(PDP6, O_PRESENT | O_RW | O_US);
	PML1[7] = pGetPDP2Mb(PDP7, O_PRESENT | O_RW | O_US);
	long i;

	for (i = 0; i < PML_SIZE; i++) {
		PDP0[i] = pGetPD2Mb(Page2Mb, O_PRESENT | O_RW | O_US);
		PDP1[i] = pGetPD2Mb(Page2Mb, O_PRESENT | O_RW | O_US);
		PDP2[i] = pGetPD2Mb(Page2Mb, O_PRESENT | O_RW | O_US);
		PDP3[i] = pGetPD2Mb(Page2Mb, O_PRESENT | O_RW | O_US);
		PDP4[i] = pGetPD2Mb(Page2Mb, O_PRESENT | O_RW | O_US);
		PDP5[i] = pGetPD2Mb(Page2Mb, O_PRESENT | O_RW | O_US);
		PDP6[i] = pGetPD2Mb(Page2Mb, O_PRESENT | O_RW | O_US);
		PDP7[i] = pGetPD2Mb(Page2Mb, O_PRESENT | O_RW | O_US);
	}

	printf("DescribedMemory: %d\n", pGetMemoryDefined() / (1024 * 1024 * 1024));

	//asm("hlt");


	printf("\nLet's clear the \"known\" page...\n");
	for (i = 0; i < 1024 * 1024 * 2; i++) {
		//Set the 2 Mb to 0.
		Page2Mb[i] = 0;
	}

	printf("\nLet's check if the memory that we defined is actualy defined:\n");
	printf("%x defined: %s\n", Page2MbHigh,
			pAddrIsDescribed(Page2MbHigh) ? "yes" : "no");

	printf("Our address should use the PML[%d]\n", pGetPML(Page2MbHigh));

	printf("\nLet's start playing with the memory\n");
	long top = (long) 8 * (1024 * 1024 * 1024);

	for (i = 1; i < top; i++) {

		if (Page2MbHigh[i - 1] != Page2MbHigh[i]) {
			printf("%x value: %d on PDP[%d].PD[%d]\n", &Page2MbHigh[i],
					Page2MbHigh[i], pGetPDP(&Page2MbHigh[i]),
					pGetPD(&Page2MbHigh[i]));
			if (Page2MbHigh[i - 1] == 0) {
				cicles++;
			}
		}

		if (i == top - 1) {
			printf("%x: last value: %d on PDP[%d].PD[%d] = %d\n",
					&Page2MbHigh[i], Page2MbHigh[i], pGetPDP(&Page2MbHigh[i]),
					pGetPD(&Page2MbHigh[i]), Page2MbHigh[i]);
		}
		Page2MbHigh[i - 1]++;
	}

	printf("%x is %sdefined\n", &Page2MbHigh[i], pAddrIsDescribed(&Page2MbHigh[i])? "":"not ");

	printf("Cicles: %d\n", cicles);
	printf("GBs \"writed\":%d\n", cicles / 2);

}
