#include "Render.h"


void CudaCheckError(cudaError_t code)
{
	if (code != cudaSuccess)
	{
		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), __FILE__, __LINE__);
		if (abort) exit(code);
	}
}


Render::Render()
	:_rayCaster(nullptr),
	_pixels(nullptr),
	_width(0),
	_height(0),
	_raysOnDev(nullptr)
{
}

Render::~Render()
{
	delete _rayCaster;
	delete[] _pixels;
}

bool Render::IsCudaDevice()
{
	int count = 0;
	cudaGetDeviceCount(&count);
	if (count)
	{
		return true;
	}
	return false;
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

	//std::cout << glm::to_string(glm::cross(point3(1.0f,0.0f, 0.0f), point3(0.0f, 0.0f, 1.0f))) << std::endl;

	//Ground
	_scene.AddShape(new Plane(point3(0.0f, 1.0f, 0.0f), 4.8f));
	_scene.GetShape(i)->GetMaterial()->SetReflection(0.0f);
	_scene.GetShape(i)->GetMaterial()->SetDiffuse(1.0f);
	_scene.GetShape(i)->GetMaterial()->SetBaseColor(color4(0.3f, 0.25f, 0.25f, 1.0f));
	++i;
	//left
	_scene.AddShape(new Plane(point3(1.0f, 0.0f, 0.0f), 10.8f));
	_scene.GetShape(i)->GetMaterial()->SetReflection(0.1f);
	_scene.GetShape(i)->GetMaterial()->SetDiffuse(1.0f);
	_scene.GetShape(i)->GetMaterial()->SetBaseColor(color4(0.0f, 0.25f, 1.0f, 1.0f));
	++i;
	//back
	_scene.AddShape(new Plane(point3(0.0f, 0.0f, 1.0f), 15.0f));
	_scene.GetShape(i)->GetMaterial()->SetReflection(0.1f);
	_scene.GetShape(i)->GetMaterial()->SetDiffuse(1.0f);
	_scene.GetShape(i)->GetMaterial()->SetBaseColor(color4(0.3f, 0.25f, 0.25f, 1.0f));
	++i;

	//A Sphere
	_scene.AddShape(new Sphere(point3(2.0f, -0.8f, -3.8f), 2.5f));
	_scene.GetShape(i)->GetMaterial()->SetReflection(0.6f);
	_scene.GetShape(i)->GetMaterial()->SetDiffuse(1.0f);
	_scene.GetShape(i)->GetMaterial()->SetBaseColor(color4(0.9f, 0.7f, 0.7f, 1.0f));
	++i;
	//Sphere 2
	_scene.AddShape(new Sphere(point3(-4.0f, -0.5f, -5.0f), 2.0f));
	_scene.GetShape(i)->GetMaterial()->SetReflection(1.0f);
	_scene.GetShape(i)->GetMaterial()->SetDiffuse(1.0f);
	_scene.GetShape(i)->GetMaterial()->SetBaseColor(color4(0.5f, 0.6f, 0.7f, 1.0f));
	++i;
	//light 1
	_scene.AddShape(new Sphere(point3(4.5f, 5.8f, 0.0f), 0.15f));
	_scene.GetShape(i)->SetLight(true);
	_scene.GetShape(i)->GetMaterial()->SetBaseColor(color4(0.9f, 0.9f, 0.2f, 1.0f));
	++i;
	//Light 2
	_scene.AddShape(new Sphere(point3(-2.0f, 5.5f, -10.0f), 0.2f));
	_scene.GetShape(i)->SetLight(true);
	_scene.GetShape(i)->GetMaterial()->SetBaseColor(color4(0.85f, 0.8f, 0.9f, 1.0f));
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

	if (IsCudaDevice())
	{
		//count bytes size of the Shapes in the scene
		for (uint i = 0; i < _scene.GetNumOfShapes(); ++i)
		{
			if (_scene.GetShape(i)->GetType() == Shape::SHAPE_SPHERE)
			{
				Sphere* s;
				CudaCheckError(cudaMalloc((void**)&s, sizeof(Sphere)));
				CudaCheckError(cudaMemcpy(s, _scene.GetShape(i), sizeof(Sphere), cudaMemcpyHostToDevice));
				_shapesOnDev.push_back(s);
				//Dosomething
			}
			else if (_scene.GetShape(i)->GetType() == Shape::SHAPE_PLANE)
			{
				Plane* p;
				CudaCheckError(cudaMalloc((void**)&p, sizeof(Plane)));
				CudaCheckError(cudaMemcpy(p, _scene.GetShape(i), sizeof(Plane), cudaMemcpyHostToDevice));
				//Do something
				_shapesOnDev.push_back(p);
			}
			else
			{
				std::cout << " Error Converting types\n";
			}
		}
		//Copy Rays to device
		CudaCheckError(cudaMalloc((void**)&_raysOnDev, sizeof(Ray) * _rayCaster->RaySize()));
		CudaCheckError(cudaMemcpy(_raysOnDev, _rayCaster->GetRayVector(), _rayCaster->RaySize() * sizeof(Ray), cudaMemcpyHostToDevice));

		//Global function launcher

		return;
	}



	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			_pixels[y * _width + x] = RayTracer(_rayCaster->CastRayThroughPixel(x, y), RECURSION_NUM);
		}
	}

}

color4 Render::RayTracer(Ray& ray, int depth)
{
	Shape* retShape = nullptr;

	color4 retColor = color4(0.0f, 0.0f, 0.0f, 1.0);

	float dist = INFINITY_FAR;

	//shooting primary ray to the scene
	for (uint i = 0; i < _scene.GetNumOfShapes(); ++i)
	{
		Shape* tmpShape = _scene.GetShape(i);
		float tmp_dist = 0.0f;

		if (tmpShape->IsIntersect(ray, tmp_dist))
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
		point3 pt = ray.GetDestination(dist);

		for (uint i = 0; i < _scene.GetNumOfShapes(); ++i)
		{
			//Find the light-diffuse
			Shape* tmp = _scene.GetShape(i);
			float shade = 1.0f;
			if (tmp->IsLight() && tmp->GetType() == Shape::SHAPE_SPHERE)
			{
				Sphere* light = (Sphere*)tmp;
				point3 dir_2nd = glm::normalize(light->GetCenter() - pt);
				normal3 norm = retShape->GetNormal(pt);
				float tmpDist = glm::length(dir_2nd);

				//dir_2nd = (1.0f) / tmpDist * dir_2nd;
				Ray ray2nd = Ray(pt + dir_2nd * THRESHOLD, dir_2nd);
				for (uint count = 0; count < _scene.GetNumOfShapes(); count++)
				{
					Shape* ss = _scene.GetShape(count);
					if ((!ss->IsLight()) && (ss->IsIntersect(ray2nd, tmpDist)))
					{
						shade = 0.001f;
						break;
					}
				}


				dir_2nd = glm::normalize(light->GetCenter() - pt);
				float diff_shape = retShape->GetMaterial()->GetDiffuse();
				if (diff_shape > 0.0f)
				{
					float diff_light = glm::dot(norm, dir_2nd);
					if (diff_light > 0.0f)
					{
						float diff = diff_light * diff_shape * shade;
						retColor += diff * retShape->GetMaterial()->GetBaseColor() *
							light->GetMaterial()->GetBaseColor();
					}
				}


				float specShape = retShape->GetMaterial()->GetSpecular();
				if (specShape > 0.0f)
				{
					// point light source: sample once for specular highlight
					point3 rayray = ray.GetDirection() - 2.0f * glm::dot(ray.GetDirection(), norm) * norm;
					float specLight = glm::dot(ray.GetDirection(), rayray);
					if (specLight > 0.0f)
					{
						float spec = powf(specLight, 20) * retShape->GetMaterial()->GetSpecular() * shade;
						retColor += spec * light->GetMaterial()->GetBaseColor();
					}
				}
			}
		}
		// calculate reflection
		float refl = retShape->GetMaterial()->GetReflection();
		if (refl > 0.0f)
		{
			normal3 N = retShape->GetNormal(pt);
			point3 rayray = ray.GetDirection() - 2.0f * glm::dot(ray.GetDirection(), N) * N;
			if (depth)
			{
				color4 getColor = RayTracer(Ray(pt + rayray * THRESHOLD, rayray), depth - 1);
				retColor += refl * getColor * retShape->GetMaterial()->GetBaseColor();
			}
		}
	}
	return retColor;
}