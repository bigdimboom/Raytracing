#include "Plane.h"


Plane::Plane(normal3& norm, float D)
	:_plane(norm, D)
{
	Shape::type = SHAPE_PLANE;
}

Plane::Plane(point3& p0, point3& p1, point3& p2)
{
	_InitPlaneFrom3Points(p0, p1, p2);
}

void Plane::_InitPlaneFrom3Points(point3& p0, point3& p1, point3& p2)
{
	point3 u = p1 - p0;
	point3 v = p2 - p0;
	point3 n = glm::normalize(glm::cross(u, v));
	float D = -(n.x * p0.x + n.y * p0.y + n.z * p0.z);
	_plane = glm::normalize(PlaneType(n, D));
}

Plane::~Plane()
{
}

point3 Plane::GetNormal(point3& pos)
{
	return normal3(_plane.x, _plane.y, _plane.z);
}

bool Plane::IsIntersect(Ray& ray, float& dist)
{
	float denom = glm::dot(point3(_plane.x, _plane.y, _plane.z), ray.GetDirection());
	if (denom != 0.0f)
	{
		dist = -(glm::dot(ray.GetOrigin(), point3(_plane.x, _plane.y, _plane.z)) + _plane.w) / denom;
		return dist >= 0.0f;
	}
	return false;
}

bool Plane::IsPointInside(point3& point)
{
	std::cout << "Problem?" << std::endl;
	return false;
}

void Plane::Update()
{

}