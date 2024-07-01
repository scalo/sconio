/***********************
 *         MAZE        *
 ***********************/

#include <sconio.h>
#include <stdlib.h>
#include <time.h>

#define DELAY 0

int w, h;
unsigned char* board;
int delay_ms = DELAY;

enum State { SPACE = ' ', WALL = 'O' };

void init_screen() {
  struct text_info info;
  gettextinfo(&info);
  w = info.screenwidth - (info.screenwidth % 2);
  h = info.screenheigh - (info.screenheigh % 2);
  board = malloc(w * h * sizeof(unsigned char));
  _initscr();
  //_set_cursortype(_NOCURSOR);
  srand(time(0));
  textbackground(WHITE);
  clrscr();
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; x++) {
      board[x + y * w] = WALL;
      //gotoxy(x + 1, y + 1);
      //putch(' ');
    }
  }
  textbackground(BLACK);
}

int dig(int x, int y) {
  x--;
  y--;
  if (x < 1 || x > w - 2 || y < 1 || y > h - 1) return 0;
  if (board[(y - 1) * w + x - 1] != WALL) return 0;
  if (board[(y - 1) * w + x] != WALL) return 0;
  if (board[(y - 1) * w + x + 1] != WALL) return 0;
  if (board[y * w + x - 1] != WALL) return 0;
  if (board[y * w + x] != WALL) return 0;
  if (board[y * w + x + 1] != WALL) return 0;
  if (board[(y + 1) * w + x - 1] != WALL) return 0;
  if (board[(y + 1) * w + x] != WALL) return 0;
  if (board[(y + 1) * w + x + 1] != WALL) return 0;
  return 1;
}

void put(int x, int y, char c) {
  board[(y - 1) * w + (x - 1)] = c;
  gotoxy(x, y);
  putch(c);
}

void maze() {
  int x = 2, y = 2, dir, sig, end = 0, hole, goback, count;
  put(x, y, '@');
  while (!end) {
    /*
          D
          ^
       C<-+->A goback
          v
          B

        XX123
        X*4?5  edge
        XX678
    */
    dir = rand() % 4 + 1;
    sig = rand() % 2 * 2  - 1;
    //cprintf("%d ",s);
    hole = 0;
    goback = 0;
    count = 0;
    while (!hole && !goback) {
      switch ((dir+count*sig+4)%4+1) {
        case 1:
          if (dig(x + 2, y)) {
            put(x + 1, y, ' ');
            put(x + 2, y, 'A');
            x = x + 2;
            hole = 1;
          }
          break;
        case 2:
          if (dig(x, y + 2)) {
            put(x, y + 1, ' ');
            put(x, y + 2, 'B');
            y = y + 2;
            hole = 1;
          }
          break;
        case 3:
          if (dig(x - 2, y)) {
            put(x - 1, y, ' ');
            put(x - 2, y, 'C');
            x = x - 2;
            hole = 1;
          }
          break;
        case 4:
          if (dig(x, y - 2)) {
            put(x, y - 1, ' ');
            put(x, y - 2, 'D');
            y = y - 2;
            hole = 1;
          }
          break;
      }
      count = count + 1;
      if (!hole && count == 4) {
        goback = 1;
      }
    }
    if (goback == 1) {
      switch (board[x - 1 + (y - 1) * w]) {
        case 'A':
          put(x, y, ' ');
          x = x - 2;
          break;
        case 'B':
          put(x, y, ' ');
          y = y - 2;
          break;
        case 'C':
          put(x, y, ' ');
          x = x + 2;
          break;
        case 'D':
          put(x, y, ' ');
          y = y + 2;
          break;
        case '@':
          end = 1;
          break;
        default:
          cputs("ERRORE goback \n");
          exit(1);
      }
    }
    delay(delay_ms);
  }
}

void wait() {
  kbhit(); // workaround
  while (!kbhit()) {
  };
}

int main(int argc, char** argv) {
  if (argc > 1) {
    int ms = atoi(argv[1]);
    delay_ms = ms;
  }
  init_screen();
  maze();
  wait();
  clrscr();
  return 0;
}
