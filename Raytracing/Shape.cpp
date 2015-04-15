#include "Shape.h"


Shape::Shape()
	:isLight(false), modelMat(1.0f),
	type(SHAPE_UNDEFINED)
{
}


Shape::~Shape()
{
}

point3 Shape::ApplyMatrixToPoint(const point3& point)
{
	return point3(modelMat * point4(point, 1.0f));
}

point3 Shape::ApplyMatrixToDirection(const point3& dir)
{
	return point3(modelMat * point4(dir, 0.0f));
}