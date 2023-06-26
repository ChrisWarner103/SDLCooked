#ifndef Recipe_H
#define Recipe_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include <vector>

using namespace ChrisFramework;

class Recipe : GameEntity {

private:

	Timer* mTimer;
	InputManager* mInput;

	Texture* recipeCard;
	Texture* recipeTimer;

	vector<Texture*> ingredience;

	Vector2 animationStartPos;
	Vector2 animationEndPos;

	bool cardCreated;

public:

	float timeRemaining = 20;
	int recipeScore = 100;
	string recipeType;
	bool isAnimating = false;
	float animationTimer;
	float animationTotalTime = 2.0f;

public:

	Recipe();
	~Recipe();

	void CreateRecipeCard();

	void CheckRecipeCard();
	float ReturnScore();

	void AddAnimation();
	void RemoveAnimation();

	void UpdatePosition(Vector2 position);

	void Update();


	void Render();

};

#endif