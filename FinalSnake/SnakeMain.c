#include "SnakeGame.h"

int main() {
    char c[256] = "";
    PlaySound(NULL, 0, 0);
    Sleep(10);
    PlaySound(TEXT("C:\\Users\\User\\OneDrive\\���� ȭ��\\���� ���ϴ�\\PPSnakeGame\\maple.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    title();

    while (1) {
        if (_kbhit()) do { key = _getch(); } while (key == 224); //Ű �Է¹���
        Sleep(speed);

        switch (key) { //�Է¹��� Ű�� �ľ��ϰ� ����  
        case LEFT:
        case RIGHT:
        case UP:
        case DOWN:
            if ((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) || (dir == UP && key != DOWN) ||
                (dir == DOWN && key != UP))//180ȸ���̵��� �����ϱ� ���� �ʿ�. 
                dir = key;
            key = 0; // Ű���� �����ϴ� �Լ��� reset 
            break;
        case PAUSE: // PŰ�� ������ �Ͻ����� 
            pause();
            break;

        case ESC: //ESCŰ�� ������ ���α׷� ���� 
            exit(0);
        }
        move(dir);

    }
}