/*==============================
 Made By ReinGD
 2022
 All rights reserved
==============================*/
#pragma once
#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <cassert>

#include <stdlib.h>  
#include <crtdbg.h>  

/*
	This memory tracker should be enabled only on debug,
	release should not be affected

*/
#include "GDMemTracker.h"
#include "GDWriter.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//comment to turn off mem tracker
#define GD_MEM_TRACKER_ENABLED

#ifndef SOLUTION_DIR
	#error SOLUTION_DIR --- MISSING ---
#endif



#if defined(_DEBUG) && defined(GD_MEM_TRACKER_ENABLED)
	#define _CRTDBG_MAP_ALLOC   
	#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )

#else
	#pragma warning( push )
	#pragma warning( disable : 4820 )
	#pragma warning( disable : 4577 )
	#pragma warning( disable : 4987 )
	#include <new>
	#pragma warning( pop )
#endif // _DEBUG


#ifdef GD_MEM_TRACKER_ENABLED 
	#ifdef _DEBUG
		#define GD_BEGIN_MEM_TRACKING \
				GDMemTracker::Initialize();
		#define GD_END_MEM_TRACKING \
				GDMemTracker::Terminate();
	#else
	#define GD_BEGIN_MEM_TRACKING 
	#define GD_END_MEM_TRACKING 
	#endif // _DEBUG
	
#endif // GD_MEM_TRACKER_ENABLED 

#define CLEAN_NEW_BEGIN	__pragma(push_macro("new"))

#define CLEAN_NEW_END __pragma(pop_macro("new"))

#define UNUSED_VAR(x) (void(x))

static struct _StaticMem
{
	_StaticMem() noexcept
	{
		GD_BEGIN_MEM_TRACKING
	}
	~_StaticMem()
	{
		GD_END_MEM_TRACKING
	}


	_StaticMem(const _StaticMem&) = delete;
	_StaticMem(_StaticMem&&) = delete;
	_StaticMem& operator = (const _StaticMem&) = delete;
	_StaticMem& operator = (_StaticMem&&) = delete;
} _StaticMemInst;



#endif // !FRAMEWORK_H
