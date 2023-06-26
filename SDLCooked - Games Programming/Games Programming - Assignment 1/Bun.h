#ifndef Bun_H
#define Bun_H

#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace ChrisFramework;

class Bun : public GameEntity {

private:

	enum class FoodStates { Normal, Plated, PlatedLettuce, PlatedCheese, PlatedMeat, PlatedCheeseLettuce, PlatedMeatCheese, PlatedMeatLetuce, PlatedFull };

	InputManager* mInput;
	Timer* mTimer;

	Texture* bun;
	Texture* platedBun;
	Texture* platedMeat;
	Texture* platedCheese;
	Texture* platedLettuce;
	Texture* platedMeatCheese;
	Texture* platedCheeseLettuce;
	Texture* platedMeatLettuce;
	Texture* platedFull;

	Texture* collider;

	FoodStates currentFoodState;

public:

	Bun();
	~Bun();

	void ChangeFoodState(FoodStates state);

	void Update();

	void Render();

};

#endif