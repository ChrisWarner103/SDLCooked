#ifndef FoodContainerBuns_H
#define FoodContainerBuns_H

#include "Bun.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include <vector>


using namespace ChrisFramework;
using namespace std;

class FoodContainerBuns : public GameEntity {
private:

	static FoodContainerBuns* sInstance;

	static const int MAX_AMOUNT_OF_FOOD = 1;

	int foodInContainer;

	InputManager* mInput;

	Texture* bunContainerTexture;
	Texture* collsionArea;

public:

	vector<Bun*> bunsContainer;

public:

	static FoodContainerBuns* Instance();
	static void Release();

	FoodContainerBuns();
	~FoodContainerBuns();

	void AddFood();
	void RemoveFood();

	void RemoveBunFromList(int itemNumber);

	void Update();

	void Render();
};

#endif