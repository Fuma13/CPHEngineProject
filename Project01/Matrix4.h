#include "Vector3.h"
#include "Matrix3.h"
#include "Vector4.h"
#include "Quaternion.h"

#ifndef __Matrix4_H__
#define __Matrix4_H__

class Matrix4 
{
    protected:
        /// The matrix entries, indexed by [row][col].
        union {
            float m[4][4];
            float _m[16];
        };	//In order to achieve portability it might be necessary to look deeper into union. OGRE does not mention anything about it, 
			// but union can work differently on different systems.
			//TODO: evaluate whether union is necessary for any operation

		 public:

        /** Default constructor.
            @note
                It does <b>NOT</b> initialize the matrix for efficiency.
        */
        Matrix4(){}

		/** Constructor. 
			@note: elements 1-4: first row, elements 5-8: second row...
		*/
        Matrix4(
            float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33 );

		/** Tests 2 matrices for equality.		*/
        bool operator == ( const Matrix4& m2 ) const;

        /** Tests 2 matrices for inequality.	*/
        bool operator != ( const Matrix4& m2 ) const;

		/** Concatenate
			@note: A * B is not B * A :)	*/
		Matrix4 operator * (const Matrix4 &m2) const;
		
		/** Multiply the Matrix4 with a Vector4 */
		Vector4 operator * ( const Vector4 & v) const;

		/** Matrix addition.	*/
        Matrix4 operator + ( const Matrix4 &m2 ) const;

		/** Matrix subtraction.		*/
        Matrix4 operator - ( const Matrix4 &m2 ) const;

		/** "Change row with columns" */
		Matrix4 transpose(void) const;


		/*-----------------------------------------------------------------------
        Translation Transformation
        -----------------------------------------------------------------------*/
        /** Sets the translation transformation part of the matrix.		*/
        void setTrans( const Vector3& v );

        /** Extracts the translation transformation part of the matrix.		*/
        Vector3 getTrans() const;

		/** Builds a translation matrix @param Vector3	 */
        void makeTrans( const Vector3& v );

		/** Gets a translation matrix.	
			@return Identity matrix with the vector it received in the fourth row*/
        static Matrix4 getTrans( const Vector3& v );

		 /*	-----------------------------------------------------------------------
        Scale Transformation
        ----------------------------------------------------------------------- */
        /** Sets the scale part of the matrix.	*/
        void setScale( const Vector3& v );

        /** Gets a scale matrix.	*/
        //static Matrix4 getScale( const Vector3& v );
		Vector3 getScale() const;

		/** Extracts the rotation / scaling part of the Matrix as a 3x3 matrix. 
			@param m3x3 Destination Matrix3		*/
        void extract3x3Matrix(Matrix3& m3x3) const;

		static const Matrix4 ZERO;

		static const Matrix4 IDENTITY;

		float* operator [] ( size_t iRow )
        {
            assert( iRow < 4 );
            return m[iRow];
        }

		Quaternion extractQuaternion() const
		{
		Matrix3 m3x3;
		extract3x3Matrix(m3x3);
		return Quaternion(m3x3);
		}

		void fromMatrix3( const Matrix3& mt3 );
};

#endif