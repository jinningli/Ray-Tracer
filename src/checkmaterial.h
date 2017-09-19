#pragma once
#include "color.h"  
#include <stdlib.h>  
#include "material.h"
namespace Tracer
{
	class CheckerMaterial: public Material
	{
	public:
		CheckerMaterial(float _scale, float _reflectiveness = 0);
		Color sample(const CRay& ray, const GVector3& position, const GVector3& normal);
	protected:
	private:
		float scale;
	};
}