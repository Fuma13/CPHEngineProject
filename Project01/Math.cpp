
#include "Math.h"

Radian& Radian::operator= ( const float& f ) 
{ mRad = f; return *this; }

Radian& Radian::operator= ( const Radian& r ) 
{ mRad = r.mRad; return *this; }

float Radian::valueRadians() const 
{ return mRad; }

Radian Radian::operator- ( const Radian& r ) const 
{ return Radian ( mRad - r.mRad ); }

Radian Radian::operator* ( float f ) const 
{ return Radian ( mRad * f ); }

Radian Radian::operator+ ( const Radian& r ) const 
{ return Radian ( mRad + r.mRad ); }

bool Radian::operator<  ( const Radian& r ) const 
{ return mRad <  r.mRad; }

bool Radian::operator>  ( const Radian& r ) const 
{ return mRad >  r.mRad; }

float Math::InvSqrt(float x)
{
	float xhalf=.5f*x;
	int i=*(int*)&x;
	i=0x5f3759df-(i>>1);
	x=*(float*)&i;
	x=x*(1.5f-xhalf*x*x);
	return x;
}