#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

#define KEY_INPUT_NUMBER 224

void gotoxy(int x,int y);
void title();
void gameStart();
char getKey();
void info();
void menu(int y);
void clean();
int input();
void mapDrawer(int* playerX, int* playerY);
void inGame();
void UI();
void fire();
void doorLock(int x,int y);
void setColor(int colorNum, int backNum);
void bossFight();


char map[20][80] =
{
	{"1111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"1000000000000000000000011111111000000000000000000000000000000000000000000000001"},
	{"100000000000000000000001111111100000000001111111111111000000000000000000T000001"},
	{"11100111111111111111100111111110000000000111111111111100000000000000000TCT00001"},
	{"111001111111111111111000000000000000000001111111111111000000000000000000T000001"},
	{"111001111111111111111000000000000T000000011111111111110000000000000000000000001"},
	{"1110011111111111111111111111111110111111111111111111111111111111111111111111111"},
	{"11000001111111111111110000000000000000000000011100000000TTT00000000000000000011"},
	{"1100K001111111111111110000000000000000000000011100000000TTT00000000000000000011"},
	{"11000001111110T00000000000000000F00000000000000000000000TTT00000000000000B00011"},
	{"11000001111110011111110000000000P00000000000011100000000TTT00000000000000000011"},
	{"11000T0000T000011111110000000000000000000000011100000000TTT00000000000000000011"},
	{"111111111111101111111111111111111L111111111111111111111111111111111111001111111"},
	{"1111111111000011111111110000000000000000011110000000000000000000000000000000001"},
	{"1111111111000011111111110000000000000000011110000000000000000000000000000000001"},
	{"1111111111000000000000000000000000000000000000000000001111111111111111111111111"},
	{"1111111111000000000000000001111111000000011110000000001111111111111111111111111"},
	{"1111111111000000000111111111111111111111111111111111111111111111111111111111111"},
	{"1111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"1111111111111111111111111111111111111111111111111111111111111111111111111111111"}

};

enum keyInput
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77
};

enum palette
{
	BLACK,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	PINK,
	ORANGE,
	WHITE,
	GRAY,
	LIGHTBLUE,
	BRIGHTGREEN,
	SKY,
	BRIGHTRED,
	BRIGHTPINK,
	BRIGHTYELLOW,
	BRIGHTWHITE

};

struct stWeapon
{
	char name[25];
	int atk;
	int length;
	int weight;
};


stWeapon sword = { "����",60,45,4};
stWeapon dagger = { "�ܰ�",35,35,3};
stWeapon greatSword = { "���",80,60,5};
stWeapon club = { "����������",40,55,2};

struct job
{
	char name[25];
	int exp;
	int hp;
	int maxHp;
	int stamina;
	int atk;
	int ag;
	int def;
	stWeapon* jobWpn;

};

job warrior = {"����",4,110,110,12,13,13,11,&greatSword};
job knight = { "���",5,140,140,10,11,11,10,&sword };
job thief = { "����",5,90,90,9,9,16,8,&dagger };
job bum = { "����",6,110,110,11,11,11,5,&club };

struct player
{
	char name[255];
	job* playerJob;
	bool isDead;

}p;

struct enemy
{
	int hp;
	int exp;
	stWeapon weapon;
	int x;
	int y;
};

enemy mob[4] =
{
	{150,60,sword,0,0},
	{90,40,dagger,0,0},
	{110,70,club,0,0},
	{200,150,greatSword,0,0}
};

int lostSouls = 0;
int requireSouls = 100;
int deathSpotX = 0;
int deathSpotY = 0;
bool isKey = false;
bool isUnlocked = false;
bool isRest = false;
bool isRespawn = false;

void battle(player* fp,int x,int y);


int main()
{
	CONSOLE_CURSOR_INFO ConsoleCursor;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

	title();
	printf("\n");
	printf("\n");
	printf("\n");
	printf("			     PRESS ANY BUTTON											\n");

	while (1)
	{
		if (_kbhit())
		{
			system("cls");
			break;
		}
	}

	menu(11);


	return 0;
}


void gotoxy(int x, int y)

{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}


void title()
{
	printf("######      ##    ######   ###  ##            #####    #####    ##  ##   ####     #####   \n");
	printf(" ##  ##    ####    ##  ##   ## ##            ##   ##  ##   ##   ##  ##    ##     ##   ##  \n");
	printf(" ##  ##   ##  ##   ##  ##   ####             ##       ##   ##   ##  ##    ##     ##        \n");
	printf(" ##  ##   ######   #####    ###               #####   ##   ##   ##  ##    ##      #####   \n");
	printf(" ##  ##   ##  ##   ####     ####                  ##  ##   ##   ##  ##    ##          ##  \n");
	printf(" ##  ##   ##  ##   ## ##    ## ##            ##   ##  ##   ##   ##  ##    ## ##  ##   ##   \n");
	printf("######    ##  ##  ###  ##  ###  ##            #####    #####     ####    ######   #####   \n");
}

void gameStart()
{
	system("cls");
	gotoxy(5, 5);
	printf("����� �̸� : ");
	scanf_s("%s", &p.name,sizeof(p.name));

	system("cls");
	printf("1. ����\n");
	printf("2. ���\n");
	printf("3. ����\n");
	printf("4. ����\n");

	printf("����� ���� (���ڷ� ����) : ");
	int num = 0;
	scanf_s("%d", &num);

	switch (num)
	{
	case 1:
		p.playerJob = &warrior;
		break;
	case 2:
		p.playerJob = &knight;
		break;
	case 3:
		p.playerJob = &thief;
		break;
	case 4:
		p.playerJob = &bum;
		break;

	}

	printf("����� ������ %s �Դϴ�. \n",p.playerJob->name);
	p.isDead = false;
	Sleep(1000);
	inGame();

}

void info()
{
	system("cls");
	
	gotoxy(0, 0);

	printf("***����*** \n");
	printf("ȭ���(F)���� �޽��� ���� �� �ִ�. ü���� ���� ȸ���ǰ� ���� �ҿ�� ������ ���� �� ������\n");
	printf("������ ������ ���͵鵵 �ٽ� ��ȯ�ȴ�.\n");
	printf("��� ���� ����(K)�� ã���� �� �� �ִ�.\n");
	printf("������ ������ ���� Ŭ����\n\n");


	printf("***����*** \n");
	printf("ȸ�Ǵ� �������� ���� ���� ���ɼ��� ��������.\n");
	printf("���� Ȯ���� �и��� ������, �Ϲ� ������ 3�迡 ���ϴ� �������� ���� �� �ִ�.\n");
	printf("��� �� ���� ������ �ִ� ��� �ҿ��� ������ ��� ������ �ڸ��� �ҿ��� �����ְ� �ȴ�. ȸ���ϸ� �ٽ� �Ҿ���� ��ŭ�� �ҿ��� ȹ���Ѵ�.\n");
	printf("�ݸ鿡 �ҿ��� �Ҿ���� ���·� �ٽ� �׾��� ���, �ҿ��� ȸ���ϴ��� �ƹ��͵� ���� �� ����.\n\n");


	printf("***���� ����***\n");
	printf("���� - ������ ���ݷ��� �������� ���ſ� ����� �����\n");
	printf("��� - ������� ��ü���� ���� ��. ������ ������ �����Ѵ�.\n");
	printf("���� - ª���� ���� ������ ������ �ܰ��� ��� �ִ�. �������� ����.\n");
	printf("���� - �ƹ��͵� ������ ���� ��. �׷��� ��� �κп� �־ �� ��ü�ɷ��� ������ �ִ�.\n");


	printf("\n ����Ϸ��� xŰ�� ��������...\n");

	while (1)
	{
		if (_kbhit())
		{
			system("cls");
			break;
		}
	}

	menu(11);


}

void menu(int y)
{
	title();
	printf("\n\n\n");

	gotoxy(9, 11);
	printf("NEW GAME			\n");
	gotoxy(9, 12);
	printf("INFO					\n");
	gotoxy(9, 13);
	printf("QUIT                  \n");

	gotoxy(7, y);

	printf(">");

	while (1)
	{
		int selection = input();
		switch (selection)
		{
		case DOWN:
			if (y < 13)
			{
				y++;
				system("cls");
				menu(y);
			}
			break;
		case UP:
			if (y > 11)
			{
				y--;
				system("cls");
				menu(y);
			}
			break;
		case 'z':
			if (y == 11)
			{
				gameStart();
				break;
			}
			else if (y == 12)
			{
				info();
				break;
			}
			else if (y == 13)
			{
				exit(0);
			}

		}

	}
	
}

void clean()
{
		for (int i = 24; i < 35; i++) 
		{
			gotoxy(0, i);
			printf("                                                                                          ");
		}
		gotoxy(0, 0);
}

int input()
{
			char in = _getch();
			
			if (in == KEY_INPUT_NUMBER)
			{
				in = _getch();
				switch (in)
				{
				case UP:
					printf("%d", in);
					in = UP;
					return in;
				case DOWN:
					printf("%d", in);
					in = DOWN;
					return in;
				case LEFT:
					printf("%d", in);
					in = LEFT;
					return in;
				case RIGHT:
					printf("%d", in);
					in = RIGHT;
					return in;
				}

			}
}


void mapDrawer(int* playerX, int* playerY)
{

	setColor(BRIGHTWHITE, BLACK); // �÷��̾� ���� ����

	gotoxy(*playerX, *playerY);

	printf("@"); // �÷��̾� �׸���

	for (int i = 0; i < 20; i++) 
	{
		for (int j = 0; j < 80; j++) 
		{
			if (map[i][j] == '0') 
			{
				setColor(WHITE, BLACK); // �� ���� ����
				gotoxy(j, i);
				printf(" "); // �� �׸���
			}
			else if (map[i][j] == '1') 
			{
				setColor(WHITE, WHITE); // ��ֹ� ���� ����
				gotoxy(j, i);
				printf("#"); // ��ֹ� �׸���
			}
			//T = ���Ͱ� ����ִٴ� ��, . = ���Ͱ� �׾��ٴ� ��
			else if (map[i][j] == 'T') 
			{
				setColor(RED, BLACK); // ���� ���� ����
				gotoxy(j, i);
				printf("T");
				 // ���� �׸���
			}
			else if (map[i][j] == '.')
			{
				setColor(RED, BLACK);
				gotoxy(j, i);

				if (p.isDead || isRespawn)
				{
					map[i][j] = 'T';
				}
				else printf(".");
			}
			else if (map[i][j] == '$')
			{
				setColor(BRIGHTGREEN, BLACK);
				gotoxy(j, i);
				printf("$");
			}
			else if (map[i][j] == 'C') 
			{
				setColor(BRIGHTYELLOW, BLACK);
				gotoxy(j, i);
				printf("C"); // ����ġ ���� �׸���
			}
			
			else if (map[i][j] == 'F') 
			{
				setColor(BRIGHTRED, BLACK); // ȭ��� ���� ����
				gotoxy(j, i);
				printf("F"); // ȭ��� �׸���
			}
			else if (map[i][j] == 'L')
			{
				setColor(BRIGHTWHITE, BLACK);
				gotoxy(j, i);
				if (isUnlocked) map[i][j] = '0';
				else printf("L");
			}
			else if (map[i][j] == 'B') 
			{
				setColor(GREEN, BLACK); // ���� ���� ����
				gotoxy(j, i);
				printf("B"); // ���� �׸���
			}
			else if (map[i][j] == 'K')
			{
				setColor(SKY, BLACK);
				gotoxy(j, i);
				printf("K");
			}
		}
	}
	isRespawn = false;
	p.isDead = false;
	setColor(BRIGHTWHITE, BLACK); // �÷��̾� ���� ����
	gotoxy(*playerX, *playerY);
	printf("@"); // �÷��̾� �׸���
}
	
void inGame()
{
	int x = 39; // �÷��̾� �ʱ� ��ġ X ��ǥ (�߾�)
	int y = 9;  // �÷��̾� �ʱ� ��ġ Y ��ǥ (�߾�)

	mapDrawer(&x, &y); // �ʱ� �� �׸���

	while (1)
	{
		UI(); // UI �׸���

		char input = getKey(); // Ű �Է� �ޱ�

		// �÷��̾� �̵� ó��
		switch (input)
		{
		case UP:
			if (y > 0 && map[y - 1][x] != '1') 
				if(map[y - 1][x] != 'L') y--;
			break;
		case DOWN:
			if (y < 19 && map[y + 1][x] != '1')
				if(map[y + 1][x] != 'L') y++;
			break;
		case LEFT:
			if (x > 0 && map[y][x - 1] != '1') x--;
			break;
		case RIGHT:
			if (x < 79 && map[y][x + 1] != '1') x++;
			break;
		}

		if (map[y][x] == 'T' || map[y][x] == '$')
		{
			battle(&p, x, y);
		}

		if (map[y - 1][x] == 'L' || map[y + 1][x] == 'L')
		{
			doorLock(x, y);
		}

		if (map[y][x] == 'K')
		{
			isKey = true;
			gotoxy(0, 24);
			printf("���踦 ȹ���ߴ�.\n");
			map[y][x] = '0';
		}

		if (map[y][x] == 'F')
		{
			isRest = true;
			fire();
		}

		if (map[y][x] == 'B') bossFight();

		mapDrawer(&x, &y); // �� �׸���
	}
}

void UI()
{
	gotoxy(1, 21);
	printf("------------------------------------------------------------------------------------\n");
	printf("�̸� : %s  ����: %s  HP :  %d   ���� ����: %s  ���� �ҿ� : %d", p.name, p.playerJob->name, p.playerJob->hp, p.playerJob->jobWpn->name,p.playerJob->exp);


}

void fire()
{
	
		isRespawn = true;
		p.playerJob->hp = p.playerJob->maxHp;
		
		while (isRest)
		{
			gotoxy(0, 24);
			printf("�ø� �ɷ�ġ�� ����: ü��(x) , ������(c), ������(v) \n �ʿ� �ҿ� : %d\n",requireSouls);

			switch (input())
			{
				case 'x':
					if (p.playerJob->exp >= requireSouls)
					{
						printf("�ִ� ü���� 10��ŭ �����ߴ�.\n");
						p.playerJob->maxHp += 10;
						p.playerJob->exp -= requireSouls;
						requireSouls += 50;
						Sleep(500);
						clean();
					}
					else
					{
						printf("�ҿ��� �����ϴ�.\n");
						Sleep(500);
						clean();
						break;
					}
					break;
				case 'c':
					if (p.playerJob->exp >= requireSouls)
					{
						printf("�������� 1��ŭ �����ߴ�.\n");
						p.playerJob->ag += 1;
						p.playerJob->exp -= requireSouls;
						requireSouls += 50;
						Sleep(500);
						clean();
					}
					else
					{
						printf("�ҿ��� �����ϴ�.\n");
						Sleep(500);
						clean();
						break;
					}
					break;

				case 'v':
					printf("ȭ��� �տ��� �Ͼ��.\n");
					Sleep(500);
					clean();
					isRest = false;
					break;
			}

		}
}

void doorLock(int x, int y)
{

	gotoxy(0, 24);

	if (isKey)
	{
		printf("���踦 ����ߴ�.");
		Sleep(500);
		clean();
		isUnlocked = true;
	}
}

void setColor(int colorNum,int backNum)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (backNum<<4) + colorNum);
}

void battle(player* fp, int x, int y)
{
	gotoxy(0, 24);

	enemy fEnm = mob[rand() % 4];

	while (fEnm.hp > 0 && fp->playerJob->hp > 0)
	{
		srand((unsigned int)time(NULL));
		int pAtk = fp->playerJob->jobWpn->atk;

		switch (rand() % p.playerJob->jobWpn->weight)
		{
		case 0:

			printf("�÷��̾ %s(��)�� ���� ����!\n", fp->playerJob->jobWpn->name);

			Sleep(500);

			if (fp->playerJob->jobWpn->length + fp->playerJob->ag >= (rand() % 50))
			{

				fEnm.hp -= pAtk;
				printf("���� %d�� ���ظ� �Ծ���.\n", pAtk);
				Sleep(500);
			}
			else printf("���� ȸ���ߴ�.\n");
			Sleep(500);
			break;

		default:
			int enmAtk = fEnm.weapon.atk;
			int pDef = fp->playerJob->def;
			int pAg = fp->playerJob->ag;

			printf("������ %s(��)�� ����!\n", fEnm.weapon.name);
			Sleep(500);
			if (rand() % pAg < 10)
			{
				if (rand() % 6 == 0)
				{
					printf("��!!\n");
					printf("���� ������ ƨ�ܳ��� ���� �ڼ��� ��������.\n");
					Sleep(1000);
					int crit = (fp->playerJob->jobWpn->atk) * 3;
					fEnm.hp -= crit;
					printf("�� ƴ�� �ϰ��� ���Ѵ�. ������ %d��ŭ�� ġ��Ÿ�� ���ȴ�.\n", crit);
					Sleep(1000);
				}
				else
				{
					int damage = enmAtk - pDef;
					fp->playerJob->hp -= damage;
					printf(" %d ��ŭ�� ���ظ� �Ծ���.\n", damage);
					Sleep(500);
				}
			}
			else
			{
				printf("������ ȸ���ߴ�.\n");
				Sleep(500);
			}
			break;

		}

		printf("�÷��̾��� ü��: %d\n", fp->playerJob->hp);
		printf("���� ü��: %d\n\n", fEnm.hp);
		Sleep(1000);
	}

	if (fp->playerJob->hp <= 0)
	{
		printf("------------------------------------\n");
		printf("	   YOU DIED				             \n");
		printf("------------------------------------\n");
		Sleep(1500);

		fp->playerJob->hp = fp->playerJob->maxHp;
		lostSouls = fp->playerJob->exp;
		fp->playerJob->exp = 0;

		if (deathSpotX > 0 && deathSpotY > 0) map[deathSpotX][deathSpotY] = 'T';

		deathSpotX = y;
		deathSpotY = x;

		map[y][x] = '$';

		system("cls");
		fp->isDead = true;
		inGame();
	}
	else
	{
		printf("�������� �¸��ߴ�!\n");

		if (map[y][x] == '$')
		{
			fp->playerJob->exp += fEnm.exp + lostSouls;
			lostSouls = 0;
			printf("****LOST SOULS ACHIEVED**** \n");
			printf(" %d�ҿ��� �����.\n", fEnm.exp);
		}
		else
		{
			fp->playerJob->exp += fEnm.exp;
			printf(" %d�ҿ��� �����.\n", fEnm.exp);
		}
		Sleep(1000);
		map[y][x] = '.';
		system("cls");
	}

}

char getKey()
{
	char key = _getch(); // Ű���� �Է� �ޱ�

	// Ư�� Ű ó��
	if (key == 0 || key == -32)
	{
		key = _getch();
		switch (key)
		{
		case 72: // ���� ȭ��ǥ Ű
			return UP;
		case 80: // �Ʒ��� ȭ��ǥ Ű
			return DOWN;
		case 75: // ���� ȭ��ǥ Ű
			return LEFT;
		case 77: // ������ ȭ��ǥ Ű
			return RIGHT;
		}
	}

	return key;
}

void bossFight()
{
	srand((unsigned int)time(NULL));
	clean();

	gotoxy(0, 24);
	printf("����� �ҸӸ� ������ ������.\n");
	Sleep(1000);

	if (rand() % 3 == 0)
	{
		printf("����� ������ ���� ���� ������ óġ�� �� �־���.\n");
		Sleep(1000);
		exit(0);
	}
	else
	{
		printf("����� ����� ������ �ο����� �ᱹ �װ� ���Ҵ�...\n");
		Sleep(1000);
		p.playerJob->exp = 0;
		inGame();

	}
		




}




