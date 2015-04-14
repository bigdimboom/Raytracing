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
	int GetNumOfShapes() const;
	Shape* GetShape(int idx);

private:
	std::vector<Shape*> _shapes;
};

