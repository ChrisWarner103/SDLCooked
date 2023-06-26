#ifndef Food_H
#define Food_H
#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace ChrisFramework;

class Food : public GameEntity {

protected:
	enum class FoodStates { raw, cooked, chopped, plated };

	InputManager* mInput;
	Timer* mTimer;

	Texture* mainTexture;
	Texture* cookedTexture;
	Texture* choppedTexture;
	Texture* collider;

	FoodStates currentFoodState;

public:

	void ChangeFoodState(FoodStates state);

	virtual void Update();

	virtual void Render();
};

class Meat : public Food {

public:

	Meat();
	~Meat();

	void Update() override;
};

class Cheese : public Food {
public:

	Cheese();
	~Cheese();

	void Update() override;
};

class Lettuce : public Food {
public:

	Lettuce();
	~Lettuce();

	void Update() override;
};
#endif // !Food_H