/*==============================
 Made By ReinGD
 2022
 All rights reserved
==============================*/
#ifndef ENGINE_MATH_UTIL_H
#define ENGINE_MATH_UTIL_H

namespace GD
{
	class Util
	{
	public:
		static bool isEqual(const float a, const float b, const float epsilon);
		static bool isNotEqual(const float a, const float b, const float epsilon);
		static bool isOne(const float a, const float epsilon);
		static bool isNonZero(const float a, const float epsilon);
		static bool isZero(const float a, const float epsilon);
	};
}

#endif

//--- End of File ---