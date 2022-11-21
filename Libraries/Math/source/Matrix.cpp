#include "MathEngine.h"
#include "QuatApp.h"
#include "VectApp.h"

namespace GD
{
// Do your magic here
   
	Matrix::Matrix()
	{
		memset(_rows, 0, sizeof(_rows));
	}

	Matrix::~Matrix()
	{
		memset(_rows, 0, sizeof(_rows));
	}

	Matrix::Matrix(const Matrix& in)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));
		//copy
		memcpy(_rows, in._rows, sizeof(_rows));
	}

	Matrix::Matrix(Special type)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));

		switch (type)
		{
			case Special::Zero:
				memset(_rows, 0, sizeof(_rows));
				break;
			case Special::Identity:
				Vect v0 = Vect(1, 0, 0, 0);
				Vect v1 = Vect(0, 1, 0, 0);
				Vect v2 = Vect(0, 0, 1, 0);
				Vect v3 = Vect(0, 0, 0, 1);
				this->_v0 = v0;
				this->_v1 = v1;
				this->_v2 = v2;
				this->_v3 = v3;
				break;
		}
	}

	Matrix::Matrix(Trans type, float x, float y, float z)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));

		switch (type)
		{
			case Trans::XYZ:
				Vect v0 = Vect(1, 0, 0, 0);
				Vect v1 = Vect(0, 1, 0, 0);
				Vect v2 = Vect(0, 0, 1, 0);
				Vect v3 = Vect(x, y, z, 1);
				this->_v0 = v0;
				this->_v1 = v1;
				this->_v2 = v2;
				this->_v3 = v3;
				break;
		}
	}

	Matrix::Matrix(Trans type, Vect in)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));

		switch (type)
		{
			case Trans::XYZ:
				Vect v0 = Vect(1, 0, 0, 0);
				Vect v1 = Vect(0, 1, 0, 0);
				Vect v2 = Vect(0, 0, 1, 0);
				Vect v3 = Vect(in[x], in[y], in[z], 1);
				this->_v0 = v0;
				this->_v1 = v1;
				this->_v2 = v2;
				this->_v3 = v3;
				break;
		}
	}

	Matrix::Matrix(Scale type, float x, float y, float z)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));

		switch (type)
		{
		case Scale::XYZ:
			Vect v0 = Vect(x, 0, 0, 0);
			Vect v1 = Vect(0, y, 0, 0);
			Vect v2 = Vect(0, 0, z, 0);
			Vect v3 = Vect(0, 0, 0, 1);
			this->_v0 = v0;
			this->_v1 = v1;
			this->_v2 = v2;
			this->_v3 = v3;
			break;
		}
	}

	Matrix::Matrix(Scale type, Vect in)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));

		switch (type)
		{
		case Scale::XYZ:
			Vect v0 = Vect(in[x], 0, 0, 0);
			Vect v1 = Vect(0, in[y], 0, 0);
			Vect v2 = Vect(0, 0, in[z], 0);
			Vect v3 = Vect(0, 0, 0, 1);
			this->_v0 = v0;
			this->_v1 = v1;
			this->_v2 = v2;
			this->_v3 = v3;
			break;
		}
	}

	Matrix::Matrix(Rot1 type, float theta)
	{
		Vect v0;
		Vect v1;
		Vect v2;
		Vect v3;

		float cosTheta = Trig::cos(theta);
		float sinTheta = Trig::sin(theta);

		switch (type)
		{
		case Rot1::X:
			v0 = Vect(1, 0, 0, 0);
			v1 = Vect(0, cosTheta, sinTheta, 0);
			v2 = Vect(0, -sinTheta, cosTheta, 0);
			v3 = Vect(0, 0, 0, 1);
			break;
		case Rot1::Y:
			v0 = Vect(cosTheta, 0, -sinTheta, 0);
			v1 = Vect(0, 1, 0, 0);
			v2 = Vect(sinTheta, 0, cosTheta, 0);
			v3 = Vect(0, 0, 0, 1);
			break;
		case Rot1::Z:
			v0 = Vect(cosTheta, sinTheta, 0, 0);
			v1 = Vect(-sinTheta, cosTheta, 0, 0);
			v2 = Vect(0, 0, 1, 0);
			v3 = Vect(0, 0, 0, 1);
			break;
		}

		this->_v0 = v0;
		this->_v1 = v1;
		this->_v2 = v2;
		this->_v3 = v3;
	}

	Matrix::Matrix(Rot3 type, float xTheta, float yTheta, float zTheta)
	{
		Vect v0;
		Vect v1;
		Vect v2;
		Vect v3;

		Matrix rotX = Matrix(Rot1::X, xTheta);
		Matrix rotY = Matrix(Rot1::Y, yTheta);
		Matrix rotZ = Matrix(Rot1::Z, zTheta);

		Matrix result;
		switch (type)
		{
		case Rot3::XYZ:
			result = (rotX * rotY) * rotZ;
			break;
		case Rot3::XZY:
			result = (rotX * rotZ) * rotY;
			break;
		case Rot3::YXZ:
			result = (rotY * rotX) * rotZ;
			break;
		case Rot3::YZX:
			result = (rotY * rotZ) * rotX;
			break;
		case Rot3::ZXY:
			result = (rotZ * rotX) * rotY;
			break;
		case Rot3::ZYX:
			result = (rotZ * rotY) * rotX;
			break;
		case Rot3::XYX:
			result = (rotX * rotY) * rotX;
			break;
		case Rot3::XZX:
			result = (rotX * rotZ) * rotX;
			break;
		case Rot3::YZY:
			result = (rotY * rotZ) * rotY;
			break;
		case Rot3::YXY:
			result = (rotY * rotX) * rotY;
			break;
		case Rot3::ZXZ:
			result = (rotZ * rotX) * rotZ;
			break;
		case Rot3::ZYZ:
			result = (rotZ * rotY) * rotZ;
			break;
		default:
			break;
		}

		result._v3 = Vect(0, 0, 0, 1);

		this->_v0 = result._v0;
		this->_v1 = result._v1;
		this->_v2 = result._v2;
		this->_v3 = result._v3;
	}

	Matrix::Matrix(Rot type, Vect in, float _angle)
	{
		UNUSED_VAR(type);

		//get the half angle
		float angle = 0.5f * _angle;

		float cos_a = Trig::cos(angle);
		float sin_a = Trig::sin(angle);

		Vect qV = in.getNorm();
		qV *= sin_a;

		Vect Q = qV;
		Q[w] = cos_a;

		float x2, y2, z2;
		float xx, xy, xz;
		float yy, yz, zz;
		float wx, wy, wz;

		x2 = Q[x] + Q[x];
		y2 = Q[y] + Q[y];
		z2 = Q[z] + Q[z];

		xx = Q[x] * x2;
		xy = Q[x] * y2;
		xz = Q[x] * z2;

		yy = Q[y] * y2;
		yz = Q[y] * z2;
		zz = Q[z] * z2;

		wx = Q[w] * x2;
		wy = Q[w] * y2;
		wz = Q[w] * z2;

		this->_m0 = 1.0f - (yy + zz);
		this->_m1 = xy + wz;
		this->_m2 = xz - wy;
		this->_m3 = 0.0f;

		this->_m4 = xy - wz;
		this->_m5 = 1.0f - (xx + zz);
		this->_m6 = yz + wx;
		this->_m7 = 0.0f;

		this->_m8 = xz + wy;
		this->_m9 = yz - wx;
		this->_m10 = 1.0f - (xx + yy);
		this->_m11 = 0.0f;

		this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix::Matrix(Orient type, Vect DoF, Vect y)
	{
		Vect v0;
		Vect v1;
		Vect v2;
		Vect v3;

		Vect nY = y.getNorm();
		Vect nDoF = DoF.getNorm();

		v0 = nY.cross(nDoF);
		v1 = nDoF.cross(nY).cross(nDoF);
		v2 = nDoF;

		v0[w] = 0.0f;
		v1[w] = 0.0f;
		v2[w] = 0.0f;

		v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);


		Matrix result;

		result._v0 = v0;
		result._v1 = v1;
		result._v2 = v2;
		result._v3 = v3;

		switch (type)
		{
		case Orient::LocalToWorld:

			break;
		case Orient::WorldToLocal:

			result.T();
			break;
		default:
			break;
		}

		this->_v0 = result._v0;
		this->_v1 = result._v1;
		this->_v2 = result._v2;
		this->_v3 = result._v3;
	}

	Matrix::Matrix(const Quat& in)
		:_rows{}
	{
		Matrix result = privQuatToMatrix(in);
		memcpy(this->_rows, result._rows, sizeof(this->_rows));
	}

	float& Matrix::operator[](m0_enum)
	{
		return this->_m0;
	}

	float& Matrix::operator[](m1_enum)
	{
		return this->_m1;
	}

	float& Matrix::operator[](m2_enum)
	{
		return this->_m2;
	}

	float& Matrix::operator[](m3_enum)
	{
		return this->_m3;
	}

	float& Matrix::operator[](m4_enum)
	{
		return this->_m4;
	}

	float& Matrix::operator[](m5_enum)
	{
		return this->_m5;
	}

	float& Matrix::operator[](m6_enum)
	{
		return this->_m6;
	}

	float& Matrix::operator[](m7_enum)
	{
		return this->_m7;
	}

	float& Matrix::operator[](m8_enum)
	{
		return this->_m8;
	}

	float& Matrix::operator[](m9_enum)
	{
		return this->_m9;
	}

	float& Matrix::operator[](m10_enum)
	{
		return this->_m10;
	}

	float& Matrix::operator[](m11_enum)
	{
		return this->_m11;
	}

	float& Matrix::operator[](m12_enum)
	{
		return this->_m12;
	}

	float& Matrix::operator[](m13_enum)
	{
		return this->_m13;
	}

	float& Matrix::operator[](m14_enum)
	{
		return this->_m14;
	}

	float& Matrix::operator[](m15_enum)
	{
		return this->_m15;
	}
	float Matrix::operator[](m0_enum) const
	{
		return this->_m0;
	}

	float Matrix::operator[](m1_enum) const
	{
		return this->_m1;
	}

	float Matrix::operator[](m2_enum) const
	{
		return this->_m2;
	}

	float Matrix::operator[](m3_enum) const
	{
		return this->_m3;
	}

	float Matrix::operator[](m4_enum) const
	{
		return this->_m4;
	}

	float Matrix::operator[](m5_enum) const
	{
		return this->_m5;
	}

	float Matrix::operator[](m6_enum) const
	{
		return this->_m6;
	}

	float Matrix::operator[](m7_enum) const
	{
		return this->_m7;
	}

	float Matrix::operator[](m8_enum) const
	{
		return this->_m8;
	}

	float Matrix::operator[](m9_enum) const
	{
		return this->_m9;
	}

	float Matrix::operator[](m10_enum) const
	{
		return this->_m10;
	}

	float Matrix::operator[](m11_enum) const
	{
		return this->_m11;
	}

	float Matrix::operator[](m12_enum) const
	{
		return this->_m12;
	}

	float Matrix::operator[](m13_enum) const
	{
		return this->_m13;
	}

	float Matrix::operator[](m14_enum) const
	{
		return this->_m14;
	}

	float Matrix::operator[](m15_enum) const
	{
		return this->_m15;
	}

	float& Matrix::m0()
	{
		return this->_m0;
	}

	float& Matrix::m1()
	{
		return this->_m1;
	}

	float& Matrix::m2()
	{
		return this->_m2;
	}

	float& Matrix::m3()
	{
		return this->_m3;
	}

	float& Matrix::m4()
	{
		return this->_m4;
	}

	float& Matrix::m5()
	{
		return this->_m5;
	}

	float& Matrix::m6()
	{
		return this->_m6;
	}

	float& Matrix::m7()
	{
		return this->_m7;
	}

	float& Matrix::m8()
	{
		return this->_m8;
	}

	float& Matrix::m9()
	{
		return this->_m9;
	}

	float& Matrix::m10()
	{
		return this->_m10;
	}

	float& Matrix::m11()
	{
		return this->_m11;
	}

	float& Matrix::m12()
	{
		return this->_m12;
	}

	float& Matrix::m13()
	{
		return this->_m13;
	}

	float& Matrix::m14()
	{
		return this->_m14;
	}

	float& Matrix::m15()
	{
		return this->_m15;
	}

	float Matrix::m0() const
	{
		return this->_m0;
	}

	float Matrix::m1() const
	{
		return this->_m1;
	}

	float Matrix::m2() const
	{
		return this->_m2;
	}

	float Matrix::m3() const
	{
		return this->_m3;
	}

	float Matrix::m4() const
	{
		return this->_m4;
	}

	float Matrix::m5() const
	{
		return this->_m5;
	}

	float Matrix::m6() const
	{
		return this->_m6;
	}

	float Matrix::m7() const
	{
		return this->_m7;
	}

	float Matrix::m8() const
	{
		return this->_m8;
	}

	float Matrix::m9() const
	{
		return this->_m9;
	}

	float Matrix::m10() const
	{
		return this->_m10;
	}

	float Matrix::m11() const
	{
		return this->_m11;
	}

	float Matrix::m12() const
	{
		return this->_m12;
	}

	float Matrix::m13() const
	{
		return this->_m13;
	}

	float Matrix::m14() const
	{
		return this->_m14;
	}

	float Matrix::m15() const
	{
		return this->_m15;
	}
	void Matrix::set(Special type)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));

		const Matrix result = Matrix(type);
		memcpy(_rows, result._rows, sizeof(_rows));

	}
	void Matrix::set(Trans type, float x, float y, float z)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));

		const Matrix result = Matrix(type, x, y, z);
		memcpy(_rows, result._rows, sizeof(_rows));

	}
	void Matrix::set(Trans type, Vect v)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));

		const Matrix result = Matrix(type, v);
		memcpy(_rows, result._rows, sizeof(_rows));
	}
	void Matrix::set(Scale type, float x, float y, float z)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));

		const Matrix result = Matrix(type, x, y, z);
		memcpy(_rows, result._rows, sizeof(_rows));
	}
	void Matrix::set(Scale type, Vect in)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));

		const Matrix result = Matrix(type, in);
		memcpy(_rows, result._rows, sizeof(_rows));
	}
	void Matrix::set(Rot1 rot, float theta)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));

		const Matrix result = Matrix(rot, theta);
		memcpy(_rows, result._rows, sizeof(_rows));
	}
	void Matrix::set(Rot3 type, float xTheta, float yTheta, float zTheta)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));

		const Matrix result = Matrix(type, xTheta, yTheta, zTheta);
		memcpy(_rows, result._rows, sizeof(_rows));
	}
	void Matrix::set(Vect v0, Vect v1, Vect v2, Vect v3)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));

		this->_v0 = v0;
		this->_v1 = v1;
		this->_v2 = v2;
		this->_v3 = v3;
	}
	void Matrix::set(Rot type, Vect v, float _angle)
	{
		UNUSED_VAR(type);
		//get the half angle
		float angle = 0.5f * _angle;

		float cos_a = Trig::cos(angle);
		float sin_a = Trig::sin(angle);

		Vect qV = v.getNorm();
		qV *= sin_a;

		Vect Q = qV;
		Q[w] = cos_a;

		float x2, y2, z2;
		float xx, xy, xz;
		float yy, yz, zz;
		float wx, wy, wz;

		x2 = Q[x] + Q[x];
		y2 = Q[y] + Q[y];
		z2 = Q[z] + Q[z];

		xx = Q[x] * x2;
		xy = Q[x] * y2;
		xz = Q[x] * z2;

		yy = Q[y] * y2;
		yz = Q[y] * z2;
		zz = Q[z] * z2;

		wx = Q[w] * x2;
		wy = Q[w] * y2;
		wz = Q[w] * z2;

		this->_m0 = 1.0f - (yy + zz);
		this->_m1 = xy + wz;
		this->_m2 = xz - wy;
		this->_m3 = 0.0f;

		this->_m4 = xy - wz;
		this->_m5 = 1.0f - (xx + zz);
		this->_m6 = yz + wx;
		this->_m7 = 0.0f;

		this->_m8 = xz + wy;
		this->_m9 = yz - wx;
		this->_m10 = 1.0f - (xx + yy);
		this->_m11 = 0.0f;

		this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
	}
	void Matrix::set(Orient type, Vect DoF, Vect y)
	{
		Vect v0;
		Vect v1;
		Vect v2;
		Vect v3;

		Vect nY = y.getNorm();
		Vect nDoF = DoF.getNorm();

		v0 = nY.cross(nDoF);
		v1 = nDoF.cross(nY).cross(nDoF);
		v2 = nDoF;

		v0[w] = 0.0f;
		v1[w] = 0.0f;
		v2[w] = 0.0f;

		v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);

		Matrix result;

		result._v0 = v0;
		result._v1 = v1;
		result._v2 = v2;
		result._v3 = v3;

		switch (type)
		{
		case Orient::LocalToWorld:

			break;
		case Orient::WorldToLocal:

			result.T();
			break;
		default:
			break;
		}

		this->_v0 = result._v0;
		this->_v1 = result._v1;
		this->_v2 = result._v2;
		this->_v3 = result._v3;
	}
	void Matrix::set(const Quat& in)
	{
		memset(this->_rows, 0, sizeof(this->_rows));

		const Matrix result = privQuatToMatrix(in);
		memcpy(this->_rows, result._rows, sizeof(this->_rows));
	}
	Vect Matrix::get(Row row)
	{
		Vect result;

		switch (row)
		{
		case Row::i0:
			result = this->_v0;
			break;
		case Row::i1:
			result = this->_v1;
			break;
		case Row::i2:
			result = this->_v2;
			break;
		case Row::i3:
			result = this->_v3;
			break;
		default:
			break;
		}

		return result;
	}
	void Matrix::set(Row row, Vect v)
	{
		switch (row)
		{
		case Row::i0:
			this->_v0 = v;
			break;
		case Row::i1:
			this->_v1 = v;
			break;
		case Row::i2:
			this->_v2 = v;
			break;
		case Row::i3:
			this->_v3 = v;
			break;
		default:
			break;
		}
	}
	void Matrix::set(Row row, float x, float y, float z, float w)
	{
		Vect v = Vect(x, y, z, w);
		switch (row)
		{
		case Row::i0:
			this->_v0 = v;
			break;
		case Row::i1:
			this->_v1 = v;
			break;
		case Row::i2:
			this->_v2 = v;
			break;
		case Row::i3:
			this->_v3 = v;
			break;
		default:
			break;
		}
	}
	const Matrix& Matrix::operator=(const Matrix& in)
	{
		//clean
		memset(_rows, 0, sizeof(_rows));
		//copy
		memcpy(_rows, in._rows, sizeof(_rows));
		return *this;
	}
	Matrix::Matrix(Vect _iv0, Vect _iv1, Vect _iv2, Vect _iv3)
		:_rows{}
	{
		
		this->_v0 = _iv0;
		this->_v1 = _iv1;
		this->_v2 = _iv2;
		this->_v3 = _iv3;

	}
	Matrix& Matrix::operator-=(const Matrix& in)
	{
		this->_v0[x] -= in._v0[x];
		this->_v0[y] -= in._v0[y];
		this->_v0[z] -= in._v0[z];
		this->_v0[w] -= in._v0[w];

		this->_v1[x] -= in._v1[x];
		this->_v1[y] -= in._v1[y];
		this->_v1[z] -= in._v1[z];
		this->_v1[w] -= in._v1[w];

		this->_v2[x] -= in._v2[x];
		this->_v2[y] -= in._v2[y];
		this->_v2[z] -= in._v2[z];
		this->_v2[w] -= in._v2[w];

		this->_v3[x] -= in._v3[x];
		this->_v3[y] -= in._v3[y];
		this->_v3[z] -= in._v3[z];
		this->_v3[w] -= in._v3[w];

		return *this;
	}
	Matrix& Matrix::operator+=(const Matrix& in)
	{
		this->_v0[x] += in._v0[x];
		this->_v0[y] += in._v0[y];
		this->_v0[z] += in._v0[z];
		this->_v0[w] += in._v0[w];

		this->_v1[x] += in._v1[x];
		this->_v1[y] += in._v1[y];
		this->_v1[z] += in._v1[z];
		this->_v1[w] += in._v1[w];

		this->_v2[x] += in._v2[x];
		this->_v2[y] += in._v2[y];
		this->_v2[z] += in._v2[z];
		this->_v2[w] += in._v2[w];

		this->_v3[x] += in._v3[x];
		this->_v3[y] += in._v3[y];
		this->_v3[z] += in._v3[z];
		this->_v3[w] += in._v3[w];

		return *this;
	}
	Matrix Matrix::operator-()
	{
		Matrix result;
		result._v0 = Vect(-this->_v0[x], -this->_v0[y], -this->_v0[z], -this->_v0[w]);
		result._v1 = Vect(-this->_v1[x], -this->_v1[y], -this->_v1[z], -this->_v1[w]);
		result._v2 = Vect(-this->_v2[x], -this->_v2[y], -this->_v2[z], -this->_v2[w]);
		result._v3 = Vect(-this->_v3[x], -this->_v3[y], -this->_v3[z], -this->_v3[w]);
		return result;
	}
	Matrix Matrix::operator+()
	{
		Matrix result;
		result._v0 = Vect(this->_v0[x], this->_v0[y], this->_v0[z], this->_v0[w]);
		result._v1 = Vect(this->_v1[x], this->_v1[y], this->_v1[z], this->_v1[w]);
		result._v2 = Vect(this->_v2[x], this->_v2[y], this->_v2[z], this->_v2[w]);
		result._v3 = Vect(this->_v3[x], this->_v3[y], this->_v3[z], this->_v3[w]);
		return result;
	}
	Matrix& Matrix::operator*=(const float scale)
	{
		this->_v0 = Vect(scale * this->_v0[x], scale * this->_v0[y], scale * this->_v0[z], scale * this->_v0[w]);
		this->_v1 = Vect(scale * this->_v1[x], scale * this->_v1[y], scale * this->_v1[z], scale * this->_v1[w]);
		this->_v2 = Vect(scale * this->_v2[x], scale * this->_v2[y], scale * this->_v2[z], scale * this->_v2[w]);
		this->_v3 = Vect(scale * this->_v3[x], scale * this->_v3[y], scale * this->_v3[z], scale * this->_v3[w]);
		return *this;
	}
	Matrix& Matrix::operator*=(const Matrix& mIn)
	{
		Matrix mTranspose = mIn.getT();
		Vect result0;
		Matrix in1 = *this;

		result0[x] = in1._v0.mdot(mTranspose._v0);
		result0[y] = in1._v0.mdot(mTranspose._v1);
		result0[z] = in1._v0.mdot(mTranspose._v2);
		result0[w] = in1._v0.mdot(mTranspose._v3);

		Vect result1;
		result1[x] = in1._v1.mdot(mTranspose._v0);
		result1[y] = in1._v1.mdot(mTranspose._v1);
		result1[z] = in1._v1.mdot(mTranspose._v2);
		result1[w] = in1._v1.mdot(mTranspose._v3);

		Vect result2;
		result2[x] = in1._v2.mdot(mTranspose._v0);
		result2[y] = in1._v2.mdot(mTranspose._v1);
		result2[z] = in1._v2.mdot(mTranspose._v2);
		result2[w] = in1._v2.mdot(mTranspose._v3);

		Vect result3;
		result3[x] = in1._v3.mdot(mTranspose._v0);
		result3[y] = in1._v3.mdot(mTranspose._v1);
		result3[z] = in1._v3.mdot(mTranspose._v2);
		result3[w] = in1._v3.mdot(mTranspose._v3);

		this->_v0 = result0;
		this->_v1 = result1;
		this->_v2 = result2;
		this->_v3 = result3;

		return *this;
	}
	const Matrix& Matrix::T()
	{
		Vect v0 = this->_v0;
		Vect v1 = this->_v1;
		Vect v2 = this->_v2;
		Vect v3 = this->_v3;

		Vect _t1 = Vect(v0.x(), v1.x(), v2.x(), v3.x());
		Vect _t2 = Vect(v0.y(), v1.y(), v2.y(), v3.y());
		Vect _t3 = Vect(v0.z(), v1.z(), v2.z(), v3.z());
		Vect _t4 = Vect(v0.w(), v1.w(), v2.w(), v3.w());

		this->_v0 = _t1;
		this->_v1 = _t2;
		this->_v2 = _t3;
		this->_v3 = _t4;
		return *this;
	}
	const Matrix Matrix::getT() const
	{
		Vect _t1 = Vect(this->_v0.x(), this->_v1.x(), this->_v2.x(), this->_v3.x());
		Vect _t2 = Vect(this->_v0.y(), this->_v1.y(), this->_v2.y(), this->_v3.y());
		Vect _t3 = Vect(this->_v0.z(), this->_v1.z(), this->_v2.z(), this->_v3.z());
		Vect _t4 = Vect(this->_v0.w(), this->_v1.w(), this->_v2.w(), this->_v3.w());

		return Matrix(_t1, _t2, _t3, _t4);
	}
	float Matrix::det() const
	{
		float det = 0;

		float det_1 = det3(Vect(this->_v1.y(), this->_v1.z(), this->_v1.w()),
			Vect(this->_v2.y(), this->_v2.z(), this->_v2.w()),
			Vect(this->_v3.y(), this->_v3.z(), this->_v3.w()));

		float det_2 = det3(Vect(this->_v1.x(), this->_v1.z(), this->_v1.w()),
			Vect(this->_v2.x(), this->_v2.z(), this->_v2.w()),
			Vect(this->_v3.x(), this->_v3.z(), this->_v3.w()));

		float det_3 = det3(Vect(this->_v1.x(), this->_v1.y(), this->_v1.w()),
			Vect(this->_v2.x(), this->_v2.y(), this->_v2.w()),
			Vect(this->_v3.x(), this->_v3.y(), this->_v3.w()));

		float det_4 = det3(Vect(this->_v1.x(), this->_v1.y(), this->_v1.z()),
			Vect(this->_v2.x(), this->_v2.y(), this->_v2.z()),
			Vect(this->_v3.x(), this->_v3.y(), this->_v3.z()));

		//+m0 -m1 +m3 -m4
		float first = this->_v0[x] * det_1;
		float second = this->_v0[y] * det_2;
		float third = this->_v0[z] * det_3;
		float fourth = this->_v0[w] * det_4;


		det = first - second + third - fourth;

		return det;
	}
	const Matrix& Matrix::inv()
	{
		/*
					+ - + -
					- + - +
					+ - + -
					- + - +
				*/


				//Get the Adjugate Matrix first then
				//multiply the reciprocal determinant by it
				//transpose it


		float det_0 = det3(Vect(this->_v1.y(), this->_v1.z(), this->_v1.w()),
			Vect(this->_v2.y(), this->_v2.z(), this->_v2.w()),
			Vect(this->_v3.y(), this->_v3.z(), this->_v3.w()));

		float det_1 = det3(Vect(this->_v1.x(), this->_v1.z(), this->_v1.w()),
			Vect(this->_v2.x(), this->_v2.z(), this->_v2.w()),
			Vect(this->_v3.x(), this->_v3.z(), this->_v3.w()));

		float det_2 = det3(Vect(this->_v1.x(), this->_v1.y(), this->_v1.w()),
			Vect(this->_v2.x(), this->_v2.y(), this->_v2.w()),
			Vect(this->_v3.x(), this->_v3.y(), this->_v3.w()));

		float det_3 = det3(Vect(this->_v1.x(), this->_v1.y(), this->_v1.z()),
			Vect(this->_v2.x(), this->_v2.y(), this->_v2.z()),
			Vect(this->_v3.x(), this->_v3.y(), this->_v3.z()));



		float det_4 = det3(Vect(this->_v0.y(), this->_v0.z(), this->_v0.w()),
			Vect(this->_v2.y(), this->_v2.z(), this->_v2.w()),
			Vect(this->_v3.y(), this->_v3.z(), this->_v3.w()));

		float det_5 = det3(Vect(this->_v0.x(), this->_v0.z(), this->_v0.w()),
			Vect(this->_v2.x(), this->_v2.z(), this->_v2.w()),
			Vect(this->_v3.x(), this->_v3.z(), this->_v3.w()));

		float det_6 = det3(Vect(this->_v0.x(), this->_v0.y(), this->_v0.w()),
			Vect(this->_v2.x(), this->_v2.y(), this->_v2.w()),
			Vect(this->_v3.x(), this->_v3.y(), this->_v3.w()));

		float det_7 = det3(Vect(this->_v0.x(), this->_v0.y(), this->_v0.z()),
			Vect(this->_v2.x(), this->_v2.y(), this->_v2.z()),
			Vect(this->_v3.x(), this->_v3.y(), this->_v3.z()));



		float det_8 = det3(Vect(this->_v0.y(), this->_v0.z(), this->_v0.w()),
			Vect(this->_v1.y(), this->_v1.z(), this->_v1.w()),
			Vect(this->_v3.y(), this->_v3.z(), this->_v3.w()));

		float det_9 = det3(Vect(this->_v0.x(), this->_v0.z(), this->_v0.w()),
			Vect(this->_v1.x(), this->_v1.z(), this->_v1.w()),
			Vect(this->_v3.x(), this->_v3.z(), this->_v3.w()));

		float det_10 = det3(Vect(this->_v0.x(), this->_v0.y(), this->_v0.w()),
			Vect(this->_v1.x(), this->_v1.y(), this->_v1.w()),
			Vect(this->_v3.x(), this->_v3.y(), this->_v3.w()));

		float det_11 = det3(Vect(this->_v0.x(), this->_v0.y(), this->_v0.z()),
			Vect(this->_v1.x(), this->_v1.y(), this->_v1.z()),
			Vect(this->_v3.x(), this->_v3.y(), this->_v3.z()));



		float det_12 = det3(Vect(this->_v0.y(), this->_v0.z(), this->_v0.w()),
			Vect(this->_v1.y(), this->_v1.z(), this->_v1.w()),
			Vect(this->_v2.y(), this->_v2.z(), this->_v2.w()));

		float det_13 = det3(Vect(this->_v0.x(), this->_v0.z(), this->_v0.w()),
			Vect(this->_v1.x(), this->_v1.z(), this->_v1.w()),
			Vect(this->_v2.x(), this->_v2.z(), this->_v2.w()));

		float det_14 = det3(Vect(this->_v0.x(), this->_v0.y(), this->_v0.w()),
			Vect(this->_v1.x(), this->_v1.y(), this->_v1.w()),
			Vect(this->_v2.x(), this->_v2.y(), this->_v2.w()));

		float det_15 = det3(Vect(this->_v0.x(), this->_v0.y(), this->_v0.z()),
			Vect(this->_v1.x(), this->_v1.y(), this->_v1.z()),
			Vect(this->_v2.x(), this->_v2.y(), this->_v2.z()));

		Matrix adj;
		adj._v0 = Vect(det_0, -det_1, det_2, -det_3);
		adj._v1 = Vect(-det_4, det_5, -det_6, det_7);
		adj._v2 = Vect(det_8, -det_9, det_10, -det_11);
		adj._v3 = Vect(-det_12, det_13, -det_14, det_15);

		float rDet = 1 / this->det();

		Matrix inverse = rDet * adj;

		this->_v0 = inverse._v0;
		this->_v1 = inverse._v1;
		this->_v2 = inverse._v2;
		this->_v3 = inverse._v3;

		this->T();
		return *this;
	}
	const Matrix Matrix::getInv() const
	{
		/*
							+ - + -
							- + - +
							+ - + -
							- + - +
				*/

				//Get the Adjugate Matrix first then
				//multiply the reciprocal determinant by it
				//transpose it

		float det_0 = det3(Vect(this->_v1.y(), this->_v1.z(), this->_v1.w()),
			Vect(this->_v2.y(), this->_v2.z(), this->_v2.w()),
			Vect(this->_v3.y(), this->_v3.z(), this->_v3.w()));

		float det_1 = det3(Vect(this->_v1.x(), this->_v1.z(), this->_v1.w()),
			Vect(this->_v2.x(), this->_v2.z(), this->_v2.w()),
			Vect(this->_v3.x(), this->_v3.z(), this->_v3.w()));

		float det_2 = det3(Vect(this->_v1.x(), this->_v1.y(), this->_v1.w()),
			Vect(this->_v2.x(), this->_v2.y(), this->_v2.w()),
			Vect(this->_v3.x(), this->_v3.y(), this->_v3.w()));

		float det_3 = det3(Vect(this->_v1.x(), this->_v1.y(), this->_v1.z()),
			Vect(this->_v2.x(), this->_v2.y(), this->_v2.z()),
			Vect(this->_v3.x(), this->_v3.y(), this->_v3.z()));



		float det_4 = det3(Vect(this->_v0.y(), this->_v0.z(), this->_v0.w()),
			Vect(this->_v2.y(), this->_v2.z(), this->_v2.w()),
			Vect(this->_v3.y(), this->_v3.z(), this->_v3.w()));

		float det_5 = det3(Vect(this->_v0.x(), this->_v0.z(), this->_v0.w()),
			Vect(this->_v2.x(), this->_v2.z(), this->_v2.w()),
			Vect(this->_v3.x(), this->_v3.z(), this->_v3.w()));

		float det_6 = det3(Vect(this->_v0.x(), this->_v0.y(), this->_v0.w()),
			Vect(this->_v2.x(), this->_v2.y(), this->_v2.w()),
			Vect(this->_v3.x(), this->_v3.y(), this->_v3.w()));

		float det_7 = det3(Vect(this->_v0.x(), this->_v0.y(), this->_v0.z()),
			Vect(this->_v2.x(), this->_v2.y(), this->_v2.z()),
			Vect(this->_v3.x(), this->_v3.y(), this->_v3.z()));



		float det_8 = det3(Vect(this->_v0.y(), this->_v0.z(), this->_v0.w()),
			Vect(this->_v1.y(), this->_v1.z(), this->_v1.w()),
			Vect(this->_v3.y(), this->_v3.z(), this->_v3.w()));

		float det_9 = det3(Vect(this->_v0.x(), this->_v0.z(), this->_v0.w()),
			Vect(this->_v1.x(), this->_v1.z(), this->_v1.w()),
			Vect(this->_v3.x(), this->_v3.z(), this->_v3.w()));

		float det_10 = det3(Vect(this->_v0.x(), this->_v0.y(), this->_v0.w()),
			Vect(this->_v1.x(), this->_v1.y(), this->_v1.w()),
			Vect(this->_v3.x(), this->_v3.y(), this->_v3.w()));

		float det_11 = det3(Vect(this->_v0.x(), this->_v0.y(), this->_v0.z()),
			Vect(this->_v1.x(), this->_v1.y(), this->_v1.z()),
			Vect(this->_v3.x(), this->_v3.y(), this->_v3.z()));



		float det_12 = det3(Vect(this->_v0.y(), this->_v0.z(), this->_v0.w()),
			Vect(this->_v1.y(), this->_v1.z(), this->_v1.w()),
			Vect(this->_v2.y(), this->_v2.z(), this->_v2.w()));

		float det_13 = det3(Vect(this->_v0.x(), this->_v0.z(), this->_v0.w()),
			Vect(this->_v1.x(), this->_v1.z(), this->_v1.w()),
			Vect(this->_v2.x(), this->_v2.z(), this->_v2.w()));

		float det_14 = det3(Vect(this->_v0.x(), this->_v0.y(), this->_v0.w()),
			Vect(this->_v1.x(), this->_v1.y(), this->_v1.w()),
			Vect(this->_v2.x(), this->_v2.y(), this->_v2.w()));

		float det_15 = det3(Vect(this->_v0.x(), this->_v0.y(), this->_v0.z()),
			Vect(this->_v1.x(), this->_v1.y(), this->_v1.z()),
			Vect(this->_v2.x(), this->_v2.y(), this->_v2.z()));

		Matrix adj;
		adj._v0 = Vect(det_0, -det_1, det_2, -det_3);
		adj._v1 = Vect(-det_4, det_5, -det_6, det_7);
		adj._v2 = Vect(det_8, -det_9, det_10, -det_11);
		adj._v3 = Vect(-det_12, det_13, -det_14, det_15);

		float rDet = 1 / this->det();

		Matrix inverse = rDet * adj;
		inverse.T();

		return inverse;
	}

	bool Matrix::isEqual(Matrix& in)
	{
		return	this->_v0.isEqual(in._v0) &&
				this->_v1.isEqual(in._v1) &&
				this->_v2.isEqual(in._v2) &&
				this->_v3.isEqual(in._v3);
	}

	bool Matrix::isIdentity()
	{
		return	this->_v0.isEqual(Vect(1, 0, 0, 0)) &&
				this->_v1.isEqual(Vect(0, 1, 0, 0)) &&
				this->_v2.isEqual(Vect(0, 0, 1, 0)) &&
				this->_v3.isEqual(Vect(0, 0, 0, 1));
	}

	bool Matrix::isIdentity(float tolerance)
	{
		return	this->_v0.isEqual(Vect(1, 0, 0, 0), tolerance) &&
				this->_v1.isEqual(Vect(0, 1, 0, 0), tolerance) &&
				this->_v2.isEqual(Vect(0, 0, 1, 0), tolerance) &&
				this->_v3.isEqual(Vect(0, 0, 0, 1), tolerance);
	}

	bool Matrix::isZero()
	{
		return	this->_v0.isZero() && 
				this->_v1.isZero() && 
				this->_v2.isZero() && 
				this->_v3.isZero();
	}

	bool Matrix::isRotation() const
	{
		Matrix qTq = *this * this->getT();
		Matrix identity = Matrix(Special::Identity);
		return qTq.isEqual(identity);
	}

	float Matrix::det3(Vect v1, Vect v2, Vect v3)
	{
		float first = v1[x] * ((v2[y] * v3[z]) - (v2[z] * v3[y]));
		float second = v1[y] * ((v2[x] * v3[z]) - (v2[z] * v3[x]));
		float third = v1[z] * ((v2[x] * v3[y]) - (v2[y] * v3[x]));
		return first - second + third;
	}
	float Matrix::det2(float a, float b, float c, float d)
	{
		return a * b - c * d;
	}

	Matrix Matrix::privQuatToMatrix(const Quat& _q)
	{

		Quat q = Quat(_q).getNorm();

		float invSlength = q.invMagSquared();

		float qXX = q[x] * q[x];
		float qYY = q[y] * q[y];
		float qZZ = q[z] * q[z];
		float qXY = q[x] * q[y];
		float qXZ = q[x] * q[z];
		float qZY = q[z] * q[y];
		float qWX = q[w] * q[x];
		float qWY = q[w] * q[y];
		float qWZ = q[w] * q[z];


		Vect v0 = Vect(1.0f - 2.0f * (qYY + qZZ) * invSlength,
							  2.0f * (qXY + qWZ) * invSlength,
							  2.0f * (qXZ - qWY) * invSlength,
							  0.0f);

		Vect v1 = Vect(		  2.0f * (qXY - qWZ) * invSlength,
					   1.0f - 2.0f * (qXX + qZZ) * invSlength,
							  2.0f * (qZY + qWX) * invSlength,
							  0.0f);

		Vect v2 = Vect(		  2.0f * (qXZ + qWY) * invSlength,
							  2.0f * (qZY - qWX) * invSlength,
					   1.0f - 2.0f * (qXX + qYY) * invSlength,
							  0.0f);

		Vect v3 = Vect(0.0f,
					   0.0f,
					   0.0f,
					   1.0f);

		Matrix result;
		result.set(v0,v1,v2,v3);
		return result;
	}

	Matrix operator+(const Matrix& A, const Matrix& B)
	{
		Matrix result;
		result._v0[x] = A._v0[x] + B._v0[x];
		result._v0[y] = A._v0[y] + B._v0[y];
		result._v0[z] = A._v0[z] + B._v0[z];
		result._v0[w] = A._v0[w] + B._v0[w];

		result._v1[x] = A._v1[x] + B._v1[x];
		result._v1[y] = A._v1[y] + B._v1[y];
		result._v1[z] = A._v1[z] + B._v1[z];
		result._v1[w] = A._v1[w] + B._v1[w];

		result._v2[x] = A._v2[x] + B._v2[x];
		result._v2[y] = A._v2[y] + B._v2[y];
		result._v2[z] = A._v2[z] + B._v2[z];
		result._v2[w] = A._v2[w] + B._v2[w];

		result._v3[x] = A._v3[x] + B._v3[x];
		result._v3[y] = A._v3[y] + B._v3[y];
		result._v3[z] = A._v3[z] + B._v3[z];
		result._v3[w] = A._v3[w] + B._v3[w];

		return result;
	}
	Matrix operator-(const Matrix& A, const Matrix& B)
	{
		Matrix result;

		result._v0[x] = A._v0[x] - B._v0[x];
		result._v0[y] = A._v0[y] - B._v0[y];
		result._v0[z] = A._v0[z] - B._v0[z];
		result._v0[w] = A._v0[w] - B._v0[w];

		result._v1[x] = A._v1[x] - B._v1[x];
		result._v1[y] = A._v1[y] - B._v1[y];
		result._v1[z] = A._v1[z] - B._v1[z];
		result._v1[w] = A._v1[w] - B._v1[w];

		result._v2[x] = A._v2[x] - B._v2[x];
		result._v2[y] = A._v2[y] - B._v2[y];
		result._v2[z] = A._v2[z] - B._v2[z];
		result._v2[w] = A._v2[w] - B._v2[w];

		result._v3[x] = A._v3[x] - B._v3[x];
		result._v3[y] = A._v3[y] - B._v3[y];
		result._v3[z] = A._v3[z] - B._v3[z];
		result._v3[w] = A._v3[w] - B._v3[w];

		return result;
	}
	Matrix operator*(const Matrix& A, const Matrix& B)
	{
		Matrix mTranspose = B.getT();
		Vect result0;
		Matrix in1 = A;

		result0[x] = in1._v0.mdot(mTranspose._v0);
		result0[y] = in1._v0.mdot(mTranspose._v1);
		result0[z] = in1._v0.mdot(mTranspose._v2);
		result0[w] = in1._v0.mdot(mTranspose._v3);

		Vect result1;
		result1[x] = in1._v1.mdot(mTranspose._v0);
		result1[y] = in1._v1.mdot(mTranspose._v1);
		result1[z] = in1._v1.mdot(mTranspose._v2);
		result1[w] = in1._v1.mdot(mTranspose._v3);

		Vect result2;
		result2[x] = in1._v2.mdot(mTranspose._v0);
		result2[y] = in1._v2.mdot(mTranspose._v1);
		result2[z] = in1._v2.mdot(mTranspose._v2);
		result2[w] = in1._v2.mdot(mTranspose._v3);

		Vect result3;
		result3[x] = in1._v3.mdot(mTranspose._v0);
		result3[y] = in1._v3.mdot(mTranspose._v1);
		result3[z] = in1._v3.mdot(mTranspose._v2);
		result3[w] = in1._v3.mdot(mTranspose._v3);



		Matrix result = Matrix(result0, result1, result2, result3);
		return result;
	}
	Matrix operator*(const float scale, const Matrix& mIn)
	{
		Matrix result;
		result._v0 = Vect(scale * mIn._v0[x], scale * mIn._v0[y], scale * mIn._v0[z], scale * mIn._v0[w]);
		result._v1 = Vect(scale * mIn._v1[x], scale * mIn._v1[y], scale * mIn._v1[z], scale * mIn._v1[w]);
		result._v2 = Vect(scale * mIn._v2[x], scale * mIn._v2[y], scale * mIn._v2[z], scale * mIn._v2[w]);
		result._v3 = Vect(scale * mIn._v3[x], scale * mIn._v3[y], scale * mIn._v3[z], scale * mIn._v3[w]);
		return result;
	}
	Matrix operator*(const Matrix& mIn, const float scale)
	{
		Matrix result;
		result._v0 = Vect(scale * mIn._v0[x], scale * mIn._v0[y], scale * mIn._v0[z], scale * mIn._v0[w]);
		result._v1 = Vect(scale * mIn._v1[x], scale * mIn._v1[y], scale * mIn._v1[z], scale * mIn._v1[w]);
		result._v2 = Vect(scale * mIn._v2[x], scale * mIn._v2[y], scale * mIn._v2[z], scale * mIn._v2[w]);
		result._v3 = Vect(scale * mIn._v3[x], scale * mIn._v3[y], scale * mIn._v3[z], scale * mIn._v3[w]);
		return result;
	}
	Matrix operator*(const Matrix& A, const Quat& B)
	{
		const Matrix mB = Matrix::privQuatToMatrix(B);
        return  A * mB;
	}
	Matrix operator*(const Quat& A, const Matrix& B)
	{
        const Matrix mA = Matrix(A);
        return mA * B;
	}
}

// ---  End of File --------------
