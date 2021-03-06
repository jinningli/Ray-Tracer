#pragma once
#include <stdlib.h>  
#include <stdio.h>  
#include <cmath>  
#include <iostream>  

namespace Tracer
{
	class Color
	{
	public:
		float r;
		float g;
		float b;
		Color();
		Color(float _r, float _g, float _b);
		Color add(const Color& c);
		Color multiply(float s) const;
		Color modulate(const Color& c) const;
		Color divide(float f);
		bool operator== (const Color& other);
		Color Color::normalize();
		void saturate();
		virtual ~Color();
		static inline Color black() { return Color(0, 0, 0); }
		static inline Color white() { return Color(1, 1, 1); }
		static inline Color red() { return Color(1, 0, 0); }
		static inline Color green() { return Color(0, 1, 0); }
		static inline Color blue() { return Color(0, 0, 1); }
		static inline Color grass() { return Color(0.0859580338, 0.981354177, 0.171916068);}
		static inline Color lgreen() { return Color(0.398132831, 0.739837408, 0.542338431); }
		static inline Color qingse() { return Color(68, 206, 246).normalize(); }
		static inline Color skyblue() { return Color(46, 78, 126).normalize(); }
		static inline Color yellow() { return Color(250, 255, 124).normalize(); }
	protected:
	private:

	};
}