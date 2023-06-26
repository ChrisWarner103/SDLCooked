#ifndef PhysicsHelper_H
#define PhysicsHelper_H

#include "CircleCollider.h"
#include "BoxCollider.h"
#include "MathHelper.h"

inline bool CircleCircleCollison(CircleCollider* c1, CircleCollider* c2)
{
	return (c1->position() - c2->position()).Magnitude() < (c1->GetRadius() + c2->GetRadius());
}

inline bool ColliderColliderCheck(Collider* c1, Collider* c2)
{
	if (c1->GetType() == Collider::ColliderType::Circle && c2->GetType() == Collider::ColliderType::Circle)
		return CircleCircleCollison(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
}

#endif // !PhysicsHelper_H

