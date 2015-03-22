#ifndef __Math_H__
#define __Math_H__

#include <math.h>

class Radian
{
	public:
		float mRad;
		
		explicit Radian ( float r=0 ) : mRad(r) {};

		Radian& operator = ( const float& f );
		Radian& operator = ( const Radian& r );

		float valueRadians() const;

		Radian operator * ( float f ) const;
		Radian operator + ( const Radian& r ) const;
		Radian operator - ( const Radian& r ) const;

		bool operator <  ( const Radian& r ) const;
		bool operator >  ( const Radian& r ) const;
};

class Math
{
	public:
		//This is taken from http://www.ogre3d.org/forums/viewtopic.php?p=258032
		static float InvSqrt(float x);
		static float Sin (const Radian& fValue) 
		{
			return ( sin(fValue.valueRadians() ));
		}
		static float Cos (const Radian& fValue) 
		{
			return (cos(fValue.valueRadians()));
		}

};

#endif