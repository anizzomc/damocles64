/*
 * video.c
 *
 *  Created on: Feb 23, 2011
 *      Author: anizzomc
 */

#include "drivers/video.h"

#define VIDEOADDR 0xB8000
#define WHITE_TXT 0x07
#define VIDEO_COLS 80
#define VIDEO_ROWS 25
#define TAB_SIZE 5

//Cantidad de memoria mapeada para el video
#define VIDEO_SIZE VIDEO_COLS*VIDEO_ROWS*2

static char *video = (char *) VIDEOADDR;

static void _putChar(int row, int column, char c);
static char _getChar(int row, int column);
static void _putAttr(int row, int column, char attr);
static char _getAttr(int row, int column);
static void scrollLine();

static int cursor = 0;

void clearScreen() {
	int i;
	for (i = 0; i < VIDEO_SIZE; i += 2) {
		video[i] = ' ';
		video[i + 1] = WHITE_TXT;
	}
	cursor = 0;
}

void print2(const char *str) {

	while (*str != 0) {
		_putChar(24, cursor, *str);

		cursor++;
		str++;
		if (cursor >= VIDEO_COLS) {
			scrollLine();
			cursor = 0;
		}

	}

}

void putChar(char c) {

	int j;

	switch (c) {
	case '\n':
		scrollLine();
		cursor = 0;
		break;
	case '\t':
		for (j = 0; j < TAB_SIZE; j++) {
			_putChar(24, cursor, ' ');
			cursor++;
			if (cursor >= VIDEO_COLS) {
				cursor = 0;
				scrollLine();
			}
		}
		break;
	default:
		_putChar(24, cursor, c);
		cursor++;
		break;
	}


	if (cursor >= VIDEO_COLS) {
		cursor = 0;
		scrollLine();
	}

}
void print(const char *str) {
	while (*str != 0) {
		putChar(*str);
		str++;
	}
}

void println(const char *str, int line) {
	printxy(str, line, 0);
}

void printxy(const char *str, int line, int col){

	while (*str != '\0' && col < VIDEO_COLS) {
		_putChar(line, col, *str);
		str++;
		col++;
	}
}

static void scrollLine() {
	int i, j;

	for (i = 1; i < VIDEO_ROWS; i++) {
		for (j = 0; j < VIDEO_COLS; j++) {
			_putChar(i - 1, j, _getChar(i, j));
			_putAttr(i - 1, j, _getAttr(i, j));
		}
	}

	for (j = 0; j < VIDEO_COLS; j++) {
		_putChar(24, j, ' ');
	}
}

static void _putChar(int row, int column, char c) {
	video[(row * VIDEO_COLS + column) * 2] = c;
}

static char _getChar(int row, int column) {
	return video[(row * VIDEO_COLS + column) * 2];
}

static void _putAttr(int row, int column, char attr) {
	video[(row * VIDEO_COLS + column) * 2 + 1] = attr;
}

static char _getAttr(int row, int column) {
	return video[(row * VIDEO_COLS + column) * 2 + 1];
}

/* end video.c */
