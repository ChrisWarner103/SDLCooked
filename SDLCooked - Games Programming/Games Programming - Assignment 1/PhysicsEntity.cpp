#include "PhysicsEntity.h"
#include "PhysicsHelper.h"
#include "PhysicsManager.h"

PhysicsEntity::PhysicsEntity()
{
	mBroadPhaseCollider = nullptr;
	ID = 0;
}

PhysicsEntity::~PhysicsEntity()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		delete mColliders[i];
		mColliders[i] = nullptr;
	}

	mColliders.clear();

	if (mBroadPhaseCollider)
	{
		delete mBroadPhaseCollider;
		mBroadPhaseCollider = nullptr;
	}

	if (ID != 0)
	{
		PhysicsManager::Instance()->UnregisterEntity(ID);
	}
}

unsigned long PhysicsEntity::GetID()
{
	return ID;
}

bool PhysicsEntity::CheckCollision(PhysicsEntity* other)
{
	if (IgnoreCollisions() || other->IgnoreCollisions())
		return false;

	return ColliderColliderCheck(mBroadPhaseCollider, other->mBroadPhaseCollider);
}

void PhysicsEntity::Hit(PhysicsEntity* other)
{

}

bool PhysicsEntity::IgnoreCollisions()
{
	return false;
}

void PhysicsEntity::AddCollider(Collider* collider, GameEntity* parent, Vector2 localPosition)
{
	collider->Parent(this);
	collider->Pos(localPosition);
	mColliders.push_back(collider);

	if (mColliders.size() > 1 || mColliders[0]->GetType() != Collider::ColliderType::Circle)
	{
		float furthestDistance = mColliders[0]->GetFurthestPoint().Magnitude();
		float distance = 0.0f;

		for (int i = 1; i < mColliders.size(); i++)
		{
			distance = mColliders[i]->GetFurthestPoint().Magnitude();

			if (distance > furthestDistance)
			{
				furthestDistance = distance;
			}
		}

		delete mBroadPhaseCollider;
		mBroadPhaseCollider = new CircleCollider(furthestDistance, true);
		mBroadPhaseCollider->Parent(this);
		mBroadPhaseCollider->Pos(localPosition);
	}
}

void PhysicsEntity::Render()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		mColliders[i]->Render();
	}

	if (mBroadPhaseCollider)
	{
		mBroadPhaseCollider->Render();
	}
}