#ifndef FoodContainerCheese_H
#define FoodContainerCheese_H

#include "Food.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include <vector>


using namespace ChrisFramework;
using namespace std;

class FoodContainerCheese : public GameEntity {
private:

	static const int MAX_AMOUNT_OF_FOOD = 1;

	int foodInContainer;

	InputManager* mInput;

	Texture* cheeseContainerTexture;
	Texture* collsionArea;

public:

	vector<Cheese*> cheeseContainer;

public:

	FoodContainerCheese();
	~FoodContainerCheese();

	void AddFood();
	void RemoveFood();

	void Update();

	void Render();
};

#endif