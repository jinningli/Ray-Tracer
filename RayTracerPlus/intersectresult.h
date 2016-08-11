#pragma once
#include "gvector3.h"
#include "material.h"
namespace Tracer
{
	class IntersectResult {
	public:
		float distance;
		bool isHit;
		GVector3 position;
		GVector3 normal;
		Material* material;
		IntersectResult() { distance = 0; isHit = false; position = GVector3(); normal = GVector3(); material = NULL; }
		static inline IntersectResult noHit() { return IntersectResult(); }
	};
}