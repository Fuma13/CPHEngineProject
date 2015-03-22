#include "Vector4.h"

Vector4::Vector4(float xF, float yF, float zF, float wF )
{
	x=xF; y=yF; z = zF, w = wF;
}

float& Vector4::operator[] ( const size_t i )
{
	assert( i < 4 ); //check for correct size
	return *(&x+i); //return the i-th element of this data
}

Vector4& Vector4::operator= ( const Vector4& otherVector )
{
	x = otherVector.x;
	y = otherVector.y;
	z = otherVector.z;
	w = otherVector.w;

	return *this;
}

bool Vector4::operator== ( const Vector4& otherVector ) const
{
	return ( x == otherVector.x && y == otherVector.y && z == otherVector.z && w == otherVector.w );
}

bool Vector4::operator!= ( const Vector4& otherVector ) const
{
	return ( x != otherVector.x || y != otherVector.y || z != otherVector.z || w == otherVector.w );
}

Vector4 Vector4::operator+ ( const Vector4& otherVector ) const
{
	return Vector4(
		x + otherVector.x,
		y + otherVector.y,
		z + otherVector.z,
		w + otherVector.w);
}

Vector4 Vector4::operator- ( const Vector4& rightSidedVector ) const
{
	return Vector4(
		x - rightSidedVector.x,
		y - rightSidedVector.y,
		z - rightSidedVector.z,
		w - rightSidedVector.w);
}

Vector4 Vector4::operator* ( const float scalar ) const
{
	return Vector4(
		x * scalar,
		y * scalar,
		z * scalar,
		w * scalar);
}

Vector4 Vector4::operator* ( const Vector4& rightSidedVector ) const
{
	return Vector4(
		x * rightSidedVector.x,
		y * rightSidedVector.y,
		z * rightSidedVector.z,
		w * rightSidedVector.w);
}

Vector4 Vector4::operator/ ( const float scalar ) const
{
	assert( scalar != 0.0 );
	float oneDividedByScalar = 1.0f / scalar;

	return Vector4(
		x * oneDividedByScalar,
		y * oneDividedByScalar,
		z * oneDividedByScalar,
		w * oneDividedByScalar);
}

Vector4 Vector4::operator / ( const Vector4& otherVector ) const
{
	return Vector4(
		x / otherVector.x,
		y / otherVector.y,
		z / otherVector.z,
		w / otherVector.w);
}

float Vector4::dotProduct(const Vector4& vec) const
{
	return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}

Vector3 Vector4::xyz() const
{
	return Vector3(x,y,z);
}