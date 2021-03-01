# CONIO.H


| function       |                                                                               |
| -------------- | ----------------------------------------------------------------------------- |
| clrscr         | clears the screen and move the cursor to upper left corner                    |
| delline        | delete the line containing the cursor and move all lines below it one line up |
| getch          | prompts the user to press a character                                         |
| getche         | reads a character from the keyboard and display it on the screen              |
| gotoxy         | places cursor at a desired location on screen                                 |
| kbhit          | determines if a keyboard key  has been pressed or not                         |
| textbackground | change of current background color in text mode                               |
| textcolor      | change the color of drawing text                                              |
| wherex         | return current horizontal cursor position                                     |
| wherey         | return current vertival cursor position                                       |
| _setcursortype | selects cursor appearance                                                     |
| delay          | sleep for ms milliseconds                                                     |
| gettextinfo    | returns information of the screen                                             |
| putch          | print a character on the screen                                               |


---

| TODO    |                                                  |
| ------- | ------------------------------------------------ |
| window  | defines the active text mode window              |
| ungetch | Pushes a character back into the keyboard buffer |
| cputs   | returns a string to the screen                   |

---

| DUMMY      |                                              |
| ---------- | -------------------------------------------- |
| textmode   | msdos only  (check terminal ?)               |
| cprintf  ? | prints formatted output to the screen        |
| cscanf   ? | reads input from the console and reformat it |
| cgets    ? | Reads a string from the console              |



## Refs

https://code-reference.com/c/conio.h

https://en.wikipedia.org/wiki/ANSI_escape_code

http://docs.embarcadero.com/products/rad_studio/radstudio2007/RS2007_helpupdates/HUpdate4/EN/html/devwin32/coniohpart_xml.html