#pragma once
#include<time.h>

class CFruit
{
private:
	COORD Coordinate;

public:
	CFruit();
	~CFruit();

	COORD getCoord();

	void Generate(int, int);

	bool isEatenBy(CSnake*);
};

//================================
//================================
CFruit::CFruit()
{
	Coordinate = { 0,0 };
}

CFruit::~CFruit()
{
	return;
}

COORD CFruit::getCoord()
{
	return Coordinate;
}

void CFruit::Generate(int _maxWidth, int _maxHeight)
{
	srand((unsigned)time(NULL));

	SHORT X = rand() % _maxWidth;
	SHORT Y = rand() % _maxHeight;

	Coordinate = { X , Y };
}

bool CFruit::isEatenBy(CSnake* snake)
{
	COORD snakeCoord = snake->getBody().pHead->Coordinate;

	return Coordinate.X == snakeCoord.X && Coordinate.Y == snakeCoord.Y;
}