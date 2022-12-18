#ifndef ENGINE_MATH_MATRIX_H
#define ENGINE_MATH_MATRIX_H

#include "Vect.h"
#include "Debug.h"

namespace GD
{
	class Quat;

	class Matrix final
	{
	public:

		enum class Special
		{
			Zero,
			Identity
		};

		enum class Rot1
		{
			X,
			Y,
			Z
		};

		enum class Trans
		{
			XYZ
		};

		enum class Scale
		{
			XYZ
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

		enum class Row
		{
			i0,
			i1,
			i2,
			i3
		};

		enum class Rot3
		{
			XYZ,
			XZY,
			YXZ,
			YZX,
			ZXY,
			ZYX,

			XYX,
			XZX,
			YZY,
			YXY,
			ZXZ,
			ZYZ
			// future combos... here
		};

	public:

		// Do your magic here
		//Constructors
		Matrix();
		~Matrix();
		Matrix(const Matrix&);
		Matrix(Special);
		Matrix(Trans, float, float, float);
		Matrix(Trans, Vect);
		Matrix(Scale, float, float, float);
		Matrix(Scale, Vect);
		Matrix(Rot1, float);
		Matrix(Rot3, float, float, float);
		Matrix(Rot, Vect, float);
		Matrix(Orient, Vect DoF, Vect y);
		Matrix(Vect _iv0, Vect _iv1, Vect _iv2, Vect _iv3);
		Matrix(const Quat&);

		//Special Sets []
		float& operator[](m0_enum);
		float& operator[](m1_enum);
		float& operator[](m2_enum);
		float& operator[](m3_enum);
		float& operator[](m4_enum);
		float& operator[](m5_enum);
		float& operator[](m6_enum);
		float& operator[](m7_enum);
		float& operator[](m8_enum);
		float& operator[](m9_enum);
		float& operator[](m10_enum);
		float& operator[](m11_enum);
		float& operator[](m12_enum);
		float& operator[](m13_enum);
		float& operator[](m14_enum);
		float& operator[](m15_enum);

		//Special Gets []
		float operator[](m0_enum) const;
		float operator[](m1_enum) const;
		float operator[](m2_enum) const;
		float operator[](m3_enum) const;
		float operator[](m4_enum) const;
		float operator[](m5_enum) const;
		float operator[](m6_enum) const;
		float operator[](m7_enum) const;
		float operator[](m8_enum) const;
		float operator[](m9_enum) const;
		float operator[](m10_enum) const;
		float operator[](m11_enum) const;
		float operator[](m12_enum) const;
		float operator[](m13_enum) const;
		float operator[](m14_enum) const;
		float operator[](m15_enum) const;

		//Special Sets ()
		float& m0();
		float& m1();
		float& m2();
		float& m3();
		float& m4();
		float& m5();
		float& m6();
		float& m7();
		float& m8();
		float& m9();
		float& m10();
		float& m11();
		float& m12();
		float& m13();
		float& m14();
		float& m15();

		//Special Gets ()
		float m0() const;
		float m1() const;
		float m2() const;
		float m3() const;
		float m4() const;
		float m5() const;
		float m6() const;
		float m7() const;
		float m8() const;
		float m9() const;
		float m10() const;
		float m11() const;
		float m12() const;
		float m13() const;
		float m14() const;
		float m15() const;

		//Set Operations
		void set(Special);
		void set(Trans, float, float, float);
		void set(Trans, Vect);
		void set(Scale, float, float, float);
		void set(Scale, Vect);
		void set(Rot1, float);
		void set(Rot3, float, float, float);
		void set(Vect v0, Vect v1, Vect v2, Vect v3 = Vect(0, 0, 0, 1));
		void set(Rot, Vect, float);
		void set(Orient, Vect DoF, Vect y);
		void set(const Quat&);

		//Row Get/Set
		Vect get(Row);
		void set(Row, Vect);
		void set(Row, float x, float y, float z, float w = 1.0f);

		const Matrix& operator= (const Matrix&);
		Matrix& operator-=(const Matrix&);
		Matrix& operator+=(const Matrix&);
		Matrix operator-();
		Matrix operator+();

		friend Matrix operator+(const Matrix&, const Matrix&);
		friend Matrix operator-(const Matrix&, const Matrix&);
		friend Matrix operator*(const Matrix&, const Matrix&);
		friend Matrix operator*(const float, const Matrix&);
		friend Matrix operator*(const Matrix&, const float);
		friend Matrix operator*(const Matrix&, const Quat&);
		friend Matrix operator*(const Quat&, const Matrix&);


		Matrix& operator*=(const float);
		Matrix& operator*=(const Matrix&);

		const Matrix& T();
		const Matrix getT() const;
		float det() const;
		const Matrix& inv();
		const Matrix getInv() const;

		bool isEqual(Matrix&);
		bool isIdentity();
		bool isIdentity(float tolerance);
		bool isZero();
		bool isRotation() const;


		// For printing
		friend void Debug::Print(const char *pName, const Matrix &r);

	private:
		//helper functions for determinant
		static float det3(Vect, Vect, Vect);
		static float det2(float a, float b, float c, float d);

		static Matrix privQuatToMatrix(const Quat&);

		union
		{

			struct
			{
				Vect _rows[4];
			};


			struct
			{
				Vect _v0;
				Vect _v1;
				Vect _v2;
				Vect _v3;
			};

			struct
			{
				float _m0;
				float _m1;
				float _m2;
				float _m3;
				float _m4;
				float _m5;
				float _m6;
				float _m7;
				float _m8;
				float _m9;
				float _m10;
				float _m11;
				float _m12;
				float _m13;
				float _m14;
				float _m15;
			};
		};
	};
}

#endif

//--- End of File ---
