/*
 * klib.c
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#include "types.h"
#include "klib.h"
#include "string.h"
#include <stdarg.h>
#include "drivers/video.h"

#define BUFFER_SIZE 100

unsigned int printf(const char *fmt, ...){

	va_list ap;
	char c, buff[BUFFER_SIZE], *p;
	int i = 0;

	va_start(ap, fmt);

	while ((c = *fmt++) != 0){
		p = NULL;

		if(c != '%'){
			putChar(c);
		}else {

			c = *fmt++;

			switch(c){
			case 'u':
			case 'd':
			case 'l':
				itoa(buff, 'd', va_arg(ap, long));
				p = buff;
				break;
			case 'b':
				itoa(buff, 'b', va_arg(ap, long));
				p = buff;
				break;
			case 'c':
				putChar(va_arg(ap, int));
				p = NULL;
				i++;
				break;
			case 'x':
				itoa(buff, 'x',(long) va_arg(ap, void*));
				p = buff;
				break;
			case 's':
				p = va_arg(ap, char *);
				break;
			default:
				putChar(c);
				p = NULL;
			}

			if(p != NULL){
				while(*p != 0){
					putChar(*p);
					p++;
				}
				i++;
				p = NULL;
			}
		}

	}
	va_end(ap);
	return i;
}


