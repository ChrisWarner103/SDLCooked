#ifndef PhysicsEntity_H
#define PhysicsEntity_H

#include <vector>

#include "Collider.h"

class PhysicsEntity : public GameEntity {

protected:

	unsigned long ID;

	vector<Collider*> mColliders;

	Collider* mBroadPhaseCollider;

public:

	PhysicsEntity();
	virtual ~PhysicsEntity();

	unsigned long GetID();

	bool CheckCollision(PhysicsEntity* other);

	virtual void Hit(PhysicsEntity* other);

	virtual void Render();

protected:

	virtual bool IgnoreCollisions();

	void AddCollider(Collider* collider, GameEntity* parent, Vector2 localPosition = VEC2_ZERO);

};

#endif // ! PhysicsEntity_H

