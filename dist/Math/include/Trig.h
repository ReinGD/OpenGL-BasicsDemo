/*==============================
 Made By ReinGD
 2022
 All rights reserved
==============================*/
#ifndef ENGINE_MATH_TRIG_H
#define ENGINE_MATH_TRIG_H

namespace GD
{
	class Trig
	{
	public:

		// Do your magic here
		static float cos(float);
		static float sin(float);
		static float tan(float);

		static float acos(float);
		static float asin(float);
		static float atan(float);

		static float sqrt(float);
		static float rsqrt(float);

		static void cossin(float&, float&, float);
		static float atan2(float, float);

		static float radians(float degree);
	};
}

#endif

//--- End of File ---
