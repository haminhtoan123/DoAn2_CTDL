#pragma once
#include "HuffmanCode.h"
#include <bitset>
#include <fstream>

string convert8bit(char s);
string ConvertStringToBit(char* index, int count_char, int count_end_bit);
void CompressHuffman(string filename, string locate);
void extract(string filename, string locate);