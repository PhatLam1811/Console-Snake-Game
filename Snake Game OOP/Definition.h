#pragma once

#pragma region Main Procs Define
void Configuration()
{
	char temp;

	cout << "Welcome to Snake Game!!!\n\n";
	cout << "Vui long chon kich thuoc map:\n";
	cout << "Chieu rong (10 < a < 100): "; cin >> g_fieldWidth;
	cout << "Chieu cao (10 < a < 100): "; cin >> g_fieldHeight;
	cout << "\nCo the xuyen tuong?(Y/N): "; cin >> temp;
	cout << "\nSetting Game..."; Sleep(2000);

	g_isWallRestricted = temp == 'Y' ? false : true;
}

void Setup()
{
	Configuration();
	cls();
	borderlineCreate();

	g_Snake = new CSnake();
	g_Fruit = new CFruit();
	g_prevFrame = new CBuffer();
	g_nextFrame = new CBuffer();

	COORD _initialCoord = { g_fieldWidth / 2, g_fieldHeight / 2 };

	g_Snake->Init (_initialCoord);
	g_Fruit->Generate(g_fieldWidth, g_fieldHeight);
	g_prevFrame->Init(g_fieldWidth, g_fieldHeight);
	g_nextFrame->Init(g_fieldWidth, g_fieldHeight);

	g_TotalScore = 0;
	g_isGameOver = false;

	hideConsoleCursor();
}

char Input()
{
	char keyInput = 0;

	if (_kbhit())
		keyInput = _getch();

	return keyInput;
}

void Processing()
{
	if (g_Fruit->isEatenBy(g_Snake))
	{
		g_Fruit->Generate(g_fieldWidth, g_fieldHeight);
		g_Snake->Grow();
		g_TotalScore += 10;
	}

	char keyInput = Input();

	g_Snake->Direct(keyInput);

	bool _isMovable = g_Snake->Move(g_isWallRestricted, g_fieldWidth, g_fieldHeight);
		
	if (_isMovable)
		g_isGameOver = g_Snake->isSelfBitten();
	else
		g_isGameOver = true;
	
	g_nextFrame->Clear();
	g_nextFrame->updateSnake(g_Snake);
	g_nextFrame->updateFruit(g_Fruit);
}

void Draw()
{
	char** _prevField = g_prevFrame->getField();
	char** _nextField = g_nextFrame->getField();

	for (int Row = 0; Row < g_fieldHeight; Row++)
		for (int Col = 0; Col < g_fieldWidth; Col++)
			if (_prevField[Row][Col] != _nextField[Row][Col])
			{
				setCursorCoord(Col + 1, Row + 1);

				cout << _nextField[Row][Col];
			}
	
	g_prevFrame->Imitate(g_nextFrame);
}

void Loop()
{
	while (!g_isGameOver)
	{
		Processing();
		Draw();
		Sleep(120);
	}
}

void cleanUp()
{
	delete g_Snake;
	delete g_Fruit;
	delete g_prevFrame;
	delete g_nextFrame;

	g_Snake = NULL;
	g_Fruit = NULL;
	g_prevFrame = NULL;
	g_nextFrame = NULL;
}
#pragma endregion

#pragma region Display Procs Define
void cls()
{
	static const HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	COORD TopLeft = { 0, 0 };

	if (!GetConsoleScreenBufferInfo(handleOut, &bufferInfo)) abort();

	DWORD length = bufferInfo.dwSize.X * bufferInfo.dwSize.Y;
	DWORD written;

	FillConsoleOutputCharacter(handleOut, TEXT(' '), length, TopLeft, &written);

	FillConsoleOutputAttribute(handleOut, bufferInfo.wAttributes, length, TopLeft, &written);

	SetConsoleCursorPosition(handleOut, TopLeft);
}

void setCursorCoord(SHORT y, SHORT x)
{
	static const HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	cout.flush();

	COORD newCursorCoord = { y, x };

	SetConsoleCursorPosition(handleOut, newCursorCoord);
}

void hideConsoleCursor()
{
	static HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(handleOut, &cursorInfo);

	cursorInfo.bVisible = false;

	SetConsoleCursorInfo(handleOut, &cursorInfo);
}

void borderlineCreate()
{
	for (int i = 0; i < g_fieldHeight + 2; i++)
	{
		setCursorCoord(0, i);

		for (int j = 0; j < g_fieldWidth + 2; j++)
			if  (  i == 0
				|| j == 0
				|| i == g_fieldHeight + 1
				|| j == g_fieldWidth + 1 )
				cout << '#';
			else
				cout << " ";
	}
}
#pragma endregion