#pragma once
#include "plane.h"
#include "sphere.h"
#include "intersectresult.h"

namespace Tracer
{
	class Scene
	{
	public:
		Plane** SCENE_PLANELIST;
		CSphere** SCENE_SPHERELIST;
		int planesize;
		int spheresize;
		Scene(int _planetot = 100, int _spheretot = 100);
		void insert(Plane* plane);
		void insert(CSphere* sphere);
		IntersectResult isIntersected(CRay& _ray);
	};

}