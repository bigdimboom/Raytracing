#include "Ray.h"

Ray::Ray()
{
}

Ray::Ray(point3 orign, point3 direction)
	:_origin(orign),
	_dir(glm::normalize(direction))
{
}

Ray::~Ray()
{
}
