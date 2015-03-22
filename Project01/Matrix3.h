#ifndef __Matrix3_H__
#define __Matrix3_H__

#include "Vector3.h"
#include "Math.h"

class Matrix3
{
	public:
		float m[3][3];

		/** Default constructor.
			@note
			It does <b>NOT</b> initialize the matrix for efficiency.	*/
		Matrix3 () {};

		/** Constructor. 
			@note: elements 1-3: first row, elements 4-6: second row...		*/
		Matrix3 (float fEntry00, float fEntry01, float fEntry02,
				float fEntry10, float fEntry11, float fEntry12,
				float fEntry20, float fEntry21, float fEntry22);

		// member access, allows use of construct mat[r][c]
        float* operator[] (size_t iRow) const
		{
			return (float*)m[iRow];
		}

		/** Tests 2 matrices for equality.	*/
		bool operator== (const Matrix3& rkMatrix) const;

		/** Tests 2 matrices for inequality.	*/
		bool operator!= (const Matrix3& rkMatrix) const;

		Matrix3 operator+ (const Matrix3& rkMatrix) const;
        Matrix3 operator- (const Matrix3& rkMatrix) const;
        Matrix3 operator* (const Matrix3& rkMatrix) const;

		/** Multiply matrix with scalar */
        Matrix3 operator* (float fScalar) const;
		/** Multiply matrix whit vector */
		Vector3 operator* (Vector3 vec) const;

        Matrix3 Transpose () const;
        bool Inverse (Matrix3& rkInverse, float fTolerance = 1e-06) const;
        Matrix3 Inverse (float fTolerance = 1e-06) const;
        float Determinant () const;

		void Matrix3::Orthonormalize ();

		// matrix must be orthonormal
        void ToAxisAngle (Vector3& rkAxis, Radian& rfAngle) const;
        void FromAxisAngle (const Vector3& rkAxis, const Radian& fRadians);

		// The matrix must be orthonormal.  The decomposition is yaw*pitch*roll
        // where yaw is rotation about the Up vector, pitch is rotation about the
        // Right axis, and roll is rotation about the Direction axis.
        bool ToEulerAnglesXYZ (Radian& rfYAngle, Radian& rfPAngle,
            Radian& rfRAngle) const;
        bool ToEulerAnglesXZY (Radian& rfYAngle, Radian& rfPAngle,
            Radian& rfRAngle) const;
        bool ToEulerAnglesYXZ (Radian& rfYAngle, Radian& rfPAngle,
            Radian& rfRAngle) const;
        bool ToEulerAnglesYZX (Radian& rfYAngle, Radian& rfPAngle,
            Radian& rfRAngle) const;
        bool ToEulerAnglesZXY (Radian& rfYAngle, Radian& rfPAngle,
            Radian& rfRAngle) const;
        bool ToEulerAnglesZYX (Radian& rfYAngle, Radian& rfPAngle,
            Radian& rfRAngle) const;
        void FromEulerAnglesXYZ (const Radian& fYAngle, const Radian& fPAngle, const Radian& fRAngle);
        void FromEulerAnglesXZY (const Radian& fYAngle, const Radian& fPAngle, const Radian& fRAngle);
        void FromEulerAnglesYXZ (const Radian& fYAngle, const Radian& fPAngle, const Radian& fRAngle);
        void FromEulerAnglesYZX (const Radian& fYAngle, const Radian& fPAngle, const Radian& fRAngle);
        void FromEulerAnglesZXY (const Radian& fYAngle, const Radian& fPAngle, const Radian& fRAngle);
        void FromEulerAnglesZYX (const Radian& fYAngle, const Radian& fPAngle, const Radian& fRAngle);

		Vector3 getColumn(int i);

		static const float EPSILON ;
		static const Matrix3 ZERO;
		static const Matrix3 IDENTITY;
		static const float ms_fSvdEpsilon;
		static const unsigned int ms_iSvdMaxIterations ;
		
		//Matrix4 toMatrix4 () const;

};

#endif