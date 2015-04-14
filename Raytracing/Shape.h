#pragma once
#include "Global.h"
#include "Ray.h"
#include "Material.h"

class Shape
{
public:
	Shape();
	virtual ~Shape();

	void ApplyModelMatrix(matrix4& mat) { modelMat = modelMat * mat; }
	void SetModelMatrix(matrix4& mat) { modelMat = mat; }
	inline const matrix4 GetModelMatrix() const { return modelMat; }

	inline const bool IsLight() const { return isLight; }

	void SetMaterial(Material& mater) { material = mater; }
	Material* GetMaterial() { return &material; }

	virtual bool IsPointInside(point3& point) = 0;
	virtual bool IsIntersect(Ray& ray, float& dist) = 0;
	virtual normal3 GetNormal(point3& pos) = 0;
	virtual void Update() = 0;

protected:
	point3 ApplyMatrixToPoint(const point3& point);
	point3 ApplyMatrixToDirection(const point3& dir);

protected:
	matrix4 modelMat;
	bool isLight;
	Material material;
};

