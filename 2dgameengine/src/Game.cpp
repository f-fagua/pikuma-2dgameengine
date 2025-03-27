#include "Game.h"
#include <iostream>
#include <SDL.h>

Game::Game() {
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

	SDL_Window* window = SDL_CreateWindow(
		NULL, 						// Title
		SDL_WINDOWPOS_CENTERED, 	// x coord
		SDL_WINDOWPOS_CENTERED,		// y coord
		800,						// width
		600,						// height
		SDL_WINDOW_BORDERLESS		// window decoration
	);

	if (!window) {
		std::cerr << "Error creating SDL window." << std::endl;
		return;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(
		window, 	// to wich window it belongs to
		-1,			// in which monitor it will be displayed (-1 == defautl)
		0 			// other flags
	);

	if (!renderer) {
		std::cerr << "Error creating SDL renderer." << std::endl;
		return;
	}
}

void Game::Run() {
	// while (true) {
	// 	ProcessInput();
	// 	Update();
	// 	Render();
	// }
}

void Game::ProcessInput() {

}

void Game::Update() {

}

void Game::Render() {

}

void Game::Destroy() {

}