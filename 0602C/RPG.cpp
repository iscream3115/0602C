#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

#define KEY_INPUT_NUMBER 224

void gotoxy(int x,int y);
void title();
void  gameStart();
char getKey();
void info();
void menu(int y);
void clean();
int input();
void mapDrawer(int playerX, int playerY);
void inGame();
void UI();
void setColor(int colorNum, int backNum);


char map[20][80] =
{
	{"1111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"1000000000000000000000011111111000000000000000000000000000000000000000000000001"},
	{"100000000000000000000001111111100000000001111111111111000000000000000000T000001"},
	{"11100111111111111111100111111110000000000111111111111100000000000000000TCT00001"},
	{"111001111111111111111000000000000000000001111111111111000000000000000000T000001"},
	{"1110011111111111111110000000000000000000011111111111110000000000000000000000001"},
	{"1110011111111111111111111111111110011111111111111111111111111111111111111111111"},
	{"1100000111111111111111000000000000000000000001110000000000000000000000000000011"},
	{"1100000111111111111111000000000000000000000001110000000000000000000000000000011"},
	{"11000001111110T00000000000000000F0000000000000000000000000000000000000000B00011"},
	{"11000001111110011111110000000000P0000000000001110000000000000000000000000000011"},
	{"11000T0000T00001111111000000000000000000000001110000000000000000000000000000011"},
	{"111111111111101111111111111111111L111111111111111111111111111111111111001111111"},
	{"1111111111000011111111110000000000000000011110000000000000000000000000000000001"},
	{"1111111111000011111111110000000000000000011110000000000000000000000000000000001"},
	{"11111111110000000000000000000000000000000000D0000000001111111111111111111111111"},
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

struct stBow
{
	char name[25];
	int atk;
	int weight;
	int magazine;
};

stWeapon sword = { "����",50,50,4};
stWeapon dagger = { "�ܰ�",10,20,1};
stWeapon greatSword = { "���",100,80,10};
stWeapon club = { "����������",30,60,3};
stBow bow = { "Ȱ",50,2,20 };

struct job
{
	char name[25];
	int exp;
	int hp;
	int mp;
	int stamina;
	int atk;
	int ag;
	int def;
	stWeapon* jobWpn;
	stBow* jobWpn2;

};

job warrior = {"����",4,11,8,12,13,13,11,&greatSword};
job knight = { "���",5,14,10,10,11,11,10,&sword };
job thief = { "����",5,9,11,9,9,16,10,&dagger };
job hunter = { "��ɲ�",4,11,9,11,12,14,11,&dagger,&bow };
job bum = { "����",6,11,11,11,11,11,11,&club };

struct player
{
	char name[255];
	job* playerJob;

}p;


int main()
{

	srand((unsigned int)time(NULL));
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
	clean();
	gotoxy(5, 5);
	printf("����� �̸� : ");
	scanf_s("%s", &p.name,sizeof(p.name));

	clean();
	printf("1. ����\n");
	printf("2. ���\n");
	printf("3. ����\n");
	printf("4. ��ɲ�\n");
	printf("5. ����\n");

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
		p.playerJob = &hunter;
		break;
	case 5:
		p.playerJob = &bum;
		break;

	}

	printf("����� ������ %s �Դϴ�. \n",p.playerJob->name);
	Sleep(1000);
	inGame();

}

void info()
{
	system("cls");
	
	gotoxy(5, 5);
	printf("����: �����¿� - �̵� , Z - �׼� �� ����\n\n");
	printf("���� ����\n\n");
	printf("���� - ������ ���ݷ��� �������� ���ſ� ����� �����\n");
	printf("��� - ������� ��ü���� ���� ��. ������ ������ �����Ѵ�.\n");
	printf("���� - ª���� ���� ������ ������ �ܰ��� ��� �ִ�. ��ø�ϴ�.\n");
	printf("��ɲ� - Ƚ�� ������ ������ Ȱ�� �� �� �ִ�.\n");
	printf("���� - �ƹ��͵� ������ ���� ��. �׷��� ��� �κп� �־ �� ��ü�ɷ��� ������ �ִ�.\n");

	printf("\n��� �Ϸ��� �ƹ�Ű�� ��������.\n");

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
				return;
			}

		}

	}
	
}

void clean()
{
		for (int i = 0; i < 24; i++) 
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

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 80; j++) {
			if (map[i][j] == '0') {
				setColor(WHITE, BLACK); // �� ���� ����
				gotoxy(j, i);
				printf(" "); // �� �׸���
			}
			else if (map[i][j] == '1') {
				setColor(BLUE, BLACK); // ��ֹ� ���� ����
				gotoxy(j, i);
				printf("#"); // ��ֹ� �׸���
			}
			else if (map[i][j] == 'T') {
				setColor(RED, BLACK); // ���� ���� ����
				gotoxy(j, i);
				printf("T"); // ���� �׸���
			}
			else if (map[i][j] == 'C') {
				setColor(RED, BLACK); // ����ġ ���� ���� ����
				gotoxy(j, i);
				printf("C"); // ����ġ ���� �׸���
			}
			else if (map[i][j] == 'F') {
				setColor(BRIGHTRED, BLACK); // ������ ���� ����
				gotoxy(j, i);
				printf("F"); // ������ �׸���
			}
			else if (map[i][j] == 'B') {
				setColor(GREEN, BLACK); // ���� ���� ����
				gotoxy(j, i);
				printf("B"); // ���� �׸���
			}
		}
	}

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
			if (y > 0 && map[y - 1][x] != '1') // �������� �̵� ������ ���
				y--;
			break;
		case DOWN:
			if (y < 19 && map[y + 1][x] != '1') // �Ʒ������� �̵� ������ ���
				y++;
			break;
		case LEFT:
			if (x > 0 && map[y][x - 1] != '1') // �������� �̵� ������ ���
				x--;
			break;
		case RIGHT:
			if (x < 79 && map[y][x + 1] != '1') // ���������� �̵� ������ ���
				x++;
			break;
		}

		mapDrawer(&x, &y); // �� �׸���
	}
}

void UI()
{
	gotoxy(0, 20);
	printf("------------------------------------------------------------------------------------------------");
	gotoxy(1, 21);
	printf("�̸� : %s    ����: %s  HP :  %d   ���ݷ� :  %d", p.name, p.playerJob->name, p.playerJob->hp, p.playerJob->atk);


}

void setColor(int colorNum,int backNum)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (backNum<<4) + colorNum);
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
