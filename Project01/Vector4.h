#ifndef __Vector4_H__
#define __Vector4_H__

#include <assert.h>
#include <math.h>
#include "Vector3.h"

class Vector4
{
	public:
		float x;
		float y;
		float z;
		float w;

		Vector4( float, float, float, float );
		float& operator[] ( const size_t );

		/** Assigns the value of one vector to the other vector
			@param The other vector	*/
		Vector4& operator= ( const Vector4& );

		/** Returns TRUE if the values for X,Y,Z,W are the same
			@param The other vector	*/
		bool operator== ( const Vector4& ) const;

		/** Returns FALSE if the valuesfor X,Y,Z,W are the different
			@param The other vector	*/
		bool operator!= ( const Vector4& ) const;

		/** Adds x to x, y to y, z to z, w to w
			@param The other vector	*/
		Vector4 operator+ ( const Vector4& ) const;

		/** Substracts x from x, y from y, z from z, w from w
			@param The right sided vector	*/
		Vector4 operator- ( const Vector4& ) const;

		/** Multiplies Vector with a scalar
			@param The scalar	*/
		Vector4 operator* ( const float ) const;

		/** Multiplies Vector with another Vector
			@param The right sided vector	*/
		Vector4 operator* ( const Vector4& ) const;

		/** Divides vector by a scalar
			@param The scalar	*/
		Vector4 operator/ ( const float ) const;

		/** Divides vector by another vector
			@param The other vector		*/
		Vector4 operator/ ( const Vector4& ) const;

		/** Calculates the dot (scalar) product of this vector with another.
			@param
				vec Vector with which to calculate the dot product (together
				with this one).
			@returns
				A float representing the dot product value.		*/
		float dotProduct(const Vector4& vec) const;

		/** return the x,y,z parametrers */
		Vector3 xyz () const;
};

#endif