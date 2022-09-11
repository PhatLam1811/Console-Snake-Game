#pragma once
#include"CSnake.h"
#include"CFruit.h"

class CBuffer
{
private:
	char** Field;
	int Width;
	int Height;

public:
	CBuffer();
	~CBuffer();

	void Init(int, int);

	char** getField();
	int getWidth();
	int getHeight();

	void Clear();
	void updateSnake(CSnake*);
	void updateFruit(CFruit*);
	void Imitate(CBuffer*);
};

//================================
//================================
CBuffer::CBuffer()
{
	Field = NULL;
	Width = Height = 0;
}

CBuffer::~CBuffer()
{
	for (int Row = 0; Row < Height; Row++)
		delete[] Field[Row];

	delete[] Field;
	Field = NULL;
}

void CBuffer::Init(int _width, int _height)
{
	Width = _width;
	Height = _height;
	Field = new char* [Height];

	for (int Row = 0; Row < Height; Row++)
	{
		Field[Row] = new char[Width];
		
		for (int Col = 0; Col < Width; Col++)
			Field[Row][Col] = 32;
	}		
}

char** CBuffer::getField()
{
	return Field;
}

int CBuffer::getWidth()
{
	return Width;
}

int CBuffer::getHeight()
{
	return Height;
}

void CBuffer::Clear()
{
	for (int Row = 0; Row < Height; Row++)
		for (int Col = 0; Col <Width; Col++)
			Field[Row][Col] = 32;
}

void CBuffer::updateSnake(CSnake* _pSnake)
{
	bodyPart* _pHead = _pSnake->getBody().pHead;
	
	bool _isHead = true;

	while (_pHead)
	{
		int Row = _pHead->Coordinate.Y;
		int Col = _pHead->Coordinate.X;

		Field[Row][Col] = _isHead ? 'S' : 'o';

		_pHead = _pHead->pNext;
		_isHead = false;
	}
}

void CBuffer::updateFruit(CFruit* _pFruit)
{
	int Row = _pFruit->getCoord().Y;
	int Col = _pFruit->getCoord().X;

	Field[Row][Col] = 'F';
}

void CBuffer::Imitate(CBuffer* _pBuffer)
{
	for (int Row = 0; Row < Height; Row++)
		for (int Col = 0; Col < Width; Col++)
			Field[Row][Col] = _pBuffer->Field[Row][Col];
}