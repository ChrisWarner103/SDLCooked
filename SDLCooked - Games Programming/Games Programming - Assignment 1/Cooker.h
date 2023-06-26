#ifndef Cooker_H
#define Cooker_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "FryingPan.h"
#include "Timer.h"

using namespace ChrisFramework;
using namespace std;

class Cooker : public GameEntity {

private:

	InputManager* mInput;

	Timer* mTimer;

	Texture* cookerCounter;

	FryingPan* fryingPan;

	Texture* cookingBar;
	Texture* cookingBarBack;

	Texture* collider;

	GameEntity* cookingItem;
	
	float cookingTime = 5;

public:

	bool canCook;
	bool isCooking;

public:

	Cooker();
	~Cooker();

	void Update();

	void Render();

};
#endif // !Cooker_H
