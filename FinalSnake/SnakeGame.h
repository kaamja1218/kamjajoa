#pragma once
#include "SnakeDefine.h"
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include <mmsystem.h> 
#pragma comment(lib, "winmm.lib")

void gotoxy(int x, int y, char* s) {
    COORD pos = { 2 * x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("%s", s);

    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
// 커서 위치를 설정해서 그 좌표에 문자열을 출력 할 수 있게해주는 함수
// + 커서를 안보이게 설정까즤

void draw_map(void) { //맵 테두리 그리는 함수 
    int i, j;
    for (i = 0; i < MAP_WIDTH; i++) {
        gotoxy(MAP_X + i, MAP_Y, ANSI_COLOR_MAGENTA"#"ANSI_COLOR_RESET);
    }
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++) {
        gotoxy(MAP_X, i, ANSI_COLOR_MAGENTA"#"ANSI_COLOR_RESET);
        gotoxy(MAP_X + MAP_WIDTH - 1, i, ANSI_COLOR_MAGENTA"#"ANSI_COLOR_RESET);
    }
    for (i = 0; i < MAP_WIDTH; i++) {
        gotoxy(MAP_X + i, MAP_Y + MAP_HEIGHT - 1, ANSI_COLOR_MAGENTA"#"ANSI_COLOR_RESET);
    }
}

int screen()
{
    int i, j;

    while (_kbhit()) _getch(); //버퍼에 있는 키값을 버림 

    draw_map();    //맵 테두리를 그림 
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++) { // 맵 테두리 안쪽을 빈칸으로 채움 
        for (j = MAP_X + 1; j < MAP_X + MAP_WIDTH - 1; j++) gotoxy(j, i, "  ");
    }
}


void title(void) {
    screen();
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 8, MAP_Y + 5, "+--------------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 8, MAP_Y + 6, "|        비앰 게임         |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 8, MAP_Y + 7, "+--------------------------+");

    gotoxy(MAP_X + (MAP_WIDTH / 2) - 10, MAP_Y + 9, " < 방향키 입력시 게임은 시작합니다. > ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 10, MAP_Y + 10, " < I룰 누르면 게임 설명입니다.    > ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 10, MAP_Y + 11, " < ESC를 누르면 게임이 종료됩니다.> ");

//타이틀 화면

    while (1) {
        if (_kbhit()) { // 키입력받음 
            char key_input = 0;
            key = _getch();
            if (key == ESC)
            {
                system("cls");
                exit(0);// ESC키면 종료 
            }
            if (key == 'i')
            {
                system("cls");
                Introduce_Screen();
                scanf_s(" %c", &key_input);  // 공백 문자를 사용하여 이전 입력 버퍼를 지웁니다.

                if (key_input == 'y')
                {
                    system("cls");
                    title();
                }
            }
            else break; //아니면 그냥 계속 진행 
        }
    }
    reset(); // 게임을 초기화 후 시작
}
int Introduce_Screen()
{
    screen();
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5, "+--------------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6, "|        게임 설명         |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7, "+--------------------------+");

    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 11, "    ←,→,↑,↓ : 이동     ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 12, "    P : 일시 정지          ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 13, "    ESC : 종료             ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 15, "    y 입력시 타이틀로      ");



    return 0;
}


void reset(void) {
    int i;
    system("cls"); //화면을 지움 
    draw_map(); //맵 테두리를 그림 
    while (_kbhit()) _getch(); //버퍼에 있는 키값을 버림 

    dir = LEFT; // 방향 초기화  
    speed = 100; // 속도 초기화 
    length = 5; //뱀 길이 초기화 
    score = 0; //점수 초기화 
    for (i = 0; i < length; i++) { //뱀 몸통값 입력 
        x[i] = MAP_WIDTH / 2 + i;
        y[i] = MAP_HEIGHT / 2;
        gotoxy(MAP_X + x[i], MAP_Y + y[i], ANSI_COLOR_GREEN"o"ANSI_COLOR_RESET);
    }
    gotoxy(MAP_X + x[0], MAP_Y + y[0], ANSI_COLOR_RED"O"ANSI_COLOR_RESET); //뱀 머리 그림 
    bap(); // bap 생성  
}





void bap(void) {
    int i;

    int bap_crush_on = 0;//bap이 뱀 몸통좌표에 생길 경우 on 
    int r = 0; //난수 생성에 사동되는 변수 
    gotoxy(MAP_X, MAP_Y + MAP_HEIGHT, " YOUR SCORE: "); //점수표시 
    printf("%3d, LAST SCORE: %3d, BEST SCORE: %3d", score, last_score, best_score);

    while (1) {
        bap_crush_on = 0;
        srand((unsigned)time(NULL) + r); //난수표생성 
        bap_x = (rand() % (MAP_WIDTH - 2)) + 1;    //난수를 좌표값에 넣음 
        bap_y = (rand() % (MAP_HEIGHT - 2)) + 1;

        for (i = 0; i < length; i++) { //bap이 뱀 몸통과 겹치는지 확인  
            if (bap_x == x[i] && bap_y == y[i]) {
                bap_crush_on = 1; //겹치면 bap_crush_on 를 on 
                r++;
                break;
            }
        }

        if (bap_crush_on == 1) continue; //겹쳤을 경우 while문을 다시 시작 

        gotoxy(MAP_X + bap_x, MAP_Y + bap_y, ANSI_COLOR_CYAN"밥"ANSI_COLOR_RESET); //안겹쳤을 경우 좌표값에 bap를 찍고 
        speed -= 3; //속도 증가 
        break;

    }
}

void move(int dir) {
    int i;

    if (x[0] == bap_x && y[0] == bap_y) { //bap하고 충돌했을 경우 
        score += 10; //점수 증가 
        bap(); //새로운 밥 추가 
        length++; //길이증가 
        x[length - 1] = x[length - 2]; //새로만든 몸통에 값 입력 
        y[length - 1] = y[length - 2];
    }
    if (x[0] == 0 || x[0] == MAP_WIDTH - 1 || y[0] == 0 || y[0] == MAP_HEIGHT - 1) { //벽과 충돌했을 경우 
        game_over();
        return; 
        //game_over에서 게임을 다시 시작하게 되면 여기서부터 반복되므로 
        //return을 사용하여 move의 나머지 부분이 실행되지 않도록 합니다. 
    }
    for (i = 1; i < length; i++) { //자기몸과 충돌했는지 검사 
        if (x[0] == x[i] && y[0] == y[i]) {
            game_over();
            return;
        }
    }

    gotoxy(MAP_X + x[length - 1], MAP_Y + y[length - 1], "  "); //몸통 마지막을 지움 
    for (i = length - 1; i > 0; i--) { //몸통좌표를 한칸씩 옮김 
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }
    gotoxy(MAP_X + x[0], MAP_Y + y[0], ANSI_COLOR_GREEN"o"ANSI_COLOR_RESET); //머리가 있던곳을 몸통으로 고침 
    if (dir == LEFT) --x[0]; //방향에 따라 새로운 머리좌표(x[0],y[0])값을 변경 
    if (dir == RIGHT) ++x[0];
    if (dir == UP) --y[0];
    if (dir == DOWN) ++y[0];
    gotoxy(MAP_X + x[i], MAP_Y + y[i], ANSI_COLOR_RED"O"ANSI_COLOR_RESET); //새로운 머리좌표값에 머리를 그림 
}

void pause(void) { // p키를 눌렀을 경우 게임을 일시 정지 
    while (1) {
        if (key == PAUSE) {
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 9, MAP_Y, "< 방향키 입력시 게임 다시 시작 > ");
            Sleep(400);
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 9, MAP_Y, "                                    ");
            Sleep(400);
        }
        else {
            draw_map();
            return;
        }
        if (_kbhit()) {

            do {
                key = _getch();
            } while (key == 224);
        }

    }
}


void game_over(void) { //게임종료 함수
    system("cls");
    draw_map();
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 5, "+----------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 6, "|      GAME OVER..     |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 7, "+----------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 8, " YOUR SCORE : ");
    printf("%d", last_score = score);

    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 12, " 다시 시작하려면 키 입력 ");

    if (score > best_score) {
        best_score = score;
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 4, MAP_Y + 10, "☆ 최고 기록 ☆");
    }
    Sleep(500);
    while (_kbhit()) _getch();
    key = _getch();
    title();
}



