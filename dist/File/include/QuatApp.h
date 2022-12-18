/*==============================
 Made By ReinGD
 2022
 All rights reserved
==============================*/
#ifndef QuatApp_H
#define QuatApp_H

#include "Quat.h"

namespace GD
{
	class QuatApp
	{
	public:
		static void Slerp(Quat &result, const Quat &source, const Quat &target, const float slerpFactor);
		static void SlerpArray(Quat *result, const Quat *source, const Quat *target, const float slerpFactor, const int numQuats);
		static void PrintQuat(const Quat&);
	};
}

#endif 

// ---  End of File ---------------