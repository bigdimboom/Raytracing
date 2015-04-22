#include "RayCaster.h"


RayCaster::RayCaster(point3 camPos, point3 front, float near, float far, int width, int height)
	:_width(width), _height(height)
{
	_cam = new Camera(camPos, front, near, far);
	_rays = new Ray[width * height];
	_nearClip = new point3[width * height];
}

RayCaster::~RayCaster()
{
	delete _cam;
	delete[] _rays;
	delete[] _nearClip;
}


void RayCaster::Init()
{
	_ConstructNearClip();
	_ConstructRays();
}


void RayCaster::_ConstructNearClip()
{
	//point3 up = _cam->GetUp();
	//point3 right = _cam->GetRight();
	//float near = _cam->GetNear();
	//point3 camPos = _cam->GetPosition();

	//float tanTheta = (_width + 1.0f) / (2.0f * near); //width
	//float tanFi = (_height + 1.0f) / (2.0f * near); //height

	//point3 p1 = camPos + near * _cam->GetFront() - near * tanTheta * right - near * tanFi * up;

	for (int i = 0; i < _height; ++i)
	{
		for (int j = 0; j < _width; ++j)
		{
			//_nearClip[i * _width + j] = p1 +
			//	((float)j / (float)_width + 0.5f) * 2.0f *0.01f * near * tanTheta * right +
			//	((float)i / (float)_height + 0.5f) * 2.0f *0.01f* near * tanFi * up;

			_nearClip[i * _width + j] = point3((-400.0f + j) * 0.01, (-300.0f + i) * 0.01, 0.0f);
		}
	}
}


void RayCaster::_ConstructRays()
{
	for (int i = 0; i < _height; ++i)
	{
		for (int j = 0; j < _width; ++j)
		{
			_rays[i * _width + j].SetOrigin(_nearClip[i * _width + j]);
			_rays[i * _width + j].SetDirection(glm::normalize(_nearClip[i * _width + j] - _cam->GetPosition()));
		}
	}
}


Camera* RayCaster::GetCamera()
{
	return _cam;
}

Ray& RayCaster::CastRayThroughPixel(int i, int j)
{
	return _rays[j * _width + i];
}