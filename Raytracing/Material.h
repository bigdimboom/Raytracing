#pragma once
#include "Global.h"


class Material
{
public:
	Material();
	~Material();
	void SetBaseColor(color4& color) { _baseColor = color; }
	inline const color4 GetBaseColor() const { return _baseColor; }
	void SetDiffuse(float diffuse) { _diffuse = diffuse; }
	void SetReflection(float reflect) { _reflect = reflect; }
	inline const float GetSpecular() const { return 1.0f - _diffuse; }
	inline const float GetDiffuse() const { return _diffuse; }
	inline const float GetReflection() const{ return _reflect; }
private:
	color4 _baseColor;
	float _reflect;
	float _diffuse;
};

