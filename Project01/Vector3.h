#ifndef __Vector3_H__
#define __Vector3_H__

#include <assert.h>
#include <Math.h>

class Vector3 
{
	public:
		float x;
		float y;
		float z;

		Vector3();

		Vector3( float, float, float );
		float& operator[] ( const size_t );

		/** Assigns the value of one vector to the other vector
			@param The other vector	*/
		Vector3& operator= ( const Vector3& );

		/** Returns TRUE if the values for X,Y,Z are the same
			@param The other vector	*/
		bool operator== ( const Vector3& ) const;

		/** Returns FALSE if the valuesfor X,Y,Z are the different
			@param The other vector	*/
		bool operator!= ( const Vector3& ) const;

		/** Adds x to x, y to y and z to z
			@param The other vector	*/
		Vector3 operator+ ( const Vector3& ) const;

		/** Substracts x from x, y from y and z from z
			@param The right sided vector	*/
		Vector3 operator- ( const Vector3& ) const;

		/** Multiplies Vector with a scalar
			@param The scalar	*/
		Vector3 operator* ( const float ) const;

		/** Multiplies Vector with another Vector
			@param The right sided vector	*/
		Vector3 operator* ( const Vector3& ) const;

		/** Divides vector by a scalar
			@param The scalar	*/
		Vector3 operator/ ( const float ) const;

		/** Divides vector by another vector
			@param The other vector		*/
		Vector3 operator/ ( const Vector3& ) const;

		/** Returns the length (magnitude) of the vector.
			@warning
				This operation requires a square root and is expensive in
				terms of CPU operations. If you don't need to know the exact
				length (e.g. for just comparing lengths) use length_squared()
				instead.	*/
		float length () const;

		/** Returns the square of the length(magnitude) of the vector.
			@remarks
				Use this if you want to find the longest / shortest vector 
				without incurring the square root.

				This  method is for efficiency - calculating the actual
				length of a vector requires a square root, which is expensive
				in terms of the operations required. This method returns the
				square of the length of the vector (the length but before the square 
				root is taken).		*/
		float length_squared () const;

		/** Returns the distance to another vector.
			@warning
				This operation requires a square root and is expensive in
				terms of CPU operations. If you don't need to know the exact
				distance (e.g. for just comparing distances) use distance_squared()
				instead.	*/
		float distance( const Vector3& ) const;

		/** Returns the square of the distance to another vector.
			@remarks
				Use this if you want to find the longest / shortest distance
				without incurring the square root.

				This method is for efficiency - calculating the actual
				distance to another vector requires a square root, which is
				expensive in terms of the operations required. This method
				returns the square of the distance to another vector, i.e.
				the same as the distance but before the square root is taken.	*/
		float distance_squared( const Vector3& ) const;

		/** Calculates the dot (scalar) product of this vector with another.
			@remarks
				The dot product can be used to calculate the angle between 2
				vectors. If both are unit vectors, the dot product is the
				cosine of the angle; otherwise the dot product must be
				divided by the product of the lengths of both vectors to get
				the cosine of the angle. This result can further be used to
				calculate the distance of a point from a plane.
			@param
				vec Vector with which to calculate the dot product (together
				with this one).
			@returns
				A float representing the dot product value.		*/
		float dotProduct( const Vector3& ) const;

		/** Normalises the vector.
			@remarks
				This method normalises the vector such that it's
				length / magnitude is 1. The result is called a unit vector.
				/n
			@note
				1. This function will not crash for zero-sized vectors, but there
				will be no changes made to their components.
				2. InOGRE but not here: returns the previous length of the vector.	*/
		void normalise();

		/// Retrurns a new vector normalized from the vector that call  this
		Vector3 normaliseTo() const;

		/** Calculates the cross-product of 2 vectors, i.e. the vector that
			lies perpendicular to them both.
			@remarks
				The cross-product is normally used to calculate the normal
				vector of a plane, by calculating the cross-product of 2
				non-equivalent vectors which lie on the plane (e.g. 2 edges
				of a triangle).
			@param
				vec Vector which, together with this one, will be used to
				calculate the cross-product.
			@returns
				A vector which is the result of the cross-product. This
				vector will <b>NOT</b> be normalised, to maximise efficiency
				- call Vector2::normalise on the result if you wish this to
				be done. 		*/
		Vector3 crossProduct( const Vector3& ) const;

		static const Vector3 ZERO;
        static const Vector3 UNIT_X;
        static const Vector3 UNIT_Y;
        static const Vector3 UNIT_Z;
        static const Vector3 NEGATIVE_UNIT_X;
        static const Vector3 NEGATIVE_UNIT_Y;
        static const Vector3 NEGATIVE_UNIT_Z;
        static const Vector3 UNIT_SCALE;

		/** Returns true if this vector is zero length. */
		bool isZeroLength(void) const;

		/** Returns the vector with inverted sign */
		Vector3 negative() const;
};

#endif