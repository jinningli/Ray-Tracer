#pragma once
#include"gvector3.h"  
#include "color.h"  
#include "ray.h"  
#include "material.h"  
// global temp  
namespace Tracer
{
	static GVector3 lightDir = GVector3(1, 1, 1).normalize();
	static Color lightColor = Color::white();

	class PhongMaterial :public Material
	{
	public:
		PhongMaterial(const Color& _diffuse, const Color& _specular, const float& _shininess, float _reflectiveness = 0);
		Color sample(const CRay& ray, const GVector3& position, const GVector3& normal);
	protected:
	private:
		Color   diffuse;
		Color   specular;
		float   shininess;
	};
}
