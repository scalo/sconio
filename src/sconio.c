#define _POSIX_C_SOURCE	199309L //need for nanosleep
#include "sconio.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

/*


FG 	BG 	Name
------------\
30	40	Black
31	41	Red
32	42	Green
33	43	Yellow
34	44	Blue
35	45	Magenta
36	46	Cyan
37	47	White
90	100	Bright Black (Gray)
91	101	Bright Red
92	102	Bright Green
93	103	Bright Yellow
94	104	Bright Blue
95	105	Bright Magenta
96	106	Bright Cyan
97	107	Bright White 


CONIO COLORS

Color   	    Value
----------------------
BLACK 	        0
BLUE 	        1
GREEN   	    2
CYAN 	        3
RED 	        4
MAGENTA 	    5
BROWN 	        6
LIGHTGRAY 	    7
DARKGRAY 	    8
LIGHTBLUE 	    9
LIGHTGREEN 	    10
LIGHTCYAN 	    11
LIGHTRED 	    12
LIGHTMAGENTA	13
YELLOW 	        14
WHITE   	    15

*/

static char * foreground[] = {"30","34","32","36","31","35","33","37",
                              "90","94","92","96","91","95","93","97"};

static char * background[] = {"40","44","42","46","41","45","43","47",
                              "100","104","102","106","101","105","103","107"};

void clrscr(void){
    printf("\033[2J");
    fflush(stdout); 
}

void delline (void){
    printf("\033[2K");
    fflush(stdout); 
}

void gotoxy(int x, int y){
    printf("\033[%d;%dH",y,x);
    fflush(stdout); 
}

void textcolor(int color){
    printf("\033[%sm",foreground[color]);
}

void textbackground(int color){
    printf("\033[%sm",background[color]);
}

void _resetcolor(){
    printf("\033[m");
    fflush(stdout); 
}

void _set_cursortype(int type){
    if(!type)
        printf("\033[?25l");
    else
        printf("\033[?25h");
}


static void _check_teminal(void){
    if (!isatty(STDIN_FILENO))
    {
        fprintf(stderr, "Not a terminal.\n");
        exit(EXIT_FAILURE);
    }
}

static void _wherexy(int *x, int *y){
    struct termios saved,raw;
    char buf[8];
    _check_teminal();
    // enable Raw Mode
    tcgetattr(STDIN_FILENO, &saved);
    tcgetattr (STDIN_FILENO, &raw);
    raw.c_lflag &= ~( ICANON | ECHO );
    raw.c_cc[VMIN] = 1; // ???? CONTROLLARE
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    write(STDOUT_FILENO, "\033[6n", 4);
    read(STDIN_FILENO, buf, 8);
    sscanf(buf,"\033[%d;%dR",y,x);
    // disable Raw Mode
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
}

int wherex(void){
    int x,y;
    _wherexy(&x,&y);
    return x;
}

int wherey(void){
    int x,y;
    _wherexy(&x,&y);
    return y;
}


static int _kbhit(int block){
    char c = '\0',d,e;
    int k = 0;
    struct termios saved,raw;
    fflush(stdout);
    //_check_teminal();
    // enable Raw Mode
    tcgetattr(STDIN_FILENO, &saved);
    tcgetattr (STDIN_FILENO, &raw);
    // raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    // raw.c_oflag &= ~(OPOST);
    //  raw.c_cflag |= (CS8);
    raw.c_lflag &= ~( ICANON | ECHO |ISIG );
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    // c = getchar();
    do {
        read(STDIN_FILENO, &c, 1);
        if (c == 27) {
            read(STDIN_FILENO, &d, 1);
            read(STDIN_FILENO, &e, 1);
            //printf("%d %d %d\r\n", c, d, e);
            if (d == 91 && e >= 65 && e <= 68) {
                k = e + (c << 8);
            }
        } else {
            k = (int)c;
        }
    } while(!c && block);
    // disable Raw Mode
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
    return k;
}

int kbhit(void){
    int k;
    k = _kbhit(0);
    if (k != 0){
        // ungetc(c, stdin);
        return k;
    }
    return 0;
}

static char _getch(int echo){
    char c;
    c = _kbhit(1);
    if(echo)
        printf("%c",c);
    return(c);
}

char getch(void){
    return(_getch(0));
}

 char getche(void){
    return(_getch(1));
}

void putch(char ch){
    putchar(ch);
    fflush(stdout);
}

void delay(int ms){
    int secs,millis;
    secs=ms/1000;
    millis=ms%1000;
	struct timespec t =  { secs,  millis * 1000000L};
	nanosleep(&t, 0);
}

void gettextinfo(struct text_info *info){
    int x,y,a,b;
    _wherexy(&x,&y);
    info->curx=x;
    info->cury=y;
    gotoxy(999,999);
    _wherexy(&a,&b);
    info->screenwidth = a;
    info->screenheigh = b;
    gotoxy(x,y);
}	

void _echo(int onoff){
    struct termios term;
    tcgetattr (STDIN_FILENO, &term);
    if(onoff)
        term.c_lflag |= ECHO ;
    else
        term.c_lflag &= ~( ECHO );
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

void noecho(void){
    _echo(0);
}

void echo(void){
    _echo(1);
}

static void _backuprestore(void){
    static struct termios *saved=NULL;
    if(saved==NULL){
        saved = (void *) malloc(sizeof(struct termios));
        tcgetattr(STDIN_FILENO, saved);
    }else{
        tcsetattr(STDIN_FILENO, TCSAFLUSH, saved);
        _set_cursortype(_NORMALCURSOR);
        echo();
    }
}

void _initscr(void){
    static int init=0;
    if(!init){
        // _check_teminal
        _check_teminal();
        // save term cfg
        _backuprestore();
        // atexit
        atexit(_backuprestore);
        _set_cursortype(_NOCURSOR);
        noecho();
        init=1;
    }
}
