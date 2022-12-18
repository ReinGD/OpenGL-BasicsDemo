//==============================
// Made by Rein_GD 2022
//==============================
#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include "File.h"
#include <vector>

class FileHelper
{
public:
	~FileHelper() = default;
	static std::vector<char> FileOpenV(const char* const fileName);
	static std::string FileOpenS(const char* const fileName);
private:
	FileHelper() = default;
};

#endif // !FILE_HELPER_H
