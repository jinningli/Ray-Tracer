#include "plane.h"  

namespace Tracer
{
	Plane::Plane()
	{
		//ctor  
	}
	Plane::~Plane()
	{
		//dtor  
	}

	Plane::Plane(const GVector3& _normal, float _d)
	{
		normal = _normal;
		d = _d;
	}
	IntersectResult Plane::isIntersected(CRay& ray)
	{
		IntersectResult result = IntersectResult::noHit();
		float a = ray.getDirection().dotMul(this->normal);
		if (a < 0)
		{
			result.isHit = 1;
			float b = this->normal.dotMul(ray.getOrigin() - normal*d);
			result.distance = -b / a;
			result.position = ray.getPoint(result.distance);
			result.normal = this->normal;
			result.material = material;
			return result;
		}
		return result;
	}
}