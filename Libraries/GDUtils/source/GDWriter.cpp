#include "GDWriter.h"
#include <cstdarg>
#include <windows.h>

GDWriter::GDWriter() noexcept
	:mode(Mode::OutConsole)
{
	memset(privBuff, 0, TraceBuffSize);
}

void GDWriter::write(const char* const fmt, ...)
{
	GDWriter& writer = GDWriter::privGetInstance();
	if (writer.mode != GDWriter::Mode::Unset)
	{
		std::lock_guard<std::mutex> lock(writer.mtx);

		va_list args;

		#pragma warning( push )
		#pragma warning( disable : 26492 )
		#pragma warning( disable : 26481 )
				va_start(args, fmt);
		#pragma warning( pop )


				if (writer.mode == Mode::OutConsole)
				{
					vprintf(fmt, args);
					vsprintf_s(&writer.privBuff[0], TraceBuffSize, fmt, args);
					OutputDebugString(&writer.privBuff[0]);
				}
				else if (writer.mode == Mode::Output)
				{
					vsprintf_s(&writer.privBuff[0], TraceBuffSize, fmt, args);
					OutputDebugString(&writer.privBuff[0]);
				}
				else 
				{
					vprintf(fmt, args);
				}
		

		//va_end(args);
		args = static_cast<va_list> (nullptr);
	}
	else 
	{
		//it is not set so do nothing
	}
}

void GDWriter::setMode(Mode setMode)
{
	GDWriter& writer = GDWriter::privGetInstance();
	writer.mode = setMode;
}

GDWriter& GDWriter::privGetInstance()
{
	static GDWriter writer;
	return writer;
}
