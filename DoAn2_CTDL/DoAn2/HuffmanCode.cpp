#include "HuffmanCode.h"

bool checkChar(Node* root, char ch)
{
	for (int i = 0; i < root->data.value.length(); i++)
		if (root->data.value[i] == ch) return 1;
	return 0;
}

void createHuffmanCode(Node* root, char ch, string& code)
{
	if (root->data.value[0] == ch && root->data.value.length() == 1)
	{
		root->data.huffmanCode = code;
		return;
	}
	else
	{
		if (checkChar(root->pLeft, ch) == 1)
		{
			code += '0';
			createHuffmanCode(root->pLeft, ch, code);
		}
		else
		{
			code += '1';
			createHuffmanCode(root->pRight, ch, code);
		}
	}
}

Char* huffmanCodeArray(Char* arr, int n)
{
	Node* root = new Node;
	makeHuffmanTree(root, arr, n);
	for (int i = 0; i < n; i++)
		createHuffmanCode(root, arr[i].value[0], arr[i].huffmanCode);
	deleteTree(root);
	return arr;
}