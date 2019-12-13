#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "CompressExtractFile.h"
#include <vector>
#include <direct.h>
#include <experimental/filesystem>
#include <Windows.h>

namespace filesys = std::experimental::filesystem;

vector<string> get_folders_in(const string& s);
vector<string> get_files_in(string folder);
void standardize(string& link);
void createFolder(string name);
vector<string> newFolder(string link);
void compressFolder(string link);
void extractFolder(string link);
string getFolderName(string link);
vector<string> subFolders(const string& s);
ostream& operator<<(ostream& out, vector<string> self);