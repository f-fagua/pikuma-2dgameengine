#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

class MovementSystem: public System {
	public:
		MovementSystem() {
			// RequireComponent<TransformComponent>();
			// RequireComponent<VelocityComponent>();
		}

		void Update() {
			// TODO:
			// Loop all the entities that the system is interested in
			// for (auto entity: GetEntities()) {
				// TODO: Update entity position based on its velocity
			// }
		}
}


#endif