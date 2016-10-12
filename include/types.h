/*
 * types.h
 *
 *  Created on: Apr 17, 2010
 *      Author: anizzomc
 */

#ifndef TYPES_H_
#define TYPES_H_

typedef unsigned int size_t;

typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;
typedef unsigned long qword;

//typedef struct {
//	int x;
//	int y;
//} coord_t;
//
//
//#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */
//
///* Descriptor de segmento */
//typedef struct {
//  word limit,
//       base_l;
//  byte base_m,
//       access,
//       attribs,
//       base_h;
//} DESCR_SEG;
//
//
///* Descriptor de interrupcion */
//typedef struct {
//  word      offset_l,
//            selector;
//  byte      cero,
//            access;
//  word	    offset_h;
//} DESCR_INT;
//
///* IDTR  */
//typedef struct {
//  word  limit;
//  dword base;
//} IDTR;
//
//
//typedef struct {
//	dword high;
//	dword low;
//} PMLDescriptor;

#define NULL (void *)0

#pragma pack(push)
#pragma pack(1)

typedef struct {
	word offset_l;
	word selector;
	word flags;
	word offset_h;
	dword offset_ext;
	dword ignore;
} IDTD_t;

#pragma pack(pop)


#endif /* TYPES_H_ */
