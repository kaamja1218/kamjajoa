#pragma once

#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_RESET    "\x1b[0m"
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m" // 색들 정의
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define PAUSE 112
#define ESC 27 // 번호 정의
#define MAP_X 3
#define MAP_Y 2
#define MAP_WIDTH 30
#define MAP_HEIGHT 20 

int x[100], y[100]; //x,y 좌표값을 저장
int bap_x, bap_y; //bap의 좌표값을 저장 
int length; //몸길이
int speed; //게임 속도 
int score; //점수 저장  -- reset함수에 의해 초기화됨
int best_score = 0; //최고 점수 저장 --r eset함수에 의해 초기화 되지 않음 
int last_score = 0; //마지막 점수 저장  -- reset함수에 의해 초기화 되지 않음
int dir; //이동방향 저장 
int key;

void title(void); //게임 시작화면 
void reset(void); //게임을 초기화 
void draw_map(void); // 게임판 테두리를 그림 
void move(int dir); //뱀머리를 이동 
void pause(void); //일시정지 
void game_over(void); //게임 오버를 확인 
void bap(void); // 음식 생성 
