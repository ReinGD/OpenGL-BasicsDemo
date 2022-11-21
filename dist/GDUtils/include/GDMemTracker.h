#include <mutex>
#ifndef GD_MEM_TRACKER_H
#define GD_MEM_TRACKER_H

class GDMemTracker
{
private:
	static const unsigned int traceBufferSize = 256;
	static const unsigned int stringSize = 512;

public:
	// -----------------------------------------------------
	// Only found this structure in documentation
	// created a shadow structure to allow error reporting 
	// -----------------------------------------------------
	typedef struct _CrtMemBlockHeader
	{
		static const unsigned int nNoMansLandSize = 4; // said in doc that its 4

		struct _CrtMemBlockHeader* pBlockHeaderNext;
		struct _CrtMemBlockHeader* pBlockHeaderPrev;
		char* szFileName;    // File name
		int nLine;           // Line number
		int nBlockUse;       // Type of block   
		size_t nDataSize;    // Size of user block
		long lRequest;       // Allocation number
		unsigned char gap[nNoMansLandSize];

		// ---------------------------------------------------
		// In an actual memory block in the debug heap,
		//    this structure is followed by:
		//       unsigned char data[nDataSize];
		//       unsigned char anotherGap[nNoMansLandSize];
		// ---------------------------------------------------

	} _CrtMemBlockHeader;

public:
	GDMemTracker() noexcept;
	~GDMemTracker() = default;

	GDMemTracker(const GDMemTracker&) = delete;
	GDMemTracker(GDMemTracker&&) = delete;
	
	GDMemTracker& operator= (const GDMemTracker&) = delete;
	GDMemTracker& operator= (GDMemTracker&&) = delete;


	static void Initialize() noexcept;
	static void Terminate() noexcept;

private:
	static GDMemTracker& privGetRef() noexcept;

	char* privStripDir(const char* const pInName) noexcept;

private:
	std::once_flag processBeginFlag;
	std::once_flag processEndFlag;
};

#endif // !GD_MEM_TRACKER_H
