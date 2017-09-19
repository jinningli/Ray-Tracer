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
		//������  
		GVector3 normal;
		//��ԭ��ľ���  
		float d;
	public:
		Material* material;
	};
}