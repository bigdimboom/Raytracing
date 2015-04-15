#define NOMINMAX

#include "Global.h"
#include "Window.h"
#include <time.h>
#include <glm/gtc/random.hpp>
#include <vector>
#include "Ray.h"
#include "Render.h"
#include "MyTimer.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Window gWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raytracing");
bool gIsRunning = false;
point4 pixels[WINDOW_WIDTH][WINDOW_HEIGHT];

Render gRender;
MyTimer gTimer;


void Init()
{
	gRender.Init(point3(0.0f, 0.0f, 4.0f), point3(0.0f, 0.0f, -1.0f), 5.0f, 1000.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
	gRender.InitScene();
	
	gTimer.Start();
	gRender.Generate();
	gTimer.Stop();

	std::cout << gTimer.GetElapsedTime() / 1000.0f << "seconds\n";

	gTimer.Reset();
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

void Display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gRender.Draw();

	gWindow.SwapBuffers();
}

void Update()
{

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
		Display();
		Update();
	}

	CleanUp();
	gWindow.DestoryGL();
	SDL_Quit();
	return 0;
}