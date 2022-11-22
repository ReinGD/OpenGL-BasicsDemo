//==============================
// Made by Rein_GD 2022
//==============================
#include "FileHelper.h"
#include <cassert>
using namespace GD;

std::vector<char> FileHelper::FileOpenV(const char* const fileName)
{

	File::Handle fileHandle;

	File::Error out_status = File::Open(fileHandle, fileName, GD::File::Mode::READ);
	assert(out_status == File::Error::SUCCESS);

	out_status = File::Seek(fileHandle, File::Position::END, 0);
	assert(out_status == File::Error::SUCCESS);

	DWORD FileLength;
	out_status = File::Tell(fileHandle, FileLength);

	std::vector<char> buffer(FileLength);
	assert(buffer.size() > 0);

	out_status = File::Seek(fileHandle, File::Position::BEGIN, 0);
	assert(out_status == File::Error::SUCCESS);

	out_status = File::Read(fileHandle, buffer.data(), FileLength);
	assert(out_status == File::Error::SUCCESS);

	out_status = File::Close(fileHandle);
	assert(out_status == File::Error::SUCCESS);

	return buffer;
}

std::string FileHelper::FileOpenS(const char* const fileName)
{
	File::Handle fileHandle;

	File::Error out_status = File::Open(fileHandle, fileName, GD::File::Mode::READ);
	assert(out_status == File::Error::SUCCESS);

	out_status = File::Seek(fileHandle, File::Position::END, 0);
	assert(out_status == File::Error::SUCCESS);

	DWORD FileLength;
	out_status = File::Tell(fileHandle, FileLength);

	std::string buffer;
	buffer.resize(FileLength);
	assert(buffer.capacity() > 0);

	out_status = File::Seek(fileHandle, File::Position::BEGIN, 0);
	assert(out_status == File::Error::SUCCESS);

	out_status = File::Read(fileHandle, buffer.data(), FileLength);
	assert(out_status == File::Error::SUCCESS);

	out_status = File::Close(fileHandle);
	assert(out_status == File::Error::SUCCESS);

	return buffer;
}
