#include "Vect.h"
#include "MathEngine.h"

namespace GD
{

	// Do your magic here

	Vect::Vect()
		:_vx(0.0f), _vy(0.0f), _vz(0.0f), _vw(1.0f)
	{
		//initializer list handles this
	}

	Vect::Vect(const Vect& input)
		: _vx(input._vx), _vy(input._vy), _vz(input._vz), _vw(input._vw)
	{
		//initializer list handles this
	}

	Vect& Vect::operator=(const Vect& input)
	{
		//clean
		this->_vx = 0.0f;
		this->_vy = 0.0f;
		this->_vz = 0.0f;
		this->_vw = 0.0f;

		//copy
		this->_vx = input._vx;
		this->_vy = input._vy;
		this->_vz = input._vz;
		this->_vw = input._vw;

		return *this;
	}

	Vect::Vect(const float x, const float y, const float z, const float w)
		:_vx(x), _vy(y), _vz(z), _vw(w)
	{
		//initializer list handles this
	}

	float& Vect::operator[](x_enum)
	{
		return this->_vx;
	}

	float& Vect::operator[](y_enum)
	{
		return this->_vy;
	}

	float& Vect::operator[](z_enum)
	{
		return this->_vz;
	}

	float& Vect::operator[](w_enum)
	{
		return this->_vw;
	}

	float Vect::operator[](x_enum) const
	{
		return this->_vx;
	}

	float Vect::operator[](y_enum) const
	{
		return this->_vy;
	}

	float Vect::operator[](z_enum) const
	{
		return this->_vz;
	}

	float Vect::operator[](w_enum) const
	{
		return this->_vw;
	}

	//lowercase setters
	float& Vect::x()
	{
		return this->_vx;
	}

	float& Vect::y()
	{
		return this->_vy;
	}

	float& Vect::z()
	{
		return this->_vz;
	}

	float& Vect::w()
	{
		return this->_vw;
	}

	//uppercase setters
	float& Vect::X()
	{
		return this->_vx;
	}

	float& Vect::Y()
	{
		return this->_vy;
	}

	float& Vect::Z()
	{
		return this->_vz;
	}

	float& Vect::W()
	{
		return this->_vw;
	}


	//lowercase getters
	float Vect::x() const
	{
		return this->_vx;
	}

	float Vect::y() const
	{
		return this->_vy;
	}

	float Vect::z() const
	{
		return this->_vz;
	}

	float Vect::w() const
	{
		return this->_vw;
	}

	//uppercase getters
	float Vect::X() const
	{
		return this->_vx;
	}

	float Vect::Y() const
	{
		return this->_vy;
	}

	float Vect::Z() const
	{
		return this->_vz;
	}

	float Vect::W() const
	{
		return this->_vw;
	}

	Vect operator+(const Vect& vA, const Vect& vB)
	{
		Vect result;
		result._vx = vA._vx + vB._vx;
		result._vy = vA._vy + vB._vy;
		result._vz = vA._vz + vB._vz;
		result._vw = 1.0f;
		return result;
	}

	Vect operator-(const Vect& vA, const Vect& vB)
	{
		Vect result;
		result._vx = vA._vx - vB._vx;
		result._vy = vA._vy - vB._vy;
		result._vz = vA._vz - vB._vz;
		result._vw = 1.0f;
		return result;
	}

	Vect operator*(const Vect& vA, const float s)
	{
		Vect v;
		v._vx = vA._vx * s;
		v._vy = vA._vy * s;
		v._vz = vA._vz * s;
		v._vw = 1.0f;
		return v;
	}

	Vect operator*(const float s, const Vect& vA) 
	{
		Vect v;
		v._vx = s * vA._vx;
		v._vy = s * vA._vy;
		v._vz = s * vA._vz;
		v._vw = 1.0f;
		return v;
	}

	Vect operator*(const Vect& in, const Matrix& mIn)
	{
		Matrix trans = mIn;

		Vect v0 = Vect(trans[m0], trans[m4], trans[m8], trans[m12]);
		Vect v1 = Vect(trans[m1], trans[m5], trans[m9], trans[m13]);
		Vect v2 = Vect(trans[m2], trans[m6], trans[m10], trans[m14]);
		Vect v3 = Vect(trans[m3], trans[m7], trans[m11], trans[m15]);

		Vect result = in;
		Vect vIn = in;

		vIn._vx = result.mdot(v0);
		vIn._vy = result.mdot(v1);
		vIn._vz = result.mdot(v2);
		vIn._vw = result.mdot(v3);
		return vIn;
	}

	Vect operator*(const Vect& v, const Quat& q)
	{
		Matrix m = Matrix(q);
		Vect result = v * m;
		return result;
	}

	Vect& Vect::operator-=(const Vect& in)
	{
		this->_vx -= in._vx;
		this->_vy -= in._vy;
		this->_vz -= in._vz;
		this->_vw = 1.0f;
		return *this;
	}

	Vect& Vect::operator+=(const Vect& in)
	{
		this->_vx += in._vx;
		this->_vy += in._vy;
		this->_vz += in._vz;
		this->_vw = 1.0f;

		return *this;
	}

	Vect& Vect::operator*=(const float in)
	{
		this->_vx = this->_vx * in;
		this->_vy = this->_vy * in;
		this->_vz = this->_vz * in;
		this->_vw = 1.0f;
		return *this;
	}


	Vect& Vect::operator*=(const Matrix& in)
	{
		Matrix trans = in;

		Vect v0 = Vect(trans[m0], trans[m4], trans[m8], trans[m12]);
		Vect v1 = Vect(trans[m1], trans[m5], trans[m9], trans[m13]);
		Vect v2 = Vect(trans[m2], trans[m6], trans[m10], trans[m14]);
		Vect v3 = Vect(trans[m3], trans[m7], trans[m11], trans[m15]);

		Vect result = *this;

		this->_vx = result.mdot(v0);
		this->_vy = result.mdot(v1);
		this->_vz = result.mdot(v2);
		this->_vw = result.mdot(v3);
		return *this;
	}

	Vect Vect::operator-() const
	{
		Vect v;
		v._vx = -_vx;
		v._vy = -_vy;
		v._vz = -_vz;
		v._vw = 1.0f;
		return v;
	}

	Vect Vect::operator+() const
	{
		Vect v;
		v._vx = _vx;
		v._vy = _vy;
		v._vz = _vz;
		v._vw = 1.0f;
		return v;
	}

	float Vect::mag() const
	{
		//			
		//	mag = square root of (vector . vector)
		//
		float dot = this->dot(*this);
		return Trig::sqrt(dot);
	}

	float Vect::magSqr() const
	{
		// magSqr = (vector . vector)
		return this->dot(*this);
	}

	float Vect::getAngle(const Vect& in)
	{
		// A . B = |A| * |B| cosTheta
		// A . B = AxBx + AyBy + AzBz

		// cosTheta = (AxBx + AyBy + AzBz) / (|A| * |B|)
		// theta = cos -1 (cosTheta)

		Vect bVect = in;
		float dotProduct = this->dot(in);

		float magA = this->mag();
		float magB = bVect.mag();

		float cosTheta = dotProduct / (magA * magB);

		return (Trig::acos(cosTheta));
	}

	float Vect::dot(const Vect& in) const
	{
		//this does not include the w
		Vect result;
		result._mv = _mm_mul_ps(this->_mv, in._mv);
		return result._vx + result._vy + result._vz;
	}
	void Vect::outerDot(Matrix& out, const Vect& in)
	{		
		//this needs to be a column vector * row vector
		out.set(Matrix::Row::i0, x() * in.x(), x() * in.y(), x() * in.z(), x() * in.w());
		out.set(Matrix::Row::i1, y() * in.x(), y() * in.y(), y() * in.z(), y() * in.w());
		out.set(Matrix::Row::i2, z() * in.x(), z() * in.y(), z() * in.z(), z() * in.w());
		out.set(Matrix::Row::i3, w() * in.x(), w() * in.y(), w() * in.z(), w() * in.w());
	}

	float Vect::mdot(const Vect& in) const
	{
		//this includes the w

		Vect result;
		result._mv = _mm_mul_ps(this->_mv, in._mv);;
		return result._vx + result._vy + result._vz + result._vw;
	}
	Vect& Vect::norm() 
	{
		//			 1
		//	norm =  --- * vector
		//			mag

		float mag = 1 / this->mag();

		*this = *this * mag;

		//hard setting the w
		this->_vw = 1.0f;

		return *this;
	}

	Vect Vect::getNorm() const
	{

		//			 1
		//	norm =  --- * vector
		//			mag

		float mag = 1 / this->mag();

		Vect result = *this * mag;

		//hard setting the w
		result._vw = 1.0f;

		return result;
	}

	void Vect::set(const float x, const float y, const float z, const float w)
	{
		//clean
		this->_vx = 0.0f;
		this->_vy = 0.0f;
		this->_vz = 0.0f;
		this->_vw = 0.0f;

		//assign
		this->_vx = x;
		this->_vy = y;
		this->_vz = z;
		this->_vw = w;
	}

	void Vect::set(const Vect& in)
	{
		//clean
		this->_vx = 0.0f;
		this->_vy = 0.0f;
		this->_vz = 0.0f;
		this->_vw = 0.0f;

		//assign
		this->_vx = in._vx;
		this->_vy = in._vy;
		this->_vz = in._vz;
		this->_vw = in._vw;
	}

	bool Vect::isEqual(const Vect& _vIn, float tolerance) const
	{
		const bool _bX = Util::isEqual(this->_vx, _vIn._vx, tolerance);
		const bool _bY = Util::isEqual(this->_vy, _vIn._vy, tolerance);
		const bool _bZ = Util::isEqual(this->_vz, _vIn._vz, tolerance);
		const bool _bW = Util::isEqual(this->_vw, _vIn._vw, tolerance);
		return _bX && _bY && _bZ && _bW;
	}

	bool Vect::isZero(float tolerance) const
	{
		const bool _bX = Util::isEqual(0.0f, this->_vx, tolerance);
		const bool _bY = Util::isEqual(0.0f, this->_vy, tolerance);
		const bool _bZ = Util::isEqual(0.0f, this->_vz, tolerance);
		const bool _bW = Util::isEqual(1.0f, this->_vw, tolerance);

		return _bX && _bY && _bZ && _bW;
	}


	Vect Vect::cross(const Vect& in) const
	{
		Vect result;
		result.x() = (this->_vy * in._vz) - (this->_vz * in._vy);
		result.y() = (this->_vz * in._vx) - (this->_vx * in._vz);
		result.z() = (this->_vx * in._vy) - (this->_vy * in._vx);
		result.w() = 1.0f;

		return result;
	}

}

//--- End of File ---
