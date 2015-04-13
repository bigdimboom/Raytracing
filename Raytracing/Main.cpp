#define NOMINMAX

#include "Global.h"
#include "Window.h"
#include <time.h>
#include <glm/gtc/random.hpp>
#include <thrust/host_vector.h>
#include <vector>
#include "Ray.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Window gWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raytracing");
bool gIsRunning = false;
point4 pixels[WINDOW_WIDTH][WINDOW_HEIGHT];

thrust::host_vector<Ray> gPrimaryRays;
//std::vector<Ray> rays;

void GenPrimaryRays()
{
	//Where the camera is 
	point3 o(0.0f, 0.0f, 5.0f);
	//place the screen on (0,0,0) facing negtive z axis
	for (int x = 0; x < WINDOW_WIDTH; ++x)
	{
		for (int y = 0; y < WINDOW_HEIGHT; ++y)
		{
			point3 dir = glm::normalize(point3(x, y, 0.0f) - o );
			gPrimaryRays.push_back(Ray(o, dir));
		}
	}

}


void Init()
{
	GenPrimaryRays();
}

void EventHandler(SDL_Event &e)
{
	if (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			gIsRunning = false;
		else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
			gIsRunning = false;
	}
}

void Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_FLOAT, pixels);

	gWindow.SwapBuffers();
}

void Update()
{
	//for (int i = 0; i < WINDOW_WIDTH; ++i)
	//{
	//	for (int j = 0; j < WINDOW_HEIGHT; ++j)
	//	{
	//		pixels[i][j] = point4(0.3f, 0.5f, 0.6f, 1.0f);
	//	}
	//}
}

void CleanUp()
{

}

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Quit();
		return 1;
	}

	gWindow.Open();
	gWindow.InitGL();
	srand((unsigned int)time(NULL));

	Init();

	SDL_Event e;
	gIsRunning = true;

	while (gIsRunning)
	{
		EventHandler(e);
		Render();
		Update();
	}

	CleanUp();
	gWindow.DestoryGL();
	SDL_Quit();
	return 0;
}