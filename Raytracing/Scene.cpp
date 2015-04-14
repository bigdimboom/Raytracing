#include "Scene.h"


Scene::Scene()
{
}


Scene::~Scene()
{
	for (uint i = 0; i < _shapes.size(); ++i)
	{
		delete _shapes[i];
	}
}

void Scene::AddShape(Shape* shape)
{
	assert(shape != nullptr);
	_shapes.push_back(shape);
}

int Scene::GetNumOfShapes() const
{
	return _shapes.size();
}

Shape* Scene::GetShape(int i)
{
	assert(i >= 0 && i < _shapes.size());
	return _shapes[i];
}