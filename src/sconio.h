/*
 *       SCONIO.H
 */

#ifndef SCONIO_H
#define SCONIO_H

#include <stdint.h>
#include <unistd.h>

/* CURSOR CODES */

enum KEYCURSOR {
  KEY_UP = 6977,
  KEY_DOWN = 6978,
  KEY_RIGHT = 6979,
  KEY_LEFT = 6980
};

enum COLORS {
  BLACK = 0,
  BLUE = 1,
  GREEN = 2,
  CYAN = 3,
  RED = 4,
  MAGENTA = 5,
  BROWN = 6,
  LIGHTGRAY = 7,
  DARKGRAY = 8,
  LIGHTBLUE = 9,
  LIGHTGREEN = 10,
  LIGHTCYAN = 11,
  LIGHTRED = 12,
  LIGHTMAGENTA = 13,
  YELLOW = 14,
  WHITE = 15
};

enum CURSOR {
  _NOCURSOR = 0,
  _NORMALCURSOR,
  _SOLIDCURSOR,
};

struct text_info {
  unsigned char curx;
  unsigned char cury;
  unsigned char screenwidth;
  unsigned char screenheigh;
};

/*
Clear the entire screen.
*/
void clrscr(void);

/*
Delete the line containing the cursor and move all lines below it one line up.
*/

void delline(void);

/*
Move the cursor to row y, column x. The upper left corner of the current window is (1,1).
*/
void gotoxy(int x, int y);

/*
The column the cursor is on. The leftmost column is 0.
(Original conio leftmost column is 1)
*/
int wherex(void);

/*
The row the cursor is on. The topmost row is 0.
(Original conio leftmost column is 1)
*/
int wherey(void);

/*
Determines if a keyboard key was pressed
Any available keystrokes can be retrieved with getch or getche.
*/
int kbhit();

/*
Pushes a character back to the keyboard buffer
*/
int ungetch(int ch);

/*
Prompts the user to press a character
*/
char getch(void);

/*
Reads a character from the keyboard and display it on the screen.
*/
char getche(void);

/*
Change the color of drawing text where color is a integer variable.
*/
void textcolor(int color);

/*
Change of current background color in text mode
*/
void textbackground(int color);

/*
 Selects cursor appearance.

Sets the cursor type to
_NOCURSOR

Turns off the cursor
_NORMALCURSOR

Normal underscore cursor
_SOLIDCURSOR

Solid block cursor
*/
/*
Set type of cursor
*/
void _set_cursortype(int type);

/*
Restore default terminal colors
*/
void _resetcolor();

/*
Sleep for ms milliseconds
*/
void delay(int ms);

/*
Returns information of the screen.
*/
void gettextinfo(struct text_info *info);

void noecho(void);

void echo(void);

void _initscr(void);
/*
Print a character on the screen
*/
void putch(char ch);

/*
void __nocursor(void);

void __cursor(void);

void disableRawMode(void);

void enableRawMode(void);
*/

#endif /* SCONIO_H */
