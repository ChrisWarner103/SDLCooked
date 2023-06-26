#ifndef RecipeDecider_H
#define RecipeDecider_H

#include "InputManager.h"
#include "AnimatedTexture.h"
#include "Player.h"
#include "Recipe.h"
#include <time.h>
#include <vector>


using namespace ChrisFramework;

class RecipeDecider {

private:

	static RecipeDecider* sInstance;
	static Player* sPlayer;
	
	InputManager* mInput;

	RecipeDecider* mRecipeDecider;

	float nextRecipeTimer;

	int maxAmountOfRecipes = 5;

public:

	vector<Recipe*> listOfRecipes;
	float currentScore;

public:

	static RecipeDecider* Instance();
	static void Release();
	static void CurrentPlayer(Player* player);

	RecipeDecider();
	~RecipeDecider();

	void ChooseRecipe();
	void CheckRecipe(string type);
	void RemoveRecipe(Recipe* object);

	void Update();

	void Render();
};
#endif // !RecipeDecider_H
