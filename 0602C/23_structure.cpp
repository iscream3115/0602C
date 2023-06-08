#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>


struct player
{
	char name[256];
	int hp;
	int def;
	int atk;
	int exp;
	int gold;
};

struct monster
{
	char name[256];
	int hp;
	int atk;
	int exp;
};


//typedef는 C언어에서 번거로움을 줄이기 위해 데이터형을 새로 정의하는 것이다. Cpp에선 굳이 안써도 된다.
typedef struct
{
	int xpos;
	int ypos;
}point;



int main()
{

	//xy좌표의 두점 사이의 거리 구하기
	point pos1;
	point pos2;
	double distance;


	printf("point pos1 : ");
	scanf_s("%d %d",&pos1.xpos,&pos1.ypos);

	printf("point pos2 : ");
	scanf_s("%d %d", &pos2.xpos, &pos2.ypos);

	//피타고라스의 정리 이용 pow = 제곱, 몇제곱인지 설정 가능 sqrt => 루트
	distance = sqrt((double)pow((pos2.xpos - pos1.xpos), 2) + pow((pos2.ypos - pos1.ypos), 2));

	printf("두 점 사이의 거리: %g\n",distance);

	return 0;
}

void rpg()
{
	player p;

	monster m[2] = { {"주황버섯",100,20,30},{"슬라임",80,40,70} };


	printf("\n game start\n");
	printf("이름을 입력 : ");
	scanf_s("%s", &p.name, sizeof(p.name));

	printf("체력 설정 : ");
	scanf_s("%d", &p.hp);

	printf("공격력 설정 : ");
	scanf_s("%d", &p.atk);

	p.exp = 0;
	p.gold = 0;


	printf("*********\n");
	printf("림그레이브\n");
	printf("*********\n");


	//while문 안에 넣게 되면 srand로 시드값이 초기화가 되는 속도보다 while문이 돌아가는 속도가 더 빠르기 때문에 제대로 작동하지 않는다.
	srand((unsigned int)time(NULL));

	while (1)
	{
		if (p.hp <= 0)
		{
			printf("%s YOU DIED\n",p.name);
			exit(1);

		}
		printf("\n당신은 계단을 내려갔다.\n");
		Sleep(1000);

		int eventKey = rand() % 5;

		switch (eventKey)
		{
			case 0:
				printf("\n %s가 보물 상자를 연다\n", p.name);
				Sleep(1000);
				p.gold += 100;

				printf("현재 룬 : %d\n", p.gold);
				Sleep(1000);

				printf("다음으로 이동\n");
				Sleep(1000);
				break;

			case 1:
				printf("\n 아이템 획득\n", p.name);
				Sleep(1000);
				p.gold += 100;

				printf("현재 룬 : %d\n", p.gold);
				Sleep(1000);

				printf("다음으로 이동\n");
				Sleep(1000);
				break;

			case 4:
				break;


		}

	}



}