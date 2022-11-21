#include "MathEngine.h"
#include "QuatApp.h"

namespace GD
{ 

// Do your magic here

    Quat::Quat()
	    :_mq{}
    {
        this->real() = 1.0f;
    }

    Quat::~Quat()
    {
        _qx = 0.0f;
        _qy = 0.0f;
        _qz = 0.0f;
        _qw = 0.0f;
    }

    Quat::Quat(const Matrix& in)
	    :_mq{}
    {

        Quat result = privMatrixToQuat(in);
        this->_qx = result._qx;
        this->_qy = result._qy;
        this->_qz = result._qz;
        this->_qw = result._qw;
    }

    Quat::Quat(const float x,const float y,const float z,const float w)
	    :_mq{}
    {
        this->_qx = x;
        this->_qy = y;
        this->_qz = z;
        this->_qw = w;
    }

    Quat::Quat(const Vect& v, float s)
	    :_mq{}
    {
        this->_qx = v[x];
        this->_qy = v[y];
        this->_qz = v[z];
        this->_qw = s;
    }

    Quat::Quat(const Special special)
	    :_mq{}
	{
        Quat result;
	    switch (special)
	    {
        case Special::Zero:
            result.set(0.0f, 0.0f, 0.0f, 0.0f);
            break;
        case Special::Identity:
            result.set(0.0f, 0.0f, 0.0f, 1.0f);
            break;
	    }
        this->set(result[x], result[y], result[z], result[w]);
    }

    Quat::Quat(const Rot rot,const Vect& v,const float angle)
	    :_mq{}
    {
	    switch (rot)
	    {
        case Rot::AxisAngle:
            Matrix m = Matrix(Matrix::Rot::AxisAngle, v, angle);
            this->set(m);
            break;
	    }
    }

    Quat::Quat(const Rot1 rot,const float angle)
    {
        Matrix m;
    	switch (rot)
        {
        case Rot1::X:
            m = Matrix(Matrix::Rot1::X, angle);
            break;
        case Rot1::Y:
            m = Matrix(Matrix::Rot1::Y, angle);
            break;
        case Rot1::Z:
            m = Matrix(Matrix::Rot1::Z, angle);
            break;
        }
        this->set(m);
    }

    Quat::Quat(const Rot3 rot,const float xAngle,const float yAngle,const float zAngle)
    {
        switch (rot)
        {
        case Rot3::XYZ:
            Matrix m = Matrix(Matrix::Rot3::XYZ, xAngle, yAngle, zAngle);
            this->set(m);
            break;
        }
    }

    Quat::Quat(const Orient orient,const Vect& vDoF,const Vect& vY)
	    :_mq{}
    {
        Matrix m;
	    switch (orient)
	    {
        case Orient::LocalToWorld:
            m = Matrix(Matrix::Orient::LocalToWorld, vDoF, vY);
            break;
        case Orient::WorldToLocal:
            m = Matrix(Matrix::Orient::WorldToLocal, vDoF, vY);
            break;
	    }
        this->set(m);
    }

    Quat::Quat(const Vect& v)
	    :_mq{}
    {
        this->set(v.X(), v.Y(), v.Z(), 0.0f);
    }

    Quat Quat::operator-() const
    {
        Quat result = Quat(-this->_qx,-this->_qy,-this->_qz, -this->_qw);
        return result;
    }

    Quat Quat::operator+() const
    {
        Quat result = Quat(this->_qx, this->_qy, this->_qz, this->_qw);
        return result;
    }

    Quat& Quat::operator-=(const Quat& in)
    {
        this->_qx -= in._qx;
        this->_qy -= in._qy;
        this->_qz -= in._qz;
        this->_qw -= in._qw;
        return *this;
    }

    Quat& Quat::operator+=(const Quat& in)
    {
        this->_qx += in._qx;
        this->_qy += in._qy;
        this->_qz += in._qz;
        this->_qw += in._qw;
        return *this;
    }

    Quat& Quat::operator-=(const float s)
    {
        this->_qx -= s;
        this->_qy -= s;
        this->_qz -= s;
        this->_qw -= s;
        return *this;
    }

    Quat& Quat::operator+=(const float s)
    {
        this->_qx += s;
        this->_qy += s;
        this->_qz += s;
        this->_qw += s;
        return *this;
    }

    Quat& Quat::operator*=(const float s)
    {
        this->_qx *= s;
        this->_qy *= s;
        this->_qz *= s;
        this->_qw *= s;
        return *this;
    }

    Quat& Quat::operator*=(const Matrix& in)
    {
        Matrix mA = Matrix(*this);
        Matrix resultMatrix = mA * in;

        Quat result = Quat(resultMatrix);
        this->set(result._qx, result._qy, result._qz, result._qw);
        return *this;
    }

    Quat& Quat::operator*=(const Quat& in)
    {
        Quat p = Quat(*this);
        Quat q = Quat(in);

        const Vect pVect = Vect(p.qx(), p.qy(), p.qz());
        const Vect qVect = Vect(q.qx(), q.qy(), q.qz());

        const float scalar = p[w] * q[w] - pVect.dot(qVect);
        const Vect rVect = qVect.cross(pVect) + (q[w] * pVect) + (p[w] * qVect);

        this->set(rVect[x], rVect[y], rVect[z], scalar);
        return (*this);
    }

    Quat& Quat::operator/=(const Quat& q)
    {
        this->_qx = this->_qx / q[x];
        this->_qy = this->_qy / q[y];
        this->_qz = this->_qz / q[z];
        this->_qw = this->_qw / q[w];
        return *this;
    }

    Quat& Quat::operator/=(const float s)
    {
        this->_qx = this->_qx / s;
        this->_qy = this->_qy / s;
        this->_qz = this->_qz / s;
        this->_qw = this->_qw / s;
        return *this;
    }

    Quat& Quat::operator=(const Quat& q)
    {
        this->set(q[x], q[y], q[z], q[w]);
        return *this;
    }

    Quat Quat::multByElement(const Quat& q) const
    {
        Quat result;
        result._qx = this->_qx * q._qx;
        result._qy = this->_qy * q._qy;
        result._qz = this->_qz * q._qz;
        result._qw = this->_qw * q._qw;
        return result;
    }

    float Quat::dot(const Quat& in)
    {
        Quat result;
        result._mq = _mm_mul_ps(this->_mq, in._mq);
        return result._qx + result._qy + result._qz + result._qw;
    }

    float Quat::mag()
    {
        float dot = this->dot(*this);
        return Trig::sqrt(dot);
    }

    float Quat::magSquared()
    {
    	float dot = this->dot(*this);
        return (dot);
    }

    float Quat::invMagSquared()
    {
        return 1/magSquared();
    }

    float Quat::invMag()
    {
        return 1 / mag();
    }

    void Quat::Lqcvq(const Vect& in, Vect& out)
    {
        Vect quatVect;
        this->getVect(quatVect);

        Vect seg_A = (2 * this->real()) * quatVect.cross(in);
        Vect seg_B = ((this->real() * this->real()) - quatVect.dot(quatVect)) * in;
        Vect seg_C = (2 * quatVect.dot(in)) * quatVect;

        out = seg_A + seg_B + seg_C;
    }

    void Quat::Lqvqc(const Vect& in, Vect& out)
    {
        Vect quatVect;
        this->getVect(quatVect);

        Vect seg_A = (2 * this->real()) * in.cross(quatVect);
        Vect seg_B = ((this->real() * this->real()) - quatVect.dot(quatVect)) * in;
        Vect seg_C = (2 * quatVect.dot(in)) * quatVect;

    	out = seg_A + seg_B + seg_C;
    }

    void Quat::set(const Quat& in)
    {
        this->set(in.qx(), in.qy(), in.qz(), in.real());
    }

    void Quat::set(const Matrix& in)
    {
        Quat q = privMatrixToQuat(in);
        this->set(q._qx, q._qy, q._qz, q._qw);
    }

    void Quat::set(const float x, const float y, const float z, const float w)
    {
        this->_qx = 0.0f;
        this->_qy = 0.0f;
        this->_qz = 0.0f;
        this->_qw = 0.0f;

        this->_qx = x;
        this->_qy = y;
        this->_qz = z;
        this->_qw = w;
    }

    void Quat::set(const Vect& v,const float s)
    {
        this->_qx = v[x];
        this->_qy = v[y];
        this->_qz = v[z];
        this->_qw = s;
    }

    void Quat::set(const Rot rot, const Vect& in,const float s)
    {
        this->_qx = 0.0f;
        this->_qy = 0.0f;
        this->_qz = 0.0f;
        this->_qw = 0.0f;

        switch (rot)
	    {
        case Rot::AxisAngle:
            Matrix matrix = Matrix(Matrix::Rot::AxisAngle, in, s);
            Quat result = privMatrixToQuat(matrix);
            this->_qx = result._qx;
            this->_qy = result._qy;
            this->_qz = result._qz;
            this->_qw = result._qw;
            break;

	    }


    }

    void Quat::set(Rot1 rot,const float s)
    {
        Matrix result;
	    switch (rot)
	    {
        case Rot1::X:
            result.set(Matrix::Rot1::X, s);
            break;
        case Rot1::Y:
            result.set(Matrix::Rot1::Y, s);
            break;
        case Rot1::Z:
            result.set(Matrix::Rot1::Z, s);
            break;
	    }
        Quat qResult = Quat(result);
        this->set(qResult._qx, qResult._qy, qResult._qz, qResult._qw);
        
    }

    void Quat::set(Special special)
    {
        Quat result;
        switch (special)
        {
        case Special::Zero:
            result.set(0.0f, 0.0f, 0.0f, 0.0f);
            break;
        case Special::Identity:
            result.set(0.0f, 0.0f, 0.0f, 1.0f);
            break;
        }
        this->set(result[x], result[y], result[z], result[w]);
    }

    void Quat::set(Orient orient,const Vect& vDoF,const Vect& vY)
    {
        this->_qx = 0.0f;
        this->_qy = 0.0f;
        this->_qz = 0.0f;
        this->_qw = 0.0f;

        Matrix m;
        switch (orient)
        {
        case Orient::LocalToWorld:
            m = Matrix(Matrix::Orient::LocalToWorld, vDoF, vY);
            break;
        case Orient::WorldToLocal:
            m = Matrix(Matrix::Orient::WorldToLocal, vDoF, vY);
            break;
        }
        this->set(m);
    }

    void Quat::setVect(const Vect& v)
    {
        this->_qx = 0.0f;
        this->_qy = 0.0f;
        this->_qz = 0.0f;
        this->_qw = 0.0f;

        this->set(v.X(), v.Y(), v.Z(), 0.0f);
    }

    void Quat::set(Rot3 rot, float xAngle, float yAngle, float zAngle)
    {
        this->_qx = 0.0f;
        this->_qy = 0.0f;
        this->_qz = 0.0f;
        this->_qw = 0.0f;

        switch (rot)
        {
        case Rot3::XYZ:
            Matrix matrix = Matrix(Matrix::Rot3::XYZ, xAngle, yAngle, zAngle);
            Quat result = privMatrixToQuat(matrix);
            this->_qx = result._qx;
            this->_qy = result._qy;
            this->_qz = result._qz;
            this->_qw = result._qw;
            break;

        }
    }

    void Quat::clear()
    {
        this->set(0.0f, 0.0f, 0.0f, 0.0f);
    }

    Quat& Quat::norm()
    {
        //			 1
       //	norm =  --- * Quat
       //			mag

        float mag = 1 / this->mag();

        *this = *this * mag;
        return *this;
    }

    Quat& Quat::conj()
    {
        const Quat conj = this->getConj();
        this->set(conj);
        return *this;
    }

    Quat& Quat::inv()
    {
        Quat result = this->getInv();
        this->set(result);
        return *this;
    }

    Quat& Quat::T()
    {
        Quat result = this->getT();
        this->set(result);
        return *this;
    }

    void Quat::getVect(Vect& out) const
    {
        out.set(this->qx(), this->qy(), this->qz());
    }

    float Quat::getAngle() const
    {
        return 2 * Trig::acos(this->_qw);
    }

    void Quat::getAxis(Vect& out) const
    {
        Vect v;
    	this->getVect(v);
        v.norm();
        
        out.set(v);
    }

    Quat Quat::getNorm()
    {
        //			 1
        //	norm =  --- * Quat
        //			mag

        float invMag = 1 / this->mag();

        Quat q = *this * invMag;

    	return q;
    }

    Quat Quat::getInv()
    {
        return this->getConj()/this->magSquared();
    }

    Quat Quat::getConj()
    {
        // q* = -qv + qw = -qx + -qy + -qz + qw
        Vect vectPart;
        this->getVect(vectPart);
        return Quat(-vectPart, this->_qw);
    }

    Quat Quat::getT() const
    {
        Matrix m = Matrix(*this);
        return Quat( m.T());
    }

    float& Quat::qx()
    {
        return this->_qx;
    }

    float& Quat::qy()
    {
        return this->_qy;
    }

    float& Quat::qz()
    {
        return this->_qz;
    }

    float& Quat::real()
    {
        return this->_qw;
    }

    float Quat::qx() const
    {
        return this->_qx;
    }

    float Quat::qy() const
    {
        return this->_qy;
    }

    float Quat::qz() const
    {
        return this->_qz;
    }

    float Quat::real() const
    {
        return this->_qw;
    }

    float& Quat::operator[](x_enum)
    {
        return this->_qx;
    }

    float& Quat::operator[](y_enum)
    {
        return this->_qy;
    }

    float& Quat::operator[](z_enum)
    {
        return this->_qz;
    }

    float& Quat::operator[](w_enum)
    {
        return this->_qw;
    }

    float Quat::operator[](x_enum) const
    {
        return this->_qx;
    }

    float Quat::operator[](y_enum) const
    {
        return this->_qy;
    }

    float Quat::operator[](z_enum) const
    {
        return this->_qz;
    }

    float Quat::operator[](w_enum) const
    {
        return this->_qw;
    }

    bool Quat::isEqual(const Quat& q,const float in)
    {

        return (Util::isEqual(q.qx(), this->qx(), in) && 
				Util::isEqual(q.qy(), this->qy(), in) &&
				Util::isEqual(q.qz(), this->qz(), in) &&
				Util::isEqual(q._qw, this->_qw, in));
    }

    bool Quat::isNegEqual(const Quat& q,const float in)
    {

        return isEqual(-q, in);
    }

    bool Quat::isEquivalent(const Quat& q,const float in)
    {
        bool pos = isEqual(q,in);
        bool neg = isEqual(-q,in);
        return pos || neg;
    }

    bool Quat::isIdentity(const float in)
    {
        const Quat identity = Quat(Matrix::Special::Identity);
        return isEqual(identity,in);
    }

    bool Quat::isNormalized(const float in)
    {
        return Util::isEqual(this->mag(),1.0f, in);
    }

    bool Quat::isZero(const float in)
    {
        return Util::isZero(this->qx(), in) && 
        	   Util::isZero(this->qy(), in) &&
               Util::isZero(this->qz(), in) &&
               Util::isZero(this->real(), in);
    }

    bool Quat::isConjugateEqual(const Quat& q, float in)
    {
        //q = x + y + z + real
        //conj = -x + -y + -z + real
        Vect qVect;
        q.getVect(qVect);
        Quat newQ = Quat(-qVect, q.real());

        return this->isEqual(newQ,in);
    }

    Quat Quat::privMatrixToQuat(const Matrix& M)
    {
        Quat result;
        float tr = M.m0() + M.m5() + M.m10();
        float S;
        if (tr > 0.0f)
        {
            S = 2 * sqrtf(tr + 1.0f);
            result._qw = 0.25f * S;
            result._qx = -(M.m9() - M.m6()) / S;
            result._qy = -(M.m2() - M.m8()) / S;
            result._qz = -(M.m4() - M.m1()) / S;
        }
        else if((M.m0() > M.m5()) && (M.m0() > M.m10()))
        {
            S = 2 * sqrtf(1.0f + M.m0() - M.m5() - M.m10());
            result._qw = -(M.m9() - M.m6()) / S;
            result._qx = 0.25f * S;
            result._qy = (M.m1() + M.m4()) / S;
            result._qz = (M.m2() + M.m8()) / S;
        }
        else if(M.m5() > M.m10())
        {
            S = 2 * sqrtf(1.0f + M.m5() - M.m0() - M.m10());
            result._qw = -(M.m2() - M.m8()) / S;
            result._qx = (M.m1() + M.m4()) / S;
            result._qy = 0.25f * S;
            result._qz = (M.m6() + M.m9()) / S;
        }
        else
        {
            S = 2 * sqrtf(1.0f + M.m10() - M.m0() - M.m5());
            result._qw = -(M.m4() - M.m1()) / S;
            result._qx = (M.m2() + M.m8()) / S;
            result._qy = (M.m6() + M.m9()) / S;
            result._qz = 0.25f * S;
        }
        return result;
    }

    Quat operator+(const Quat& A, const Quat& B)
    {
        Quat result;
        result._qx = A._qx + B._qx;
        result._qy = A._qy + B._qy;
        result._qz = A._qz + B._qz;
        result._qw = A._qw + B._qw;
        return result;
    }

    Quat operator+(const Quat& in, const float s)
    {
        Quat result;
        result._qx = in._qx + s;
        result._qy = in._qy + s;
        result._qz = in._qz + s;
        result._qw = in._qw + s;
        return result;
    }

    Quat operator+(const float& s, const Quat& in)
    {
        Quat result;
        result._qx = s + in._qx;
        result._qy = s + in._qy;
        result._qz = s + in._qz;
        result._qw = s + in._qw;
        return result;
    }

    Quat operator-(const Quat& A, const Quat& B)
    {
        Quat result;
        result._qx = A._qx - B._qx;
        result._qy = A._qy - B._qy;
        result._qz = A._qz - B._qz;
        result._qw = A._qw - B._qw;
        return result;
    }

    Quat operator-(const Quat& in, const float s)
    {
        Quat result;
        result._qx = in._qx - s;
        result._qy = in._qy - s;
        result._qz = in._qz - s;
        result._qw = in._qw - s;
        return result;
    }

    Quat operator-(const float& s, const Quat& in)
    {
        Quat result;
        result._qx = s - in._qx;
        result._qy = s - in._qy;
        result._qz = s - in._qz;
        result._qw = s - in._qw;
        return result;
    }

    Quat operator*(const Quat& q, const float s)
    {
        Quat result;
        result._qx = q._qx * s;
        result._qy = q._qy * s;
        result._qz = q._qz * s;
        result._qw = q._qw * s;
        return result;
    }

    Quat operator*(const float s, const Quat& q)
    {
        Quat result;
        result._qx = s * q._qx;
        result._qy = s * q._qy;
        result._qz = s * q._qz;
        result._qw = s * q._qw;
        return result;
    }

    Quat operator*(const Quat& A, const Quat& B)
    {
        Quat p = Quat(A);
        Quat q = Quat(B);

        Vect pVect = Vect(p.qx(), p.qy(), p.qz());
        Vect qVect = Vect(q.qx(), q.qy(), q.qz());

        float scalar = p[w] * q[w] - pVect.dot(qVect);
        Vect rVect = qVect.cross(pVect) + (q[w] * pVect) + (p[w] * qVect);

        Quat result;
        result.set(rVect[x], rVect[y], rVect[z], scalar);
        return result;
    }


    

    Quat operator/(const Quat& p, const Quat& q)
    {
        Quat result;
        result._qx = p[x] / q[x];
        result._qy = p[y] / q[y];
        result._qz = p[z] / q[z];
        result._qw = p[w] / q[w];
        return result;
    }

    Quat operator/(const float s, const Quat& p)
    {
        Quat result;
        result._qx = s / p[x];
        result._qy = s / p[y];
        result._qz = s / p[z];
        result._qw = s / p[w];
        return result;
    }

    Quat operator/(const Quat& p, const float s)
    {
        Quat result;
        result._qx = p[x] / s;
        result._qy = p[y] / s;
        result._qz = p[z] / s;
        result._qw = p[w] / s;
        return result;
    }

}

// ---  End of File ---------------
