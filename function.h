#ifndef FUNCTION_H
#define FUNCTION_H
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define pianx 14
#define piany 8
#define Choice cout <<"⊙";
#define keydown GetAsyncKeyState(VK_DOWN)
#define keyup GetAsyncKeyState(VK_UP)
#define keyleft GetAsyncKeyState(VK_LEFT)
#define keyright GetAsyncKeyState(VK_RIGHT)
#define keyenter GetAsyncKeyState(VK_SHIFT)
#define length 60
#define width 30

void SetWindows();
bool WelCome();
void Position(int,int);
void DrawTable(int pos[5][5],int,int);
void FrameWork(int,int);
void ClearTable(int,int);
void Change(int pos[5][5],char,int&);
void lose(int);
void setcolor(int);
int relatedcolor(int);
bool check(int pos[5][5]);

#endif
