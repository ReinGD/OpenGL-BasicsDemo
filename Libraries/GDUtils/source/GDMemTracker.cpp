#include "GDMemTracker.h"
#include "Framework.h"
//THIS IS BASED ON ED KEENANS MEMORY TRACKER
//MODIFIED FOR FUTURE UPGRADES

GDMemTracker::GDMemTracker() noexcept
{
	memset(&privBuff[0], 0, traceBufferSize);
}

void GDMemTracker::Initialize() noexcept
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GDMemTracker& tracker = GDMemTracker::privGetRef();

	std::call_once(tracker.processBeginFlag, [&tracker]() noexcept
	{
			tracker.privOut("\n");
			tracker.privOut("--------------------------------\n");
			tracker.privOut("    Memory Tracking: start()    \n");
			tracker.privOut("--------------------------------\n");
			tracker.privOut("\n");
			printf("--------------------------------\n");
			printf("    Memory Tracking: start()    \n");
			printf("--------------------------------\n");
			printf("\n");

		
	});

}

void GDMemTracker::Terminate() noexcept
{

	GDMemTracker& tracker = GDMemTracker::privGetRef();

	std::call_once(tracker.processEndFlag, [&tracker]() noexcept 
	{
			_CrtMemState state{ 0 };
			_CrtMemCheckpoint(&state);

			tracker.privOut("\n");
			_CrtMemBlockHeader* pTmp;
			pTmp = reinterpret_cast<GDMemTracker::_CrtMemBlockHeader*> (state.pBlockHeader);

			unsigned int i = 0;

			size_t appMaxIndex = 0;
			size_t appMaxSize = 0;
			size_t appCount = 0;
			size_t appTotalSize = 0;
			_CrtMemBlockHeader* pAppMaxTmp = nullptr;

			size_t extMaxIndex = 0;
			size_t extMaxSize = 0;
			size_t extCount = 0;
			size_t extTotalSize = 0;
			_CrtMemBlockHeader* pExtMaxTmp = nullptr;

			int NormBlockLeakCount = 0;

			// Walk to the end of list && see if there is any leaks
			while (pTmp != nullptr)
			{
				if (pTmp->nBlockUse == _NORMAL_BLOCK)
				{
					NormBlockLeakCount++;
				}

				if (pTmp->pBlockHeaderNext == nullptr)
				{
					break;
				}
				pTmp = pTmp->pBlockHeaderNext;
			}


			if (NormBlockLeakCount > 0)
			{
				tracker.privOut("------------------------------------------------------\n");
				tracker.privOut(">>>   Memory Tracking: Leaks detected              <<<\n");
				tracker.privOut(">>>   Double-click on file string to Leak location <<<\n");
				tracker.privOut("------------------------------------------------------\n");
				tracker.privOut("\n");
 
			}


			while (pTmp != nullptr)
			{
				if (pTmp->nBlockUse == _NORMAL_BLOCK)
				{
					// treat allocation with/without names as different groups
					if (pTmp->szFileName == nullptr)
					{
						extTotalSize += pTmp->nDataSize;
						extCount++;
						if (extMaxSize < pTmp->nDataSize)
						{
							extMaxSize = pTmp->nDataSize;
							extMaxIndex = i;
							pExtMaxTmp = pTmp;
						}
						//if (pFile != nullptr)
						//{
						//	fprintf(pFile, "Leak(%d)  %d bytes ref:%d \n", (int)i, (int)pTmp->nDataSize, (int)pTmp->lRequest);
						//}
					}
					else
					{
						appTotalSize += pTmp->nDataSize;
						appCount++;
						if (appMaxSize < pTmp->nDataSize)
						{
							appMaxSize = pTmp->nDataSize;
							appMaxIndex = i;
							pAppMaxTmp = pTmp;
						}

						tracker.privOut("Leak(%d)  %d bytes ref:%d %s \n", i, pTmp->nDataSize, pTmp->lRequest, tracker.privStripDir(pTmp->szFileName));
						tracker.privOut("   %s(%d) : <double-click> \n", &pTmp->szFileName[strlen(SOLUTION_DIR)], pTmp->nLine);
						tracker.privOut("\n");
					}

					i++;
				}
				pTmp = pTmp->pBlockHeaderPrev;
			}

			tracker.privOut("Memory Tracking statistics \n");
			tracker.privOut("\n");
			tracker.privOut("     Application files: \n");
			tracker.privOut("                num of leaks: %d \n", appCount);
			tracker.privOut("          total bytes leaked: %d \n", appTotalSize);
			if (pAppMaxTmp != nullptr)
			{
				tracker.privOut("          largest individual: Leak(%d) size: %d \n", appMaxIndex, pAppMaxTmp->nDataSize);
			}
			tracker.privOut("\n");
			tracker.privOut("     External Libs: \n");
			tracker.privOut("                num of leaks: %d \n", extCount);
			tracker.privOut("          total bytes leaked: %d \n", extTotalSize);

			if (pExtMaxTmp != nullptr)
			{
				tracker.privOut("          largest individual: Leak(%d) size: %d \n", extMaxIndex, pExtMaxTmp->nDataSize);
			}


			tracker.privOut("--------------------------------\n");
			printf("--------------------------------\n");
			if (appCount)
			{
				tracker.privOut(">>> Memory Tracking: FAIL <<<<<<\n");
				printf(">>> Memory Tracking: FAIL <<<<<<\n");
			}
			else
			{
				tracker.privOut("    Memory Tracking: PASS \n");
				printf("    Memory Tracking: PASS \n");
			}
			tracker.privOut("--------------------------------\n");
			tracker.privOut("    Memory Tracking: end()      \n");
			tracker.privOut("--------------------------------\n");
			printf("--------------------------------\n");
			printf("    Memory Tracking: end()      \n");
			printf("--------------------------------\n");
			printf("\n");
	});
}

GDMemTracker& GDMemTracker::privGetRef() noexcept
{
	static GDMemTracker tracker;
	return tracker;
}

void GDMemTracker::privOut(const char* const fmt, ...) noexcept
{
	GDMemTracker& tracker = GDMemTracker::privGetRef();
	
	//lock the mutex
	std::lock_guard<std::mutex> lock(tracker.mtx);

	va_list args;


	#pragma warning( push )
	#pragma warning( disable : 26492 )
	#pragma warning( disable : 26481 )
		va_start(args, fmt);
	#pragma warning( pop )

	vsprintf_s(&tracker.privBuff[0], traceBufferSize, fmt, args);
	OutputDebugString(&tracker.privBuff[0]);

	args = static_cast<va_list> (nullptr);

}

char* GDMemTracker::privStripDir(const char* const pInName) noexcept
{
	char* pReturn = (char*)(pInName);

	const char* pch = pInName;

	while (pch != nullptr)
	{
		pch = strstr(pch, "\\");
		if (pch != nullptr)
		{
			pch += 1;
			pReturn = (char*)pch;
		}
	}

	return pReturn;
}
