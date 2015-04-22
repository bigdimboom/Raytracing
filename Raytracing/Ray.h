#pragma once
#include "Global.h"

class Ray
{
public:
	__host__ __device__ Ray();
	__host__ __device__ Ray(point3 origin, point3 direction);
	__host__ __device__ ~Ray();
	__host__ __device__ void SetOrigin(point3 origin) { _origin = origin; }
	__host__ __device__ void SetDirection(point3 dir) { _dir = dir; }
	__host__ __device__ const point3 GetOrigin() const { return  _origin; }
	__host__ __device__ const point3 GetDirection() const { return _dir; }
	__host__ __device__ point3 GetDestination(float dist) { return _origin + dist * _dir; }
private:
	point3 _origin;
	point3 _dir;
};

