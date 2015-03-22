#include "Matrix3.h"

//TODO: see whether this should be somewhere else
#define PI 3.14159265
#define HALF_PI 1.57079632

Matrix3::Matrix3 (float fEntry00, float fEntry01, float fEntry02,
				float fEntry10, float fEntry11, float fEntry12,
				float fEntry20, float fEntry21, float fEntry22)
{
	m[0][0] = fEntry00;
	m[0][1] = fEntry01;
	m[0][2] = fEntry02;
	m[1][0] = fEntry10;
	m[1][1] = fEntry11;
	m[1][2] = fEntry12;
	m[2][0] = fEntry20;
	m[2][1] = fEntry21;
	m[2][2] = fEntry22;
}

bool Matrix3::operator== (const Matrix3& m2) const
{
	if( 
		m[0][0] != m2.m[0][0] || m[0][1] != m2.m[0][1] || m[0][2] != m2.m[0][2] ||
		m[1][0] != m2.m[1][0] || m[1][1] != m2.m[1][1] || m[1][2] != m2.m[1][2] ||
		m[2][0] != m2.m[2][0] || m[2][1] != m2.m[2][1] || m[2][2] != m2.m[2][2] )
	return false;
	// "else"
	return true;
}

bool Matrix3::operator!= (const Matrix3& m2) const
{
	if( 
		m[0][0] != m2.m[0][0] || m[0][1] != m2.m[0][1] || m[0][2] != m2.m[0][2] ||
		m[1][0] != m2.m[1][0] || m[1][1] != m2.m[1][1] || m[1][2] != m2.m[1][2] ||
		m[2][0] != m2.m[2][0] || m[2][1] != m2.m[2][1] || m[2][2] != m2.m[2][2] )
	return true;
	// "else"
	return false;
}

Matrix3 Matrix3::operator+ (const Matrix3& rkMatrix) const
{
	Matrix3 kSum;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			kSum.m[iRow][iCol] = m[iRow][iCol] + rkMatrix.m[iRow][iCol];
		}
	}
	return kSum;
}

Matrix3 Matrix3::operator- (const Matrix3& rkMatrix) const
{
	Matrix3 kDiff;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			kDiff.m[iRow][iCol] = m[iRow][iCol] - rkMatrix.m[iRow][iCol];
		}
	}
	return kDiff;
}

Matrix3 Matrix3::operator* (const Matrix3& rkMatrix) const
{
	Matrix3 kProd;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			kProd.m[iRow][iCol] =
				m[iRow][0]*rkMatrix.m[0][iCol] +
				m[iRow][1]*rkMatrix.m[1][iCol] +
				m[iRow][2]*rkMatrix.m[2][iCol];
		}
	}
	return kProd;
}

Matrix3 Matrix3::operator* (float fScalar) const
{
	Matrix3 kProd;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
			kProd[iRow][iCol] = fScalar*m[iRow][iCol];
	}
	return kProd;
}

Vector3 Matrix3::operator *( const Vector3  v) const
{
	Vector3 result = Vector3(0.0,0.0,0.0);
	
	result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
	result.x = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
	result.x = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;

	return result;

}

Matrix3 Matrix3::Transpose () const
{
	Matrix3 kTranspose;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
			kTranspose[iRow][iCol] = m[iCol][iRow];
	}
	return kTranspose;
}

bool Matrix3::Inverse (Matrix3& rkInverse, float fTolerance) const
{
	// Invert a 3x3 using cofactors.  This is about 8 times faster than
	// the Numerical Recipes code which uses Gaussian elimination.

	rkInverse[0][0] = m[1][1]*m[2][2] -
		m[1][2]*m[2][1];
	rkInverse[0][1] = m[0][2]*m[2][1] -
		m[0][1]*m[2][2];
	rkInverse[0][2] = m[0][1]*m[1][2] -
		m[0][2]*m[1][1];
	rkInverse[1][0] = m[1][2]*m[2][0] -
		m[1][0]*m[2][2];
	rkInverse[1][1] = m[0][0]*m[2][2] -
		m[0][2]*m[2][0];
	rkInverse[1][2] = m[0][2]*m[1][0] -
		m[0][0]*m[1][2];
	rkInverse[2][0] = m[1][0]*m[2][1] -
		m[1][1]*m[2][0];
	rkInverse[2][1] = m[0][1]*m[2][0] -
		m[0][0]*m[2][1];
	rkInverse[2][2] = m[0][0]*m[1][1] -
		m[0][1]*m[1][0];

	float fDet =
		m[0][0]*rkInverse[0][0] +
		m[0][1]*rkInverse[1][0]+
		m[0][2]*rkInverse[2][0];

	if ( abs(fDet) <= fTolerance )
		return false;

	float fInvDet = 1.0f/fDet;
	for (size_t iRow = 0; iRow < 3; iRow++)
	{
		for (size_t iCol = 0; iCol < 3; iCol++)
			rkInverse[iRow][iCol] *= fInvDet;
	}
	return true;
}

Matrix3 Matrix3::Inverse (float fTolerance) const
{
	Matrix3 kInverse = Matrix3(0,0,0,0,0,0,0,0,0);
	Inverse(kInverse,fTolerance);
	return kInverse;
}

float Matrix3::Determinant () const
{
	float fCofactor00 = m[1][1]*m[2][2] -
		m[1][2]*m[2][1];
	float fCofactor10 = m[1][2]*m[2][0] -
		m[1][0]*m[2][2];
	float fCofactor20 = m[1][0]*m[2][1] -
		m[1][1]*m[2][0];

	float fDet =
		m[0][0]*fCofactor00 +
		m[0][1]*fCofactor10 +
		m[0][2]*fCofactor20;
	return fDet;
}


//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------




   void Matrix3::Orthonormalize ()
    {
        // Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
        // M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
        //
        //   q0 = m0/|m0|
        //   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
        //   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
        //
        // where |V| indicates length of vector V and A*B indicates dot
        // product of vectors A and B.

        // compute q0
        float fInvLength = Math::InvSqrt(m[0][0]*m[0][0]
            + m[1][0]*m[1][0] +
            m[2][0]*m[2][0]);

        m[0][0] *= fInvLength;
        m[1][0] *= fInvLength;
        m[2][0] *= fInvLength;

        // compute q1
        float fDot0 =
            m[0][0]*m[0][1] +
            m[1][0]*m[1][1] +
            m[2][0]*m[2][1];

        m[0][1] -= fDot0*m[0][0];
        m[1][1] -= fDot0*m[1][0];
        m[2][1] -= fDot0*m[2][0];

        fInvLength = Math::InvSqrt(m[0][1]*m[0][1] +
            m[1][1]*m[1][1] +
            m[2][1]*m[2][1]);

        m[0][1] *= fInvLength;
        m[1][1] *= fInvLength;
        m[2][1] *= fInvLength;

        // compute q2
        float fDot1 =
            m[0][1]*m[0][2] +
            m[1][1]*m[1][2] +
            m[2][1]*m[2][2];

        fDot0 =
            m[0][0]*m[0][2] +
            m[1][0]*m[1][2] +
            m[2][0]*m[2][2];

        m[0][2] -= fDot0*m[0][0] + fDot1*m[0][1];
        m[1][2] -= fDot0*m[1][0] + fDot1*m[1][1];
        m[2][2] -= fDot0*m[2][0] + fDot1*m[2][1];

        fInvLength = Math::InvSqrt(m[0][2]*m[0][2] +
            m[1][2]*m[1][2] +
            m[2][2]*m[2][2]);

        m[0][2] *= fInvLength;
        m[1][2] *= fInvLength;
        m[2][2] *= fInvLength;
    }

       //-----------------------------------------------------------------------
    void Matrix3::ToAxisAngle (Vector3& rkAxis, Radian& rfRadians) const
    {
        // Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
        // The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 where
        // I is the identity and
        //
        //       +-        -+
        //   P = |  0 -z +y |
        //       | +z  0 -x |
        //       | -y +x  0 |
        //       +-        -+
        //
        // If A > 0, R represents a counterclockwise rotation about the axis in
        // the sense of looking from the tip of the axis vector towards the
        // origin.  Some algebra will show that
        //
        //   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P
        //
        // In the event that A = pi, R-R^t = 0 which prevents us from extracting
        // the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
        // P^2 = (R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
        // z^2-1.  We can solve these for axis (x,y,z).  Because the angle is pi,
        // it does not matter which sign you choose on the square roots.

        float fTrace = m[0][0] + m[1][1] + m[2][2];
        float fCos = 0.5f*(fTrace-1.0f);
        rfRadians = acos(fCos);  // in [0,PI]

        if ( rfRadians > Radian(0.0) )
        {
            if ( rfRadians < Radian(PI) )
            {
                rkAxis.x = m[2][1]-m[1][2];
                rkAxis.y = m[0][2]-m[2][0];
                rkAxis.z = m[1][0]-m[0][1];
                rkAxis.normalise();
            }
            else
            {
                // angle is PI
                float fHalfInverse;
                if ( m[0][0] >= m[1][1] )
                {
                    // r00 >= r11
                    if ( m[0][0] >= m[2][2] )
                    {
                        // r00 is maximum diagonal term
                        rkAxis.x = 0.5f*sqrt(m[0][0] -
                            m[1][1] - m[2][2] + 1.0f);
                        fHalfInverse = 0.5f/rkAxis.x;
                        rkAxis.y = fHalfInverse*m[0][1];
                        rkAxis.z = fHalfInverse*m[0][2];
                    }
                    else
                    {
                        // r22 is maximum diagonal term
                        rkAxis.z = 0.5f*sqrt(m[2][2] -
                            m[0][0] - m[1][1] + 1.0f);
                        fHalfInverse = 0.5f/rkAxis.z;
                        rkAxis.x = fHalfInverse*m[0][2];
                        rkAxis.y = fHalfInverse*m[1][2];
                    }
                }
                else
                {
                    // r11 > r00
                    if ( m[1][1] >= m[2][2] )
                    {
                        // r11 is maximum diagonal term
                        rkAxis.y = 0.5f*sqrt(m[1][1] -
                            m[0][0] - m[2][2] + 1.0f);
                        fHalfInverse  = 0.5f/rkAxis.y;
                        rkAxis.x = fHalfInverse*m[0][1];
                        rkAxis.z = fHalfInverse*m[1][2];
                    }
                    else
                    {
                        // r22 is maximum diagonal term
                        rkAxis.z = 0.5f*sqrt(m[2][2] -
                            m[0][0] - m[1][1] + 1.0f);
                        fHalfInverse = 0.5f/rkAxis.z;
                        rkAxis.x = fHalfInverse*m[0][2];
                        rkAxis.y = fHalfInverse*m[1][2];
                    }
                }
            }
        }
        else
        {
            // The angle is 0 and the matrix is the identity.  Any axis will
            // work, so just use the x-axis.
            rkAxis.x = 1.0;
            rkAxis.y = 0.0;
            rkAxis.z = 0.0;
        }
    }
    //-----------------------------------------------------------------------
    void Matrix3::FromAxisAngle (const Vector3& rkAxis, const Radian& fRadians)
    {

		float fCos = cos(fRadians.valueRadians());
        float fSin = sin(fRadians.valueRadians());
        float fOneMinusCos = 1.0f-fCos;
        float fX2 = rkAxis.x*rkAxis.x;
        float fY2 = rkAxis.y*rkAxis.y;
        float fZ2 = rkAxis.z*rkAxis.z;
        float fXYM = rkAxis.x*rkAxis.y*fOneMinusCos;
        float fXZM = rkAxis.x*rkAxis.z*fOneMinusCos;
        float fYZM = rkAxis.y*rkAxis.z*fOneMinusCos;
        float fXSin = rkAxis.x*fSin;
        float fYSin = rkAxis.y*fSin;
        float fZSin = rkAxis.z*fSin;

        m[0][0] = fX2*fOneMinusCos+fCos;
        m[0][1] = fXYM-fZSin;
        m[0][2] = fXZM+fYSin;
        m[1][0] = fXYM+fZSin;
        m[1][1] = fY2*fOneMinusCos+fCos;
        m[1][2] = fYZM-fXSin;
        m[2][0] = fXZM-fYSin;
        m[2][1] = fYZM+fXSin;
        m[2][2] = fZ2*fOneMinusCos+fCos;
    }
    //-----------------------------------------------------------------------
    bool Matrix3::ToEulerAnglesXYZ (Radian& rfYAngle, Radian& rfPAngle,
        Radian& rfRAngle) const
    {
        // rot =  cy*cz          -cy*sz           sy
        //        cz*sx*sy+cx*sz  cx*cz-sx*sy*sz -cy*sx
        //       -cx*cz*sy+sx*sz  cz*sx+cx*sy*sz  cx*cy

        rfPAngle = Radian(asin(m[0][2]));
        if ( rfPAngle < Radian(HALF_PI) )
        {
            if ( rfPAngle > Radian(-HALF_PI) )
            {
                rfYAngle = atan2(-m[1][2],m[2][2]);
                rfRAngle = atan2(-m[0][1],m[0][0]);
                return true;
            }
            else
            {
				float helperfloat = atan2(m[1][0],m[1][1]);
                // WARNING.  Not a unique solution.
                Radian fRmY = Radian(helperfloat);
                rfRAngle = Radian(0.0);  // any angle works
                rfYAngle = rfRAngle - fRmY;
                return false;
            }
        }
        else
        {
			float helperfloat = atan2(m[1][0],m[1][1]);
            // WARNING.  Not a unique solution.
            Radian fRpY = Radian(helperfloat);
            rfRAngle = Radian(0.0);  // any angle works
            rfYAngle = fRpY - rfRAngle;
            return false;
        }
    }
    //-----------------------------------------------------------------------
    bool Matrix3::ToEulerAnglesXZY (Radian& rfYAngle, Radian& rfPAngle,
        Radian& rfRAngle) const
    {
        // rot =  cy*cz          -sz              cz*sy
        //        sx*sy+cx*cy*sz  cx*cz          -cy*sx+cx*sy*sz
        //       -cx*sy+cy*sx*sz  cz*sx           cx*cy+sx*sy*sz

        rfPAngle = asin(-m[0][1]);
        if ( rfPAngle < Radian(HALF_PI) )
        {
            if ( rfPAngle > Radian(-HALF_PI) )
            {
                rfYAngle = atan2(m[2][1],m[1][1]);
                rfRAngle = atan2(m[0][2],m[0][0]);
                return true;
            }
            else
            {
				float helperfloat = atan2(-m[2][0],m[2][2]);
                // WARNING.  Not a unique solution.
                Radian fRmY = Radian(helperfloat);
                rfRAngle = Radian(0.0);  // any angle works
                rfYAngle = rfRAngle - fRmY;
                return false;
            }
        }
        else
        {
			float helperfloat = atan2(-m[2][0],m[2][2]);
            // WARNING.  Not a unique solution.
            Radian fRpY = Radian(helperfloat);
            rfRAngle = Radian(0.0);  // any angle works
            rfYAngle = fRpY - rfRAngle;
            return false;
        }
    }
    //-----------------------------------------------------------------------
    bool Matrix3::ToEulerAnglesYXZ (Radian& rfYAngle, Radian& rfPAngle,
        Radian& rfRAngle) const
    {
        // rot =  cy*cz+sx*sy*sz  cz*sx*sy-cy*sz  cx*sy
        //        cx*sz           cx*cz          -sx
        //       -cz*sy+cy*sx*sz  cy*cz*sx+sy*sz  cx*cy

        rfPAngle = asin(-m[1][2]);
        if ( rfPAngle < Radian(HALF_PI) )
        {
            if ( rfPAngle > Radian(-HALF_PI) )
            {
                rfYAngle = atan2(m[0][2],m[2][2]);
                rfRAngle = atan2(m[1][0],m[1][1]);
                return true;
            }
            else
            {
				float helperfloat = atan2(-m[0][1],m[0][0]);
                // WARNING.  Not a unique solution.
                Radian fRmY = Radian(helperfloat);
                rfRAngle = Radian(0.0);  // any angle works
                rfYAngle = rfRAngle - fRmY;
                return false;
            }
        }
        else
        {
			float helperfloat = atan2(-m[0][1],m[0][0]);
            // WARNING.  Not a unique solution.
            Radian fRpY = Radian(helperfloat);
            rfRAngle = Radian(0.0);  // any angle works
            rfYAngle = fRpY - rfRAngle;
            return false;
        }
    }
    //-----------------------------------------------------------------------
    bool Matrix3::ToEulerAnglesYZX (Radian& rfYAngle, Radian& rfPAngle,
        Radian& rfRAngle) const
    {
        // rot =  cy*cz           sx*sy-cx*cy*sz  cx*sy+cy*sx*sz
        //        sz              cx*cz          -cz*sx
        //       -cz*sy           cy*sx+cx*sy*sz  cx*cy-sx*sy*sz

        rfPAngle = asin(m[1][0]);
        if ( rfPAngle < Radian(HALF_PI) )
        {
            if ( rfPAngle > Radian(-HALF_PI) )
            {
                rfYAngle = atan2(-m[2][0],m[0][0]);
                rfRAngle = atan2(-m[1][2],m[1][1]);
                return true;
            }
            else
            {
				float helperfloat = atan2(m[2][1],m[2][2]);
                // WARNING.  Not a unique solution.
                Radian fRmY = Radian(helperfloat);
                rfRAngle = Radian(0.0);  // any angle works
                rfYAngle = rfRAngle - fRmY;
                return false;
            }
        }
        else
        {
			float helperfloat = atan2(m[2][1],m[2][2]);
            // WARNING.  Not a unique solution.
            Radian fRpY = Radian(helperfloat);
            rfRAngle = Radian(0.0);  // any angle works
            rfYAngle = fRpY - rfRAngle;
            return false;
        }
    }
    //-----------------------------------------------------------------------
    bool Matrix3::ToEulerAnglesZXY (Radian& rfYAngle, Radian& rfPAngle,
        Radian& rfRAngle) const
    {
        // rot =  cy*cz-sx*sy*sz -cx*sz           cz*sy+cy*sx*sz
        //        cz*sx*sy+cy*sz  cx*cz          -cy*cz*sx+sy*sz
        //       -cx*sy           sx              cx*cy

        rfPAngle = asin(m[2][1]);
        if ( rfPAngle < Radian(HALF_PI) )
        {
            if ( rfPAngle > Radian(-HALF_PI) )
            {
                rfYAngle = atan2(-m[0][1],m[1][1]);
                rfRAngle = atan2(-m[2][0],m[2][2]);
                return true;
            }
            else
            {
				float helperFloat = atan2(m[0][2],m[0][0]);
                // WARNING.  Not a unique solution.
                Radian fRmY = Radian(helperFloat);
                rfRAngle = Radian(0.0);  // any angle works
                rfYAngle = rfRAngle - fRmY;
                return false;
            }
        }
        else
        {
			float helperFloat = atan2(m[0][2],m[0][0]);
            // WARNING.  Not a unique solution.
            Radian fRpY = Radian(helperFloat);
            rfRAngle = Radian(0.0);  // any angle works
            rfYAngle = fRpY - rfRAngle;
            return false;
        }
    }
    //-----------------------------------------------------------------------
    bool Matrix3::ToEulerAnglesZYX (Radian& rfYAngle, Radian& rfPAngle,
        Radian& rfRAngle) const
    {
        // rot =  cy*cz           cz*sx*sy-cx*sz  cx*cz*sy+sx*sz
        //        cy*sz           cx*cz+sx*sy*sz -cz*sx+cx*sy*sz
        //       -sy              cy*sx           cx*cy

        rfPAngle = asin(-m[2][0]);
        if ( rfPAngle < Radian(HALF_PI) )
        {
            if ( rfPAngle > Radian(-HALF_PI) )
            {
                rfYAngle = atan2(m[1][0],m[0][0]);
                rfRAngle = atan2(m[2][1],m[2][2]);
                return true;
            }
            else
            {
				float helperFloat = atan2(-m[0][1],m[0][2]);
                // WARNING.  Not a unique solution.
                Radian fRmY = Radian(helperFloat);
                rfRAngle = Radian(0.0);  // any angle works
                rfYAngle = rfRAngle - fRmY;
                return false;
            }
        }
        else
        {
			float helperFloat = atan2(-m[0][1],m[0][2]);
            // WARNING.  Not a unique solution.
            Radian fRpY = Radian(helperFloat);
            rfRAngle = Radian(0.0);  // any angle works
            rfYAngle = fRpY - rfRAngle;
            return false;
        }
    }
    //-----------------------------------------------------------------------
    void Matrix3::FromEulerAnglesXYZ (const Radian& fYAngle, const Radian& fPAngle,
        const Radian& fRAngle)
    {
        float fCos, fSin;

		fCos = cos(fYAngle.valueRadians());
		fSin = sin(fYAngle.valueRadians());
        Matrix3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

        fCos = cos(fPAngle.valueRadians());
        fSin = sin(fPAngle.valueRadians());
        Matrix3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

        fCos = cos(fRAngle.valueRadians());
        fSin = sin(fRAngle.valueRadians());
        Matrix3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

        *this = kXMat*(kYMat*kZMat);
    }
    //-----------------------------------------------------------------------
    void Matrix3::FromEulerAnglesXZY (const Radian& fYAngle, const Radian& fPAngle,
        const Radian& fRAngle)
    {
        float fCos, fSin;

        fCos = cos(fYAngle.valueRadians());
        fSin = sin(fYAngle.valueRadians());
        Matrix3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

        fCos = cos(fPAngle.valueRadians());
        fSin = sin(fPAngle.valueRadians());
        Matrix3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

        fCos = cos(fRAngle.valueRadians());
        fSin = sin(fRAngle.valueRadians());
        Matrix3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

        *this = kXMat*(kZMat*kYMat);
    }
    //-----------------------------------------------------------------------
    void Matrix3::FromEulerAnglesYXZ (const Radian& fYAngle, const Radian& fPAngle,
        const Radian& fRAngle)
    {
        float fCos, fSin;

        fCos = cos(fYAngle.valueRadians());
        fSin = sin(fYAngle.valueRadians());
        Matrix3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

        fCos = cos(fPAngle.valueRadians());
        fSin = sin(fPAngle.valueRadians());
        Matrix3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

        fCos = cos(fRAngle.valueRadians());
        fSin = sin(fRAngle.valueRadians());
        Matrix3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

        *this = kYMat*(kXMat*kZMat);
    }
    //-----------------------------------------------------------------------
    void Matrix3::FromEulerAnglesYZX (const Radian& fYAngle, const Radian& fPAngle,
        const Radian& fRAngle)
    {
        float fCos, fSin;

        fCos = cos(fYAngle.valueRadians());
        fSin = sin(fYAngle.valueRadians());
        Matrix3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

        fCos = cos(fPAngle.valueRadians());
        fSin = sin(fPAngle.valueRadians());
        Matrix3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

        fCos = cos(fRAngle.valueRadians());
        fSin = sin(fRAngle.valueRadians());
        Matrix3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

        *this = kYMat*(kZMat*kXMat);
    }
    //-----------------------------------------------------------------------
    void Matrix3::FromEulerAnglesZXY (const Radian& fYAngle, const Radian& fPAngle,
        const Radian& fRAngle)
    {
        float fCos, fSin;

        fCos = cos(fYAngle.valueRadians());
        fSin = sin(fYAngle.valueRadians());
        Matrix3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

        fCos = cos(fPAngle.valueRadians());
        fSin = sin(fPAngle.valueRadians());
        Matrix3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

        fCos = cos(fRAngle.valueRadians());
        fSin = sin(fRAngle.valueRadians());
        Matrix3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

        *this = kZMat*(kXMat*kYMat);
    }
    //-----------------------------------------------------------------------
    void Matrix3::FromEulerAnglesZYX (const Radian& fYAngle, const Radian& fPAngle,
        const Radian& fRAngle)
    {
        float fCos, fSin;

        fCos = cos(fYAngle.valueRadians());
        fSin = sin(fYAngle.valueRadians());
        Matrix3 kZMat(fCos,-fSin,0.0,fSin,fCos,0.0,0.0,0.0,1.0);

        fCos = cos(fPAngle.valueRadians());
        fSin = sin(fPAngle.valueRadians());
        Matrix3 kYMat(fCos,0.0,fSin,0.0,1.0,0.0,-fSin,0.0,fCos);

        fCos = cos(fRAngle.valueRadians());
        fSin = sin(fRAngle.valueRadians());
        Matrix3 kXMat(1.0,0.0,0.0,0.0,fCos,-fSin,0.0,fSin,fCos);

        *this = kZMat*(kYMat*kXMat);
    }

	
Vector3 Matrix3::getColumn(int i)
{
	Vector3 returnVector;
	if (i == 0)
	{
		returnVector[0] = m[0][0];
		returnVector[1] = m[0][1];
		returnVector[2] = m[0][2];
	}
	else if (i == 1)
	{
		returnVector[0] = m[1][0];
		returnVector[1] = m[1][1];
		returnVector[2] = m[1][2];
	}
	else if (i == 2)
	{
		returnVector[0] = m[2][0];
		returnVector[1] = m[2][1];
		returnVector[2] = m[2][2];
	}

	return  returnVector;
}
	

	const float Matrix3::EPSILON = 1e-06;
	const Matrix3 Matrix3::ZERO(0,0,0,0,0,0,0,0,0);
	const Matrix3 Matrix3::IDENTITY(1,0,0,0,1,0,0,0,1);
	const float Matrix3::ms_fSvdEpsilon = 1e-04;
	const unsigned int Matrix3::ms_iSvdMaxIterations = 32;
	/*
float Matrix3::InvSqrt(float x){
   float xhalf=.5f*x;
   int i=*(int*)&x;
   i=0x5f3759df-(i>>1);
   x=*(float*)&i;
   x=x*(1.5f-xhalf*x*x);
   return x;
}
*/
