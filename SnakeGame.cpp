#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define _CRT_SECURE_NO_WARNINGS

int loby_screen();
int introduce_screen();
int game_screen();

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw_game_board(int width, int height)
{
    int i, j;

    for (i = 0; i < width + 2; i++) {
        gotoxy(i, 0);
        printf("*");
        gotoxy(i, height + 1);
        printf("*");
    }

    for (j = 0; j < height + 2; j++) {
        gotoxy(0, j);
        printf("*");
        gotoxy(width + 1, j);
        printf("*");
    }
}
//game state = 0 일때 찍힘
int loby_screen()
{
    printf("***********************************\n");
    printf("*                                 *\n");
    printf("*           지렁이 게임           *\n");
    printf("*           (Snake Bite)          *\n");
    printf("*                                 *\n");
    printf("*   1.게임 시작                   *\n");
    printf("*   2.게임 설명                   *\n");
    printf("*   3.게임 랭킹 보기              *\n");
    printf("*   4.게임 종료(ESC)              *\n");
    printf("***********************************\n");


    return 0;
}
int game_screen()
{
    int width, height;

    printf("게임 플레이할 경기장의 넓이와 높이를 입력해주세요 : ");
    if (scanf_s("%d %d", &width, &height) != 2) {
        printf("잘못 입력 하셨습니다. 넓이와 높이 두개의 정수를 입력해주세요.\n");
        return 1;
    }

    system("cls"); // 입력 받은 후 화면을 clear


    draw_game_board(width, height);
    printf("\n타이틀 화면으로 돌아갈까요? (Y/N)");



    return 0;
}

int introduce_screen()
{
    printf("****************************************\n");
    printf("*        게임 설명 화면입니다.         *\n");
    printf("*   시대가 어느 시댄데 메뉴얼을 만드냐 *\n");
    printf("****************************************\n");
    printf("타이틀 화면으로 돌아갈까요? (Y/N) \n");

    return 0;
}


int main()
{

    int game_state = 0;
    int game_running = 1;
    int screen = 1;
    while (game_running)
    {
        char key_input = 0;
        switch (game_state)
        {
        case 0:
            if (screen == 1)
            {
                loby_screen();
                screen = 0;
            }
            key_input = 0;
            key_input = _getch();
            if (key_input == '1')
            {
                game_state = 1;
                screen = 1;
            }
            else if (key_input == '2')
            {
                game_state = 2;
                screen = 2;
            }
            else if (key_input == '3')
            {
                game_state = 3;
                screen = 3;
            }
            else if (key_input == '4' || key_input == 27)
                game_running = 0;
            break;
        case 1:
            if (screen == 1)
            {
                game_screen();
                screen = 1;
            }
            key_input = 0;
            key_input = _getch();
            if (key_input == 'y')
            {
                system("cls");
                game_state = 0;
                screen = 1;
            }
            break;
        case 2:
            if (screen == 2)
            {
                introduce_screen();
                screen = 0;
            }
            key_input = 0;
            key_input = _getch();
            if (key_input == 'y')
            {
                game_state = 0;
                screen = 1;
            }
            break;
        default:
            break;
        }
    }
    return 0;
}
