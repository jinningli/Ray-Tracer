#pragma once
#include "color.h"
#include "gvector3.h"
#include "intersectresult.h"
#include "scene.h"
namespace Tracer
{
	class PointLight
	{
	public:
		PointLight();
		PointLight(Color _color, GVector3 _position, bool _isShadow);
		virtual ~PointLight();
		Color intersect(Scene &scence, IntersectResult &result);
	protected:
	private:
		bool isShadow;
		Color color;
		GVector3 position;
	};
}