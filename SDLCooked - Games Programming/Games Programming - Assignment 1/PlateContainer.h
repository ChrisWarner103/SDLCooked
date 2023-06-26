#ifndef PlateContainer_H
#define PlateContainer_H


#include "Plate.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include <vector>

using namespace ChrisFramework;

class PlateContainer : public GameEntity {

private:

	static PlateContainer* sInstance;

	static const int MAX_AMOUNT_OF_FOOD = 1;

	int plateInContainer;

	InputManager* mInput;

	Texture* plateContainerTexture;
	Texture* collsionArea;

public:

	vector<Plate*> plateContainer;

public:

		static PlateContainer* Instance();
	static void Release();

	PlateContainer();
	~PlateContainer();

	void AddFood();
	void RemoveFood();

	void RemovePlateFromList(int itemNumber);

	void Update();

	void Render();
};

#endif