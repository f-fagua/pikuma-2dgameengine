#include "ECS.h"

//////////////////////////////////////////////////////////////////////
// Entity
//////////////////////////////////////////////////////////////////////
int Entity::GetId() const {
	return id;
}

//////////////////////////////////////////////////////////////////////
// System
//////////////////////////////////////////////////////////////////////
void System::AddEntityToSystem(Entity entity) {
	entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
	
	entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other) {
		return entity == other;
	}), entities.end());
}
		
std::vector<Entity> System::GetSystemEntities() const {
	return entities;
}
		
const Signature& System::GetComponentSignature() const {
	return componentSignature;
}