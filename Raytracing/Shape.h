#pragma once
#include "Global.h"
#include "Ray.h"
#include "Material.h"


#define SHAPE_UNDEFINED "undefined"
#define SHAPE_PLANE "PLANE"
#define SHAPE_SPHERE "SPHERE"

class Shape
{
public:
	Shape();
	virtual ~Shape() = 0;

	void ApplyModelMatrix(matrix4& mat) { modelMat = modelMat * mat; }
	void SetModelMatrix(matrix4& mat) { modelMat = mat; }
	inline const matrix4 GetModelMatrix() const { return modelMat; }

	inline const bool IsLight() const { return isLight; }
	inline void SetLight(bool enable) { isLight = enable; }

	void SetMaterial(Material& mater) { material = mater; }
	Material* GetMaterial() { return &material; }

	virtual bool IsPointInside(point3& point) = 0;
	virtual bool IsIntersect(Ray& ray, float& dist) = 0;
	virtual normal3 GetNormal(point3& pos) = 0;
	virtual color4 GetColor(point3& pos) { return material.GetBaseColor(); }

	virtual void Update() = 0;

	inline const std::string GetType() const { assert(type != SHAPE_UNDEFINED); return type; }

protected:
	point3 ApplyMatrixToPoint(const point3& point);
	point3 ApplyMatrixToDirection(const point3& dir);

protected:
	matrix4 modelMat;
	bool isLight;
	Material material;
	std::string type;
};

