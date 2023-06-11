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
void youDied();
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
	{"1100000111111111111111000000000000000000000001110000000000T00000000000000000011"},
	{"1100K00111111111111111000000000000000000000001110000000000T00000000000000000011"},
	{"11000001111110T00000000000000000F0000000000000000000000000T00000000000000B00011"},
	{"11000001111110011111110000000000P0000000000001110000000000T00000000000000000011"},
	{"11000T0000T00001111111000000000000000000000001110000000000T00000000000000000011"},
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

stWeapon sword = { "직검",50,40,4};
stWeapon dagger = { "단검",10,20,1};
stWeapon greatSword = { "대검",100,70,10};
stWeapon club = { "나무몽둥이",30,50,3};
stBow bow = { "활",50,2,20 };

struct job
{
	char name[25];
	int exp;
	int hp;
	int stamina;
	int atk;
	int ag;
	int def;
	stWeapon* jobWpn;
	stBow* jobWpn2;

};

job warrior = {"전사",4,110,12,13,13,11,&greatSword};
job knight = { "기사",5,140,10,11,11,10,&sword };
job thief = { "도적",5,90,9,9,16,10,&dagger };
job hunter = { "사냥꾼",4,110,11,12,14,11,&dagger,&bow };
job bum = { "거지",6,110,11,11,11,11,&club };

struct player
{
	char name[255];
	job* playerJob;

}p;

struct enemy
{
	int hp;
	int exp;
	stWeapon weapon;
	int x;
	int y;
	bool isInit;
};

enemy mob[4] =
{
	{150,50,sword,0,0,false},
	{90,50,dagger,0,0,false},
	{110,50,club,0,0,false},
	{200,50,greatSword,0,0,false}
};
int mobCount = 0;

//사망시 떨구는 소울 위치와 값 정보 
struct strSoul
{
	int x;
	int y;
	int exp;

}soul;

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
	clean();
	gotoxy(5, 5);
	printf("당신의 이름 : ");
	scanf_s("%s", &p.name,sizeof(p.name));

	clean();
	printf("1. 전사\n");
	printf("2. 기사\n");
	printf("3. 도적\n");
	printf("4. 사냥꾼\n");
	printf("5. 거지\n");

	printf("당신의 직업 (숫자로 선택) : ");
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

	printf("당신의 직업은 %s 입니다. \n",p.playerJob->name);
	Sleep(1000);
	inGame();

}

void info()
{
	system("cls");
	
	gotoxy(0, 0);

	printf("진행 \n");
	printf("화톳불(F)에서 휴식을 취할 수 있다. 체력이 전부 회복되고 가진 소울로 스탯을 찍을 수 있지만\n");
	printf("보스를 제외한 몬스터들도 다시 소환된다.\n\n");
	printf("잠긴 문은 반대편에서 열거나 열쇠를 찾으면 열 수 있다.");
	printf("보스를 잡으면 게임 클리어\n");


	printf("전투 \n");
	printf("회피,방어,공격 같은 행동에 지구력을 소모한다. 지구력이 모두 떨어지면 회복까지 기다려야 한다.\n");
	printf("회피는 성공시 스테미나를 소모하며 스테미나가 없어도 계속 발동 할 수 있다. 그러나 스테미나 회복에 방해가 될 수 있다.\n\n");
	printf("회복속도는 민첩성에 따라 달라진다.\n");
	printf("낮은 확률로 패링에 성공시, 일반 공격의 3배에 달하는 데미지를 입힐 수 있다.\n");
	printf("사망 시 현재 가지고 있던 모든 소울을 잃으며 상대 몬스터의 자리에 소울이 남아있게 된다. 회수하면 다시 잃어버린 만큼의 소울을 획득한다.\n");


	printf("직업 설명\n\n");
	printf("전사 - 강력한 공격력을 가지지만 무거운 대검을 들었다\n");
	printf("기사 - 평균적인 신체력을 가진 자. 직검을 가지고 시작한다.\n");
	printf("도적 - 짧지만 빠른 공격이 가능한 단검을 들고 있다. 민첩하다.\n");
	printf("사냥꾼 - 횟수 제한이 있지만 활을 쏠 수 있다.\n");
	printf("거지 - 아무것도 가지지 못한 자. 그러나 모든 부분에 있어서 고른 신체능력을 가지고 있다.\n");


	printf("\n 계속하려면 x키를 누르세요...\n");

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

	setColor(BRIGHTWHITE, BLACK); // 플레이어 색상 설정

	gotoxy(*playerX, *playerY);

	printf("@"); // 플레이어 그리기

	for (int i = 0; i < 20; i++) 
	{
		for (int j = 0; j < 80; j++) 
		{
			if (map[i][j] == '0') 
			{
				setColor(WHITE, BLACK); // 벽 색상 설정
				gotoxy(j, i);
				printf(" "); // 벽 그리기
			}
			else if (map[i][j] == '1') 
			{
				setColor(BLUE, BLACK); // 장애물 색상 설정
				gotoxy(j, i);
				printf("#"); // 장애물 그리기
			}
			//T = 몬스터가 살아있다는 뜻, . = 몬스터가 죽었다는 뜻
			else if (map[i][j] == 'T') 
			{
				setColor(RED, BLACK); // 몬스터 색상 설정
				gotoxy(j, i);
				printf("T");
				 // 몬스터 그리기
			}

			else if (map[i][j] == '.')
			{
				setColor(RED, BLACK);
				gotoxy(j, i);

				printf(".");
			}
			else if (map[i][j] == 'C') 
			{
				setColor(BRIGHTYELLOW, BLACK);
				gotoxy(j, i);
				printf("C"); // 경험치 상자 그리기
			}
			
			else if (map[i][j] == 'F') 
			{
				setColor(BRIGHTRED, BLACK); // 화톳불 색상 설정
				gotoxy(j, i);
				printf("F"); // 화톳불 그리기
			}
			else if (map[i][j] == 'B') 
			{
				setColor(GREEN, BLACK); // 보스 색상 설정
				gotoxy(j, i);
				printf("B"); // 보스 그리기
			}
		}
	}

	setColor(BRIGHTWHITE, BLACK); // 플레이어 색상 설정
	gotoxy(*playerX, *playerY);
	printf("@"); // 플레이어 그리기
	if(mobCount >= 10) mobCount = 0;
}
	
void inGame()
{
	int x = 39; // 플레이어 초기 위치 X 좌표 (중앙)
	int y = 9;  // 플레이어 초기 위치 Y 좌표 (중앙)

	mapDrawer(&x, &y); // 초기 맵 그리기

	while (1)
	{
		UI(); // UI 그리기

		char input = getKey(); // 키 입력 받기

		// 플레이어 이동 처리
		switch (input)
		{
		case UP:
			if (y > 0 && map[y - 1][x] != '1') y--;
			break;
		case DOWN:
			if (y < 19 && map[y + 1][x] != '1') y++;
			break;
		case LEFT:
			if (x > 0 && map[y][x - 1] != '1') x--;
			break;
		case RIGHT:
			if (x < 79 && map[y][x + 1] != '1') x++;
			break;
		}

		if (map[y][x] == 'T')
		{
			battle(&p,x,y);
		
		}

		mapDrawer(&x, &y); // 맵 그리기
	}
}

void UI()
{
	gotoxy(0, 20);
	gotoxy(1, 21);
	printf("이름 : %s    직업: %s  HP :  %d   지구력 :  %d  현재 소울 : %d", p.name, p.playerJob->name, p.playerJob->hp, p.playerJob->stamina,p.playerJob->exp);


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

		switch (p.playerJob->jobWpn->weight < rand() % 4)
		{
		case 0:

			printf("플레이어가 %s로 적을 공격!\n", fp->playerJob->jobWpn->name);

			fp->playerJob->stamina -= p.playerJob->jobWpn->weight;

			Sleep(500);

			if (fp->playerJob->jobWpn->length > (rand() % 80))
			{

				fEnm.hp -= pAtk;
				printf("적이 %d의 피해를 입었다.\n", pAtk);
				Sleep(500);
			}
			else printf("적이 회피했다.\n");
			Sleep(500);
			break;

		default:
			int enmAtk = fEnm.weapon.atk;
			int pDef = fp->playerJob->def;
			int pAg = fp->playerJob->ag;

			printf("상대방이 %s로 공격!\n", fEnm.weapon.name);
			Sleep(500);
			if ((rand() % 8) + pAg <= 17)
			{
				if (rand() % 6 == 0)
				{
					printf("팅!!\n");
					printf("적의 공격을 튕겨내자 적의 자세가 무너졌다.\n");
					Sleep(1000);
					int crit = (fp->playerJob->jobWpn->atk) * 3;
					fEnm.hp -= crit;
					printf("그 틈에 일격을 가한다. 적에게 %d만큼의 치명타를 날렸다.\n", crit);
					Sleep(500);
				}
				else
				{
					int damage = enmAtk - pDef;
					fp->playerJob->hp -= damage;
					printf(" %d 만큼의 피해를 입었다.\n", damage);
					Sleep(500);
				}
			}
			else
			{
				printf("공격을 회피했다.\n");
				Sleep(500);
			}

			printf("플레이어의 체력: %d\n", fp->playerJob->hp);
			printf("적의 체력: %d\n\n", fEnm.hp);
			Sleep(500);
		}

		fp->playerJob->stamina += fp->playerJob->ag;
	}

	if (fp->playerJob->hp <= 0)
	{
		printf("------------------------------------\n");
		printf("			YOU DIED						\n");
		printf("------------------------------------\n");


		for (int i = 0; i < 8; i++)
			fEnm.isInit = false;
		inGame();
	}
	else
	{
		printf("전투에서 승리했다!\n");
		fp->playerJob->exp += fEnm.exp;
		printf(" %d소울을 얻었다.\n", fEnm.exp);
		map[y][x] = '.';
	}

}

char getKey()
{
	char key = _getch(); // 키보드 입력 받기

	// 특수 키 처리
	if (key == 0 || key == -32)
	{
		key = _getch();
		switch (key)
		{
		case 72: // 위쪽 화살표 키
			return UP;
		case 80: // 아래쪽 화살표 키
			return DOWN;
		case 75: // 왼쪽 화살표 키
			return LEFT;
		case 77: // 오른쪽 화살표 키
			return RIGHT;
		}
	}

	return key;
}

void youDied()
{

	


}





