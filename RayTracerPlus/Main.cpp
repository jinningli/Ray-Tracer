#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include "Vec3f.h"
#define STBI_ONLY_PNG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "screen.h"
#include "camera.h"
#include "gvector3.h"
#include "sphere.h"
#include "plane.h"
#include "checkmaterial.h"
#include "phong.h"
#include "scene.h"
using namespace Tracer;

Vec3f spotpos;
Vec3f screen_origin;
Vec3f screen_dir1;
Vec3f screen_dir2;

int w;
int h;
int comp = 3;


void simpletrace(STBI_SCREEN & scr)
{
	float horiz = 0.0;
	float dep = 10;
	perspectiveCamera camera(GVector3(horiz, 10, dep), GVector3(0, 0, -1), GVector3(0, 1, 0), 90);
	long maxDepth = 18;
	CSphere* sphere1 = new CSphere(GVector3(0, 10, -10), 10.0);
	float dx = 1.0f / w;
	float dy = 1.0f / h;
	float dD = 255.0f / maxDepth;
	for (long y = 0; y < w; ++y)
	{
		float sy = 1 - dy*y;
		for (long x = 0; x < h; ++x)
		{
			float sx = dx*x;
			CRay ray(camera.generateRay(sx, sy));
			IntersectResult result = sphere1->isIntersected(ray);
			if (result.isHit)
			{
				double t = MIN(result.distance*dD, 255.0f);
				int depth = (int)(255 - t);
				scr.STBI_SCREEN_SET_PIX(x, y, depth, depth, depth);
			}

		}
	}     
}

void protrace(STBI_SCREEN& scr)
{
	perspectiveCamera camera(GVector3(0, 10, 10), GVector3(0, -0.5, -1), GVector3(1, 0, 0), 90);
	Plane plane1(GVector3(0, 1, 0), 1.0);
	CSphere sphere1(GVector3(0, 5, -10), 5.0);
	plane1.material = new CheckerMaterial(0.1f);
	sphere1.material = new PhongMaterial(Color::red(), Color::white(), 16);
	long maxDepth = 20;

	float dx = 1.0f / w;
	float dy = 1.0f / h;
	float dD = 255.0f / maxDepth;
	for (long y = 0; y < h; ++y)
	{
		float sy = 1 - dy*y;
		for (long x = 0; x < w; ++x)
		{
			float sx = dx*x;
			CRay ray(camera.generateRay(sx, sy));
			//IntersectResult result = sphere1.isIntersected(ray);
			IntersectResult result = plane1.isIntersected(ray);  
			if (result.isHit)
			{
				//Color color = sphere1.material->sample(ray, result.position, result.normal);
				Color color =plane1.material->sample(ray, result.position, result.normal);  
				color.saturate();
				//color.show(); 
				scr.STBI_SCREEN_SET_PIX(x, y, color.r * 255, color.g * 255, color.b * 255);
			}
		}
	}
}

Color rayTraceRecursive(Scene* scene, CRay& ray, long maxReflect)
{
	IntersectResult result = scene->isIntersected(ray);
	if (result.material)
	{
		float reflectiveness = result.material->getRef();
		Color color = result.material->sample(ray, result.position, result.normal);
		color = color.multiply(1 - reflectiveness);
		if ((reflectiveness > 0) && (maxReflect > 0))
		{
			GVector3 r = result.normal*(-2 * result.normal.dotMul(ray.getDirection())) + ray.getDirection();
			CRay rfray = CRay(result.position, r);
			Color reflectedColor = rayTraceRecursive(scene, rfray, maxReflect - 1);
			color = color.add(reflectedColor.multiply(reflectiveness));
		}
		return color;
	}
	else return Color::black();
}

void proprotrace(STBI_SCREEN& scr)
{
	perspectiveCamera camera(GVector3(0, 10, 10), GVector3(0, -0.2, -1), GVector3(0, 1, 0), 90);
	Plane* plane1 = new Plane(GVector3(0, 1, 0), 1.0);
	CSphere* sphere1 = new CSphere(GVector3(-2, 5, -10), 5.0);
	CSphere* sphere2 = new CSphere(GVector3(5, 5, -10), 3.0);
	plane1->material = new CheckerMaterial(0.1f, 0.5f);
	sphere1->material = new PhongMaterial(Color::red(), Color::white(), 16, 0.25f);
	sphere2->material = new PhongMaterial(Color::blue(), Color::white(), 16, 0.25f);
	Scene dimension;
	dimension.insert(plane1);
	dimension.insert(sphere1);
	dimension.insert(sphere2);

	long maxDepth = 20;
	float dx = 1.0f / w;
	float dy = 1.0f / h;
	float dD = 255.0f / maxDepth;
	for (long y = 0; y < h; ++y)
	{
		float sy = 1 - dy*y;
		for (long x = 0; x < w; ++x)
		{
			float sx = dx*x;
			CRay ray(camera.generateRay(sx, sy));
			//IntersectResult result = sphere1.isIntersected(ray);
			IntersectResult result = dimension.isIntersected(ray);
			if (result.material)
			{
				//Color color = sphere1.material->sample(ray, result.position, result.normal);
				Color color = rayTraceRecursive(&dimension, ray, 5);
				color.saturate();
				//color.show(); 
				scr.STBI_SCREEN_SET_PIX(x, y, color.r * 255, color.g * 255, color.b * 255);
			}
		}
	}
}
int main()
{	
	freopen("variable.txt", "r", stdin);
	printf("please set w & h:\n");
	scanf("%d%d%d", &w, &h, &comp);
	STBI_SCREEN scr(w, h, comp);
	scr.STBI_SCREEN_SET_POS(screen_origin, screen_dir1, screen_dir2);
	unsigned char* image;
	image = new unsigned char[w * h * comp];
	//simpletrace(scr);
	//protrace(scr);
	proprotrace(scr);
	//scr.STBI_SCREEN_SHOW(1);
	scr.STBI_SCREEN_OUTPUT(image);
	stbi_write_png("testout.png", w, h, comp, image, 0);
	return 0;
}