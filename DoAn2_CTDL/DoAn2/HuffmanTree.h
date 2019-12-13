#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Char
{
	int freq;
	string value;
	string huffmanCode;
};

struct Node
{
	Char data;
	Node* pLeft;
	Node* pRight;
};

void swap(Char& x, Char& y);
void sortArray(Char* arr, int n);
Node* newNode(string Value, int Freq);
void newTop(Node*& Top, Node* Left, Node* Right);
void deleteTree(Node*& root);
void makeHuffmanTree(Node*& root, Char* arr, int n);
void treeOutput(Node* root);