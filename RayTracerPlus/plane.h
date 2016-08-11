#pragma once
#include "gvector3.h"  
#include "intersectresult.h"  
#include "ray.h"  
#include "checkmaterial.h"   
#include "material.h"
namespace Tracer
{
	class Plane
	{
	public:
		Plane();
		Plane(const GVector3& _normal, float _d);
		virtual ~Plane();
		virtual IntersectResult isIntersected(CRay& RAY);
	protected:
	private:
		//法向量  
		GVector3 normal;
		//到原点的距离  
		float d;
	public:
		Material* material;
	};
}