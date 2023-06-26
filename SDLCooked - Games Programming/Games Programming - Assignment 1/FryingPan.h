#ifndef FryingPan_H
#define FryingPan_H

#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace ChrisFramework;

class FryingPan : public GameEntity {

private:

	enum class CookingState { raw, cooked, chopped, plated };

	InputManager* mInput;
	Timer* mTimer;

	Texture* fryingPan;
	Texture* collider;

	CookingState currentCookingState;

public:

	bool hasMeat = false;
	bool onCooker;


public:

	FryingPan();
	~FryingPan();

	void ChangeFoodState(CookingState state);

	void Update();

	void Render();
};

#endif