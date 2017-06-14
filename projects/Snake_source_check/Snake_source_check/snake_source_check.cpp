#include <stdio.h>			/*<stdio.h> 스탠다드 인풋/아웃풋 헤더 포함 (입출력 함수 printf, scanf 사용가능)*/
#include <time.h>			/*<time.h> 타임 헤더 포함 ( 시간관련 함수 time(NULL) 사용가능)*/
#include <windows.h>		/*<windows.h> 윈도우즈 헤더 포함 (소리 beep(주파수,재생시간) / 화면지우기 system(“CLS”) / 지연 Sleep(시간))*/

struct SnakeNode			/* 구조체 SnakeNode 정의 */
{
	int x;
	int y;
	struct SnakeNode *next; /* SnakeNode형 구조체 *next에 int x, int y 들어감 */
};

struct Food					/* 구조체 Food 정의 */
{
	int x;
	int y;
	int isEaten;
};

void Gotoxy(int column, int row);
/* void Gotoxy (가로, 세로) 함수 선언 [역할: 원하는 곳에 커서 찍어주는 함수] */
int CreateScoreFile();		/*int CreateScoreFile 함수 선언 [역할: Score File.txt 외부 파일 생성해주는 함수]*/
void CreateSnake(struct SnakeNode **snake);
/* void CreateSnake(SnakeNode 형 구조체 **snake) 함수 선언
[역할: 가로 27, 세로 10 위치에 snake 위치시켜주는 함수]*/
void Graphics(struct SnakeNode *snake, struct Food food, int score, int highscore, int life);
/* void Graphics (SnakeNode 형 구조체 *snake, Food 형 구조체 food, int score, int highscore) 함수 선언
[역할: snake의 움직임, food의 움직임, 점수, 최고점수를 dos 화면에 띄워주는 함수]*/
int isSnake(int x, int y, struct SnakeNode *snake);
/*int isSnake(int x, int y, SnakeNode 형 구조체 *ㄴsnake) 함수 선언
[역할: snake의 위치를 실시간으로 저장해주는 함수 - food의 위치와 일치할시 score 올라가게 하기 위해 필요]*/
void CreateFood(struct Food *food, struct SnakeNode *snake);
/*void CreateFood(Food 형 구조체 *food, SnakeNode 형 구조체 *snake) 함수 선언
[역할: food의 위치를 무작위로 배치해주는 함수]*/
int GetSnakeSize(struct SnakeNode *snake);
/*int GetSnakeSize(SnakeNode 형 구조체 *snake) 함수 선언
[역할: snake의 길이를 정해주는 함수]*/
struct SnakeNode * GetListItem(struct SnakeNode *snake, int index);
/*SnakeNode 형 구조체 포인터 GetListItem(SnakeNode 형 구조체 *snake, int index) 함수 선언
[역할: snake의 앞 node를 따라 그다음 node가 따라가게 해주는 함수]*/
int lose(struct SnakeNode *snake);
/*int lose(SnakeNode 형 구조체 *snake) 함수 선언
[역할: 닿으면 1, 안닿으면 0을 반환해 게임을 지속하거나 종료시키는 두 가지 경우의 변수를 제공하는 함수]*/
void SaveScore(int score);  /*void Savescore(int score) 함수 선언
							[역할: score를 특정한 경우에 외부 파일 Score File.txt로 입력 및 저장시켜주는 함수]*/
void Physics(struct SnakeNode **snake, int *direction, struct Food *food, int *score, int *highscore, int *endgame, int *life);
/*void Physics(SnakeNode 형 **snake, int *direction, Food형 구조체 *food, int *score, int *highscore, int *endgame) 함수 선언
[역할: 1. 키보드 입력에 따라 snake node가 움직이게 해주는 역할
2. food와 snake의 node의 위치가 일치하면 점수를 10 올려주는 역할,
3. snake node가 창을 벗어나면 그 반대 편으로 넘어가서 움직이도록 처리하는 역할
4. lose함수의 반환 값에 따라 게임을 지속하거나 종료시키게 하는 역할]*/
void DestroySnake(struct SnakeNode **snake);
/*void DestroySnake(SnakeNode 형 **snake) 함수 선언
[역할: SnakeNode형 구조체 **snake에 할당된 메모리 해제하는 역할]*/

char map[20][50] =			/*char형 2차원 전역 배열 map[20][50] 선언*/
{ "#################################################",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#                                               #",
"#################################################" };

int main()							/* 메인 함수 시작 */
{
	int endgame = 0;				/* int형 변수 endgame 선언 및 초기화 */
	int gamespeed = 33;				/* int형 변수 gamespeed 선언 및 변수 값에 25 대입 */
	int score = 0;					/* int형 변수 score 선언 및 초기화 */
	int highscore = 0;				/* int형 변수 highscore 선언 및 초기화 */
	int direction = 1;				/* int형 변수 direction 선언 및 변수 값에 1 대입 */
	int life = 2;
	struct SnakeNode *snake = NULL;	/* SnakeNode 형 구조체 *snake 선언 및 초기화(NULL) */
	struct Food food;				/* Food 형 구조체 food 선언 */

	food.isEaten = 1;				/* 구조체 food의 원소 isEaten의 값에 1 대입 */

	srand(time(NULL));				/* 이번 코드 이후 rand()값이 무작위로 되도록 설정 */

	highscore = CreateScoreFile();	/* highscore 변수에 CreateScoreFile()함수 값 대입 */

	CreateSnake(&snake);			/* CreateSnake(&snake)함수 실행 : 가로 27 세로 10 위치 에서 구조체 snake 놓임 */

	while (life >= 0)
	{

		int endgame = 0;				/* int형 변수 endgame 선언 및 초기화 */
		int gamespeed = 33;				/* int형 변수 gamespeed 선언 및 변수 값에 25 대입 */
		int score = 0;					/* int형 변수 score 선언 및 초기화 */
		int highscore = 0;				/* int형 변수 highscore 선언 및 초기화 */
		int direction = 1;				/* int형 변수 direction 선언 및 변수 값에 1 대입 */
		struct SnakeNode *snake = NULL;	/* SnakeNode 형 구조체 *snake 선언 및 초기화(NULL) */
		struct Food food;				/* Food 형 구조체 food 선언 */

		food.isEaten = 1;				/* 구조체 food의 원소 isEaten의 값에 1 대입 */

		srand(time(NULL));				/* 이번 코드 이후 rand()값이 무작위로 되도록 설정 */

		highscore = CreateScoreFile();	/* highscore 변수에 CreateScoreFile()함수 값 대입 */

		CreateSnake(&snake);			/* CreateSnake(&snake)함수 실행 : 가로 27 세로 10 위치 에서 구조체 snake 놓임 */
		do								/* 우선 아래의 식 실행 */
		{
			CreateFood(&food, snake);	/* CreateFood(&food, snake) 함수 실행 */
			Graphics(snake, food, score, highscore, life);
			/* Graphics(snake, food, score, highscore) 함수 실행 */
			Sleep(gamespeed);			/* gamespeed 값 만큼 화면 변화 지연 */
			system("cls");				/* 화면 지우기(windows.h 헤더 포함 필수)*/
			Physics(&snake, &direction, &food, &score, &highscore, &endgame, &life);
			/* Physics(&snake, &direction, &food, &score, &highscore, &endgame) 함수 실행 한 다음,*/
		} while (endgame == 0);			/* 이후에는 endgame이 0과 같다는 식이 참일 때까지 반복으로 실행
										endgame이 0과 같은 것이 거짓일 경우 while문 탈출 (아래의 식으로 실행)*/
		life--;

	}


	DestroySnake(&snake);			/* DestroySnake(&snake) 함수 실행 : **snake에 할당된 메모리 해제 */

	return 0;						/* 0 반환 */
}									/* 메인 함수 종료 */

void Gotoxy(int column, int row)	/* 원하는 곳에 커서 찍어주는 함수 */
{
	COORD c;

	c.X = column;
	c.Y = row;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int CreateScoreFile()				/* Score File.txt 외부 파일 생성해주는 함수 */
{
	FILE *scfile;
	int highscore = 0;

	scfile = fopen("Score file.txt", "r");

	if (scfile == NULL)
	{
		scfile = fopen("Score file.txt", "w");
		fprintf(scfile, "%d", highscore);
	}
	else
	{
		fscanf(scfile, "%d", &highscore);
	}

	fclose(scfile);

	return highscore;
}

void CreateSnake(struct SnakeNode **snake)	/* 가로 27, 세로 10 위치에 snake 위치시켜주는 함수*/
{
	struct SnakeNode *hnext = NULL;
	struct SnakeNode *hprev = NULL;

	int x = 27;
	int y = 10;
	int size = 0;

	*snake = (struct SnakeNode *)malloc(sizeof(struct SnakeNode));

	(*snake)->x = x;
	(*snake)->y = y;
	(*snake)->next = NULL;

	hprev = *snake;
	hnext = (*snake)->next;

	while (hnext != NULL || size < 4)
	{
		x--;

		hnext = (struct SnakeNode *)malloc(sizeof(struct SnakeNode));

		hnext->x = x;
		hnext->y = y;
		hnext->next = NULL;

		hprev->next = hnext;
		hprev = hnext;

		hnext = hnext->next;

		size++;
	}
}

void Graphics(struct SnakeNode *snake, struct Food food, int score, int highscore, int life) /* snake의 움직임, food의 움직임, 점수, 최고점수를 dos 화면에 띄워주는 함수 */
{
	int x, y;
	struct SnakeNode *temp = NULL;

	for (y = 0; y<20; y++)
	{
		for (x = 0; x<50; x++)
		{
			printf("%c", map[y][x]);
		}

		printf("\n");
	}

	Gotoxy(food.x, food.y);
	printf("$");

	temp = snake;

	while (temp != NULL)
	{
		Gotoxy(temp->x, temp->y);
		printf("*");

		temp = temp->next;
	}

	Gotoxy(0, 20);
	printf("\nScore: %d", score);

	if (score <= highscore)
	{
		printf(" ------ Highscore: %d", highscore);
		printf("LIFE : %d", life);
	}
	else
	{
		printf(" ------ Highscore: %d", score);
		printf("\tLIFE : %d", life);
	}
}

int isSnake(int x, int y, struct SnakeNode *snake) /* snake의 위치를 실시간으로 저장해주는 함수 - food의 위치와 일치할시 score 올라가게 하기 위해 필요 */
{
	struct SnakeNode *temp = NULL;

	temp = snake;

	while (temp != NULL)
	{
		if (temp->x == x && temp->y == y)
		{
			return 1;
		}

		temp = temp->next;
	}

	return 0;
}

void CreateFood(struct Food *food, struct SnakeNode *snake) /* food의 위치를 무작위로 배치해주는 함수 */
{
	if (food->isEaten)
	{
		food->x = rand() % 48 + 1;
		food->y = rand() % 18 + 1;
		food->isEaten = 0;

		do
		{
			if (isSnake(food->x, food->y, snake))
			{
				food->x = rand() % 48 + 1;
				food->y = rand() % 18 + 1;
			}
		} while (isSnake(food->x, food->y, snake));
	}
}

struct SnakeNode * GetListItem(struct SnakeNode *snake, int index) /* snake의 앞 node를 따라 그다음 node가 따라가게 해주는 함수 */
{
	int i;
	struct SnakeNode *node = NULL;

	node = snake;

	for (i = 0; i<index; i++)
	{
		node = node->next;
	}

	return node;
}

int GetSnakeSize(struct SnakeNode *snake) /* snake의 길이를 정해주는 함수 */
{
	int size = 0;

	while (snake != NULL)
	{
		size++;
		snake = snake->next;
	}

	return size;
}

int lose(struct SnakeNode *snake)		/* 닿으면 1, 안닿으면 0을 반환해 게임을 지속하거나 종료시키는 두 가지 경우의 변수를 제공하는 함수 */
{
	struct SnakeNode *iterator;

	iterator = snake->next;

	while (iterator != NULL)
	{
		if (snake->x == iterator->x && snake->y == iterator->y)
		{
			return 1;
		}

		iterator = iterator->next;
	}

	return 0;
}

void SaveScore(int score) /* score를 특정한 경우에 외부 파일 Score File.txt로 입력 및 저장시켜주는 함수 */
{
	FILE *savscore;
	int filescore;

	savscore = fopen("Score file.txt", "r");

	if (savscore != NULL)
	{
		fscanf(savscore, "%d", &filescore);

		if (score > filescore)
		{
			fclose(savscore);

			savscore = fopen("Score file.txt", "w");

			fprintf(savscore, "%d", score);
		}
	}

	fclose(savscore);
}

void Physics(struct SnakeNode **snake, int *direction, struct Food *food, int *score, int *highscore, int *endgame, int *life)
/*역할
1. 키보드 입력(RIGHT,LEFT,UP,DOWN)에 따라 snake node가 움직이게 해주는 역할
2. food와 snake의 node의 위치가 일치하면 점수를 10 올려주는 역할,
3. snake node가 창을 벗어나면 그 반대 편으로 넘어가서 움직이도록 처리하는 역할
4. lose함수의 반환 값에 따라 게임을 지속하거나 종료시키게 하는 역할*/
{
	int i;
	struct SnakeNode *lnode = NULL;
	struct SnakeNode *fnode = NULL;
	struct SnakeNode *nnode = NULL;

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (*direction == 3)
		{
			*endgame = 1;
			Graphics(*snake, *food, *score, *highscore, *life);
			SaveScore(*score);
			Beep(250, 250);
			Sleep(2000);
		}
		else
		{
			*direction = 1;
		}
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (*direction == 1)
		{
			*endgame = 1;
			Graphics(*snake, *food, *score, *highscore, *life);
			SaveScore(*score);
			Beep(250, 250);
			Sleep(2000);
		}
		else
		{
			*direction = 3;
		}
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		if (*direction == 2)
		{
			*endgame = 1;
			Graphics(*snake, *food, *score, *highscore, *life);
			SaveScore(*score);
			Beep(250, 250);
			Sleep(2000);
		}
		else
		{
			*direction = 4;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (*direction == 4)
		{
			*endgame = 1;
			Graphics(*snake, *food, *score, *highscore, *life);
			SaveScore(*score);
			Beep(250, 250);
			Sleep(2000);
		}
		else
		{
			*direction = 2;
		}
	}

	if (*direction == 1)
	{
		for (i = GetSnakeSize(*snake) - 1; i>0; i--)
		{
			lnode = GetListItem(*snake, i);

			fnode = GetListItem(*snake, i - 1);

			lnode->x = fnode->x;
			lnode->y = fnode->y;
		}

		(*snake)->x = (*snake)->x + 1;

		if ((*snake)->x >= 48)
		{
			*endgame = 1;
			Graphics(*snake, *food, *score, *highscore, *life);
			SaveScore(*score);
			Beep(250, 250);
			Sleep(2000);
		}
	}
	else if (*direction == 3)
	{
		for (i = GetSnakeSize(*snake) - 1; i>0; i--)
		{
			lnode = GetListItem(*snake, i);

			fnode = GetListItem(*snake, i - 1);

			lnode->x = fnode->x;
			lnode->y = fnode->y;
		}

		(*snake)->x = (*snake)->x - 1;

		if ((*snake)->x <= 1)
		{
			*endgame = 1;
			Graphics(*snake, *food, *score, *highscore, *life);
			SaveScore(*score);
			Beep(250, 250);
			Sleep(2000);
		}
	}
	else if (*direction == 4)
	{
		for (i = GetSnakeSize(*snake) - 1; i>0; i--)
		{
			lnode = GetListItem(*snake, i);

			fnode = GetListItem(*snake, i - 1);

			lnode->x = fnode->x;
			lnode->y = fnode->y;
		}

		(*snake)->y = (*snake)->y - 1;

		if ((*snake)->y <= 1)
		{
			*endgame = 1;
			Graphics(*snake, *food, *score, *highscore, *life);
			SaveScore(*score);
			Beep(250, 250);
			Sleep(2000);
		}
	}
	else
	{
		for (i = GetSnakeSize(*snake) - 1; i>0; i--)
		{
			lnode = GetListItem(*snake, i);

			fnode = GetListItem(*snake, i - 1);

			lnode->x = fnode->x;
			lnode->y = fnode->y;
		}

		(*snake)->y = (*snake)->y + 1;

		if ((*snake)->y >= 18)
		{
			*endgame = 1;
			Graphics(*snake, *food, *score, *highscore, *life);
			SaveScore(*score);
			Beep(250, 250);
			Sleep(2000);
		}
	}

	if (lose(*snake))
	{
		*endgame = 1;
		Graphics(*snake, *food, *score, *highscore, *life);
		SaveScore(*score);
		Beep(250, 250);
		Sleep(2000);
	}

	if ((*snake)->x == (*food).x && (*snake)->y == (*food).y)
	{
		(*food).isEaten = 1;

		*score = *score + 10;

		Beep(1000, 25);

		lnode = GetListItem(*snake, GetSnakeSize(*snake) - 1);

		nnode = (struct SnakeNode *)malloc(sizeof(struct SnakeNode));

		nnode->x = lnode->x;
		nnode->y = lnode->y;
		nnode->next = NULL;

		lnode->next = nnode;
	}
}

void DestroySnake(struct SnakeNode **snake) /* SnakeNode형 구조체 **snake에 할당된 메모리 해제하는 역할 */
{
	struct SnakeNode *temp = NULL;

	while (*snake != NULL)
	{
		temp = *snake;
		*snake = (*snake)->next;
		free(temp);
	}
}