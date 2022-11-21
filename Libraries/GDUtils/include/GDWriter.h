#pragma once
#include <cstdint>
#include <mutex>
#ifndef GD_WRITTER_H
#define GD_WRITTER_H


//BASED ON ED KEENAN'S TRACE 
//MODIFIED FOR UPGRADABILITY

class GDWriter
{
public:
	enum Mode : uint8_t
	{
		Unset = 0000,
		Output = 0001,
		Console = 0010,
		OutConsole = 0011
	};

private:
	static const unsigned int TraceBuffSize = 256;

public:
	GDWriter() noexcept;
	~GDWriter() = default;

	GDWriter(const GDWriter&) = delete;
	GDWriter(GDWriter&&) = delete;
	GDWriter& operator= (const GDWriter&) = delete;
	GDWriter& operator= (GDWriter&&) = delete;

	//write to debug window
	static void write(const char* const fmt, ...);
	static void setMode(Mode setMode);
private:
	static GDWriter& privGetInstance();
	
	char privBuff[TraceBuffSize];
	std::mutex mtx;
	Mode mode;

};

#endif // !GD_WRITTER_H
