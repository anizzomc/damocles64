/*
 * demoPagination.h
 *
 *  Created on: Apr 6, 2011
 *      Author: anizzomc
 */

#ifndef DEMOPAGINATION_H_
#define DEMOPAGINATION_H_


/**
 * Demo pagination shows how to paginate a physical address to a high memory
 * sector trough pagination. This demo affects the this memory addresses:
 *
 *  0x200000: 4kb for the PML[1]
 *  0x200000 + 512: for PDP[1].PDP[0]
 *
 *  0x400000: 2Mb page to be written.
 *
 *  This demo paginates 8Gb of memory to 2Mb physical page. With each cicle
 *  writes +1 data in each char, showing how many times the same byte was written.
 *
 */
void doDemoPagination1();


#endif /* DEMOPAGINATION_H_ */
