#pragma once
#include "Global.h"
#include "Shape.h"
#include <vector>

class Scene
{
public:
	Scene();
	~Scene();
	void AddShape(Shape* shape);
	uint GetNumOfShapes();
	Shape* GetShape(uint idx);

private:
	std::vector<Shape*> _shapes;
};

