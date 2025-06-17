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
	int index = -1;

	for (int i = 0; index == -1 && i < entities.size(); i++) {
		if (entity.GetId() == entities[i].GetId())
			index = i;
	}

	if (index != -1)
		entities.erase(entities.begin() + index);
}
		
std::vector<Entity> System::GetSystemEntities() const {
	return entities;
}
		
const Signature& System::GetComponentSignature() const {
	return componentSignature;
}