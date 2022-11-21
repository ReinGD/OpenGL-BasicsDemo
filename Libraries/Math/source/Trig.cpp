#include <math.h>    // <--- ONLY location for <math.h> allowed
#include "Trig.h"

#include <intrin.h>
#include "..\include\Trig.h"
#include <Constants.h>

namespace GD
{

	// Do your magic here

	float Trig::cos(float in)
	{
		return cosf(in);
	}

	float Trig::sin(float in)
	{
		return sinf(in);
	}

	float Trig::tan(float in)
	{
		return tanf(in);
	}

	float Trig::acos(float in)
	{
		return acosf(in);
	}

	float Trig::asin(float in)
	{
		return asinf(in);
	}

	float Trig::atan(float in)
	{
		return atanf(in);
	}

	float Trig::sqrt(float in)
	{
		return sqrtf(in);
	}

	float Trig::rsqrt(float in)
	{
		float result;
		_mm_store_ss(&result, _mm_sqrt_ss(_mm_load_ss(&in)));
		return 1 / result;
	}

	void Trig::cossin(float& _cos, float& _sin, float num)
	{
		_cos = cos(num);
		_sin = sin(num);

	}

	float Trig::atan2(float x0, float x1)
	{
		return atan2f(x0, x1);
	}

}

//--- End of File ---
