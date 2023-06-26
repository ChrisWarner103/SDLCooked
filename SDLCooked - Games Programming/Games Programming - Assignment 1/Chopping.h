#ifndef Chopping_H
#define Chopping_H

#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace ChrisFramework;
using namespace std;

class Chopping : public GameEntity {

private:

	InputManager* mInput;
	Timer* mTimer;

	Texture* choppingCounter;
	
	Texture* choppingBar;
	Texture* choppingBarBack;

	Texture* collider;

	GameEntity* choppingItem;

	int choppingAmount = 15;

	Vector2 choppingBarLocation;

public:

	bool canChop;
	bool isChopping;

public:

	Chopping();
	~Chopping();

	void Update();

	void Render();

};
#endif // !Cooker_H
