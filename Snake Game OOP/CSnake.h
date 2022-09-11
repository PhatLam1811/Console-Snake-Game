#pragma once

struct bodyPart
{
	COORD Coordinate;
	bodyPart* pNext;
};

struct bodyChain
{
	bodyPart* pHead;
	bodyPart* pTail;
};

enum eDirection { STOP, UP, LEFT, DOWN, RIGHT };

bodyPart* CreateBodyPart(COORD);
void AddTail(bodyChain&, bodyPart*);

//================================
//================================
class CSnake
{
private:
	bodyChain Body;
	eDirection Direction;
	int Length;

public:
	CSnake();
	~CSnake();

	void Init(COORD);

	bodyChain getBody();

	bool isSelfBitten();

	void Direct(char);
	bool Move(bool, int, int);
	void Grow();
};

//================================
//================================
CSnake::CSnake()
{
	Body.pHead = Body.pTail = NULL;
	Direction = STOP;
	Length = 0;
}

CSnake::~CSnake()
{
	bodyPart* p = Body.pHead;

	while (p)
	{
		bodyPart* t = p;
		
		p = p->pNext;
		delete t;
		t = NULL;
	}

	Body.pHead = Body.pTail = NULL;
}

void CSnake::Init(COORD _initialCoord) 
{
	bodyPart* snakeHead = CreateBodyPart(_initialCoord);

	Length = 1;
	Direction = STOP;
	Body.pHead = Body.pTail = snakeHead;
}

bodyChain CSnake::getBody()
{
	return Body;
}

bool CSnake::isSelfBitten()
{
	bodyPart* p_snakeHead = Body.pHead;
	bodyPart* p_snakeBody = Body.pHead->pNext;

	while (p_snakeBody)
	{
		if (p_snakeHead->Coordinate.X == p_snakeBody->Coordinate.X &&
			p_snakeHead->Coordinate.Y == p_snakeBody->Coordinate.Y)
			return true;

		p_snakeBody = p_snakeBody->pNext;
	}

	return false;
}

void CSnake::Direct(char inputKey = 0)
{
	switch (inputKey)
	{
	case 'w':
	case 'W':
		if (Direction != DOWN)
			Direction = UP;
		break;
	case 'a':
	case 'A':
		if (Direction != RIGHT)
			Direction = LEFT;
		break;
	case 's':
	case 'S':
		if (Direction != UP)
			Direction = DOWN;
		break;
	case 'd':
	case 'D':
		if (Direction != LEFT)
			Direction = RIGHT;
		break;
	case 'p':
	case 'P':
		Direction = STOP;
		break;
	}
}

bool CSnake::Move(bool _isWallRestricted, int _maxWidth, int _maxHeight)
{
	if (Direction == STOP) return true;

	//Change tail's coordinate
	bodyPart* p = Body.pHead->pNext;
	COORD prevCoord = Body.pHead->Coordinate;
	
	while (p)
	{
		COORD temp = p->Coordinate;
		p->Coordinate = prevCoord;
		prevCoord = temp;
		p = p->pNext;
	}

	//Change head's coordinate
	switch (Direction)
	{
	case UP:
	{
		if (Body.pHead->Coordinate.Y > 0)
			Body.pHead->Coordinate.Y--;
		else
		{
			if (_isWallRestricted) return false;

			Body.pHead->Coordinate.Y = _maxHeight - 1;
		}
		break;
	}
	case LEFT:
	{
		if (Body.pHead->Coordinate.X > 0)
			Body.pHead->Coordinate.X--;
		else
		{
			if (_isWallRestricted) return false;

			Body.pHead->Coordinate.Y = _maxWidth - 1;
		}
		break;
	}
	case DOWN:
	{
		if (Body.pHead->Coordinate.Y < _maxHeight - 1)
			Body.pHead->Coordinate.Y++;
		else
		{
			if (_isWallRestricted) return false;

			Body.pHead->Coordinate.Y = 0;
		}
		break;
	}
	case RIGHT:
	{
		if (Body.pHead->Coordinate.X < _maxWidth - 1)
			Body.pHead->Coordinate.X++;
		else
		{
			if (_isWallRestricted) return false;

			Body.pHead->Coordinate.X = 0;
		}
		break;
	}
	}
	
	return true;
}

void CSnake::Grow()
{
	Length++;

	COORD _newPartCoord = { 0, 0 };

	AddTail(Body, CreateBodyPart(_newPartCoord));
}

//================================
//================================
bodyPart* CreateBodyPart(COORD _coord = { 0,0 })
{
	bodyPart* p = new bodyPart();

	if (!p)
		return NULL;

	p->Coordinate = _coord;
	p->pNext = NULL;

	return p;
}

void AddTail(bodyChain& snake, bodyPart* p)
{
	if (!snake.pHead)
	{
		snake.pHead = snake.pTail = p;
	}
	else
	{
		snake.pTail->pNext = p;
		snake.pTail = p;
	}
}