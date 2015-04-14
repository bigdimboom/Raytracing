#include "Camera.h"


Camera::Camera(point3 camPos, point3 front, float near, float far)
	:position(camPos), front(glm::normalize(front)),
	nearDist(near), farDist(far)
{
	Update();
}


Camera::~Camera()
{
}

void Camera::Update()
{
	up = point3(0.0f, 1.0f, 0.0f);
	right = glm::cross(front, up);
}