#ifndef FoodContainerLettuce_H
#define FoodContainerLettuce_H

#include "Food.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include <vector>


using namespace ChrisFramework;
using namespace std;

class FoodContainerLettuce : public GameEntity{
private:

	static const int MAX_AMOUNT_OF_FOOD = 1;

	int foodInContainer;

	InputManager* mInput;

	Texture* lettuceContainerTexture;
	Texture* collsionArea;

public:

	vector<Lettuce*> lettuceContainer;

public:

	FoodContainerLettuce();
	~FoodContainerLettuce();

	void AddFood();
	void RemoveFood();

	void Update();

	void Render();
};

#endif