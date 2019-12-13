#include "CompressExtractFile.h"

string convert8bit(char s)
{
	bitset<8> x(s);
	return x.to_string();
}

string ConvertStringToBit(char* index, int count_char, int count_end_bit)
{
	string kq = "";
	for (int i = 0; i < count_char; i++)
	{
		kq += convert8bit(index[i]);
	}

	return kq.substr(0, count_char * 8 - count_end_bit);
}

void CompressHuffman(string filename, string locate)
{

	ifstream f;
	f.open(filename);
	if (f.is_open())
	{
		cout << "COMPRESSING...";
		f.close();
		f.open(filename, ios::binary);

		int capacity = 0;
		int k[256];// char tu -128->127
		for (int i = 0; i < 256; i++)
		{
			k[i] = 0;
		}
		char buffer[GETTER];

		while (f.read(buffer, GETTER))
		{

			for (int i = 0; i < GETTER; i++)
			{
				int a = int(buffer[i]);
				if (a < 0) a = a + 256;
				if (k[a] == 0) capacity++;
				k[a]++;
			}
		}
		for (int i = 0; i < f.gcount(); i++)
		{

			int a = int(buffer[i]);
			if (a < 0) a = a + 256;
			if (k[a] == 0) capacity++;
			k[a]++;
		}

		Char* tmp = new Char[capacity];
		int pivot = 0;
		for (int i = 0; i < 256; i++)
		{
			if (k[i] != 0)
			{
				tmp[pivot].freq = k[i];
				tmp[pivot].value = char(i);
				pivot++;
			}
		}


		tmp = huffmanCodeArray(tmp, capacity);
		/*for (int i = 0; i < capacity; i++)
			cout << tmp[i].value << ", " << tmp[i].freq << ", " << tmp[i].huffmanCode << endl;*/
		f.clear();
		f.seekg(0, ios::beg);

		// OUT FILE
		string name;
		int pos = filename.length() - 1;
		while (filename[pos] != '/' && filename[pos] != '\\' && pos > 0) pos--;
		for (pos; pos < filename.length(); pos++)
			name += filename[pos];

		ofstream outfile;
		outfile.open(locate + name + "_compressed", ios::binary);

		outfile << " " << endl << capacity << endl;
		for (int i = 0; i < capacity; i++)
		{
			outfile << tmp[i].value;
			outfile << tmp[i].freq;
			outfile << "\n";
		}

		//char s;
		string bit_buffer = "";
		while (f.read(buffer, GETTER))
		{
			for (int j = 0; j < GETTER; j++)
			{
				for (int i = 0; i < capacity; i++)
				{
					if (buffer[j] == tmp[i].value[0])
					{
						bit_buffer += tmp[i].huffmanCode;

						break;

					}
				}
			}
			for (int i = 0; i < bit_buffer.length() - bit_buffer.length() % 8; i += 8)
			{
				int dec_value = 0;
				int data = 1;
				for (int j = i + 7; j >= i; j--)
				{
					if (bit_buffer[j] == '1') dec_value += data;
					data = data * 2;

				}
				outfile << char(dec_value);
			}
			bit_buffer = bit_buffer.substr(bit_buffer.length() - bit_buffer.length() % 8, bit_buffer.length());
		}

		for (int j = 0; j < f.gcount(); j++)
		{
			for (int i = 0; i < capacity; i++)
			{
				if (buffer[j] == tmp[i].value[0])
				{
					bit_buffer += tmp[i].huffmanCode;

					break;

				}
			}
		}
		int end_bit = 8 - bit_buffer.length() % 8;
		for (int i = 0; i < end_bit; i++)
		{
			bit_buffer += '0';
		}
		for (int i = 0; i < bit_buffer.length(); i += 8)
		{
			int dec_value = 0;
			int data = 1;
			for (int j = i + 7; j >= i; j--)
			{
				if (bit_buffer[j] == '1') dec_value += data;
				data = data * 2;

			}
			outfile << char(dec_value);
		}

		outfile.clear();
		outfile.seekp(0, ios::beg);
		outfile << end_bit;
		f.close();
		outfile.close();
		system("cls");
	}
	else cout << "File not found!" << endl;

}

void extract(string filename, string locate)
{
	ifstream k;
	k.open(filename);
	if (k.is_open())
	{
		k.close();
		k.open(filename, ios::binary);

		Char* a;
		int count_bit_end;// count bit end
		k >> count_bit_end;
		int capacity;
		k >> capacity;

		// doc vao struct Char
		a = new Char[capacity];
		char* des = new char[2];
		k.read(des, 1);
		for (int i = 0; i < capacity; i++)
		{
			char des2;
			k.read(&des2, 1);
			a[i].value = des2;
			k >> a[i].freq;
			k.read(des, 1);
		}

		Node* huffmanTree = new Node;

		string name;
		int pos = filename.length() - 11;
		while (filename[pos] != '/' && filename[pos] != '\\' && pos > 0) pos--;
		for (pos; pos < filename.length() - 11; pos++)
			name += filename[pos];

		ofstream output;
		output.open(locate + name, ios::binary);

		makeHuffmanTree(huffmanTree, a, capacity);
		char getter[GETTER];
		Node* run = huffmanTree;
		string bit = "";
		float count = 0;
		while (k.read(getter, GETTER))
		{

			for (int i = 0; i < GETTER; i++)
			{
				bit += convert8bit(getter[i]);
			}
			for (int i = 0; i < bit.length(); i++)
			{
				if (bit[i] == '0')
					run = run->pLeft;
				else
					run = run->pRight;
				if (run->pLeft == NULL && run->pRight == NULL)
				{
					output << run->data.value;
					run = huffmanTree;
				}
			}
			bit = "";
		}
		for (int i = 0; i < k.gcount(); i++)
		{
			bit += convert8bit(getter[i]);
		}
		bit = bit.substr(0, bit.length() - count_bit_end);
		for (int i = 0; i < bit.length(); i++)
		{
			if (bit[i] == '0') run = run->pLeft;
			else
				run = run->pRight;
			if (run->pLeft == NULL && run->pRight == NULL)
			{
				output << run->data.value;
				run = huffmanTree;
			}
		}
		k.close();
		output.close();
	}
	else cout << "File not found" << endl;
}