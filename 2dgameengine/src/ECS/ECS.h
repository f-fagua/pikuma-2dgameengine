#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>

const unsigned int MAX_COMPONENTS = 32;

////////////////////////////////////////////////////////////////////////////////
// Signature
////////////////////////////////////////////////////////////////////////////////
// We use a bitset (1s and 0s) to keep track of which components an entity has,
// and also helps track of which entities a system is interested in.
////////////////////////////////////////////////////////////////////////////////
typedef std::bitset<MAX_COMPONENTS> Signature;

////////////////////////////////////////////////////////////////////////////////
// Component
////////////////////////////////////////////////////////////////////////////////
struct IComponent
{
	protected:
		static int nextId;	
};

// Used to assign a unique id to a compolnent type
template <typename T>
class Component : public IComponent {
	// Returns the unique id of Component<T>
	static int GetId() {
		static auto id = nextId++;
		return id;
	}
};

////////////////////////////////////////////////////////////////////////////////
// Entity
////////////////////////////////////////////////////////////////////////////////
class Entity {
	private:
		int id;

	public:
		Entity(int id): id(id) {};
		Entity(const Entity& entity) = default;
		int GetId() const;

		Entity& operator =(const Entity& other) = default;
		bool operator ==(const Entity& other) const { return id == other.id; };
		bool operator !=(const Entity& other) const { return id != other.id; };
		bool operator >(const Entity& other) const { return id > other.id; };
		bool operator <(const Entity& other) const { return id < other.id; };
};


////////////////////////////////////////////////////////////////////////////////
// System
////////////////////////////////////////////////////////////////////////////////
// The system processes entities that contain a specific signature
////////////////////////////////////////////////////////////////////////////////
class System {
	private:
		Signature componentSignature;
		std::vector<Entity> entities;

	public: 
		System() = default;
		~System() = default;

		void AddEntityToSystem(Entity entity);
		void RemoveEntityFromSystem(Entity entity);
		std::vector<Entity> GetSystemEntities() const;
		const Signature& GetComponentSignature() const;

		// Define the component type T that entities must have to be
		// considered by the system
		template <typename TComponent> void RequireComponent();
};

////////////////////////////////////////////////////////////////////////////////
// Pool
////////////////////////////////////////////////////////////////////////////////
// A pool is just a vector (contiguous data) of objects of type T
////////////////////////////////////////////////////////////////////////////////
class IPool {
	public:
		virtual ~IPool() {}
};


template <typename T>
class Pool: IPool {
	
	private:
		std::vector<T> data;

	public:
		Pool(int size = 100) { 
			data.resize(size); 
		}
		
		virtual ~Pool() = default;

		bool isEmpty() const { 
			return data.empty(); 
		}

		int GetSize() const { 
			return data.size(); 
		}

		void Resize(int n) { 
			data.resize(n); 
		}

		void Clear() { 
			data.clear(); 
		}

		void Add(T object) { 
			data.push_back(object); 
		}

		void Set(int index, T object) { 
			data[index] = object; 
		}

		T& Get(int index) { 
			return static_cast<T&>(data[index]); 
		}

		T& operator [] (unsigned int index) { 
			return data[index]; 
		}
};

////////////////////////////////////////////////////////////////////////////////
// Registry (coordinator, manager)
////////////////////////////////////////////////////////////////////////////////
// The Registry manages the creation and destruction of entities, add systems, 
// and components.
////////////////////////////////////////////////////////////////////////////////
class Registry {
	
	private:
		// Keep track of how many entities were added to the scene
		int numEntities = 0;

		// Vecotr of component pools, each pool contains all the data for a certain component type
		// [Vector index = component type id]
		// [Pool index = entity id]
		std::vector<IPool*> componentPools;
		
		// Vector of component signatures.
		// The signatures lets us know which components are turned "on" for an entity
		// [vector index = entity id]
		std::vector<Signature> entityComponentSignatures;

		// Map of active systems [index = system typeid]
		std::unordered_map<std::type_index, System*> systems;

		// Set of entities that are flagged to be added or removed in the next registry Update()
		std::set<Entity> entitiesToBeAdded;
		std::set<Entity> entitiesToBeKilled;

	public:
		Registry() = default;

		// The registry Update finally processes the entities that are waiting to be added/killed
		void Update();
		
		// Entity management
		Entity CreateEntity();
		
		// Component management
		template <typename TComponent, ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);

		//void AddEntityToSystem(Entity entity);

		// void KillEntity(Entity entity);
		//		
		// void RemoveComponent(Entity entity);
		// bool HasComponent(Entity entity)
		// Component GetCompoent(Entity entity)
		//
		// void AddSystem(System system)
		// void RemoveSystem(System system)
		// bool HasSystem(System)
		// Sysyem* GetSystem()

};

// Implementations of the function template
template <typename TComponent> 
void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}

template <typename TComponent, ...TArgs> 
void Registry::AddComponent(Entity entity, TArgs&& ...args) {
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.GetId();

	if (componentId >= componentPools.size()) {
		componentPools.resize(componentId + 1, nullptr);
	}

	if (!componentPools[componentId]) {
		Pool<TComponent>* newComponentPool = new Pool<TComponent>();
		componentPools[componentId] = newComponent;
	}

	Pool<TComponent>* componentPool = componentPools[componentId];

	if (entityId >= componentPool->GetSize()){
		componentPool->Resize(numEntities);
	}

	TComponent newComponent(std::forward<TArgs>(args)...);

	componentPool->Set(entityId, newComponent);
}


#endif