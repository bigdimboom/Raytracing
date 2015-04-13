#pragma once
#include "Global.h"
#include "Ray.h"
#include "Material.h"

class Shape
{
public:
	Shape();
	virtual ~Shape();
	void ApplyModelMatrix(matrix4& mat); 
	inline const matrix4 GetModelMatrix() const { return _modelMat; }
	inline const bool IsLight() const { return _isLight; }
	Material* GetMaterial() { return &_material; }
	void SetMaterial(Material& material) { _material = _material; }
	virtual bool IsIntersect(Ray& ray, float& dist) = 0;
	virtual point3 GetNormal(point3 pos) = 0;
private:
	matrix4 _modelMat;
	bool _isLight;
	Material _material;
};

