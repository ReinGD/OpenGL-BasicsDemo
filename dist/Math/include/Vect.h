/*==============================
 Made By ReinGD
 2022
 All rights reserved
==============================*/
#ifndef ENGINE_MATH_VECT_H
#define ENGINE_MATH_VECT_H

// Includes to handle SIMD register types
#include <xmmintrin.h>
#include <smmintrin.h> 

#include "Constants.h"
#include "Debug.h"
#include "Enum.h"

// This file assumes Framework.h is included in executable for Align16

namespace GD
{
	// forward declare
	class Matrix;
	class Quat;

	class Vect final
	{
	public:		   
	// Do your magic here
	//
		Vect();
		Vect(const Vect&);
		Vect& operator=(const Vect&);
		~Vect() = default;

		Vect(const float x, const float y = 0.0f, const float z = 0.0f, const float w = 1.0f);

		//allows for [x],[y],[z],[w] as setters
		float& operator[](x_enum);
		float& operator[](y_enum);
		float& operator[](z_enum);
		float& operator[](w_enum);

		//allows for [x],[y],[z],[w] as getters
		float operator[](x_enum) const;
		float operator[](y_enum) const;
		float operator[](z_enum) const;
		float operator[](w_enum) const;

		//allows for v.x(), v.y(), v.z(), v.w() as setters
		float& x();
		float& y();
		float& z();
		float& w();

		//uppercase variant
		float& X();
		float& Y();
		float& Z();
		float& W();

		//allows for v.x(), v.y(), v.z(), v.w() as getters
		float x() const; 
		float y() const; 
		float z() const; 
		float w() const;

		//uppercase variant
		float X() const;
		float Y() const;
		float Z() const;
		float W() const;


		Vect& operator-=(const Vect&);
		Vect& operator+=(const Vect&);
		Vect& operator*=(const float);
		Vect& operator*=(const Matrix&);

		Vect operator-() const;
		Vect operator+() const;

		friend Vect operator+(const Vect&, const Vect&);
		friend Vect operator-(const Vect&, const Vect&);
		friend Vect operator*(const Vect&, const float);
		friend Vect operator*(const float, const Vect&);
		friend Vect operator*(const Vect&, const Matrix&);
		friend Vect operator*(const Vect&, const Quat&);


		float mag() const;
		float magSqr() const;

		float getAngle(const Vect&);
		float dot(const Vect&) const;
		void outerDot(Matrix&, const Vect&);
		float mdot(const Vect&) const;
		Vect cross(const Vect&) const;
		Vect& norm();
		Vect getNorm() const;

		//setters
		void set(const float x, const float y, const float z, const float w = 1.0f);
		void set(const Vect& in);

		//special
		bool isEqual(const Vect&, float tolerance = MATH_TOLERANCE) const;
		bool isZero(float tolerance = MATH_TOLERANCE) const;

		// for printing
		friend void Debug::Print(const char *pName, const Vect &r);

private:

		union
		{
			__m128	_mv;

			// anonymous struct
			struct
			{
				float _vx;
				float _vy;
				float _vz;
				float _vw;
			};
		};
	};
}

#endif

//--- End of File ---
