// --------------------------------
// Working with C++ Templates
// --------------------------------

class System {
	private:
		Signature componentSignature;
		std::vector<Entity> entities;

	public: 
		System() = default;
		~System() = default;

		void AddEntityToSystem(Entity entity);
		void RemoveEntityFromSystem();
		std::vector<Entity> GetSystemEntities() const;
		const Signature& GetComponentSignature() const;

		// Define the component type T that entities must have to be
		// considered by the system
		template <typename T> void RequireComponent();
};

// Implementations of the function template
template <typename T> void System::RequireComponent()
{
	const auto componentId = Component<T>::GetId();
	componentSignature.set(componentId);
}


// --------------------------------
// System Component Signatures
// --------------------------------

const unsignet int MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;

class Entity {
	int id;
}

class Component {
	int id;
}

class System {
	private:
		// Which components and entity must have for the system to consider the entity
		Signature componentSignature;

		// List of all entities that the system is interested in
		std::vector<Entity> entities;
}



// --------------------------------
// Entity-Component-System Design
// --------------------------------

class Entity {
	int id;
};

struct TransformComponent {
	glm::vec2 position;
	glm::vec2 scale;
	double rotation;
};

struct VelocityComponent {
	glm::vec2 velocity;
};

class MovementSystem {
	public:
		MovementSystem() {
			RequireComponent<TransformComponent>();
			RequireComponent<VelocityComponent>();
		}

		void Update(double deltaTime) {
			for (auto entity: GetEntities()) {
				VelocityComponent& velocity = entity.GetComponent<VelocityComponent>();
				TransformComponent& transform = entity.GetComponent<TransformComponent>();

				// Update entity's position on its velocity
				transform.position.x += rigidbody.velocity.x * deltaTime;
				transform.position.y += rigidbody.velocity.y * deltaTime; 
			}
		}
};


// --------------------------------
// Component-Based Design
// --------------------------------

class Entity {
	vector<Component*> components;
	void AddComponent<T>(component);
	void Update(deltaTime);
	void Render();
	...
};

class Component {
	Entity owner;

	virtual Update();
	virtual Render();
};

class TransformComponent: public Component {
	glm::vec2 position;
	glm::vec2 scale;
	double rotation;

	Update() override {
		/* TODO: ...*/
	}

	Render() override {
		/* TODO: ...*/
	}
};

class ColliderComponent: public Component {
	SDL_Rect collider;

	Update() override {
		/* TODO: ...*/
	}

	Render() override {
		/* TODO: ...*/
	}
};

class Registry { // World - Entity Manager
	vector<Entity*> entities;

	void AddEntity(entity);
	void RemoveEntity(entity);
	void Update(deltaTime);
	void Render();
	...
};

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