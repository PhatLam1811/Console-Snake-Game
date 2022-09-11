#include<iostream>
#include<Windows.h>
#include<conio.h>
using namespace std;

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

char** prevBuffer;
char** nextBuffer;

bool ck_isGameOver;
char ck_isWallRestrict;

enum eDirection { STOP, UP, LEFT, DOWN, RIGHT };
eDirection eSnakeDir;

int* a_snakeX;
int* a_snakeY;

int GAME_FIELD_WIDTH;
int GAME_FIELD_HEIGHT;

int g_tailLength;
int g_fruitX;
int g_fruitY;
int g_TotalScore;

//Main game
void Configuration();
void Setup();
void Input();
void Logic();
void Draw();
void GameLoop();

//Snake
void SnakeInit();
void SnakeDirect();

//Fruit
void FruitGenerate();

//Buffer
void BufferInit();
void FieldInit();
void FieldClear();
void nextBufferUpdate();

//Processing
void cls();
void SetCursorPosition(int, int);
bool isCollided();
bool isSnakeEatFruit();

int main()
{
	Configuration();

	Setup();

	GameLoop();

	SetCursorPosition(0, GAME_FIELD_HEIGHT + 3);
	cout << "Total Score: " << g_TotalScore;
	cout << "\nNhan Enter de ket thuc!";

	return 0;
}

#pragma region Main Game
void Configuration()
{
	cout << "Welcome to Snake Game!!!\n\n";
	cout << "Vui long chon kich thuoc map:\n";
	cout << "Chieu rong (10 < a < 100): "; cin >> GAME_FIELD_WIDTH;
	cout << "Chieu cao (10 < a < 100): "; cin >> GAME_FIELD_HEIGHT;
	cout << "\nCo the xuyen tuong?(Y/N): "; cin >> ck_isWallRestrict;
	cout << "\nSetting Game..."; Sleep(3000);
}

void Setup()
{
	cls();

	BufferInit();

	FieldInit();

	SnakeInit();

	FruitGenerate();

	ck_isGameOver = false;

	g_TotalScore = 0;
}

void Input()
{
	if (_kbhit())
	{
		char keyboardAscii = _getch();

		switch (keyboardAscii)
		{
		case 'W':
		case 'w':
			if (eSnakeDir != DOWN)
				eSnakeDir = UP;
			break;
		case 'A':
		case 'a':
			if (eSnakeDir != RIGHT)
				eSnakeDir = LEFT;
			break;
		case 'S':
		case 's':
			if (eSnakeDir != UP)
				eSnakeDir = DOWN;
			break;
		case 'D':
		case 'd':
			if (eSnakeDir != LEFT)
				eSnakeDir = RIGHT;
			break;
		}
	}
}

void Logic()
{
	if (isSnakeEatFruit())
	{
		g_tailLength++;

		g_TotalScore += 10;

		FruitGenerate();
	}

	SnakeDirect();

	if (isCollided() && ck_isWallRestrict == 'Y')
			ck_isGameOver = true;
	else
	{
		if (a_snakeX[0] > GAME_FIELD_WIDTH)
			a_snakeX[0] = 1;

		if (a_snakeY[0] > GAME_FIELD_HEIGHT)
			a_snakeY[0] = 1;

		if (a_snakeX[0] <= 0)
			a_snakeX[0] = GAME_FIELD_WIDTH;

		if (a_snakeY[0] <= 0)
			a_snakeY[0] = GAME_FIELD_HEIGHT;
	}

	for (int i = 1; i < g_tailLength; i++)
		if (a_snakeX[0] == a_snakeX[i] && a_snakeY[0] == a_snakeY[i])
			ck_isGameOver = true;
}

void Draw()
{
	for (int i = 0; i < GAME_FIELD_HEIGHT + 2; i++)
		for (int j = 0; j < GAME_FIELD_WIDTH + 2; j++)
			if (prevBuffer[i][j] != nextBuffer[i][j])
			{
				SetCursorPosition(j, i);

				cout << nextBuffer[i][j];

				prevBuffer[i][j] = nextBuffer[i][j];
			}

	Sleep(120);
}

void GameLoop()
{
	while (true)
	{
		FieldClear();

		Input();

		Logic();

		if (ck_isGameOver)
			return;

		nextBufferUpdate();

		Draw();
	}
}
#pragma endregion

#pragma region Snake
void SnakeInit()
{
	eSnakeDir = STOP;

	g_tailLength = 1;

	a_snakeX = new int[GAME_FIELD_HEIGHT * GAME_FIELD_WIDTH]{ NULL };
	a_snakeY = new int[GAME_FIELD_HEIGHT * GAME_FIELD_WIDTH]{ NULL };

	a_snakeX[0] = GAME_FIELD_WIDTH / 2;
	a_snakeY[0] = GAME_FIELD_HEIGHT / 2;
}

void SnakeDirect()
{
	int prevX = a_snakeX[0];
	int prevY = a_snakeY[0];
	int prev2X, prev2Y;

	for (int i = 1; i < g_tailLength; i++)
	{
		prev2X = a_snakeX[i];
		prev2Y = a_snakeY[i];
		a_snakeX[i] = prevX;
		a_snakeY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (eSnakeDir)
	{
	case UP:
		a_snakeY[0]--;
		break;
	case LEFT:
		a_snakeX[0]--;
		break;
	case DOWN:
		a_snakeY[0]++;
		break;
	case RIGHT:
		a_snakeX[0]++;
		break;
	}
}
#pragma endregion

#pragma region Fruit
void FruitGenerate()
{
	g_fruitX = rand() % GAME_FIELD_WIDTH + 1;
	g_fruitY = rand() % GAME_FIELD_HEIGHT + 1;
}
#pragma endregion

#pragma region Buffer
void BufferInit()
{
	prevBuffer = new char* [GAME_FIELD_HEIGHT + 2];

	for (int i = 0; i < GAME_FIELD_HEIGHT + 2; i++)
		prevBuffer[i] = new char[GAME_FIELD_WIDTH + 2]{ 0 };

	nextBuffer = new char* [GAME_FIELD_HEIGHT + 2];

	for (int i = 0; i < GAME_FIELD_HEIGHT + 2; i++)
		nextBuffer[i] = new char[GAME_FIELD_WIDTH + 2]{ 0 };
}

void FieldInit()
{
	for (int i = 0; i < GAME_FIELD_HEIGHT + 2; i++)
		for (int j = 0; j < GAME_FIELD_WIDTH + 2; j++)
		{
			if (i != 0 && i != GAME_FIELD_HEIGHT + 1 && j != 0 && j != GAME_FIELD_WIDTH + 1)
				nextBuffer[i][j] = ' ';
			else
				nextBuffer[i][j] = '#';
		}
}

void FieldClear()
{
	for (int i = 1; i <= GAME_FIELD_HEIGHT; i++)
		for (int j = 1; j <= GAME_FIELD_WIDTH; j++)
			nextBuffer[i][j] = ' ';
}

void nextBufferUpdate()
{
	nextBuffer[g_fruitY][g_fruitX] = 'F';

	for (int i = 0; a_snakeX[i] != NULL; i++)
		nextBuffer[a_snakeY[i]][a_snakeX[i]] = i == 0 ? '0' : 'o';
}
#pragma endregion

#pragma region Processing
void cls()
{
	static const HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	COORD TopLeft = { 0,0 };

	cout.flush();

	if (!GetConsoleScreenBufferInfo(outputHandle, &bufferInfo)) abort();

	DWORD length = bufferInfo.dwSize.X * bufferInfo.dwSize.Y;
	DWORD written;

	FillConsoleOutputCharacter(outputHandle, TEXT(' '), length, TopLeft, &written);

	FillConsoleOutputAttribute(outputHandle, bufferInfo.wAttributes, length, TopLeft, &written);

	SetConsoleCursorPosition(outputHandle, TopLeft);
}

void SetCursorPosition(int x, int y)
{
	static HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	cout.flush();

	COORD coord = { (SHORT)x, (SHORT)y };

	SetConsoleCursorPosition(outputHandle, coord);
}

bool isCollided()
{
	return a_snakeX[0] < 1 || a_snakeX[0] > GAME_FIELD_WIDTH || a_snakeY[0] < 1 || a_snakeY[0] > GAME_FIELD_HEIGHT;
}

bool isSnakeEatFruit()
{
	return g_fruitX == a_snakeX[0] && g_fruitY == a_snakeY[0];
}
#pragma endregion