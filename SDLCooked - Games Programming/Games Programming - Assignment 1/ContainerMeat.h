#ifndef ContainerMeat_H
#define ContainerMeat_H


#include <vector>

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "Food.h"

using namespace ChrisFramework;

class ContainerMeat : public GameEntity {

private:

	static const int MAX_AMOUNT_OF_FOOD = 1;

	int foodInContainer;

	InputManager* mInput;

	Texture* meatContainerTexture;
	Texture* collsionArea;

protected:

	vector<Meat*> meatContainer;

public:

	ContainerMeat();
	~ContainerMeat();

	void AddFood();
	void RemoveFood();

	void Update();

	void Render();
};

#endif