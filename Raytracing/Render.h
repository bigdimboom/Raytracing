#pragma once
#include "Global.h"
#include "RayCaster.h"
#include "Scene.h"
#include "Shape.h"
#include "Sphere.h"
#include "Plane.h"
#include <limits>
#include "Ray.h"

#include <thrust/device_vector.h>


#define INFINITY_FAR 9999999.0f
#define RECURSION_NUM 3
#define THRESHOLD 0.001f

class Render
{
public:
	Render();
	~Render();
	void Init(point3 camPos, point3 front, float near, float far, int width, int height);
	void InitScene();
	void Generate();

	__global__ void GenerateOnGPU(Shape* shapes, int numOfShape, Ray* rays, point4* imgResult, int width, int height);
	
	color4 RayTracer(Ray& ray, int depth);
	void Draw();

	RayCaster* GetRayCaster();
	Scene& GetScene();
	color4* GetPixels();

public:
	static bool IsCudaDevice();


private:
	RayCaster* _rayCaster;
	Scene _scene;
	color4* _pixels;
	int _width, _height;

	std::vector<Shape*> _shapesOnDev;
	Ray* _raysOnDev;
	//Ray* _deviceRays;
};