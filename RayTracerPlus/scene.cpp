#include "scene.h"

namespace Tracer
{
	Scene::Scene(int _planetot, int _spheretot)
	{ 
		SCENE_PLANELIST = new Plane*[_planetot];
		SCENE_SPHERELIST = new CSphere*[_spheretot];
		planesize = spheresize = 0;
	}
	void Scene::insert(Plane* plane)
	{
		SCENE_PLANELIST[++planesize] = plane;
	}
	void Scene::insert(CSphere* sphere)
	{
		SCENE_SPHERELIST[++spheresize] = sphere;
	}
	IntersectResult Scene::isIntersected(CRay& _ray)
	{
		float inf = 1e30;
		float min = inf;
		IntersectResult minres = IntersectResult::noHit();
		for (int i = 1; i <= planesize; i++)
		{
			IntersectResult result = SCENE_PLANELIST[i]->isIntersected(_ray);
			if (result.isHit && result.material && result.distance < min)
			{
				min = result.distance;
				minres = result;
			}
		}
		for (int i = 1; i <= spheresize; i++)
		{
			IntersectResult result = SCENE_SPHERELIST[i]->isIntersected(_ray);
			if (result.isHit && result.material && result.distance < min)
			{
				min = result.distance;
				minres = result;
			}
		}
		return minres;
	}

}
