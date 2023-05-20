#define _CRT_SECURE_NO_WARNINGS

#include <iostream> //컴파일러와 같은 폴더 안에 있는 것을 이용 가능한 꺽쇠
#include <conio.h>
#include "GameLoop.hpp"// 

using namespace std;

int main() {
	MuSoeun::Scene GameLoop;// 네임스페이스 정의 후 클래스 이용
	GameLoop.Run();
}