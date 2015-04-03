#define NOMINMAX

#include "Global.h"
#include "Window.h"
#include <time.h>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Window gWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raytracing");
bool gIsRunning = false;

void Init()
{

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
		Render();
		Update();
	}

	CleanUp();
	gWindow.DestoryGL();
	SDL_Quit();
	return 0;
}