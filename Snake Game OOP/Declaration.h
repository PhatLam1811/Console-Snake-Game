#pragma once
#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include"CBuffer.h"
#include"CSnake.h"
#include"CFruit.h"
using namespace std;

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

//================================
//================================
CBuffer* g_prevFrame = NULL;
CBuffer* g_nextFrame = NULL;

CSnake* g_Snake = NULL;
CFruit* g_Fruit = NULL;

char** prevBuffer;
char** nextBuffer;

bool g_isGameOver;
bool g_isWallRestricted;

int g_fieldWidth;
int g_fieldHeight;
int g_TotalScore;

//================================
//================================
void Configuration();
void Setup();
char Input();
void Processing();
void Draw();
void Loop();
void cleanUp();

//================================
//================================
void cls();
void setCursorCoord(SHORT, SHORT);
void hideConsoleCursor();
void borderlineCreate();