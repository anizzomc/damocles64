/*
 * video.h
 *
 *  Created on: Feb 23, 2011
 *      Author: anizzomc
 */

#ifndef VIDEO_H_
#define VIDEO_H_

/**
 * Clears the screen erasing all characters.
 */
void clearScreen();

/**
 * Prints the given character to the current position in the
 * screen.
 * \n returns the carrier and scrolls
 * \t makes a tab
 * @param c the character to print
 */

void putChar(char c);

/**
 * Returns the character at the given position of the cursor.
 */
char getChar();


/**
 * Prints a line at the bottom of the screen, scrolling if
 * its necesary.
 * @param str the string to be printed at the bottom of the
 * screen.
 */
void print(const char *str);

/**
 * Prints a string in at the given line number.
 * @param str the string to be printed.
 * @param line the line that the given string would be printed.
 */
void println(const char *str, int line);


void printxy(const char *str, int line, int col);

#endif /* VIDEO_H_ */
