#include "HuffmanTree.h"

void swap(Char& x, Char& y)
{
	Char temp = x;
	x = y;
	y = temp;
}

void sortArray(Char* arr, int n)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = i; j < n; j++)
			if (arr[i].freq < arr[j].freq) swap(arr[i], arr[j]);
}

Node* newNode(string Value, int Freq)
{
	Node* cur = new Node;
	cur->data.value = Value;
	cur->data.freq = Freq;
	cur->pLeft = NULL;
	cur->pRight = NULL;
	return cur;
}

void newTop(Node*& Top, Node* Left, Node* Right)
{
	Top = newNode(Left->data.value + Right->data.value, Left->data.freq + Right->data.freq);
	Top->pLeft = Left;
	Top->pRight = Right;
}

void deleteTree(Node*& root)
{
	if (root == NULL) return;
	deleteTree(root->pLeft);
	deleteTree(root->pRight);
	delete root;

}

void makeHuffmanTree(Node*& root, Char* arr, int n)
{
	int count = 1;
	sortArray(arr, n);
	Node** tree = new Node * [n];
	for (int i = 0; i < n; i++)
		tree[i] = newNode(arr[i].value, arr[i].freq);

	while (n > 1)
	{
		newTop(root, tree[n - 1], tree[n - 2]);
		n--;
		tree[n - 1] = root;
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i; j < n; j++)
			{
				if (tree[i]->data.freq < tree[j]->data.freq)
				{
					Node* temp = tree[i];
					tree[i] = tree[j];
					tree[j] = temp;
				}
			}
		}
	}
	delete[] tree;
}

void treeOutput(Node* root)
{
	if (root == NULL) return;
	cout << root->data.value << ", " << root->data.freq << endl;
	if (root->data.huffmanCode.size() > 0) cout << "Huffman code: ";
	for (int i = 0; i < root->data.huffmanCode.size(); i++)
		cout << root->data.huffmanCode[i];
	if (root->data.huffmanCode.size() > 0) cout << endl;
	treeOutput(root->pLeft);
	treeOutput(root->pRight);
}