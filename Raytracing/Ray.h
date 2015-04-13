#pragma once
#include "Global.h"

class Ray
{
public:
	Ray(point3 origin, point3 direction);
	~Ray();
	inline void SetOrigin(point3 origin) { _origin = origin; }
	inline void SetDirection(point3 dir) { _dir = dir; }
	inline const point3 GetOrigin() const { return  _origin; }
	inline const point3 GetDirection() const { return _dir; }
private:
	point3 _origin;
	point3 _dir;
};

