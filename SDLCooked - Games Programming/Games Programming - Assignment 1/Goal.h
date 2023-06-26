#ifndef Goal_H
#define Goal_H

#include "AnimatedTexture.h"

#include "InputManager.h"
#include "RecipeDecider.h"

using namespace ChrisFramework;

class Goal : public GameEntity {

private:

	InputManager* mInput;

	Texture* goalCounter;
	Texture* collider;

	GameEntity* itemHeld;

public:

	Goal();
	~Goal();
	void CheckRecipe(GameEntity* itemHeld);

	void Update();
	void Render();

};
#endif // !Goal_H