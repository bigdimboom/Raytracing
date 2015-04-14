#pragma once
#include "Shape.h"

typedef glm::vec4 PlaneType;

class Plane :
	public Shape
{
public:
	Plane(normal3& norm, float D);
	Plane(point3& p0, point3& p1, point3& p2);
	~Plane();
	bool IsPointInside(point3& point) override;
	bool IsIntersect(Ray& ray, float& dist) override;
	point3 GetNormal(point3& pos) override;
	void Update() override;
private:
	PlaneType _plane;
	void _InitPlaneFrom3Points(point3& p0, point3& p1, point3& p2);
};

