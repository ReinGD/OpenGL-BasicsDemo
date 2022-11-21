#ifndef ENGINE_MATH_QUAT_H
#define ENGINE_MATH_QUAT_H

#include "Debug.h"

//------------------------------------------------------------------------
// 
//  This class contains functions and data structure for a 4-dimensional
//  Quaternions.  The quaternions are internally stored interms of the
//  imaginary components (x,y,z) and the real components (real).
// 
//  In the Math library, quaternions can be thought of as "rotational"
//  matrices, everything that you can represent with rotational matrices
//  you can use with quaternions.  Such as quaternion concatenation,
//  inverses, transpose, normalize, multiplying with matrices, and with
//  vectors.
// 
//------------------------------------------------------------------------
namespace GD
{
	class Matrix;

	class Quat final
	{
	public:
		enum class Rot1
		{
			X,
			Y,
			Z
		};

		enum class Special
		{
			Zero,
			Identity
		};

		enum class Rot
		{
			AxisAngle,
		};

		enum class Orient
		{
			LocalToWorld,
			WorldToLocal
		};

		enum class Rot3
		{
			XYZ
			// future combos... here
		};

	public:

		// Do your magic here
		Quat();
		~Quat();
		Quat(const Matrix&);
		Quat(const float,const float,const float,const float);
		Quat(const Vect&,const float);
		Quat(const Special);
		Quat(const Rot,const Vect&,const float);
		Quat(const Rot1,const float);
		Quat(const Rot3,const float,const float,const float);
		Quat(const Orient,const Vect&,const Vect&);
		Quat(const Vect&);
		
		Quat operator-() const;
		Quat operator+() const;

		Quat& operator-=(const Quat&);
		Quat& operator+=(const Quat&);
		Quat& operator-=(const float);
		Quat& operator+=(const float);
		Quat& operator*=(const float);
		Quat& operator*=(const Matrix&);
		Quat& operator*=(const Quat&);
		Quat& operator/=(const Quat&);
		Quat& operator/=(const float);

		Quat& operator=(const Quat&);

		friend Quat operator+(const Quat&, const Quat&);
		friend Quat operator+(const Quat&, const float);
		friend Quat operator+(const float&, const Quat&);

		friend Quat operator-(const Quat&, const Quat&);
		friend Quat operator-(const Quat&, const float);
		friend Quat operator-(const float&, const Quat&);

		friend Quat operator*(const Quat&, const float);
		friend Quat operator*(const float, const Quat&);
		friend Quat operator*(const Quat&, const Quat&);

		friend Quat operator/(const Quat&, const Quat&);
		friend Quat operator/(const float, const Quat&);
		friend Quat operator/(const Quat&, const float);

		Quat multByElement(const Quat&) const;

		float dot(const Quat&);
		float mag();
		float magSquared();
		float invMagSquared();
		float invMag();
		void Lqcvq(const Vect&, Vect&);
		void Lqvqc(const Vect&, Vect&);


		//sets
		void set(const Quat&);
		void set(const Matrix&);
		void set(const float, const float, const float, const float);
		void set(const Vect&, const float);
		void set(const Rot, const Vect&, const float);
		void set(const Rot1, const float);
		void set(const Special);
		void set(const Orient,const Vect&,const Vect&);
		void setVect(const Vect&);
		void set(Rot3, const float, const float, const float);

		void clear();
		Quat& norm();
		Quat& conj();
		Quat& inv();
		Quat& T();

		//gets
		void getVect(Vect&) const;
		float getAngle() const;
		void getAxis(Vect&) const;
		Quat getNorm();
		Quat getInv();
		Quat getConj();
		Quat getT() const;

		//allows for q.qx(), q.qy(), q.qz(), q.real() as setters
		float& qx();
		float& qy();
		float& qz();
		float& real();

		//allows for q.qx(), q.qy(), q.qz(), q.real() as getters
		float qx() const;
		float qy() const;
		float qz() const;
		float real() const;

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


		//booleans
		bool isEqual(const Quat&,const float in = MATH_TOLERANCE);
		bool isNegEqual(const Quat&,const float in = MATH_TOLERANCE);
		bool isEquivalent(const Quat&,const float in = MATH_TOLERANCE);
		bool isIdentity(const float in = MATH_TOLERANCE);
		bool isNormalized(const float in = MATH_TOLERANCE);
		bool isZero(const float in = MATH_TOLERANCE);
		bool isConjugateEqual(const Quat&,const float in = MATH_TOLERANCE);

		// For printing
		friend void Debug::Print(const char *pName, const Quat &r);

	private:
		static Quat privMatrixToQuat(const Matrix&);

		// anonymous union
		union
		{
			__m128	_mq;

			// anonymous struct
			struct
			{
				float _qx;
				float _qy;
				float _qz;
				float _qw;
			};
		};

	};
}

#endif 

// ---  End of File ---------------
