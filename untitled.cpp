// --------------------------------
// Logger Class
// --------------------------------



// --------------------------------
// Deta time
// --------------------------------

// Difference in ticks from the last frame, converted to seconds
double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0f;

// Make the game object move 20 pixels per second
playerPosition.x += 20 * deltaTime;


// --------------------------------
// Game Class
// --------------------------------

void Game::Run{
	while (true) {
		ProcessInput();
		Update();
		Render();
	}
}


//Updating the /libs Folder

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <sol/sol.hpp>


int main() {
    // Simply tries to use the Lua language with the Sol library
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    // Tries to create a vector2 and normalize it with the GLM library
    glm::vec2 velocity = glm::vec2(5.0, -2.5);
    velocity = glm::normalize(velocity);

    // Tries to initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    std::cout << "Yay! Dependencies work correctly." << std::endl;
    return 0;
}