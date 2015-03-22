#include <assert.h>
#include <math.h>

#ifndef __Vector2_H__
#define __Vector2_H__

class Vector2 
{
	public:
		float x;
		float y;

		// empty default constructor
		Vector2(){};

		Vector2( float, float );
		float& operator[] ( const size_t );

		/** Assigns the value of one vector to the other vector
			@param The other vector		*/
		Vector2& operator= ( const Vector2& );

		/** Returns TRUE if the values for X,Y are the same
			@param The other vector		*/
		bool operator== ( const Vector2& ) const;

		/** Returns FALSE if the valuesfor X,Y are the different
			@param The other vector		*/
		bool operator!= ( const Vector2& ) const;

		/** Adds x to x, y to y 
			@param The other vector		*/
		Vector2 operator+ ( const Vector2& ) const;

		/** Substracts x from x, y from y 
			@param The right sided vector		*/
		Vector2 operator- ( const Vector2& ) const;

		/** Multiplies Vector with a scalar
			@param The scalar	*/
		Vector2 operator* ( const float ) const;

		/** Multiplies Vector with another Vector
			@param The right sided vector	*/
		Vector2 operator* ( const Vector2& ) const;

		/** Divides vector by a scalar
			@param The scalar	*/
		Vector2 operator/ ( const float ) const;

		/** Divides vector by another vector
			@param The other vector		*/
		Vector2 operator / ( const Vector2& ) const;

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
		float length_squared  () const;

		/** Returns the distance to another vector.
			@warning
				This operation requires a square root and is expensive in
				terms of CPU operations. If you don't need to know the exact
				distance (e.g. for just comparing distances) use distance_squared()
				instead.	*/
		float distance( const Vector2& ) const;

		/** Returns the square of the distance to another vector.
			@remarks
			Use this if you want to find the longest / shortest distance
			without incurring the square root.

			This method is for efficiency - calculating the actual
			distance to another vector requires a square root, which is
			expensive in terms of the operations required. This method
			returns the square of the distance to another vector, i.e.
			the same as the distance but before the square root is taken.	*/
		float distance_squared( const Vector2& ) const;

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
		float dotProduct( const Vector2& ) const;

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

        /** Calculates the 2 dimensional cross-product of 2 vectors, which results
			in a single floating point value which is 2 times the area of the triangle.		*/		
		float crossProduct( const Vector2& ) const;

		/** Returns true if this vector is zero length. */
		bool isZeroLength(void) const;

};

#endif

/*

		Vector2 bla(2,3);
		cout << " main testing vector position 0 =" << bla[0] << "position 1 =" << bla[1]<< endl;
		Vector2 blu(2,3);
		cout << " second testing vector position 0 =" << bla[0] << "position 1 =" << bla[1]<< endl;
		Vector2 not_blubla(3,2);
		if (bla==blu) cout << "true" ;
		if (bla != not_blubla) {cout << "and false both work." << endl;}
		Vector2 added = blu+bla;
		cout << "addition" << added[0] << " and " <<added[1]<< endl;
		Vector2 subtraction = blu-bla;
		cout << "subtraction" << subtraction[0] << " and " << subtraction[1]<< endl;
		float scalarThingy = 3;
		Vector2 scalarMulti = blu*scalarThingy;
		cout << "scalar multiplication with " << scalarThingy << "results in " << scalarMulti[0] << " and " << scalarMulti[1]<< endl;
		Vector2 scalarDivi = blu/scalarThingy;
		cout << "scalar divison with " << scalarThingy << "results in " << scalarDivi[0] << " and " << scalarDivi[1]<< endl;
		Vector2 vectorMulti = blu*bla;
		cout << "vector multiplication  "  << "results in " << vectorMulti[0] << " and " << vectorMulti[1]<< endl;
		Vector2 vectorDivi = blu/bla;
		cout << "vector divison  "  << "results in " << vectorDivi[0] << " and " << vectorDivi[1] << endl;
		float lenger = blu.length();
		cout << "length  "  << lenger << endl;
		float lenger_sq = blu.length_squared();
		cout << "length_squared  "  << lenger_sq << endl;
		float dista = blu.distance(not_blubla);
		cout << "distance to third vector  "  << dista  << endl;
		float dista_sq = blu.distance_squared(not_blubla);
		cout << "squared distance to third vector  "  << dista_sq  << endl;
		float dotaproda = blu.dotProduct(not_blubla);
		cout << "dot product with third vector  " << dotaproda  << endl;
		Vector2 norma(2,3);
		norma.normalise();
		cout << " normalised " << norma[0] << " and at position 1 =" << norma[1]<< endl;
		float crosspro = bla.crossProduct(not_blubla);
		cout << " crossproduct " << crosspro<< endl;


*/