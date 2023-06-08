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


//typedef�� C���� ���ŷο��� ���̱� ���� ���������� ���� �����ϴ� ���̴�. Cpp���� ���� �Ƚᵵ �ȴ�.
typedef struct
{
	int xpos;
	int ypos;
}point;



int main()
{

	//xy��ǥ�� ���� ������ �Ÿ� ���ϱ�
	point pos1;
	point pos2;
	double distance;


	printf("point pos1 : ");
	scanf_s("%d %d",&pos1.xpos,&pos1.ypos);

	printf("point pos2 : ");
	scanf_s("%d %d", &pos2.xpos, &pos2.ypos);

	//��Ÿ����� ���� �̿� pow = ����, ���������� ���� ���� sqrt => ��Ʈ
	distance = sqrt((double)pow((pos2.xpos - pos1.xpos), 2) + pow((pos2.ypos - pos1.ypos), 2));

	printf("�� �� ������ �Ÿ�: %g\n",distance);

	return 0;
}

void rpg()
{
	player p;

	monster m[2] = { {"��Ȳ����",100,20,30},{"������",80,40,70} };


	printf("\n game start\n");
	printf("�̸��� �Է� : ");
	scanf_s("%s", &p.name, sizeof(p.name));

	printf("ü�� ���� : ");
	scanf_s("%d", &p.hp);

	printf("���ݷ� ���� : ");
	scanf_s("%d", &p.atk);

	p.exp = 0;
	p.gold = 0;


	printf("*********\n");
	printf("���׷��̺�\n");
	printf("*********\n");


	//while�� �ȿ� �ְ� �Ǹ� srand�� �õ尪�� �ʱ�ȭ�� �Ǵ� �ӵ����� while���� ���ư��� �ӵ��� �� ������ ������ ����� �۵����� �ʴ´�.
	srand((unsigned int)time(NULL));

	while (1)
	{
		if (p.hp <= 0)
		{
			printf("%s YOU DIED\n",p.name);
			exit(1);

		}
		printf("\n����� ����� ��������.\n");
		Sleep(1000);

		int eventKey = rand() % 5;

		switch (eventKey)
		{
			case 0:
				printf("\n %s�� ���� ���ڸ� ����\n", p.name);
				Sleep(1000);
				p.gold += 100;

				printf("���� �� : %d\n", p.gold);
				Sleep(1000);

				printf("�������� �̵�\n");
				Sleep(1000);
				break;

			case 1:
				printf("\n ������ ȹ��\n", p.name);
				Sleep(1000);
				p.gold += 100;

				printf("���� �� : %d\n", p.gold);
				Sleep(1000);

				printf("�������� �̵�\n");
				Sleep(1000);
				break;

			case 4:
				break;


		}

	}



}