#include "GDMemTracker.h"
#include "Framework.h"
//THIS IS BASED ON ED KEENANS MEMORY TRACKER
//MODIFIED FOR FUTURE UPGRADES

GDMemTracker::GDMemTracker() noexcept
{
}

void GDMemTracker::Initialize() noexcept
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GDMemTracker& tracker = GDMemTracker::privGetRef();

	std::call_once(tracker.processBeginFlag, [&tracker]() noexcept
	{		
			GDWriter::write("\n");
			GDWriter::write("------------------------------------------------------\n");
			GDWriter::write("                Memory Tracking: Started              \n");
			GDWriter::write("------------------------------------------------------\n");
			GDWriter::write("\n");

	});

}

void GDMemTracker::Terminate() noexcept
{

	GDMemTracker& tracker = GDMemTracker::privGetRef();

	std::call_once(tracker.processEndFlag, [&tracker]() noexcept 
	{
			_CrtMemState state{ 0 };
			_CrtMemCheckpoint(&state);

			GDWriter::write("\n");
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
				GDWriter::write("------------------------------------------------------\n");
				GDWriter::write(">>>   Memory Tracking: Leaks detected              <<<\n");
				GDWriter::write(">>>   Double-click on file string to Leak location <<<\n");
				GDWriter::write("------------------------------------------------------\n");
				GDWriter::write("\n");
 
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

						GDWriter::write("Leak(%d)  %d bytes ref:%d %s \n", i, pTmp->nDataSize, pTmp->lRequest, tracker.privStripDir(pTmp->szFileName));
						GDWriter::write("   %s(%d) : <double-click> \n", &pTmp->szFileName[strlen(SOLUTION_DIR)], pTmp->nLine);
						GDWriter::write("\n");
					}

					i++;
				}
				pTmp = pTmp->pBlockHeaderPrev;
			}

			GDWriter::write("Memory Tracking statistics \n");
			GDWriter::write("\n");
			GDWriter::write("     Application files: \n");
			GDWriter::write("                num of leaks: %d \n", appCount);
			GDWriter::write("          total bytes leaked: %d \n", appTotalSize);
			if (pAppMaxTmp != nullptr)
			{
				GDWriter::write("          largest individual: Leak(%d) size: %d \n", appMaxIndex, pAppMaxTmp->nDataSize);
			}
			GDWriter::write("\n");
			GDWriter::write("     External Libs: \n");
			GDWriter::write("                num of leaks: %d \n", extCount);
			GDWriter::write("          total bytes leaked: %d \n", extTotalSize);

			if (pExtMaxTmp != nullptr)
			{
				GDWriter::write("          largest individual: Leak(%d) size: %d \n", extMaxIndex, pExtMaxTmp->nDataSize);
			}


			GDWriter::write("------------------------------------------------------\n");
			if (appCount)
			{
				GDWriter::write(">>>>>> Memory Tracking: FAIL <<<<<<\n");
			}
			else
			{
				GDWriter::write("                Memory Tracking: PASS \n");
			}
			GDWriter::write("------------------------------------------------------\n");
			GDWriter::write("                Memory Tracking: Finished             \n");
			GDWriter::write("------------------------------------------------------\n");
			GDWriter::write("\n");
	});
}

GDMemTracker& GDMemTracker::privGetRef() noexcept
{
	static GDMemTracker tracker;
	return tracker;
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
