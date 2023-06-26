#ifndef  FoodPlate_H
#define FoodPlate_H

#include "PhysicsEntity.h"
#include "Timer.h"

using namespace ChrisFramework;

class FoodPlate : public PhysicsEntity {

private:

	Timer* mTimer;

	Texture* mPlate;
	Texture* mPlate1;
	Texture* mPlate2;
	Texture* mPlate3;

public:

	FoodPlate(bool empty);
	~FoodPlate();

	void Hit(PhysicsEntity* other) override;

	void Update();

	void Render();
};
#endif // ! FoodPlate_H

