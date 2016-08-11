#include <assert.h>
#pragma once

namespace Tracer
{
	class GVector3;
    class Vec3f
    {
    public:

        //Constructors
        Vec3f();
        Vec3f(float x,float y, float z);
        Vec3f(const Vec3f& v);
		Vec3f(const GVector3& other);
        //Deconstructor
        virtual ~Vec3f();
    public:
        //Operators

        //Operator []
        __forceinline float& operator [](int index)
        {
            assert(index>=0&&index<3);
            return _p[index];
        }
        __forceinline const float& operator [](int index) const
        {
            assert(index>=0&&index<3);
            return _p[index];
        }
        
        //Operator =
        Vec3f& operator = (const Vec3f& v);

        //Operators +=,-=, *=, /=
        void operator +=(const Vec3f& v);
        void operator +=(float f);
        void operator -=(const Vec3f& v);
        void operator -=(float f);
        void operator *=(const Vec3f& v);
        void operator *=(float f);
        void operator /=(const Vec3f& v);
        void operator /=(float f);

        //Operators +,-.*,/
        Vec3f operator +(const Vec3f&v) const;
        Vec3f operator +(float f) const;
        Vec3f operator -(const Vec3f&v) const;
        Vec3f operator -(float f) const;
        Vec3f operator *(const Vec3f&v) const;
        Vec3f operator *(float f) const;
        Vec3f operator /(const Vec3f&v) const;
        Vec3f operator /(float f) const;

        Vec3f operator -() const;

    public:
		Vec3f Vec3f::Normalize();
        float L2Norm_Sqr();
		float Vec3f::Dot(const Vec3f& other);
		Vec3f Vec3f::Cross(const Vec3f& other);
    public:
        union
        {
            struct
            { float _p[3]; };
            struct
            { float x,y,z; };
            struct
            { unsigned char r,g,b; };
        };
        enum {_len = 3};   
        
    };
}

 