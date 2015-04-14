#include "Sphere.h"


Sphere::Sphere(point3 center, float radius)
	:_center(center), _radius(radius), 
	_radiusSq(_radius * _radius)
{
}


Sphere::~Sphere()
{
}

normal3 Sphere::GetNormal(point3& pos)
{
	return ( pos - _center ) * (1.0f / _radius);
}

bool Sphere::IsIntersect(Ray& ray, float& dist)
{
	return glm::intersectRaySphere(ray.GetOrigin(), ray.GetDirection(), _center, _radiusSq, dist);
}

bool Sphere::IsPointInside(point3& point)
{
	if (point.x * point.x + point.y * point.y + point.z * point.z <= _radiusSq + TOLLRANCE)
	{
		return true;
	}
	return false;
}

void Sphere::Update()
{
	_center = ApplyMatrixToPoint(_center);
}