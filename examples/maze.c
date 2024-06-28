/**********************
 *         MAZE        *
 ***********************/

#include <sconio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int w, h;
int* board;

enum State { SPACE = 40, BORDER = 1 };

void init_screen() {
  struct text_info info;
  gettextinfo(&info);
  w = info.screenwidth - (info.screenwidth % 2);
  h = info.screenheigh - (info.screenwidth % 2);
  board = malloc(w * h * sizeof(int));
  _initscr();
  _set_cursortype(_NOCURSOR);
  clrscr();
  srand(time(0));
  textbackground(WHITE);
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; x++) {
      board[x + (h - 1) * w] = BORDER;
      gotoxy(x, y);
      putch(' ');
    }
  }
  textbackground(BLACK);
}

int edge(int x, int y) {
  if (x < 1 || x > w - 1 || y < 1 || y > h - 1) return 0;
  if (board[(y - 1) * w + x - 1] == BORDER) return 0;
  if (board[(y - 1) * w + x] == BORDER) return 0;
  if (board[(y - 1) * w + x + 1] == BORDER) return 0;
  if (board[(y)*w + x - 1] == BORDER) return 0;
  if (board[(y)*w + x] == BORDER) return 0;
  if (board[(y)*w + x + 1] == BORDER) return 0;
  if (board[(y - 1) * w + x - 1] == BORDER) return 0;
  if (board[(y + 1) * w + x] == BORDER) return 0;
  if (board[(y + 1) * w + x + 1] == BORDER) return 0;
  return 1;
}

void maze() {
  int x = 2, y = 2, d, end = 0, dig=0, goback=0, count;
  gotoxy(x, y);
  putch('@');
  while (!end) {
    /*
        1->E A
        2->S B
        3->W C
        4->N D

        XX123
        X 405
        XX678
    */
    d = rand() % 4 + 1;
    count = 0;
    //printf("%d ",d);
    while (dig && !goback) {
      switch (d) {
        case 1:
          if (edge(x + 2, y)) {
            gotoxy(x+1,y);
            putch(' ');
            x += 2;
            board[y * w + x ]='A';
            dig=1;
          }
          break;
        case 2:
          if (edge(x, y + 2)) {
            gotoxy(x,y+1);
            putch(' ');
            board[y * w + x ]='B';
            y += 2;
            dig=1;
          }
          break;
        case 3:
          if (edge(x - 2, y)) {
            gotoxy(x-1,y);
            putch(' ');
            board[y * w + x ]='C';
            x -= 2;
            dig=1;
          }
          break;
        case 4:
          if (edge(x, y - 2)) {
            gotoxy(x,y-1);
            putch(' ');
            y -= 2;
            board[y * w + x ]='D';
            dig=1;
          }
          break;
      }
      count = (count+1) % d;
      // check goback
      if(!dig && count==0){
        goback=1;
      }
      delay(10000);
    }
  }
}

int main() {
  init_screen();
  maze();
  while (!kbhit()) {
  };
  puts("");
  return 0;
}
