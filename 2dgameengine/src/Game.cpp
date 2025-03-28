#include "Game.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>

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

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup() {
	playerPosition = glm::vec2(10.0, 20.0);
	playerVelocity = glm::vec2(1.0, 0.0);
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
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), milisecsPreviousFrame + MILLISECS_PER_FRAME));

	// Store the current frane time
	milisecsPreviousFrame = SDL_GetTicks();

	playerPosition.x += playerVelocity.x;
	playerPosition.y += playerVelocity.y;
}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	// Load a PNG texture
	SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	// What is the destination rectangle that we want to place our texture
	SDL_Rect dstRect = {
		static_cast<int>(playerPosition.x), 
		static_cast<int>(playerPosition.y), 
		32, 
		32};
	SDL_RenderCopy(renderer, texture, NULL, &dstRect);
	SDL_DestroyTexture(texture);

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}