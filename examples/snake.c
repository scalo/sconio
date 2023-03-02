// Snake
// adapted to sconio from RosettaCode https://rosettacode.org/wiki/Snake#C

// The problem with implementing this task in C is, the language standard
// does not cover some details essential for interactive games:
// a nonblocking keyboard input, a positional console output,
// a and millisecond-precision timer: these things are all system-dependent.

// Therefore the program is split in two pieces, a system-independent
// game logic, and a system-dependent UI, separated by a tiny API:
int nonblocking_getch();
void positional_putch(int x, int y, char ch);
void millisecond_sleep(int n);
void init_screen();
void update_screen();
void close_screen();

#include <sconio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int w, h;
int* board;

int  nonblocking_getch() {
  return kbhit();
}

void millisecond_sleep(int n) { delay(n); }
void update_screen() { fflush(stdout); }
void init_screen() {
  struct text_info info;
  gettextinfo(&info);
  w = info.screenwidth;
  h = info.screenheigh;
  board = malloc(w * h * sizeof(int));
  _initscr();
  _set_cursortype(_NORMALCURSOR);
  // noecho();
  clrscr();
}
void close_screen() {}
void positional_putch(int x, int y, char ch) {
  gotoxy(x, y);
  putch(ch);
}

int head;
enum Dir { N,
           E,
           S,
           W } dir;
int quit;

enum State { SPACE = 0,
             FOOD = 1,
             BORDER = 2 };
// negative values denote the snake (a negated time-to-live in given cell)

// reduce a time-to-live, effectively erasing the tail
void age() {
  int i;
  for (i = 0; i < w * h; ++i)
    if (board[i] < 0)
      ++board[i];
}

// put a piece of food at random empty position
void plant() {
  int r;
  do
    r = rand() % (w * h);
  while (board[r] != SPACE);
  board[r] = FOOD;
}

// initialize the board, plant a very first food item
void start(void) {
  int i;
  for (i = 0; i < w; ++i)
    board[i] = board[i + (h - 1) * w] = BORDER;
  for (i = 0; i < h; ++i)
    board[i * w] = board[i * w + w - 1] = BORDER;
  head = w * (h - 1 - h % 2) / 2;  // screen center for any h
  board[head] = -5;
  dir = N;
  quit = 0;
  srand(time(0));
  plant();
}

void step() {
  int len = board[head];
  switch (dir) {
    case N:
      head -= w;
      break;
    case S:
      head += w;
      break;
    case W:
      --head;
      break;
    case E:
      ++head;
      break;
  }
  switch (board[head]) {
    case SPACE:
      board[head] = len - 1;  // keep in mind len is negative
      age();
      break;
    case FOOD:
      board[head] = len - 1;
      plant();
      break;
    default:
      quit = 1;
  }
}

void show() {
  const char* symbol = " @.";  // array of symbols
  int i;
  for (i = 0; i < w * h; ++i)
    positional_putch(i % w + 1, i / w + 1,  // bug in original source , inverted x y
                     board[i] < 0 ? '#' : symbol[board[i]]);
  update_screen();
}

int main() {
  init_screen();
  start();
  do {
    show();
    switch (nonblocking_getch()) {
      case 'q' :
      case  KEY_UP :
        dir = N;
        break;
      case 'o' :
      case KEY_LEFT:
        dir = W;
        break;
      case 'a' :
      case KEY_DOWN:
        dir = S;
        break;
      case 'p' :
      case KEY_RIGHT:
        dir = E;
        break;
      case 'x':
        quit = 1;
        break;
    }
    step();
    millisecond_sleep(100);  // beware, this approach
                             // is not suitable for anything but toy projects like this
  } while (!quit);
  millisecond_sleep(999);
  close_screen();
  return 0;
}