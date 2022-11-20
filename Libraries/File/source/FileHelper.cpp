//==============================
// Made by Rein_GD 2022
//==============================
#include "FileHelper.h"
#include <cassert>
using namespace GD;

std::vector<char> FileHelper::FileOpen(const char* const fileName, GD::File::Mode openMode, GD::File::Error* out_status)
{

	File::Handle fileHandle;

	*out_status = File::Open(fileHandle, fileName, openMode);
	assert(*out_status == File::Error::SUCCESS);

	*out_status = File::Seek(fileHandle, File::Position::END, 0);
	assert(*out_status == File::Error::SUCCESS);

	DWORD FileLength;
	*out_status = File::Tell(fileHandle, FileLength);

	std::vector<char> buffer(FileLength);
	assert(buffer.size() > 0);

	*out_status = File::Seek(fileHandle, File::Position::BEGIN, 0);
	assert(*out_status == File::Error::SUCCESS);

	*out_status = File::Read(fileHandle, buffer.data(), FileLength);
	assert(*out_status == File::Error::SUCCESS);

	*out_status = File::Close(fileHandle);
	assert(*out_status == File::Error::SUCCESS);

	return buffer;
}
