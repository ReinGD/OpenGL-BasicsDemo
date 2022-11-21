#include "MathEngine.h"
#include "Debug.h"

namespace GD
{

	// Do your magic here
	void Debug::Print(const char* pName, const Vect& r)
	{
		GDWriter::write("%s:(Vect) \n", pName);
		GDWriter::write(" %9.4g %9.4g %9.4g %9.4g \n", r._vx, r._vy, r._vz, r._vw);
		GDWriter::write("\n");
	}

	void Debug::Print(const char *pName, const Quat &r)
	{
		GDWriter::write("%s:(Quat) \n", pName);
		GDWriter::write(" %9.4g %9.4g %9.4g %9.4g \n", r._qx, r._qy, r._qz, r._qw);
		GDWriter::write("\n");
	}

	void Debug::Print(const char* pName, const Matrix& r)
	{
		GDWriter::write("%s:(Matrix) \n", pName);
		GDWriter::write(" %9.4g %9.4g %9.4g %9.4g \n", r._m0, r._m1, r._m2, r._m3);
		GDWriter::write(" %9.4g %9.4g %9.4g %9.4g \n", r._m4, r._m5, r._m6, r._m7);
		GDWriter::write(" %9.4g %9.4g %9.4g %9.4g \n", r._m8, r._m9, r._m10, r._m11);
		GDWriter::write(" %9.4g %9.4g %9.4g %9.4g \n", r._m12, r._m13, r._m14, r._m15);		
		GDWriter::write("\n");
	}

}

//--- End of File ---
