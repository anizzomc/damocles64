/*
 * keyboard.c
 *
 *  Created on: Aug 28, 2011
 *      Author: anizzomc
 */

#include "drivers/keyboard.h"
#include "types.h"
#include "klib.h"
#include "drivers/video.h"

char SCtoASCIInum[0xff] =
{    /*  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E     F    */
/*0*/   NOP, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', NOP, '\b', '\t',
/*1*/   'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', NOP, '+', '\n', NOP, 'a', 's',
/*2*/   'd', 'f', 'g', 'h', 'j', 'k', 'l', NOP, '{', '}', NOP, '<', 'z', 'x', 'c', 'v',
/*3*/   'b', 'n', 'm', ',', '.', '/', NOP, '*', NOP, ' ', NOP, 0xB3, NOP, NOP, NOP, NOP,
/*4*/   NOP, NOP, NOP, NOP, NOP, NOP, NOP, '7', '8', '9', '-', '4', '5', '6', '+', '1',
/*5*/   '2', '3', '0', '.', NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP
};

char SCtoASCIIplain[0xff] =
{    /*  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E     F    */
/*0*/   NOP, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', NOP, '\b', '\t',
/*1*/   'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', NOP, '+', '\n', NOP, 'a', 's',
/*2*/   'd', 'f', 'g', 'h', 'j', 'k', 'l', NOP, '{', '}', NOP, '<', 'z', 'x', 'c', 'v',
/*3*/   'b', 'n', 'm', ',', '.', '-', NOP, '*', NOP, ' ', NOP, 0xB3, NOP, NOP, NOP, NOP,
/*4*/   NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, 0xC1, NOP, '-', 0xB4, NOP, 0xC3, '+', NOP,
/*5*/   0xC2, NOP, 0xDC, 0xB2, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP
};

char SCtoASCIIshift[0xff] =
{    /*  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E     F    */
/*0*/   NOP, ESC, '!', '"', '#', '$', '%', '&', '/', '(', ')', '=', '?', NOP, '\b', NOP,
/*1*/   'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', NOP, '*', '\n', NOP, 'A', 'S',
/*2*/   'D', 'F', 'G', 'H', 'J', 'K', 'L', NOP, '[', ']', NOP, '>', 'Z', 'X', 'C', 'V',
/*3*/   'B', 'N', 'M', ';', ':', '_', NOP, NOP, NOP, ' ', NOP, 0xB3, NOP, NOP, NOP, NOP,
/*4*/   NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, 0xC1, NOP, '-', 0xB4, NOP, 0xC3, '+', NOP,
/*5*/   0xC2, NOP, 0xDC, 0xB2, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP
};

char SCtoASCIIplainCAPS[0xff] =
{    /*  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E     F    */
/*0*/   NOP, ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', NOP, '\b', '\t',
/*1*/   'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', NOP, '+', '\n', NOP, 'A', 'S',
/*2*/   'D', 'F', 'G', 'H', 'J', 'K', 'L', NOP, '{', '}', NOP, '<', 'Z', 'X', 'C', 'V',
/*3*/   'B', 'N', 'M', ',', '.', '-', NOP, NOP, NOP, ' ', NOP, 0xB3, NOP, NOP, NOP, NOP,
/*4*/   NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, 0xC1, NOP, '-', 0xB4, NOP, 0xC3, '+', NOP,
/*5*/   0xC2, NOP, 0xDC, 0xB2, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP
};

char SCtoASCIIshiftCAPS[0xff] =
{    /*  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E     F    */
/*0*/   NOP, ESC, '!', '"', '#', '$', '%', '&', '/', '(', ')', '=', '?', NOP, '\b', NOP,
/*1*/   'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', NOP, '*', '\n', NOP, 'a', 's',
/*2*/   'd', 'f', 'g', 'h', 'j', 'k', 'l', NOP, '[', ']', NOP, '>', 'z', 'x', 'c', 'v',
/*3*/   'b', 'n', 'm', ';', ':', '_', NOP, NOP, NOP, ' ', NOP, 0xB3, NOP, NOP, NOP, NOP,
/*4*/   NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, 0xC1, NOP, '-', 0xB4, NOP, 0xC3, '+', NOP,
/*5*/   0xC2, NOP, 0xDC, 0xB2, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP, NOP
};


static int isShiftPressed();
static void shiftPress();
static void shiftRelease();
static int shiftFlag = 0;

static int handleSpecialKeys(byte scanCode);

void keyIn(byte scanCode){


		char input;

		if(handleSpecialKeys(scanCode)){
			//If special keys were handled, the work is done.
			return;
		}

		if (SCtoASCIIplain[ scanCode ] == NOP )
	         return;


		if(!isShiftPressed()){
			input = SCtoASCIIplain[scanCode];
		} else {
			input = SCtoASCIIshift[scanCode];
		}

		putChar(input);
}

static int isShiftPressed() {
	return shiftFlag;
}
static void shiftPress() {
	shiftFlag = 1;
}
static void shiftRelease() {
	shiftFlag = 0;
}

static int handleSpecialKeys(byte scanCode) {

	int ret = 0;

	switch(scanCode){
	case RSHIFT:
	case LSHIFT:
		 shiftPress();
		 ret = 1;
		 break;
	case RSHIFTUP:
	case LSHIFTUP:
		shiftRelease();
		ret = 1;
		break;
	}


	return ret;

}

