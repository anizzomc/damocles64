/*
 * memory.c
 *
 *  Created on: Mar 9, 2011
 *      Author: anizzomc
 */

#include "arch/pagination.h"
#include "arch/memory.h"
#include "klib.h"

void testMemory1(void *upperBound) {
	long *ptr = (long *)0;

	long longs = 0;
	while(ptr <= (long *)upperBound){
		if(pAddrIsDescribed(ptr))
			longs+= COUNT;
		ptr+=COUNT;
	}

	printf("Longs described: %d below %x\n", longs, ptr);
	long bytes = longs*8;
	long kilobytes = bytes/1024;
	long megabytes = kilobytes/1024;
	long gigabytes = megabytes/1024;
	printf("Thats like: %d gigabytes\n", gigabytes);

}


void infoMemory(){

	long memory = pGetMemoryDefined();
	long kilo = memory/1024;
	long mega = kilo/1024;
	long giga = mega/1024;
	printf("\nThe amount of memory defined is: %d bytes\n", memory);
	printf("That's like %d kilobytes\n", kilo);
	printf("That's like %d megabytes\n", mega);
	printf("That's like %d gigabytes\n", giga);



}
