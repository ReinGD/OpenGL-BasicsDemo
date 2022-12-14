/*==============================
 Made By ReinGD
 2022
 All rights reserved
==============================*/
#ifndef ENGINE_MATH_DEBUG_H
#define ENGINE_MATH_DEBUG_H

namespace GD
{
	// Forward declarations:
	class Vect; 
	class Matrix;
	class Quat;

	// ----------------------------------------------------------------------
	// Output Print for Vect and Matrix
	// ----------------------------------------------------------------------
	class Debug
	{
	public:
		static void Print(const char* pName, const Vect &r);
		static void Print(const char *pName, const Quat &r);
		static void Print(const char* pName, const Matrix& r);

	};

}

#endif

//--- End of File ---
