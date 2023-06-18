#include "SnakeGame.h"

int main() {
    char c[256] = "";
    PlaySound(NULL, 0, 0);
    Sleep(10);
    PlaySound(TEXT("C:\\Users\\User\\OneDrive\\바탕 화면\\패턴 파일덜\\PPSnakeGame\\maple.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    title();

    while (1) {
        if (_kbhit()) do { key = _getch(); } while (key == 224); //키 입력받음
        Sleep(speed);

        switch (key) { //입력받은 키를 파악하고 실행  
        case LEFT:
        case RIGHT:
        case UP:
        case DOWN:
            if ((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) || (dir == UP && key != DOWN) ||
                (dir == DOWN && key != UP))//180회전이동을 방지하기 위해 필요. 
                dir = key;
            key = 0; // 키값을 저장하는 함수를 reset 
            break;
        case PAUSE: // P키를 누르면 일시정지 
            pause();
            break;

        case ESC: //ESC키를 누르면 프로그램 종료 
            exit(0);
        }
        move(dir);

    }
}