#include "Vector2.h"

Vector2::Vector2( float xF, float yF )
{
	x=xF; y=yF;
}

float& Vector2::operator[] ( const size_t i )
{
	assert( i < 2 ); //check for correct size
	return *(&x+i); //return the i-th element of this data
}

Vector2& Vector2::operator= ( const Vector2& otherVector )
{
	x = otherVector.x;
	y = otherVector.y;

	return *this;
}

bool Vector2::operator== ( const Vector2& otherVector ) const
{
	return ( x == otherVector.x && y == otherVector.y );
}

bool Vector2::operator!= ( const Vector2& otherVector ) const
{
	return ( x != otherVector.x || y != otherVector.y );
}

Vector2 Vector2::operator+ ( const Vector2& otherVector ) const
{
	return Vector2(
		x + otherVector.x,
		y + otherVector.y);
}

Vector2 Vector2::operator- ( const Vector2& rightSidedVector ) const
{
	return Vector2(
		x - rightSidedVector.x,
		y - rightSidedVector.y);
}

Vector2 Vector2::operator* ( const float scalar ) const
{
	return Vector2(
		x * scalar,
		y * scalar);
}

Vector2 Vector2::operator* ( const Vector2& rightSidedVector) const
{
	return Vector2(
		x * rightSidedVector.x,
		y * rightSidedVector.y);
}

Vector2 Vector2::operator/ ( const float scalar ) const
{
	assert( scalar != 0.0 );
	float oneDividedByScalar = 1.0f / scalar;

	return Vector2(
		x * oneDividedByScalar,
		y * oneDividedByScalar);
}

Vector2 Vector2::operator / ( const Vector2& otherVector) const
{
	return Vector2(
		x / otherVector.x,
		y / otherVector.y);
}

float Vector2::length () const
{
	return sqrt( x * x + y * y );
}

float Vector2::length_squared  () const
{
	return x * x + y * y;
}

float Vector2::distance( const Vector2& rightHandedVector ) const
{
	return ( *this - rightHandedVector ).length();
}

float Vector2::distance_squared( const Vector2& rightHandedVector ) const
{
	return ( *this - rightHandedVector ).length_squared();
}

float Vector2::dotProduct( const Vector2& otherVector ) const
{
	return x * otherVector.x + y * otherVector.y;
}

void Vector2::normalise()
{
	float fLength = sqrt( x * x + y * y);

	// Will also work for zero-sized vectors, but will change nothing
	if ( fLength > 1e-08 )
	{
		float fInvLength = 1.0f / fLength;
		x *= fInvLength;
		y *= fInvLength;
	}
	//return fLength;
}

float Vector2::crossProduct( const Vector2& otherVector ) const
{
	return x * otherVector.y - y * otherVector.x;
}

bool Vector2::isZeroLength(void) const
{
	float sqlen = (x * x) + (y * y);
	return (sqlen < (1e-06 * 1e-06));
}


/** Vector2 testing code

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