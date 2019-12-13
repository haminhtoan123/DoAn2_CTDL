#pragma once
#include "HuffmanTree.h"

#define GETTER 1000000

struct NODE
{
	int freq = 1;
	char S;
	NODE* pNext;
};

bool checkChar(Node* root, char ch);
void createHuffmanCode(Node* root, char ch, string& code);
Char* huffmanCodeArray(Char* arr, int n);