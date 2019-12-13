#include "Menu.h"

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void TextColor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void Khung()
{
	gotoxy(40, 1);
	TextColor(12);
	cout << "HUFFMAN COMPRESS AND EXTRACT PROGRAM";
	gotoxy(1, 4);
	TextColor(14);
	cout << "Link input: "; //(13, 4)
	TextColor(10);
	gotoxy(1, 6);
	cout << "Or choose the location";
	TextColor(15);
	gotoxy(1, 3);
	cout << "Use left and down arrow to control right to go foward and left to go backward, 'C' to compress or 'E' to extract";
}

vector<string> ListDriveLetters()
{
	vector<string> driveList;
	char cDriveLetter;
	cDriveLetter = 'A';
	DWORD dwDrivemap = GetLogicalDrives();
	while (cDriveLetter <= 'Z')
	{
		if (0 < (dwDrivemap & 0x00000001L))
		{
			string temp;
			temp += cDriveLetter;
			temp += ":\\";
			driveList.push_back(temp);
		}
		cDriveLetter++;
		dwDrivemap = dwDrivemap >> 1;
	}
	return driveList;
}

char choose(int& x, int& y, vector<string> list)
{
	char c = _getch();
	while (c != 75 && c != 77 && c != 'c' && c != 'C' && c != 'e' && c != 'E')
	{
		if (c == 72 && y > 7)
		{
			gotoxy(x, y);
			cout << ' ';
			y--;
			gotoxy(x, y);
			cout << char(175);
		}
		if (c == 80 && y < 7 + list.size() - 1)
		{
			gotoxy(x, y);
			cout << ' ';
			y++;
			gotoxy(x, y);
			cout << char(175);
		}
		c = _getch();
	}
	return c;
}

bool isFileOrFolder(string link) //0 la file, 1 la folder
{
	for (int i = link.length() - 1; i > 0; i--)
	{
		if (link[i] == '.') return 0;
		if (link[i] == '/' || link[i] == '\\') return 1;
	}
}

void backward(string& link)
{
	string temp;
	int pos = 0;
	for (int i = link.length() - 1; i > 0; i--)
	{
		if (link[i] == '/' || link[i] == '\\')
		{
			pos = i;
			break;
		}
	}
	if (pos != 1)
	{
		for (int i = 0; i < pos; i++)
			temp += link[i];
	}
	link = temp;
}

int Menu()
{
chon:
	system("cls");
	Khung();
	vector<string> list = ListDriveLetters();
	for (int i = 0; i < list.size(); i++)
	{
		gotoxy(2, 7 + i);
		cout << list[i];
	}
	int x = 0, y = 7;
	TextColor(12);
	gotoxy(x, y);
	cout << char(175);
	int choice = choose(x, y, list);
	string link;
	while (choice == 75 || choice == 77 || choice == 'c' || choice == 'C' || choice == 'e' || choice == 'E')
	{
		if (choice == 77)
		{
			if (isFileOrFolder(list[y - 7]) != 0)
			{
				link = list[y - 7];
				vector<string> subfolders = subFolders(link);
				vector<string> files = get_files_in(link);
				system("cls");
				gotoxy(13, 4);
				cout << link;
				list.resize(subfolders.size() + files.size());
				for (int i = 0; i < list.size(); i++)
				{
					if (i < subfolders.size()) list[i] = link + '\\' + subfolders[i];
					else list[i] = link + '\\' + files[i - subfolders.size()];
				}
				Khung();
				for (int i = 0; i < subfolders.size(); i++)
				{
					gotoxy(2, 7 + i);
					cout << subfolders[i];
				}
				for (int i = 0; i < files.size(); i++)
				{
					gotoxy(2, 7 + subfolders.size() + i);
					cout << files[i];
				}
				x = 0; y = 7;
			}
			TextColor(12);
			gotoxy(x, y);
			cout << char(175);
			choice = choose(x, y, list);
		}
		if (choice == 75)
		{
			if (list[0].length() == 3 || link.length() == 3) goto chon;
			backward(link);
			standardize(link);
			vector<string> subfolders = subFolders(link);
			vector<string> files = get_files_in(link);
			system("cls");
			gotoxy(13, 4);
			cout << link;
			list.resize(subfolders.size() + files.size());
			for (int i = 0; i < list.size(); i++)
			{
				if (i < subfolders.size()) list[i] = link + '\\' + subfolders[i];
				else list[i] = link + '\\' + files[i - subfolders.size()];
			}
			Khung();
			for (int i = 0; i < subfolders.size(); i++)
			{
				gotoxy(2, 7 + i);
				cout << subfolders[i];
			}
			for (int i = 0; i < files.size(); i++)
			{
				gotoxy(2, 7 + subfolders.size() + i);
				cout << files[i];
			}
			x = 0; y = 7;
			TextColor(12);
			gotoxy(x, y);
			cout << char(175);
			choice = choose(x, y, list);
		}
		if (choice == 'c' || choice == 'C')
		{
			if (link.length() == 0)
			{
				gotoxy(1, 5);
				cout << "Can't compress a disk drive!";
				TextColor(12);
				gotoxy(x, y);
				cout << char(175);
				choice = choose(x, y, list);
			}
			else
			{
				system("cls");
				vector<string> subfolders = subFolders(link);
				vector<string> files = get_files_in(link);
				list.resize(subfolders.size() + files.size());
				for (int i = 0; i < list.size(); i++)
				{
					if (i < subfolders.size()) list[i] = link + '\\' + subfolders[i];
					else list[i] = link + '\\' + files[i - subfolders.size()];
				}
				if (isFileOrFolder(list[y - 7]) == 0)
				{
					string temp = list[y - 7];
					backward(temp);
					clock_t start, finish;
					start = clock();
					CompressHuffman(list[y - 7], temp);
					finish = clock();
					clock_t duration = finish - start;
					gotoxy(1, 5);
					TextColor(14);
					cout << "Time: " << duration / 1000.0 << "s";
				}
				else
				{
					clock_t start, finish;
					start = clock();
					compressFolder(list[y - 7]);
					finish = clock();
					clock_t duration = finish - start;
					gotoxy(1, 5);
					TextColor(14);
					cout << "Time: " << duration / 1000.0 << "s";
				}
				gotoxy(1, 2);
				TextColor(10);
				cout << "Compress complete!";
				gotoxy(1, 10);
				TextColor(12);
				cout << "Press ENTER to go back or ESC to exit!";
				char c = _getch();
				if (c == 27) return 0;
				else
				{
					system("cls");
					gotoxy(13, 4);
					cout << link;
					Khung();
					for (int i = 0; i < subfolders.size(); i++)
					{
						gotoxy(2, 7 + i);
						cout << subfolders[i];
					}
					for (int i = 0; i < files.size(); i++)
					{
						gotoxy(2, 7 + subfolders.size() + i);
						cout << files[i];
					}
					x = 0; y = 7;
					TextColor(12);
					gotoxy(x, y);
					cout << char(175);
					choice = choose(x, y, list);
				}
			}
		}
		if (choice == 'e' || choice == 'E')
		{
			if (link.length() == 0)
			{
				gotoxy(1, 5);
				cout << "Can't extract a disk drive!";
				TextColor(12);
				gotoxy(x, y);
				cout << char(175);
				choice = choose(x, y, list);
			}
			else
			{
				system("cls");
				vector<string> subfolders = subFolders(link);
				vector<string> files = get_files_in(link);
				list.resize(subfolders.size() + files.size());
				for (int i = 0; i < list.size(); i++)
				{
					if (i < subfolders.size()) list[i] = link + '\\' + subfolders[i];
					else list[i] = link + '\\' + files[i - subfolders.size()];
				}
				if (isFileOrFolder(list[y - 7]) == 0)
				{
					string temp = list[y - 7];
					backward(temp);
					clock_t start, finish;
					start = clock();
					extract(list[y - 7], temp);
					finish = clock();
					clock_t duration = finish - start;
					gotoxy(1, 5);
					TextColor(14);
					cout << "Time: " << duration / 1000.0 << "s";
				}
				else
				{
					clock_t start, finish;
					start = clock();
					extractFolder(list[y - 7]);
					finish = clock();
					clock_t duration = finish - start;
					gotoxy(1, 5);
					TextColor(14);
					cout << "Time: " << duration / 1000.0 << "s";
				}
				TextColor(10);
				gotoxy(1, 2);
				cout << "Extract complete!";
				TextColor(12);
				gotoxy(1, 10);
				cout << "Press ENTER to go back or ESC to exit!";
				char c = _getch();
				if (c == 27) return 0;
				else
				{
					system("cls");
					gotoxy(13, 4);
					cout << link;
					Khung();
					for (int i = 0; i < subfolders.size(); i++)
					{
						gotoxy(2, 7 + i);
						cout << subfolders[i];
					}
					for (int i = 0; i < files.size(); i++)
					{
						gotoxy(2, 7 + subfolders.size() + i);
						cout << files[i];
					}
					x = 0; y = 7;
					TextColor(12);
					gotoxy(x, y);
					cout << char(175);
					choice = choose(x, y, list);
				}
			}
		}
	}
	return 0;
}