#pragma once
#include "gvector3.h"  
#include "ray.h"  
#include "color.h"  
namespace Tracer
{
	class Material
	{
	public:
		Material();
		Material(float _reflectiveness);
		float getRef();
		void setRef(float _reflectiveness);
		virtual ~Material();
		virtual Color sample(const CRay& ray, const GVector3& position, const GVector3& normal);
	protected:
		float reflectiveness;
	private:

	};
}