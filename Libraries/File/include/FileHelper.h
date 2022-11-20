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
	static std::vector<char> FileOpen(const char* const fileName, GD::File::Mode openMode, GD::File::Error* out_status);

private:
	FileHelper() = default;
};

#endif // !FILE_HELPER_H
