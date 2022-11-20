//==============================
// Made by Rein_GD 2022
//==============================
#include "File.h"
#include "Framework.h"
namespace GD
{

	bool File::IsHandleValid(File::Handle fh) noexcept
	{			
		bool result = false;
		Handle input = NULL;
		Handle currentProcess = GetCurrentProcess();
		if (fh != INVALID_HANDLE_VALUE)
		{
			if (DuplicateHandle(currentProcess, fh, currentProcess, &input, 0, TRUE, DUPLICATE_SAME_ACCESS))
			{
				result = true;
				CloseHandle(input);
			}
		}
		
		return result;
	}


	File::Error File::Open(File::Handle& fh, const char* const fileName, File::Mode mode) noexcept
	{
		File::Error result = File::Error::OPEN_FAIL;
		//open the file with CreateFile
		
		if (fileName != nullptr)
		{
			switch (mode)
			{
			case GD::File::Mode::READ:
				fh = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);
				break;
			case GD::File::Mode::WRITE:
				fh = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);
				break;
			case GD::File::Mode::READ_WRITE:
				fh = CreateFile(fileName, (GENERIC_READ | GENERIC_WRITE), FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);
				break;
			default:
				break;
			}

			if (IsHandleValid(fh))
			{
				result = Error::SUCCESS;
			}
		}
		else result = Error::OPEN_FAIL;
		
		return 	result;
	}

	File::Error File::Close(File::Handle &fh) noexcept
	{
		Error result = Error::CLOSE_FAIL;
		if (IsHandleValid(fh))
		{
			if (CloseHandle(fh))
			{
				result = Error::SUCCESS;
				fh = INVALID_HANDLE_VALUE;
			}			
		}
		return 	result;
	}

	File::Error File::Write(File::Handle fh, const void* const buffer, const DWORD inSize) noexcept
	{
		Error result = Error::WRITE_FAIL;
		if (buffer != nullptr)
		{
			DWORD dwRead;

			if (IsHandleValid(fh))
			{
				if (WriteFile(fh, buffer, inSize, &dwRead, NULL))
				{
					result = Error::SUCCESS;
				}
				else dwRead = GetLastError();
			}
			else result = Error::WRITE_FAIL;
		}
		else result = Error::WRITE_FAIL;
		return 	result;
	}

	File::Error File::Read(File::Handle fh, void* const buffer, const DWORD inSize) noexcept
	{
		Error result = Error::READ_FAIL;
		
		if (IsHandleValid(fh))
		{
			DWORD dwRead;
			if (ReadFile(fh, buffer, inSize, &dwRead, NULL) == 0)
			{
				result = Error::READ_FAIL;
			}
			else result = Error::SUCCESS;
		}
		else result = Error::READ_FAIL;

		
		return 	result;
	}

	File::Error File::Seek(File::Handle fh, File::Position location, int offset) noexcept
	{
		Error result = Error::SEEK_FAIL;

		DWORD pos = 0;
		switch (location)
		{
		case GD::File::Position::BEGIN:
			pos = 0;
			break;
		case GD::File::Position::CURRENT:
			pos = 1;
			break;
		case GD::File::Position::END:
			pos = 2;
			break;
		default:
			break;
		}

		if (INVALID_SET_FILE_POINTER == SetFilePointer(fh, offset, NULL, pos))
		{
			result = Error::SEEK_FAIL;
		}
		else result = Error::SUCCESS;
		return 	result;
	}

	File::Error File::Tell(File::Handle fh, DWORD& offset) noexcept
	{
		Error result = Error::TELL_FAIL;

		if (IsHandleValid(fh))
		{
			offset = SetFilePointer(fh, 0, NULL, FILE_CURRENT);
			result = Error::SUCCESS;
		}
		else result = Error::TELL_FAIL;

		return result;
	}

	File::Error File::Flush(File::Handle fh) noexcept
	{
		Error result = Error::FLUSH_FAIL;
		
		if (IsHandleValid(fh))
		{
			if (FlushFileBuffers(fh))
			{
				result = Error::SUCCESS;
			}
		}
		else result = Error::FLUSH_FAIL;
		return result;
	}

}

// ---  End of File ---------------
