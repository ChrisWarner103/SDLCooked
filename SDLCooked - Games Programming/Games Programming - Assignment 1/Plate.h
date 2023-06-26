#ifndef Plate_H
#define Plate_H

#include "AnimatedTexture.h"
#include "InputManager.h"

#include "Food.h"
#include "Bun.h"

using namespace ChrisFramework;

class Plate : public GameEntity {

private:

	enum class PlateStates { empty, first, second, third};

	InputManager* mInput;
	Timer* mTimer;

	Texture* plate;
	Texture* collider;

	PlateStates currentFoodState;

	bool hasBun = false;
	bool hasLettuce = false;
	bool hasCheese = false;
	bool hasMeat = false;

	GameEntity* bun;


public:

	Plate();
	~Plate();

	void ChangeFoodState(PlateStates state);

	void Update();

	void Render();
};

#endif