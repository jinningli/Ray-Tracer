#pragma once
#include <iostream>  
#include "gvector3.h"  
#define PI 3.14159  
using namespace std;
namespace Tracer
{
	class CRay
	{
	private:
		GVector3 origin;
		GVector3 direction;
	public:
		CRay();
		CRay(GVector3 o, GVector3 d);
		~CRay();
		void setOrigin(GVector3 o);
		void setDirection(GVector3 d);
		GVector3 getOrigin();
		GVector3 getDirection() const;
		//通过向射线的参数方程传入参数t而获得在射线上的点  
		GVector3 getPoint(double t);

	};
}