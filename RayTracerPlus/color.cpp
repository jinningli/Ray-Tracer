#include "color.h"  
namespace Tracer
{
	Color::Color()
	{
		//ctor  
	}

	Color::~Color()
	{
		//dtor  
	}
	Color::Color(float _r, float _g, float _b)
	{
		r = _r;g = _g;b = _b;
	}
	bool Color::operator== (const Color& other)
	{
		return r == other.r && g == other.g && b == other.b;
	}
	Color Color::add(const Color& c)
	{
		return Color(r + c.r, g + c.g, b + c.b);
	}
	Color Color::divide(float f)
	{
		return Color(r / f, g / f, b / f);
	}
	Color Color::multiply(float s) const
	{
		return Color(r * s, g * s, b * s);
	}
	Color Color::modulate(const Color&c) const
	{
		return Color(r * c.r, g * c.g, b * c.b);
	}
	void Color::saturate()
	{
		r = r > 1.0 ? 1.0 : r;
		g = g > 1.0 ? 1.0 : g;
		b = b > 1.0 ? 1.0 : b;
	}
	Color Color::normalize()
	{
		float k = sqrt(r * r + g * g + b * b);
		r /= k;
		g /= k;
		b /= k;
		return *this;
	}
}