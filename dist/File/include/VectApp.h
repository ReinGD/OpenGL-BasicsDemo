/*==============================
 Made By ReinGD
 2022
 All rights reserved
==============================*/
#ifndef VectApp_H
#define VectApp_H

#include "Vect.h"

namespace GD
{
	class VectApp
	{

	public:

		// lerp
		static void Lerp(Vect &out, const Vect &a, const Vect &b, const float t);
		// lerp array
		static void LerpArray(Vect *out, const Vect *a, const Vect *b, const float t, const int numVects);

		//static void InverseLerp(float& out, const Vect& a, const Vect& b, const Vect& val);
		static void PrintVect(const Vect& in);
	};
}


#endif 

/**** END of VectApp.h *******************************************************/
