#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>

Game::Game() {
	isRunning = false;
	registry = std::make_unique<Registry>();
	Logger::Log("Game consturctor called!");
}

Game::~Game() {
	Logger::Log("Game desturctor called!");
}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Logger::Err("Error initializing SDL.");
		return;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	windowWidth = displayMode.w;
	windowHeight = displayMode.h;

	window = SDL_CreateWindow(
		NULL, 						// Title
		SDL_WINDOWPOS_CENTERED, 	// x coord
		SDL_WINDOWPOS_CENTERED,		// y coord
		windowWidth,				// width
		windowHeight,				// height
		SDL_WINDOW_BORDERLESS		// window decoration
	);

	if (!window) {
		Logger::Err("Error creating SDL window.");
		return;
	}

	renderer = SDL_CreateRenderer(
		window, 	// to wich window it belongs to
		-1,			// in which monitor it will be displayed (-1 == defautl)
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC 	// other flags
	);

	if (!renderer) {
		Logger::Err("Error creating SDL renderer.");
		return;
	}

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	isRunning = true;
}

void Game::Run() {
	Setup();

	while (isRunning) {
	 	ProcessInput();
	 	Update();
	 	Render();
	}
}

void Game::Setup() {
	// Create some entities
	Entity tank = registry->CreateEntity(); 
	Entity truck = registry->CreateEntity();
}

void Game::ProcessInput() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
					isRunning = false;
				} 
				break;
		}
	}
}

void Game::Update() {
	// If we are too fast, waste some time until we reach the MILISECS_PER_FRAME
	int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
	if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME){
		SDL_Delay(timeToWait);
	}

	double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0f;

	// Store the current frane time
	millisecsPreviousFrame = SDL_GetTicks();

	// TODO:
	// MovementSystem.Update();
	// CollisionSystem.Update();
	// DamageSystem.Update();
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	// TODO: Render game objects...

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}