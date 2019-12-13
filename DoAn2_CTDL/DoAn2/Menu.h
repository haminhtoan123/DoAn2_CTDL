#pragma once
#include "CompressExtractFolder.h"
#include <time.h>
#include <conio.h>

void gotoxy(int x, int y);
void TextColor(int x);
void Nocursortype();
void Khung();
vector<string> ListDriveLetters();
char choose(int& x, int& y, vector<string> list);
bool isFileOrFolder(string link);
void backward(string& link);
int Menu();