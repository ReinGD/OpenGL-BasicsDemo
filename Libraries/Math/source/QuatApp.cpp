#include "MathEngine.h"
#include "MathApp.h"

//----------------------------------------------------------------------------- 
// Mutates result to be a slerp between the source and target by the
// specified factor.
// For a factor of 0.0, result == source.
// For a factor of 1.0, result == target.
//----------------------------------------------------------------------------- 

namespace GD
{
	void QuatApp::Slerp(Quat &result, const Quat &_src, const Quat &_tar, const float slerpFactor)
	{
		Quat qTar = _tar;
		Quat src = _src;

		if (!src.isEqual(qTar))
		{
			float tmpCos = src.dot(_tar);

			if (tmpCos < 0)
			{
				tmpCos = -tmpCos;
				qTar = -qTar;
			}

			const float theta = Trig::acos(tmpCos);

			const float Segment_A = (Trig::sin((1-slerpFactor)*theta)) / (Trig::sin(theta));
			const Quat Src_Segment_A = src * Segment_A;

			float Segment_B = (Trig::sin((slerpFactor) * theta)) / (Trig::sin(theta));
			const Quat Tar_Segment_B = qTar * Segment_B;

			result = Src_Segment_A + Tar_Segment_B;

			if (theta == 0.0f) result.set(0.0f,0.0f,0.0f,1.0f);
		}
		else result = src;
		
		
	};

	void QuatApp::SlerpArray(Quat *out, const Quat *source, const Quat *target, const float slerpFactor, const int numQuats)
	{
		for (int i = 0; i < numQuats; i++)
		{

			Slerp(*out, *source, *target, slerpFactor);

			//moving up to the next values with pointer arithmetic
			out++;
			source++;
			target++;
		}
		
	}
	void QuatApp::PrintQuat(const Quat& in)
	{
		GDWriter::write("- - qx: %f,  qy: %f,  qz: %f,  qw: %f\n",
			in.qx(), in.qy(), in.qz(), in.real());
	}
	;
}

// ---  End of File ---------------
