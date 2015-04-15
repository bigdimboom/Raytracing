#pragma once
#include "Global.h"
#include "Ray.h"
#include "Camera.h"

class RayCaster
{
public:
	RayCaster(point3 camPos, point3 front, float near, float far, int width, int height);
	~RayCaster();
	void Init();
	Ray& CastRayThroughPixel(int i, int j);
	Camera* GetCamera();
private:
	void _ConstructRays();
	void _ConstructNearClip();
	Camera* _cam;
	int _width, _height;
	Ray* _rays;
	point3*_nearClip;
};

