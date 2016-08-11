#include "pointlight.h"  

namespace Tracer
{
	PointLight::PointLight()
	{
		//ctor  
	}

	PointLight::~PointLight()
	{
		//dtor  
	}
	PointLight::PointLight(Color _color, GVector3 _position, bool _isShadow)
	{
		color = _color;
		position = _position;
		isShadow = _isShadow;
	}
	//通过光线与场景的相交结果计算光照结果  
	Color PointLight::intersect(Scene &scence, IntersectResult &rayResult)
	{
		//生产shadowRay的修正值  
		const float k = 1e-4;
		GVector3 delta = this->position - rayResult.position;
		float distance = delta.getLength();
		//生成与光照相反方向的shadowRay  
		CRay shadowRay = CRay(rayResult.position, delta.normalize());
		GVector3 shadowDir = delta.normalize();
		//计算shadowRay是否与场景相交  
		IntersectResult lightResult = scence.isIntersected(shadowRay);
		Color resultColor = Color::black();
		Color returnColor = Color::black();
		//如果shadowRay与场景中的物体相交  
		if (lightResult.material && (lightResult.distance <= distance))
		{
			return resultColor;
		}
		else
		{
			resultColor = this->color.divide(distance*distance);
			float NdotL = rayResult.normal.dotMul(shadowDir);
			if (NdotL >= 0)
				returnColor = returnColor.add(resultColor.multiply(NdotL));
			return returnColor;
		}

	}
}