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
// Ŀ�� ��ġ�� �����ؼ� �� ��ǥ�� ���ڿ��� ��� �� �� �ְ����ִ� �Լ�
// + Ŀ���� �Ⱥ��̰� ������p

void draw_map(void) { //�� �׵θ� �׸��� �Լ� 
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

    while (_kbhit()) _getch(); //���ۿ� �ִ� Ű���� ���� 

    draw_map();    //�� �׵θ��� �׸� 
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++) { // �� �׵θ� ������ ��ĭ���� ä�� 
        for (j = MAP_X + 1; j < MAP_X + MAP_WIDTH - 1; j++) gotoxy(j, i, "  ");
    }
}


void title(void) {
    screen();
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 8, MAP_Y + 5, "+--------------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 8, MAP_Y + 6, "|        ��� ����         |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 8, MAP_Y + 7, "+--------------------------+");

    gotoxy(MAP_X + (MAP_WIDTH / 2) - 10, MAP_Y + 9, " < ����Ű �Է½� ������ �����մϴ�. > ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 10, MAP_Y + 10, " < I�� ������ ���� �����Դϴ�.    > ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 10, MAP_Y + 11, " < ESC�� ������ ������ ����˴ϴ�.> ");

//Ÿ��Ʋ ȭ��

    while (1) {
        if (_kbhit()) { // Ű�Է¹��� 
            char key_input = 0;
            key = _getch();
            if (key == ESC)
            {
                system("cls");
                exit(0);// ESCŰ�� ���� 
            }
            if (key == 'i')
            {
                system("cls");
                Introduce_Screen();
                scanf_s(" %c", &key_input);  // ���� ���ڸ� ����Ͽ� ���� �Է� ���۸� ����ϴ�.

                if (key_input == 'y')
                {
                    system("cls");
                    title();
                }
            }
            else break; //�ƴϸ� �׳� ��� ���� 
        }
    }
    reset(); // ������ �ʱ�ȭ �� ����
}
int Introduce_Screen()
{
    screen();
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5, "+--------------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6, "|        ���� ����         |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7, "+--------------------------+");

    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 11, "    ��,��,��,�� : �̵�     ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 12, "    P : �Ͻ� ����          ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 13, "    ESC : ����             ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 15, "    y �Է½� Ÿ��Ʋ��      ");



    return 0;
}


void reset(void) {
    int i;
    system("cls"); //ȭ���� ���� 
    draw_map(); //�� �׵θ��� �׸� 
    while (_kbhit()) _getch(); //���ۿ� �ִ� Ű���� ���� 

    dir = LEFT; // ���� �ʱ�ȭ  
    speed = 100; // �ӵ� �ʱ�ȭ 
    length = 5; //�� ���� �ʱ�ȭ 
    score = 0; //���� �ʱ�ȭ 
    for (i = 0; i < length; i++) { //�� ���밪 �Է� 
        x[i] = MAP_WIDTH / 2 + i;
        y[i] = MAP_HEIGHT / 2;
        gotoxy(MAP_X + x[i], MAP_Y + y[i], ANSI_COLOR_GREEN"o"ANSI_COLOR_RESET);
    }
    gotoxy(MAP_X + x[0], MAP_Y + y[0], ANSI_COLOR_RED"O"ANSI_COLOR_RESET); //�� �Ӹ� �׸� 
    bap(); // bap ����  
}





void bap(void) {
    int i;

    int bap_crush_on = 0;//bap�� �� ������ǥ�� ���� ��� on 
    int r = 0; //���� ������ �絿�Ǵ� ���� 
    gotoxy(MAP_X, MAP_Y + MAP_HEIGHT, " YOUR SCORE: "); //����ǥ�� 
    printf("%3d, LAST SCORE: %3d, BEST SCORE: %3d", score, last_score, best_score);

    while (1) {
        bap_crush_on = 0;
        srand((unsigned)time(NULL) + r); //����ǥ���� 
        bap_x = (rand() % (MAP_WIDTH - 2)) + 1;    //������ ��ǥ���� ���� 
        bap_y = (rand() % (MAP_HEIGHT - 2)) + 1;

        for (i = 0; i < length; i++) { //bap�� �� ����� ��ġ���� Ȯ��  
            if (bap_x == x[i] && bap_y == y[i]) {
                bap_crush_on = 1; //��ġ�� bap_crush_on �� on 
                r++;
                break;
            }
        }

        if (bap_crush_on == 1) continue; //������ ��� while���� �ٽ� ���� 

        gotoxy(MAP_X + bap_x, MAP_Y + bap_y, ANSI_COLOR_CYAN"��"ANSI_COLOR_RESET); //�Ȱ����� ��� ��ǥ���� bap�� ��� 
        speed -= 3; //�ӵ� ���� 
        break;

    }
}

void move(int dir) {
    int i;

    if (x[0] == bap_x && y[0] == bap_y) { //bap�ϰ� �浹���� ��� 
        score += 10; //���� ���� 
        bap(); //���ο� �� �߰� 
        length++; //�������� 
        x[length - 1] = x[length - 2]; //���θ��� ���뿡 �� �Է� 
        y[length - 1] = y[length - 2];
    }
    if (x[0] == 0 || x[0] == MAP_WIDTH - 1 || y[0] == 0 || y[0] == MAP_HEIGHT - 1) { //���� �浹���� ��� 
        game_over();
        return; 
        //game_over���� ������ �ٽ� �����ϰ� �Ǹ� ���⼭���� �ݺ��ǹǷ� 
        //return�� ����Ͽ� move�� ������ �κ��� ������� �ʵ��� �մϴ�. 
    }
    for (i = 1; i < length; i++) { //�ڱ���� �浹�ߴ��� �˻� 
        if (x[0] == x[i] && y[0] == y[i]) {
            game_over();
            return;
        }
    }

    gotoxy(MAP_X + x[length - 1], MAP_Y + y[length - 1], "  "); //���� �������� ���� 
    for (i = length - 1; i > 0; i--) { //������ǥ�� ��ĭ�� �ű� 
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }
    gotoxy(MAP_X + x[0], MAP_Y + y[0], ANSI_COLOR_GREEN"o"ANSI_COLOR_RESET); //�Ӹ��� �ִ����� �������� ��ħ 
    if (dir == LEFT) --x[0]; //���⿡ ���� ���ο� �Ӹ���ǥ(x[0],y[0])���� ���� 
    if (dir == RIGHT) ++x[0];
    if (dir == UP) --y[0];
    if (dir == DOWN) ++y[0];
    gotoxy(MAP_X + x[i], MAP_Y + y[i], ANSI_COLOR_RED"O"ANSI_COLOR_RESET); //���ο� �Ӹ���ǥ���� �Ӹ��� �׸� 
}

void pause(void) { // pŰ�� ������ ��� ������ �Ͻ� ���� 
    while (1) {
        if (key == PAUSE) {
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 9, MAP_Y, "< ����Ű �Է½� ���� �ٽ� ���� > ");
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


void game_over(void) { //�������� �Լ�
    system("cls");
    draw_map();
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 5, "+----------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 6, "|      GAME OVER..     |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 7, "+----------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 6, MAP_Y + 8, " YOUR SCORE : ");
    printf("%d", last_score = score);

    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 12, " �ٽ� �����Ϸ��� Ű �Է� ");

    if (score > best_score) {
        best_score = score;
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 4, MAP_Y + 10, "�� �ְ� ��� ��");
    }
    Sleep(500);
    while (_kbhit()) _getch();
    key = _getch();
    title();
}



