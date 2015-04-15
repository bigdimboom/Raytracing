#include "Scene.h"


Scene::Scene()
{
}


Scene::~Scene()
{
	for (uint i = 0; i < _shapes.size(); ++i)
	{
		delete _shapes.at(i);
	}
}

void Scene::AddShape(Shape* shape)
{
	assert(shape != nullptr);
	_shapes.push_back(shape);
}

uint Scene::GetNumOfShapes()
{
	return _shapes.size();
}


Shape* Scene::GetShape(uint i)
{
	assert(i >= 0 && i < _shapes.size());
	return _shapes.at(i);
}