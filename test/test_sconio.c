#include "unity.h"
#include "sconio.h"
#include <stdio.h>
#include <time.h>
#include <ctype.h>

#define DELAY 500 //msec

//-----------
void setUp(void){
     _initscr();
     //_set_cursortype(_NOCURSOR);
     //noecho();
}

void tearDown(void){
    //_set_cursortype(_NORMALCURSOR);
    //echo();
}
//-----------

// Tests

void test_delay1(void){
    printf("Sleep for 2.5 sec\n");
    delay(2500);
}

void test_delay2(void){
    // test to correct bug
    printf("Sleep for 1 sec\n");
    delay(1000);
}

void test_cursor(void){
    delay(DELAY);
    _set_cursortype(_NORMALCURSOR);
    delay(DELAY);
    _set_cursortype(_NOCURSOR);
    delay(DELAY);
    _set_cursortype(_SOLIDCURSOR);
    TEST_ASSERT(1);
}

void test_textcolor(void){
    textcolor(RED);
    printf("ROUGE");
    _resetcolor();
    putchar('\n');
    TEST_ASSERT(1);
    delay(DELAY);
}

void _box(void){
    struct text_info info;
    int i;
    gettextinfo(&info);
    gotoxy(1,1);printf("╔");
    for(i=2;i<info.screenwidth;i++){
        printf("═");
    }
    printf("╗");
    gotoxy(1,info.screenheigh);printf("╚");
    for(int i=2;i<info.screenwidth;i++){
        printf("═");
    }
    printf("╝");
    for(int i=2;i<(info.screenheigh);i++){
        gotoxy(1,i);
        printf("║");
    }
    for(int i=2;i<info.screenheigh;i++){
        gotoxy(info.screenwidth,i);
        printf("║");
    }
}

void test_gotoxy(void){
    int x,y,steps=5;
    _box();
    x = wherex(); // save position
    y = wherey();
    for(int i=1;i<=steps;i++){
        gotoxy(30+i,10+i);
        textcolor(MAGENTA);
        textbackground(YELLOW);
        printf("@");
        _resetcolor();
        delay(DELAY);
        gotoxy(30+i,10+i);
        printf(" ");
    }
    putch('\n');
    gotoxy(x,y); // restore position
    TEST_ASSERT(1);
}

void test_textbackground(void){
    textbackground(LIGHTGREEN);
    printf("LIGHTGREEN BACKGROUND");
    _resetcolor();
    putchar('\n');
    TEST_ASSERT(1);
    delay(DELAY);
}

void test_gettextinfo(void){
    struct text_info info;
    gettextinfo(&info);
    printf("curx:%u\n",info.curx);
    printf("cury:%u\n",info.cury);
    printf("screenwidth:%u\n",info.screenwidth);
    printf("screenheigh:%u\n",info.screenheigh);
    TEST_ASSERT(1);
    delay(DELAY);
}

void test_clrscr(void){
    gotoxy(1,1);
    clrscr();
    TEST_ASSERT(1);
    delay(DELAY);
}

void test_kbhit1(void){
    printf("Press a key\n");
    while(!kbhit()){}
    printf("Key pressed\n");
    //getch(); //drop char
    TEST_ASSERT(1);
}

void test_kbhit2(void){
    int i = 0;
    char c;
    while(!(c=kbhit())){
        printf("%d Press a key \n",i);
        i++;
    }
    printf("Key %c pressed\n",c);
    //getch(); //drop char
    delay(1000);
    TEST_ASSERT(1);
}

void test_keymap(void){
    int k;
    printf("Keymap  press 'q' exit \n");
    while (1) {
        k = kbhit();
        if (k > 0) {
            if (iscntrl(k) || k > 255) {
                printf("%d\r\n", k);
            } else {
                printf("%d ('%c')\r\n", k, k);
            }
            if (k == 'q')
                break;
        }
        delay(1000);
        putchar('.');
    }
    TEST_ASSERT(1);

}

void test_getch(){
    char c;
    printf("getch type 'a' char>");
    c = getch();
    printf(" %c pressed with no  echo\n",c);
    TEST_ASSERT_EQUAL_CHAR('a',c);
}

void test_getche(){
    printf("getche type a char>");
    char c;
    c = getche();
    printf(" %c pressed with echo\n",c);
    TEST_ASSERT_EQUAL_CHAR('a',c);
}

void test_kbget(void){
    int c,i;
    while(!kbhit()){
        printf("%d Press a key \n",i);
        i++;
    }
    c = getch();
    printf("Key %c pressed\n",c);
    delay(1000);
    TEST_ASSERT(1);
}

int main(void){
    UNITY_BEGIN();
    // RUN_TEST(test_kbget);
    RUN_TEST(test_keymap);
    RUN_TEST(test_kbhit2);
    RUN_TEST(test_gettextinfo);
    RUN_TEST(test_delay2);
    RUN_TEST(test_clrscr);
    RUN_TEST(test_gotoxy);
    RUN_TEST(test_textcolor);
    RUN_TEST(test_delay1);
    RUN_TEST(test_textbackground);
    RUN_TEST(test_kbhit1);
    RUN_TEST(test_getch);
    RUN_TEST(test_getche);
    return UNITY_END();
}