#pragma once
#include "Shape.h"

#define TOLLRANCE 0.001

class Sphere :
	public Shape
{
public:
	Sphere(point3 center, float radius);
	~Sphere();
	inline const point3 GetCenter() const { return _center; }
	inline const float GetRadius() const { return _radius; }
	inline const float GetRadiusSquared() const { return _radiusSq; }

	normal3 GetNormal(point3& pos) override;
	bool IsIntersect(Ray& ray, float& dist) override;
	bool IsPointInside(point3& point) override;
	void Update() override;

private:
	point3 _center;
	float _radius;
	float _radiusSq;
};

