#include "Render.h"

Render::Render()
	:_rayCaster(nullptr),
	_pixels(nullptr),
	_width(0),
	_height(0)
{
}

Render::~Render()
{
	delete _rayCaster;
	delete[] _pixels;
}

void Render::Init(point3 camPos, point3 front, float near, float far, int width, int height)
{
	_width = width;
	_height = height;
	_rayCaster = new RayCaster(camPos, front, near, far, width, height);
	_pixels = new color4[width * height];
}

void Render::InitScene()
{
	int i = 0;

	//Ground
	_scene.AddShape(new Plane(point3(0.0f, 1.0f, 0.0f), 3.0f));
	_scene.GetShape(i)->GetMaterial()->SetReflection(0.0f);
	_scene.GetShape(i)->GetMaterial()->SetDiffuse(1.0f);
	_scene.GetShape(i)->GetMaterial()->SetBaseColor(color4(0.4f, 0.3f, 0.3f, 1.0f));
	++i;
	//A Sphere
	_scene.AddShape(new Sphere(point3(2.0f, -0.8f, -3.8f), 2.5f));
	_scene.GetShape(i)->GetMaterial()->SetReflection(0.6f);
	_scene.GetShape(i)->GetMaterial()->SetDiffuse(0.8f);
	_scene.GetShape(i)->GetMaterial()->SetBaseColor(color4(0.7f, 0.7f, 0.7f, 1.0f));
	++i;
	//Sphere 2
	_scene.AddShape(new Sphere(point3(-3.5f, -0.5f, -6.0f), 1.5f));
	_scene.GetShape(i)->GetMaterial()->SetReflection(0.6f);
	_scene.GetShape(i)->GetMaterial()->SetDiffuse(0.8f);
	_scene.GetShape(i)->GetMaterial()->SetBaseColor(color4(0.7f, 0.7f, 0.7f, 1.0f));
	++i;

	//light 1
	_scene.AddShape(new Sphere(point3(0.0f, 5.0f, -4.0f), 0.1f));
	_scene.GetShape(i)->SetLight(true);
	_scene.GetShape(i)->GetMaterial()->SetBaseColor(color4(0.6f, 0.3f, 0.2f, 1.0f));
	++i;
	//Light 2
	_scene.AddShape(new Sphere(point3(-3.0f, 5.0f, -4.0f), 0.1f));
	_scene.GetShape(i)->SetLight(true);
	_scene.GetShape(i)->GetMaterial()->SetBaseColor(color4(0.45f, 0.8f, 0.9f, 1.0f));
	++i;

}

void Render::Draw()
{
	glDrawPixels(_width, _height, GL_RGBA, GL_FLOAT, _pixels);
}

RayCaster* Render::GetRayCaster()
{
	assert(_rayCaster);
	return _rayCaster;
}

Scene& Render::GetScene()
{
	return _scene;
}

color4* Render::GetPixels()
{
	assert(_pixels);
	return _pixels;
}

void Render::Generate()
{
	assert(_rayCaster && _pixels);
	_rayCaster->Init();

	int count = 0;

	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			_pixels[y * _width + x] = RayTracer(_rayCaster->CastRayThroughPixel(x, y));
		}
	}
}

color4 Render::RayTracer(Ray* ray)
{
	Shape* retShape = nullptr;
	color4 retColor = color4(0.0f, 0.0f, 0.0f, 1.0);

	float dist = INFINITY_FAR;

	//shooting primary ray to the scene
	for (uint i = 0; i < _scene.GetNumOfShapes(); ++i)
	{
		Shape* tmpShape = _scene.GetShape(i);
		float tmp_dist = 0.0f;

		if (tmpShape->IsIntersect(*ray, tmp_dist))
		{
			if (tmp_dist < dist)
			{
				dist = tmp_dist;
				retShape = tmpShape;
			}
		}
	}

	if (retShape == nullptr)
	{
		return retColor;
	}

	if (retShape->IsLight())
	{
		return retShape->GetMaterial()->GetBaseColor();
		//return color4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		//Shooting the secondary ray from the first touching point
		point3 pt = ray->GetDestination(dist);

		for (uint i = 0; i < _scene.GetNumOfShapes(); ++i)
		{
			//Find the light
			Shape* tmp = _scene.GetShape(i);
			if (tmp->IsLight() && tmp->GetType() == SHAPE_SPHERE)
			{
				Sphere* s = (Sphere*)tmp;
				point3 dir_2nd = glm::normalize(s->GetCenter() - pt);
				normal3 norm = retShape->GetNormal(pt);
				float diff_shape = retShape->GetMaterial()->GetDiffuse();
				if (diff_shape > 0.0f)
				{
					float diff_light = glm::dot(norm, dir_2nd);
					if (diff_light > 0.0f)
					{
						float diff = diff_light * diff_shape;
						retColor += diff * retShape->GetMaterial()->GetBaseColor() *
							s->GetMaterial()->GetBaseColor();
					}
				}
			}
		}
	}
	return retColor;
}