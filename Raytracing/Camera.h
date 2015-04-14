#pragma once
#include "Global.h"


class Camera
{
public:
	Camera(point3 camPos, point3 front, float near, float far);
	~Camera();
	inline point3 GetFront() const{ return front; }
	inline point3 GetRight() const { return right; }
	inline point3 GetUp() const { return up; }
	inline point3 GetPosition() const { return position; }

	inline void SetFront(point3 front) { this->front = front; }
	inline void SetPosition(point3 camPos) { this->position = camPos; }

	inline float GetNear() const{ return nearDist; }
	inline float GetFar() const { return farDist; }
	inline void SetNear(float near){ nearDist = near; }
	inline void SetFar(float far){ farDist = far; }


	void Update();

protected:
	point3 position;
	point3 up;
	point3 right;
	point3 front;
	float nearDist;
	float farDist;
};

