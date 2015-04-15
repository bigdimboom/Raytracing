#pragma once
#include "Global.h"
#include "RayCaster.h"
#include "Scene.h"
#include "Shape.h"
#include "Sphere.h"
#include "Plane.h"
#include <limits>


#define INFINITY_FAR 9999999.0f
#define RECURSION_NUM 5
#define THRESHOLD 0.00001f

class Render
{
public:
	Render();
	~Render();
	void Init(point3 camPos, point3 front, float near, float far, int width, int height);
	void InitScene();
	void Generate();
	
	color4 RayTracer(Ray& ray, int depth);
	void Draw();

	RayCaster* GetRayCaster();
	Scene& GetScene();
	color4* GetPixels();
private:
	RayCaster* _rayCaster;
	Scene _scene;
	color4* _pixels;
	int _width, _height;
};