#include "Game.h"
#include <iostream>
#include <SDL.h>

Game::Game() {
	isRunning = false;
	std::cout << "Game consturctor called!" << std::endl;
}

Game::~Game() {
	std::cout << "Game desturctor called!" << std::endl;
}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL." << std::endl;
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
		std::cerr << "Error creating SDL window." << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(
		window, 	// to wich window it belongs to
		-1,			// in which monitor it will be displayed (-1 == defautl)
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC 	// other flags
	);

	if (!renderer) {
		std::cerr << "Error creating SDL renderer." << std::endl;
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
	// TODO: Initialize game objects...
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
	// TODO: Update game objects...
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// Draw a rectangle
	SDL_Rect player = {
		10, 	// x
		10,		// y
		20,		// width
		20		// height
	};

	SDL_RenderFillRect(renderer, &player);

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}