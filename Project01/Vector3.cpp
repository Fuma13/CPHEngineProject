/*To some extent this is based on the Ogre engine
some that might be nice to have but are not in this class:
const Vector3 & 	operator+ () const
Vector3 	operator- () const
Vector3 & 	operator+= (const Vector3 &rkVector)
Vector3 & 	operator+= (const Real fScalar)
Vector3 & 	operator-= (const Vector3 &rkVector)
Vector3 & 	operator-= (const Real fScalar)
Vector3 & 	operator*= (const Real fScalar)
Vector3 & 	operator*= (const Vector3 &rkVector)
Vector3 & 	operator/= (const Real fScalar)
Vector3 & 	operator/= (const Vector3 &rkVector)

Radian 	angleBetween (const Vector3 &dest)
 	Gets the angle between 2 vectors.
Quaternion 	getRotationTo (const Vector3 &dest, const Vector3 &fallbackAxis=Vector3::ZERO) const
 	Gets the shortest arc quaternion to rotate this vector to the destination vector.


*/
#include "Vector3.h"

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(float xF, float yF, float zF)
{
	x=xF; y=yF; z = zF;
}

float& Vector3::operator[] ( const size_t i )
{
	assert( i < 3 ); //check for correct size
	return *(&x+i); //return the i-th element of this data
}


Vector3& Vector3::operator= ( const Vector3& otherVector )
{
	x = otherVector.x;
	y = otherVector.y;
	z = otherVector.z;

	return *this;
}

bool Vector3::operator== ( const Vector3& otherVector ) const
{
	return ( x == otherVector.x && y == otherVector.y && z == otherVector.z );
}

bool Vector3::operator!= ( const Vector3& otherVector ) const
{
	return ( x != otherVector.x || y != otherVector.y || z != otherVector.z );
}

Vector3 Vector3::operator+ ( const Vector3& otherVector ) const
{
	return Vector3(
		x + otherVector.x,
		y + otherVector.y,
		z + otherVector.z);
}

Vector3 Vector3::operator- ( const Vector3& rightSidedVector ) const
{
	return Vector3(
		x - rightSidedVector.x,
		y - rightSidedVector.y,
		z - rightSidedVector.z);
}

Vector3 Vector3::operator* ( const float scalar ) const
{
	return Vector3(
		x * scalar,
		y * scalar,
		z * scalar);
}

Vector3 Vector3::operator* ( const Vector3& rightSidedVector) const
{
	return Vector3(
		x * rightSidedVector.x,
		y * rightSidedVector.y,
		z * rightSidedVector.z);
}

Vector3 Vector3::operator/ ( const float scalar ) const
{
	assert( scalar != 0.0 );
	float oneDividedByScalar = 1.0f / scalar;

	return Vector3(
		x * oneDividedByScalar,
		y * oneDividedByScalar,
		z * oneDividedByScalar);
}

Vector3 Vector3::operator / ( const Vector3& otherVector) const
{
	return Vector3(
		x / otherVector.x,
		y / otherVector.y,
		z / otherVector.z);
}

float Vector3::length () const
{
	return sqrt( x * x + y * y + z * z );
}

float Vector3::length_squared  () const
{
	return x * x + y * y + z * z;
}

float Vector3::distance( const Vector3& rightHandedVector ) const
{
	return ( *this - rightHandedVector ).length();
}

float Vector3::distance_squared( const Vector3& rightHandedVector ) const
{
	return ( *this - rightHandedVector ).length_squared();
}

float Vector3::dotProduct( const Vector3& otherVector ) const
{
	return x * otherVector.x + y * otherVector.y + z * otherVector.z;
}

void Vector3::normalise()
{
	float fLength = sqrt( x * x + y * y + z * z );

	// Will also work for zero-sized vectors, but will change nothing
	if ( fLength > 1e-08 )
	{
		float fInvLength = 1.0f / fLength;
		x = x * fInvLength;
		y = y * fInvLength;
		z = z * fInvLength;
	}
	//return fLength;
}

Vector3 Vector3::crossProduct( const Vector3& otherVector ) const
{
	return Vector3(
		y * otherVector.z - z * otherVector.y,
		z * otherVector.x - x * otherVector.z,
		x * otherVector.y - y * otherVector.x);
}

bool Vector3::isZeroLength(void) const
{
	float sqlen = (x * x) + (y * y) + (z * z);
	return (sqlen < (1e-06 * 1e-06));
}

Vector3 Vector3::negative() const
{
	return Vector3( -x, -y, -z);
}

Vector3 Vector3::normaliseTo() const
{
	float fLength = sqrt( x * x + y * y + z * z );
	Vector3 normalized;

	// Will also work for zero-sized vectors, but will change nothing
	if ( fLength > 1e-08 )
	{
		float fInvLength = 1.0f / fLength;
		normalized.x = x * fInvLength;
		normalized.y = y * fInvLength;
		normalized.z = z * fInvLength;
	}

	return normalized;
}


	const Vector3 Vector3::ZERO( 0, 0, 0 );
    const Vector3 Vector3::UNIT_X( 1, 0, 0 );
    const Vector3 Vector3::UNIT_Y( 0, 1, 0 );
    const Vector3 Vector3::UNIT_Z( 0, 0, 1 );
    const Vector3 Vector3::NEGATIVE_UNIT_X( -1,  0,  0 );
    const Vector3 Vector3::NEGATIVE_UNIT_Y(  0, -1,  0 );
    const Vector3 Vector3::NEGATIVE_UNIT_Z(  0,  0, -1 );
    const Vector3 Vector3::UNIT_SCALE(1, 1, 1);