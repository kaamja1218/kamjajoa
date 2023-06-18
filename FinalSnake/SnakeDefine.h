#pragma once

#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_RESET    "\x1b[0m"
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m" // ���� ����
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define PAUSE 112
#define ESC 27 // ��ȣ ����
#define MAP_X 3
#define MAP_Y 2
#define MAP_WIDTH 30
#define MAP_HEIGHT 20 

int x[100], y[100]; //x,y ��ǥ���� ����
int bap_x, bap_y; //bap�� ��ǥ���� ���� 
int length; //������
int speed; //���� �ӵ� 
int score; //���� ����  -- reset�Լ��� ���� �ʱ�ȭ��
int best_score = 0; //�ְ� ���� ���� --r eset�Լ��� ���� �ʱ�ȭ ���� ���� 
int last_score = 0; //������ ���� ����  -- reset�Լ��� ���� �ʱ�ȭ ���� ����
int dir; //�̵����� ���� 
int key;

void title(void); //���� ����ȭ�� 
void reset(void); //������ �ʱ�ȭ 
void draw_map(void); // ������ �׵θ��� �׸� 
void move(int dir); //��Ӹ��� �̵� 
void pause(void); //�Ͻ����� 
void game_over(void); //���� ������ Ȯ�� 
void bap(void); // ���� ���� 
