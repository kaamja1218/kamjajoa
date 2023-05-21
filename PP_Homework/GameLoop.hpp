#define _CRT_SECURE_NO_WARNINGS
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"
#define ANSI_COLOR_GREEN    "\x1b[32m"


#include <iostream>
#include <stdlib.h>
#include <vector>
#include <windows.h>

namespace MuSoeun
{
    class Object {
    public:
        int CoordX, CoordY;

        Object() {}
        virtual ~Object() {}

        // 자식 클래스(오브젝트 모양)가 상속받은 후 재정의할 수 있도록 가상 함수로 설정
        virtual void Render(char* screenBuf, int width, int height) = 0;
    };

    

    class Rectangle : public Object {
    public:
        Rectangle() {}
        ~Rectangle() {}

        // 가로로 긴 직사각형을 screenBuf에 x, y 좌표를 시작으로 저장
        void Render(char* screenBuf, int width, int height) override {
            for (int y = 0; y < 3; y++)
                for (int x = 0; x < 10; x++)
                    screenBuf[(width + 1) * (CoordY + y) + (CoordX + x)] = 'R';
        }
    };

    class Scene {
    private:
        int width = 50, height = 20;
        char screenBuf[51 * 20 + 1], input[10]; // width + (width * height)
        std::vector<Object*> objList;

        void gotoxy(int x, int y) {
            COORD pos = { x, y };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        }

        void Draw() {
            for (Object* obj : objList) {
                obj->Render(screenBuf, width, height);
            }
            system("cls");
            std::cout << screenBuf << std::endl;
        }

        int gamestate = 1;

        void ReleaseScreenBuf() {
            int i = 0;  /* 가로 index */
            int j = 0;  /* 세로 index */
            while (j < height) {
                while (i < width + 1) {
                    if (i == width)
                        screenBuf[i + (j * (width + 1))] = '\n';
                    else {
                        if (i == 0 || i == 1 || i == (width - 1) || i == (width - 2) || j == 0 || j == (height - 1))
                            screenBuf[i + (j * (width + 1))] = '#';
                        else
                            screenBuf[i + (j * (width + 1))] = ' ';
                    }
                    i = i + 1;
                }
                i = 0;
                j = j + 1;
                screenBuf[height * (width + 1) - 1] = '\0';

                if (gamestate == 1)
                {
                    MainScreen();
                }
            }
        }
        void MainScreen() {
            const char* lines[] = {
                "Snake Game",
                "1. Game Start",
                "2. Game Introduce",
                "3. Game Ranking",
                "4. Game Exit"
            };
            int numLines = sizeof(lines) / sizeof(lines[0]);
            int lineHeight = height / (numLines + 2);
            for (int line = 0; line < numLines; line++) {
                int offset = (width - strlen(lines[line])) / 2;
                int textStart = (line + 1) * lineHeight;
                int textLength = strlen(lines[line]);
                for (int k = 0; k < textLength; k++) {
                    screenBuf[(width + 1) * textStart + offset + k] = lines[line][k];
                }
            }  
        }

        void ClearScreenBuf() {
            ReleaseScreenBuf();
            system("cls");
            std::cout << screenBuf << std::endl;
        }

        void ObjectCreate() {

            Rectangle* obj1 = new Rectangle();
            obj1->CoordX = 33;
            obj1->CoordY = 7;

            objList.push_back(obj1);
        }

    public:
        Scene() {
            ClearScreenBuf();
            ObjectCreate();
        }

        ~Scene() {
            for (Object* obj : objList) {
                delete obj;
            }
        }

        void Run() {
            while (true) {
                gotoxy(0, height);
                std::cout << objList.size() << "개의 오브젝트\n"
                    << ANSI_COLOR_MAGENTA"게임 오브젝트 그리기: D\n";
                std::cout << ANSI_COLOR_CYAN "화면 초기화: R" << std::endl;

                std::cout << ANSI_COLOR_RESET;
                std::cin >> input;
                if (_kbhit()) {
                    if (_getch() == 'z') break;
                }


                switch (input[0]) {
                case 'd':
                case 'D':
                    Draw();
                    break;

                case 'r':
                case 'R':
                    ClearScreenBuf();
                    break;
                }
            }
        }
    };
}