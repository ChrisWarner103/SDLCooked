#ifndef CircleCollider_H
#define CircleCollider_H

#include "Collider.h"

class CircleCollider : public Collider {

private:

	float mRadius;

public:

	CircleCollider(float radius, bool broadPhase = false);
	~CircleCollider();

	Vector2 GetFurthestPoint() override;

	float GetRadius();
};

#endif // !CircleCollider_H

