#pragma once
#include "Global.h"


class Material
{
public:
	Material();
	~Material();
	void SetBaseColor(color4& color) { _baseColor = color; }
	inline const color4 GetBaseColor() const { return _baseColor; }
private:
	color4 _baseColor;

};

