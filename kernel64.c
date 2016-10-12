/* kernel64.c */

#include "drivers/video.h"
#include "klib.h"
#include "string.h"
#include "control.h"
#include "types.h"
#include "arch/loader.h"
#include "prog/demoPagination.h"
#include "arch/pagination.h"
#include "arch/interrupt.h"
#include "presentation.h"

static long ticks = 0;

void foo(){
		ticks++;
		char buff[15];
		itoa (buff, 10, ticks);
		printxy(buff, 0, 65);
}

int main()
{
	clearScreen();
	printf("Damocles64 Kernel\n");

	pSetPresent((qword*)&PML[256], 0); //This entry is the same as PML[0]

	printf("The eokl is %x\n", eokl);

	iSetIDTD((qword)timerTickHandler, 0x20);
	iSetIDTD((qword)keyboardHandler, 0x21);


	printf("IDTD set\n");


    /* 1 1 1 1 1 0 0 0
     * ? ? ? ? ? 2 K T  T = timer, K = Keyboard, 2 = IRQ2
     */

	setPic1Mask((byte)0xFC);

	printf("PIC1 set\n");

	asm("sti");

	while(1)
	{
		//printf("\nSistem halted");
	  asm("hlt");
	}
	return (0);
};




