#include "CompressExtractFolder.h"

vector<string> get_folders_in(const string& s)
{
	std::vector<string> r;
	for (auto& p : filesys::recursive_directory_iterator(s))
		if (p.status().type() == filesys::file_type::directory)
			r.push_back(p.path().string());
	return r;
}

vector<string> get_files_in(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

void standardize(string& link)
{
	if (link.length() == 1) link += ":\\";
	else
	{
		if (link.length() == 2 && link[1] == ':') link += '\\';
		int pos = link.length() - 1;
		if ((link[pos] == '/' || link[pos] == '\\') && pos > 2) link.pop_back();
	}
}

void createFolder(string name)
{
	int check = _mkdir(name.c_str());
}

vector<string> newFolder(string link)
{
	vector<string> folders = get_folders_in(link);
	vector<string> newfolders;
	for (int i = 0; i < folders.size(); i++)
	{
		string temp;
		for (int j = 0; j < folders[i].length(); j++)
		{
			if (j > link.length() - 1) temp += folders[i][j];
		}
		newfolders.push_back(temp);
	}
	return newfolders;
}

void compressFolder(string link)
{
	standardize(link);
	if (_mkdir(link.c_str()) == -1)
	{
		string compressedfolder = link + "_compressed";
		vector<string> newfolders = newFolder(link);
		createFolder(compressedfolder);
		vector<string> folders = get_folders_in(link);
		vector<string> files = get_files_in(link);
		for (int i = 0; i < files.size(); i++)
			CompressHuffman(link + '/' + files[i], compressedfolder);
		for (int i = 0; i < folders.size(); i++)
		{
			createFolder(compressedfolder + newfolders[i]);
			files = get_files_in(folders[i]);
			for (int j = 0; j < files.size(); j++)
				CompressHuffman(folders[i] + '/' + files[j], compressedfolder + newfolders[i]);
		}
	}
	else
	{
		_rmdir(link.c_str());
		cout << "Folder not found!" << endl;
	}
}

void extractFolder(string link)
{
	standardize(link);
	if (_mkdir(link.c_str()) == -1)
	{
		string extractedFolder = link.substr(0, link.length() - 11);
		createFolder(extractedFolder);
		vector<string> folders = get_folders_in(link);
		vector<string> newfolders = newFolder(link);
		vector<string> files = get_files_in(link);
		for (int i = 0; i < files.size(); i++)
			extract(link + '/' + files[i], extractedFolder);
		for (int i = 0; i < folders.size(); i++)
		{
			createFolder(extractedFolder + newfolders[i]);
			files = get_files_in(folders[i]);
			for (int j = 0; j < files.size(); j++)
				extract(folders[i] + '/' + files[j], extractedFolder + newfolders[i]);
		}
	}
	else
	{
		_rmdir(link.c_str());
		cout << "Folder not found!" << endl;
	}
}

string getFolderName(string link)
{
	string name;
	int pos = link.length() - 1;
	while (link[pos - 1] != '/' && link[pos - 1] != '\\' && pos > 0) pos--;
	for (pos; pos < link.length(); pos++)
		name += link[pos];
	return name;
}

vector<string> subFolders(const string& s)
{
	std::vector<string> r;
	for (auto& p : filesys::recursive_directory_iterator(s))
	{
		if (p.status().type() == filesys::file_type::directory)
		{
			int pos = s.length() - 1;
			int count = 0;
			for (int i = pos; i < p.path().string().length(); i++)
			{
				if (p.path().string()[i] == '\\' || p.path().string()[i] == '/') count++;
				if (count == 2) break;
			}
			if (count == 1) r.push_back(getFolderName(p.path().string()));
		}
	}
	return r;
}

ostream& operator<<(ostream& out, vector<string> self)
{
	for (int i = 0; i < self.size(); i++)
		out << self[i] << endl;
	return out;
}