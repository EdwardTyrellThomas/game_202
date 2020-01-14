/*
Name:edward thomas
course:
prof
title
date: 1/14/2020
*/


//
#include "SDL.h"
#include <cstdlib>

//
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//
SDL_Renderer *renderer;

//
bool running = true;

//
SDL_Event event;

// mouse coordinates;
int mouse_x, mouse_y;
int speed_x, speed_y;
int direction[2] = { -1, 1 };


//
SDL_Rect PlayerPaddle;
SDL_Rect AIPaddle;
SDL_Rect ball;
SDL_Rect midline;

/*
purpose
*/
void LoadGame()
{
	//
	SDL_Window *window;

	//
	window = SDL_CreateWindow("Basic SDL Sprites",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
		if (!window) {
			return;
	}

	//
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		return;
	}

	//
	PlayerPaddle.x = 20;
	PlayerPaddle.y = 250;
	PlayerPaddle.h = 100;
	PlayerPaddle.w = 20;

	//
	AIPaddle.x = 760;
	AIPaddle.y = 250;
	AIPaddle.h = 100;
	AIPaddle.w = 20;

	//
	ball.x = 370;
	ball.y = 290;
	ball.h = 20;
	ball.w = 20;

	//
	midline.x = 400;
	midline.y = 25;
	midline.h = 550;
	midline.w = 5;

	speed_x = -1;
	speed_y = -1;
}

/*
get user input
*/
void Input() {

	//queuing events
	while (SDL_PollEvent(&event)) {

		// track mouse movement
		if (event.type == SDL_MOUSEMOTION)
			SDL_GetMouseState(&mouse_x, &mouse_y);

		//clicking 'x' or pressong F4
		if (event.type == SDL_QUIT)
			running = false;

		//pressing a key
		if (event.type == SDL_KEYDOWN)
			switch (event.key.keysym.sym)
			{

				//pressing ESC exits from the game
			case SDLK_ESCAPE:
				running = false;
				break;
		
			}
	}
}

/*
purpose
*/
void Update()
{
	PlayerPaddle.y = mouse_y;

	ball.x += speed_x;
	ball.y += speed_y;

	//
	//
	if (ball.x < 0 || ball.x > WINDOW_WIDTH)
	{
		ball.x = WINDOW_WIDTH / 2;
		ball.y = WINDOW_HEIGHT / 2;
		//this expression produces random numbers -1, -2, 1 and 2
		speed_x = (rand() % 2 + 1) * direction[rand() % 2];
		speed_y = (rand() % 2 + 1) * direction[rand() % 2];
	}
	if (ball.y < 0 || ball.y > (WINDOW_HEIGHT-ball.h))
	{
		speed_y = -speed_y;
	}

	SDL_Delay(10);
}

/*

*/
void Drawscreen()
{
	//
	SDL_RenderClear(renderer);

	//
	SDL_Rect background = { 0, 0, 800, 600 };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &background);

	//
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &PlayerPaddle);
	SDL_RenderFillRect(renderer, &AIPaddle);
	SDL_RenderFillRect(renderer, &midline);

	//
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &ball);

	//
	SDL_RenderPresent(renderer);
}

/*
purpose
*/
void Quit()
{
	//
	SDL_Quit();
}

/*
purpose
*/
int main(int argc, char *argv[])
{
	//
	LoadGame();

	//
	while (running == true)
	{
		Input();		//
		Update();		//
		Drawscreen();	//
	}

	//
	Quit();

	return 0;
}